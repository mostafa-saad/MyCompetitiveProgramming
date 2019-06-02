(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys3.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Najmniejsze n-1 liczb a_i wybiera dowolnie,    *
 *                        ostatnia jest wyznaczona jednoznacznie.        *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;

var
  n, i : Integer;
  a, t : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;

procedure qsort(l, r : Integer);
var
  i, j : Integer;
  x, y : LongWord;
begin
  i := l; j := r; x := t[(i + j) div 2];
  repeat
    while t[i] < x do
      Inc(i);
    while t[j]>x do
      Dec(j);
    if i <= j then
    begin
      y := t[i]; t[i] := t[j]; t[j] := y;
      Inc(i); Dec(j)
    end (* if *)
  until i > j;
  if i < r then
    qsort(i, r);
  if l < j then
    qsort(l, j)
end; (* qsort *)

procedure sprawdz;
var
  i : Integer;
  w : LongWord;
begin
  w := 0;
  for i := 0 to n - 2 do
    w := w xor t[i];
  if w <= a[n - 1] then
    Inc(wynik)
end; (* sprawdz *)

procedure brutalny(poz : Integer);
var
  i : LongWord;
begin
  if poz = n - 1 then
    sprawdz
  else
  for i := 0 to a[poz] do
  begin
    t[poz] := i;
    brutalny(poz + 1)
  end (* for *)
end; (* brutalny *)

procedure pisz(x : QWord);
var
  s : String;
  i : Integer;
begin
  s := '';
  while x > QWord(0) do
  begin
    s := s + Chr(Byte(x mod QWord(10)) + Ord('0'));
    x := x div QWord(10)
  end; (* while *)
  for i := length(s) downto 1 do
    Write(s[i]);
  WriteLn
end; (* pisz *)

begin
  ReadLn(n);
  for i := 0 to n - 1 do
    Read(a[i]);
  qsort(0, n - 1);
  wynik := 0;
  brutalny(0);
  pisz(wynik - 1)
end. (* program *)
