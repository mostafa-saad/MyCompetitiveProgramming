(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb4.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Algorytm o z³o¿ono¶ci O(n*max(a_i)^2).         *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;
const MAX_K = 2000000;

var
  n, i : Integer;
  a : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;
  tab, tab1 : array[0..MAX_K] of QWord;

function min(a, b : LongWord) : LongWord;
begin
  if a < b then
    min := a
  else
    min := b
end; (* min *)

procedure qsort(l, r : Integer);
var
  i, j : Integer;
  x, y : LongWord;
begin
  i := l; j := r; x := a[(i + j) div 2];
  repeat
    while a[i] < x do
      Inc(i);
    while a[j] > x do
      Dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      Inc(i); Dec(j)
    end (* if *)
  until i > j;
  if i < r then
    qsort(i, r);
  if l < j then
    qsort(l, j)
end; (* qsort *)

procedure dynamik;
var
  x, wlk, wlk1, ile, j, k : LongWord;
  i : Integer;
begin
  wlk := 1;
  tab[0] := 1;
  for i := 0 to n - 2 do
  begin
    wlk1 := wlk;
    for j := 0 to wlk - 1 do
      tab1[j] := 0;
    for ile := 0 to a[i] do
      for j := 0 to wlk - 1 do
      begin
        x := j xor ile;
        if x >= wlk1 then
        begin
          for k := wlk1 to x do
            tab1[k] := 0;
          wlk1 := x + 1
        end; (* if *)
        Inc(tab1[x], tab[j])
      end; (* for *)
    wlk := wlk1;
    for j := 0 to wlk - 1 do
      tab[j] := tab1[j]
  end; (* for *)
  for j := 0 to min(wlk - 1, a[n - 1]) do
    Inc(wynik, tab[j])
end; (* dynamik *)

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
  dynamik;
  pisz(wynik - 1)
end. (* program *)
