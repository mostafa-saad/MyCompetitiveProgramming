(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans3.pas                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *************************************************************************)

const MOD_ = 2005;
const MAXN = 1000;

var 
  N, K, L : longint;
  choose, tab : array[0..MAXN, 0..MAXN] of longint;
  n2, k2, i : longint;

begin
  read(N, K, L);
  if N>MAXN then while true do;
  for n2 := 0 to N do
  begin
    choose[n2][1] := 1;
    for i := 2 to n2 do
      choose[n2][i] := (n2-i+1)*choose[n2][i-1] mod MOD_;
  end;
  for n2 := 0 to N do
    for k2 := 0 to K do
      tab[n2][k2] := 0;
  tab[0][0] := 1;
  for k2 := 1 to K do
    for n2 := k2*L to N do
    begin
      tab[n2][k2] := 0;
      for i := L to n2-(k2-1)*L do
        tab[n2][k2] := (tab[n2][k2]+choose[n2][i]*tab[n2-i][k2-1]) mod MOD_;
    end;
  writeln(tab[N][K]);
end.
