(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb6.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Algorytm o z³o¿ono¶ci O(sqrt(iloczyn a_i)).    *
 *                        Uznany formalnie za b³êdny, gdy¿ mo¿e nie      *
 *                        mie¶ciæ siê w pamiêci.                         *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;
const MAX_K = 500000;

var
  n, i : LongInt;
  a, t : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;
  lewy, prawy : array[0..MAX_N - 1] of LongWord;
  Lew, Pra : array[0..MAX_K - 1] of QWord;
  l, p : LongInt;
  x : LongWord;

procedure qsort(l, r : Integer); {tablicê a}
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

procedure sprawdzl;
var
  w : LongWord;
  i : LongInt;
begin
  w := 0;
  for i := 0 to l - 1 do
    w := w xor t[i];
  Inc(Lew[w])
end; (* sprawdzl *)

procedure brutalnyl(poz : LongInt);
var
  i : LongWord;
begin
  if poz = l then
    sprawdzl
  else
  for i := 0 to lewy[poz] do
  begin
    t[poz] := i;
    brutalnyl(poz + 1)
  end (* for *)
end; (* brutalnyl *)

procedure sprawdzp;
var
  w : LongWord;
  i : LongInt;
begin
  w := 0;
  for i := 0 to p - 1 do
    w := w xor t[i];
  Inc(Pra[w])
end; (* sprawdzp *)

procedure brutalnyp(poz : LongInt);
var
  i : LongWord;
begin
  if poz = p then
    sprawdzp
  else
  for i := 0 to prawy[poz] do
  begin
    t[poz] := i;
    brutalnyp(poz + 1)
  end (* for *)
end; (* brutalnyp *)

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
  l := 0; p := 0;
  for i := 0 to n - 1 do
    if i mod 2 = 1 then
    begin
      prawy[p] := a[i];
      Inc(p)
    end (* if *)
    else
    begin
      lewy[l] := a[i];
      Inc(l)
    end; (* else *)
  wynik := 0;
{  for i := 0 to MAX_K - 1 do
  begin
    Lew[i] := 0;
    Pra[i] := 0
  end; (* for *)}
  FillChar(Lew, SizeOf(Lew), 0);
  FillChar(Pra, SizeOf(Pra), 0);
  brutalnyl(0);
  brutalnyp(0);
  for i := 0 to MAX_K - 1 do
    Inc(wynik, Lew[i] * Pra[i]);
  pisz(wynik - 1)
end. (* program *)
