(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kryb2.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Algorytm o z³o¿ono¶ci O(sqrt(iloczyn a_i)).    *
 *                        Uznany formalnie za b³êdny, gdy¿ mo¿e nie      *
 *                        mie¶ciæ siê w pamiêci.                         *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;
const MAX_K = 4000000;

var
  n, i, j, ile1, ile2 : LongInt;
  a, t : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;
  lewy, prawy : array[0..MAX_N - 1] of LongWord;
  Lew, Pra : array[0..MAX_K - 1] of LongWord;
  l, p, le, pr : LongInt;
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

procedure qsort1(l, r : LongInt); {tablicê Lew}
var
  i, j : LongInt;
  x, y : LongWord;
begin
  i := l; j := r; x := Lew[(i + j) div 2];
  repeat
    while Lew[i] < x do
      Inc(i);
    while Lew[j] > x do
      Dec(j);
    if i <= j then
    begin
      y := Lew[i]; Lew[i] := Lew[j]; Lew[j] := y;
      Inc(i); Dec(j)
    end (* if *)
  until i > j;
  if i < r then
    qsort1(i, r);
  if l < j then
    qsort1(l, j)
end; (* qsort1 *)

procedure qsort2(l, r : LongInt); {tablicê Pra}
var
  i, j : LongInt;
  x, y : LongWord;
begin
  i := l; j := r; x := Pra[(i + j) div 2];
  repeat
    while Pra[i] < x do
      Inc(i);
    while Pra[j] > x do
      Dec(j);
    if i <= j then
    begin
      y := Pra[i]; Pra[i] := Pra[j]; Pra[j] := y;
      Inc(i); Dec(j)
    end (* if *)
  until i > j;
  if i < r then
    qsort2(i, r);
  if l < j then
    qsort2(l, j)
end; (* qsort1 *)


procedure sprawdzl;
var
  w : LongWord;
  i : LongInt;
begin
  w := 0;
  for i := 0 to l - 1 do
    w := w xor t[i];
  Lew[le] := w;
  Inc(le)
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
  Pra[pr] := w;
  Inc(pr)
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
  le := 0; pr := 0;
  brutalnyl(0);
  brutalnyp(0);
  qsort1(0, le - 1);
  qsort2(0, pr - 1);
  i := 0; j := 0;
  while (i < le) and (j < pr) do
  begin
    if Lew[i] <= Pra[j] then
      x := Lew[i]
    else
      x := Pra[j];
    ile1 := 0; ile2 := 0;
    while (i < le) and (Lew[i] = x) do
    begin
      Inc(i);
      Inc(ile1)
    end; (* while *)
    while (j < pr) and (Pra[j] = x) do
    begin
      Inc(j);
      Inc(ile2)
    end; (* while *)
    Inc(wynik, QWord(ile1) * ile2)
  end; (* while *)
  pisz(wynik - 1)
end. (* program *)
