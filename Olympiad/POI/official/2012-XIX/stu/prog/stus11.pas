(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max(x_i)) * log(n))                    *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Uzycie drzewa potegowego                         *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

function min(a, b : longint) : longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b : longint) : longint;
begin
  if a > b then
    max := a
  else
    max := b;
end;

type tree = record
    size : longint;
    t : array of int64;
   end;

procedure clear(var t : tree);
  var i : longint;
begin
  for i := 0 to t.size - 1 do
    t.t[i] := 0;
end;

procedure init(var t : tree; s : longint);
begin
  t.size := s + 2;
  setlength(t.t, t.size);
  clear(t);
end;

procedure _add(var t : tree; p, v : longint);
begin
  while p < t.size do
  begin
    t.t[p] := t.t[p] + v;
    p := p + (p and (-p));
  end;
end;

procedure add(var t : tree; p, q, v : longint); { [p; q) }
begin
  if q <= p then
    exit;
  _add(t, p+1, v);
  _add(t, q+1, -v);
end;

function query(var t : tree; x : longint) : int64;
begin
  query := 0;
  x := x + 1;
  while x <> 0 do
  begin
    query := query + t.t[x];
    x := x - (x and (-x));
  end;
end;

var x : array[0..MAXN]of longint; (* grubosc warstwy piasku, dane z wejscia *)
  pom : array[0..MAXN] of longint;
  (* pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia *)
  lewa, prawa : tree;
  n : longint;
  m : int64; (* liczba ruchow lopaty, na ktore Bajtazar ma sile *)

(* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu *)

function wyrownaj(p : longint) : int64;
  var  ruchy : int64;
      i : longint;
begin
  ruchy := 0;
  
  for i:=1 to n-1 do
  begin
    if pom[i] + p < pom[i+1] then
    begin
      ruchy := ruchy + pom[i+1] - (pom[i] + p);
      pom[i+1] := pom[i] + p;
    end;
  end;
  
  for i:=n downto 2 do
  begin
    if pom[i] + p < pom[i-1] then
    begin
      ruchy := ruchy + pom[i-1] - (pom[i] + p);
      pom[i-1] := pom[i] + p;
    end;
  end;
  wyrownaj := ruchy;
end;

(* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. *)

function gdzie_kopac(p : longint) : longint;
  var ruchy : int64;
      i : longint;
begin
  for i := 1 to n do (* przygotowanie tablicy pomocniczej *)
    pom[i] := x[i];

  ruchy := wyrownaj(p);

  (* jesli Bajtazar nie ma wystarczajaco sily na wyrownanie terenu,
   * to tym bardziej na dokopanie sie do wody *)
  if ruchy > m then
  begin
    gdzie_kopac := -1;
    exit;
  end;

  clear(prawa);
  clear(lewa);
  for i := 1 to n do
  begin
    add(lewa, i, min(n+1, i + (pom[i] div p)), p);
    add(lewa, min(n+1, i + (pom[i] div p)), min(n+1, i + (pom[i] div p) + 1), pom[i] mod p);

    add(prawa, max(1, i - (pom[i] div p) + 1), i+1, p);
    add(prawa, max(0, i - (pom[i] div p)), max(0, i - (pom[i] div p) + 1), pom[i] mod p);
  end;

  (* wyliczenie kosztu dokopania sie do wody w punkcie 1 *)
  for i := 1 to n do
  begin
    if pom[i] <= p*(i-1) then
      break
    else
      ruchy := ruchy + (pom[i] - p*(i-1));
  end;
  if ruchy <= m then
  begin
    gdzie_kopac := 1;
    exit;
  end;

  for i := 2 to n do
  begin
    (* Aktualizacja kosztu dokopania sie do wody w miejscu i
     * na podstawie poprzedniego kosztu oraz podanego wzoru *)
    ruchy := ruchy - query(lewa, i-1) + query(prawa, i);
    if ruchy <= m then
    begin
      gdzie_kopac := i;
      exit;
    end;
  end;

  gdzie_kopac := -1;
end;

var
  i, p, q, r, h : longint;
  sumx : int64;

Begin
  h := 0; (* najgrubsza warstwa piasku *)
  sumx := 0;
  readln(n, m);
  init(lewa, n+4);
  init(prawa, n+4);
  for i := 1 to n do
  begin
    read(x[i]);
    sumx := sumx + x[i];
    h := max(h, x[i]);
  end;
  if sumx <= m then
  begin
    writeln('1 0');
    halt(0);
  end;
  p := 1;
  q := h;
  while p < q do (* wyszukiwanie binarne po wyniku *)
  begin
    r := (p+q) div 2;
    if gdzie_kopac(r) <> -1 then
      q := r
    else
      p := r + 1;
  end;
  writeln(gdzie_kopac(p), ' ', p);
End.

