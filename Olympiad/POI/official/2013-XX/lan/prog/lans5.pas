(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdej pozycji w ciagu sprawdzamy, czy    *
 *                         kolejne d elementow spelnia warunek zadania.  *
 *                         (d = suma wszystkich l[i])                    *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000 * 1000;

var 
  n, m, d : longint;
  wynik : longint;
  l, c, lancuch, ile_w_kolorze, ile_ma_byc : array[1..MAXN] of longint;
  i, j : longint;

function podciag_zgodny : boolean;
var i : longint;
begin
  for i := 1 to n do 
    if ile_w_kolorze[i] <> ile_ma_byc[i] then begin
      podciag_zgodny := false;
      exit
    end;
  podciag_zgodny := true
end;

begin
  read(n, m);
  {Zerowanie zmiennych i tablic }
  wynik := 0;
  d := 0;
  for i := 1 to n do begin
    ile_ma_byc[i] := 0;
    ile_w_kolorze[i] := 0;
  end;
  for i := 1 to m do begin
    read(l[i]);
    d := d + l[i];
    if d > n then begin
      writeln(0);
      exit
    end
  end;
  for i := 1 to m do 
    read(c[i]);
  for i := 1 to m do
    ile_ma_byc[c[i]] := l[i];
  for i := 1 to n do
    read(lancuch[i]);
  
  for i := 1 to n + 1 - d do begin
    for j := 1 to n do
      ile_w_kolorze[j] := 0;
    for j := i to i + d - 1 do
      inc(ile_w_kolorze[lancuch[j]]);
    if podciag_zgodny then 
      inc(wynik)
  end;
  
  writeln(wynik);
end.

