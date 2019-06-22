(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys5.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Implementacja rozwi±zania autorskiego,         *
 *                        bez osobnego traktowania dla k<=4.             *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;

var
  n, i : Integer;
  a : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;
  t, dlugosc : array[0..MAX_N - 1] of Integer;

function max(a, b : Integer) : Integer;
begin
  if a < b then
    max := b
  else
    max := a
end; (* max *)

function max_dlug : Integer; {liczy max d³ugo¶æ binarn± liczb a_i}
var
  maxlen, i, akt : Integer;
  m : LongWord;
begin
  maxlen := 0;
  for i := 0 to n - 1 do
  begin
    m := a[i]; akt := 0;
    while m > 0 do
    begin
      Inc(akt);
      m := m div 2
    end; (* while *)
    maxlen := max(maxlen, akt);
    dlugosc[i] := akt
  end; (* for *)
  max_dlug := maxlen
end; (* max_dlug *)

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

procedure generuj(dlug : Integer);
var
  k, i, poz, ile : Integer;
  pom, tmp : QWord;
begin
  qsort(0, n - 1);
  max_dlug;
  if dlug = 0 then
  begin
    Inc(wynik);
    exit
  end; (* if *)
  k := n - 1;
  while (k >= 0) and (dlugosc[k] >= dlug) do
    Dec(k);
  Inc(k);
  if k = n then (* nie ma nic do roboty na tym bicie *)
  begin
    generuj(dlug - 1);
    exit
  end; (* if *)
  for i := k to n - 1 do {na pocz±tku zbiór pusty}
    t[i] := 0;
  (* przechodzimy przez wszystkie podzbiory *)
  pom := 1;
  for i := 0 to k - 1 do
    pom := pom * (a[i] + 1);
  
  poz := n - 1;
  while true do
  begin
    ile := 0;
    for i := k to n - 1 do
      Inc(ile, t[i]);
    if (ile mod 2 = 0) and (ile < n - k) then {niepe³ny podzbiór parzystej mocy}
    begin
      for poz := k to n - 1 do
        if t[poz] = 0 then
          break;
      tmp := pom;
      for i := k to n - 1 do
        if i <> poz then
        begin
          if t[i] > 0 then
            tmp := tmp * (a[i] - (LongWord(1) shl (dlug - 1)) + 1)
          else
            tmp := tmp * (LongWord(1) shl (dlug - 1))
        end; (* if *)
      Inc(wynik, tmp)
    end; (* if *)
    if (ile = n - k) and (ile mod 2 = 0) then
    begin
      for i := k to n - 1 do
        a[i] := a[i] xor (LongWord(1) shl (dlug - 1));
      generuj(dlug - 1);
      exit
    end; (* if *)
    Inc(t[n - 1]);
    poz := n - 1;
    while (poz >= k) and (t[poz] = 2) do
    begin
      t[poz] := 0;
      Dec(poz);
      if poz >= k then
        Inc(t[poz])
    end; (* while *)
    if poz < k then
      break
  end (* while *)
end; (* generuj *)

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
  wynik := 0;
  generuj(max_dlug);
  pisz(wynik - QWord(1))
end. (* program *)
