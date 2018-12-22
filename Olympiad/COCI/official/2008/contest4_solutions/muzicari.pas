program muzicari;

const MAXT = 5000;
const MAXN = 500;

var
   T, n : integer;
   dp : array[0..MAXN,0..MAXT] of integer;
   pause : array[1..MAXN] of integer;
   group : array[1..MAXN] of integer;
   i, j : integer;
   sum1, sum2 : integer;

begin
   readln( T, n );

   dp[0,0] := 1;

   for i := 1 to n do begin
      read( pause[i] );

      for j := 0 to T do begin
         if dp[i-1,j] <> 0 then dp[i,j] := 1;
         if j < pause[i] then continue;
         if dp[i-1,j-pause[i]] <> 0 then dp[i,j] := 2;
      end;
   end;

   j := T;
   while dp[n,j] = 0 do dec( j );

   for i := n downto 1 do begin
      group[i] := dp[i,j];
      if group[i] = 2 then j := j - pause[i];
   end;

   sum1 := 0;
   sum2 := 0;

   for i := 1 to n do begin;
      if i > 1 then write( ' ' );

      if group[i] = 1 then begin
         write( sum1 );
         sum1 := sum1 + pause[i];
      end else begin
         write( sum2 );
         sum2 := sum2 + pause[i];
      end;
   end;
   writeln;
end.
