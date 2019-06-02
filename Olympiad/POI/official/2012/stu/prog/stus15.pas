(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max(x_i)) * log(n))                    *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Uzycie drzewa przedzialowego oraz kolejki        *
 *                      priorytetowej przy obu fazach rozwiazania        *
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
  for i := 0 to 2*t.size - 1 do
    t.t[i] := 0;
end;

procedure init(var t : tree; s : longint);
begin
  t.size := 1;
  while t.size < s do t.size := t.size shl 1;
  setlength(t.t, 2*t.size);
  clear(t);
end;

procedure _add(var t : tree; p, q, v : longint);
begin
  if p + 1 = q then
  begin
    t.t[p] := t.t[p] + v;
    exit;
  end;
  if p and 1 = 1 then
  begin
    t.t[p] := t.t[p] + v;
    _add(t, p+1, q, v);
    exit;
  end;
  if q and 1 = 1 then
  begin
    t.t[q-1] := t.t[q-1] + v;
    _add(t, p, q-1, v);
    exit;
  end;
  _add(t, p shr 1, q shr 1, v);
end;

procedure add(var t : tree; p, q, v : longint); { [p; q) }
begin
  if q <= p then
    exit;
  _add(t, t.size+p, t.size+q, v);
end;

function query(var t : tree; x : longint) : int64;
begin
  query := 0;
  x := x + t.size;
  while x <> 0 do
  begin
    query := query + t.t[x];
    x := x shr 1;
  end;
end;

var x : array[0..MAXN]of longint; (* grubosc warstwy piasku, dane z wejscia *)
  pom : array[0..MAXN] of longint;
  (* pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia *)
  lewa, prawa : tree;
  n : longint;
  m : int64; (* liczba ruchow lopaty, na ktore Bajtazar ma sile *)

type kr = record
    nr : longint;
    d : longint;
  end;

function make_kr(nr, d : longint) : kr;
begin
  make_kr.nr := nr;
  make_kr.d := d;
end;

type queue_t = record
    tab : array of kr;
    size, max_size : longint;
  end;

(* implementacja kolejki priorytetowej *)
var queue : queue_t;

procedure push(var q : queue_t; el : kr);
  var i : longint;
    tmp : kr;
    tab : array of kr;
begin
  if q.size = q.max_size then
  begin
    setlength(tab, q.size+1);
    for i := 1 to q.size do tab[i] := q.tab[i];
    q.max_size := q.max_size shl 1;
    setlength(q.tab, q.max_size+1);
    for i := 1 to q.size do q.tab[i] := tab[i];
  end;
  q.size := q.size + 1;
  q.tab[q.size] := el;
  i := q.size;
  while (i > 1) and (q.tab[i].d < q.tab[i shr 1].d) do
  begin
    tmp := q.tab[i];
    q.tab[i] := q.tab[i shr 1];
    q.tab[i shr 1] := tmp;
    i := i shr 1;
  end;
end;

procedure heapify(var q : queue_t; x : longint);
  var lar : longint;
    tmp : kr;
begin
  lar := x;
  if (x shl 1 <= q.size) and (q.tab[lar].d > q.tab[x shl 1].d) then
    lar := x shl 1;
  if (x shl 1 < q.size) and (q.tab[lar].d > q.tab[1 + (x shl 1)].d) then
    lar := 1 + (x shl 1);
  if lar <> x then
  begin
    tmp := q.tab[lar];
    q.tab[lar] := q.tab[x];
    q.tab[x] := tmp;
    heapify(q, lar);
  end;
end;

procedure pop(var q : queue_t);
begin
  q.tab[1] := q.tab[q.size];
  q.size := q.size - 1;
  heapify(q, 1);
end;

(* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu *)

function wyrownaj(p : longint) : int64;
  var ruchy : int64;
      i : longint;
begin
  ruchy := 0; (* liczba potrzebnych ruchow *)
  for i := 1 to n do
    push(queue, make_kr(i, pom[i]));
  while queue.size > 0 do
  begin
    i := queue.tab[1].nr;
    pop(queue);
    if (i > 1) and (pom[i] + p < pom[i-1]) then
    begin
      ruchy := ruchy + pom[i-1] - (pom[i] + p);
      pom[i-1] := pom[i] + p;
      push(queue, make_kr(i-1, pom[i-1]));
    end;
    if (i < n) and (pom[i] + p < pom[i+1]) then
    begin
      ruchy := ruchy + pom[i+1] - (pom[i] + p);
      pom[i+1] := pom[i] + p;
      push(queue, make_kr(i+1, pom[i+1]));
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
  queue.size := 0;
  setlength(queue.tab, MAXN+1);
  queue.max_size := MAXN;
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
