(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n^2 * log(max(x_i)))                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Wyszukiwanie binarne oraz brutalne liczenie      *
 *                      kosztu dokopania sie dla kazdego miejsca         *
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

var   n, h, p, q, r : longint;
    m : int64; (* liczba ruchow lopaty, na ktore Bajtazar ma sile *)
    sumx : int64;
    x : array[0..MAXN] of longint; (* grubosc warstwy piasku, dane z wejscia *)
    pom : array[0..MAXN] of longint;
    (* pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia *)

(* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu *)

function wyrownaj(p : longint) : int64;
  var  ruchy : int64; (* liczba potrzebnych ruchow *)
      i : longint;
begin
  ruchy := 0;
  
  for i:=1 to n-1 do (* wyrownanie terenu od lewej do prawej *)
  begin
    if pom[i] + p < pom[i+1] then
    begin
      ruchy := ruchy + pom[i+1] - (pom[i] + p);
      pom[i+1] := pom[i] + p;
    end;
  end;
  
  for i:=n downto 2 do (* i od prawej do lewej *)
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
  var   i, j : longint;
      ruchy, koszt : int64;
begin
  for i:=1 to n do (* przygotowanie tablicy pomocniczej *)
    pom[i] := x[i];
  
  ruchy := wyrownaj(p);
  
  (* jesli Bajtazar nie ma wystarczajaco sily na wyrownanie terenu,
   * to tym bardziej na dokopanie sie do wody *)
  if m < ruchy then
  begin
    gdzie_kopac := -1;
    exit;
  end;
  
  for i:=1 to n do
  begin
    (* Brutalne liczenie kosztu dokopania sie do wody w punkcie i *)
    koszt := ruchy + pom[i];
    (* Wyrownanie terenu od lewej strony *)
    for j:=i-1 downto 1 do
    begin
      if (pom[j] <= p*(i-j)) or (koszt > m) then
        break
      else
        koszt := koszt + pom[j] - p*(i-j);
    end;
    (* Wyrownanie terenu od prawej strony *)
    for j:=i+1 to n do
    begin
      if (pom[j] <= p*(j-i)) or (koszt > m) then
        break
      else
        koszt := koszt + pom[j] - p*(j-i);
    end;
    if koszt <= m then
    begin
      gdzie_kopac := i;
      exit;
    end;
  end;
  
  gdzie_kopac := -1;
end;

var i : longint;

begin
  read(n, m);
  h := 0; (* najgrubsza warstwa piasku *)
  sumx := 0;
  for i:=1 to n do
  begin
    read(x[i]);
    sumx := sumx + x[i];
    h := max(h, x[i]);
  end;
  if sumx <= m then
  begin
    writeln('1 0');
    halt;
  end;
  
  p := 1;
  q := h;
  while p < q do (* wyszukiwanie binarne po wyniku *)
  begin
    r := (p+q) div 2;
    if gdzie_kopac(r) = -1 then
      p := r + 1
    else
      q := r;
  end;
  writeln(gdzie_kopac(p), ' ', p);
end.
