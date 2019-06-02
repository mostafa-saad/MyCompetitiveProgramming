(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Bartosz Kostka                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program zaladunek;
Uses math;

const max_n = 1000000;
const inf = 1000000000000000000;

var
  i, n, s, lk, ilepociagow: longint;
  tab : array[1..max_n] of int64;
  dp : array[0..max_n] of int64;

begin
  read(n,s);
  for i := 1 to n do
    read(tab[i]);
  for i := 2 to n do
    if tab[i-1]>=tab[i] then
      tab[i] := tab[i-1]+1;
  dp[0] := 0;
  lk := 0;
  for i := 1 to n do
  begin
    dp[i] := INF;
    ilepociagow := i-lk-1;
    while(lk < i) and (max(dp[lk]+ilepociagow, tab[i]) + ilepociagow + 2*s < dp[i]) do
    begin
      dp[i] := max(dp[lk]+ilepociagow, tab[i]) + ilepociagow + 2*s;
      lk := lk + 1;
      ilepociagow := ilepociagow - 1;
    end;
    lk := lk-1;
  end;
  writeln(dp[n]);
end.
