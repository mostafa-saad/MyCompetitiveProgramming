(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Pawel Parys                                   *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program zaladunek;
Uses math;

const max_n = 1000;
const inf = 1000000000000000000;

var
  i, j, k, n, s : longint;
  tab : array[1..max_n] of int64;
  dp : array[0..max_n,0..max_n] of int64;
  { dp[i][j] - i pociągow było w B, j pociągów w A }

begin
  read(n,s);
  for i := 1 to n do
    read(tab[i]);
  for i := 2 to n do
    if tab[i-1]>=tab[i] then
      tab[i] := tab[i-1]+1;
  for i := 1 to n do 
    dp[i,0] := tab[i]+s;
  for i := 1 to n do
    for j := 1 to i do begin
       dp[i,j] := INF;
       for k := 1 to i-j do 
          dp[i,j] := min(dp[i,j], max(dp[i-k,j] + s + k - 1, dp[i,0]));
       for k := 1 to j do
          dp[i,j] := min(dp[i,j], dp[i,j-k] + s + k - 1);
    end;
  writeln(dp[n][n]);
end.
