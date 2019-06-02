(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                kry0.pas                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;

type Nowy = record
  first : LongWord;
  second : Integer
end; (* nowy *)

var
  n, i : Integer;
  a : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;
  t, dlugosc : array[0..MAX_N - 1] of Integer;
  dwum : array[0..MAX_N, 0..MAX_N] of QWord;
  nowe : array[0..MAX_N - 1] of Nowy;
  ilen : Integer;


function max(a, b : Integer) : Integer;
begin
  if a < b then
    max := b
  else
    max := a
end; (* max *)

procedure licz_dwum; {liczy wspó³czynniki dwumianowe}
var
  i, j : Integer;
begin
  dwum[0, 0] := 1;
  for i := 1 to n do
  begin  
    dwum[i, 0] := 1; dwum[i, i] := 1;
    for j := 1 to i - 1 do
      dwum[i, j] := dwum[i - 1, j - 1] + dwum[i - 1, j];
  end (* for *)
end; (* licz_dwum *)

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

function max_dlug : Integer; {liczy max d³ugo¶æ binarn± liczb a_i}
var
  maxlen, i, akt : Integer;
  m : LongWord;
begin
  maxlen := 0;
  for i := 0 to n - 1 do
  begin
    m := a[i];
    akt := 0;
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


procedure zrob_nowe; {grupuje te same liczby}
var
  i, i0 : Integer;
begin
  i := 0;
  ilen := 0;
  while i < n do
  begin
    i0 := i;
    while (i0 < n) and (a[i0] = a[i]) do
      Inc(i0);
    nowe[ilen].first := a[i];
    nowe[ilen].second := i0 - i;
    Inc(ilen);
    i := i0
  end (* while *)
end; (* zrob_nowe *)

procedure max_dlug1; {liczy max d³ugo¶æ binarn± liczb nowe_i}
var
  i, akt : Integer;
  m : LongWord;
begin
  for i := 0 to ilen - 1 do
  begin
    m := nowe[i].first;
    akt := 0;
    while m > 0 do
    begin
      Inc(akt);
      m := m div 2
    end; (* while *)
    dlugosc[i] := akt
  end (* for *)
end; (* max_dlug1 *)


procedure generuj(dlug : Integer); {g³ówna procedura}
var
  k, i, j, poz, ile, suma : Integer;
  pom, tmp : QWord;
  tymcz : Integer;
begin
  qsort(0, n - 1);
  zrob_nowe;
  max_dlug1;
  if dlug = 0 then
  begin
    Inc(wynik);
    exit
  end; (* if *)
  k := ilen - 1;
  while (k >= 0) and (dlugosc[k] >= dlug) do
    Dec(k);
  Inc(k);
  if k = ilen then (* nie ma nic do roboty na tym bicie *)
  begin
    generuj(dlug - 1);
    exit
  end; (* if *)
  for i := k to ilen - 1 do {na pocz±tku zbiór pusty}
    t[i] := 0;
  pom := 1;
  for i := 0 to k - 1 do
    for j := 1 to nowe[i].second do
      pom := pom * (nowe[i].first + 1);
  
  poz := ilen - 1;
  suma := 0;
  for i := k to ilen - 1 do
    Inc(suma, nowe[i].second);

  (* przechodzimy przez wszystkie podzbiory *)
  while true do
  begin
    ile := 0;
    for i := k to ilen - 1 do
      Inc(ile, t[i]);
    if (ile mod 2 = 0) and (ile < suma) then {niepe³ny podzbiór parzystej mocy}
    begin
      for poz := k to ilen - 1 do
        if t[poz] < nowe[poz].second then
          break;
      tmp := pom;
      for i := k to ilen - 1 do
      begin
        if i = poz then
          tymcz := 1
        else
          tymcz := 0;
        for j := 1 to t[i] do
          tmp := tmp * (nowe[i].first - (LongWord(1) shl (dlug - 1)) + 1);
        for j := 1 to nowe[i].second - t[i] - tymcz do
          tmp := tmp * (LongWord(1) shl (dlug - 1));
        tmp := tmp * dwum[nowe[i].second][t[i]]
      end; (* for *)
      Inc(wynik, tmp)
    end; (* if *)
    if (ile = suma) and (ile mod 2 = 0) then
    begin
      for i := 0 to n - 1 do
        a[i] := a[i] and LongWord((QWord(1) shl dlug) - 1 - (LongWord(1) shl (dlug - 1)));
      generuj(dlug - 1);
      exit
    end; (* if *)

    (* Zwiêkszamy podzbiór *)
    Inc(t[ilen - 1]);
    poz := ilen - 1;
    while (poz >= k) and (t[poz] > nowe[poz].second) do
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
  licz_dwum;
  generuj(max_dlug);
  pisz(wynik - 1)
end. (* program *)
