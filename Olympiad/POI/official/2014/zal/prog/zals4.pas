(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Pawel Parys                                   *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program zaladunek;
Uses math;

const max_n = 1000000;
const inf = 1000000000000000000;

var
  i, n, s, k, ilepociagow: longint;
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
  for i := 1 to n do
  begin
    dp[i] := INF;
    for k := 0 to i-1 do begin
      ilepociagow := i-k-1;
      dp[i] := min(dp[i], max(dp[k]+ilepociagow, tab[i]) + ilepociagow + 2*s);
    end;
  end;
  writeln(dp[n]);
end.
