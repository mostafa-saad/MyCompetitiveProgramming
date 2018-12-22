program zapis;

const MAX = 200;

var
   i, j, n : longint;
   s : string;
   otvorena, zatvorena : string;
   memo : array[1..MAX,1..MAX] of int64;
   ret : int64;

function rec( lo, hi : longint ) : int64;
var
   mid, tip : longint;
begin;
   if lo > hi then begin
      rec := 1;
   end else if memo[lo][hi] >= 0 then begin
      rec := memo[lo][hi];
   end else begin
      memo[lo][hi] := 0;

      for mid := lo+1 to hi do
         if (mid-lo) mod 2 = 1 then
            for tip := 1 to 3 do
               if (s[lo] = otvorena[tip]) or (s[lo] = '?') then
                  if (s[mid] = zatvorena[tip]) or (s[mid] = '?') then begin
                     memo[lo][hi] := memo[lo][hi] + rec(lo+1,mid-1) * rec(mid+1,hi);
                     if memo[lo][hi] > 100000 then
                        memo[lo][hi] := 100000 + memo[lo][hi] mod 100000
                  end;

      rec := memo[lo][hi];
   end;
end;

begin
   readln( n );
   readln( s );

   otvorena  := '([{';
   zatvorena := ')]}';

   for i := 1 to n do
      for j := 1 to n do
         memo[i,j] := -1;

   ret := rec( 1, n );

   if ret < 100000 then begin
      writeln( ret );
   end else begin
      ret := ret - 100000;
      if ret < 10000 then write( '0' );
      if ret < 1000 then write( '0' );
      if ret < 100 then write( '0' );
      if ret < 10 then write( '0' );
      writeln( ret );
   end;

end.
