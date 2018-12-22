program dejavu;

var n, i : longint;
    x, y : array [1..100000] of longint;
    freqX, freqY : array[1..100000] of longint;
    ret : int64;

begin
   readln( n );

   for i := 1 to 100000 do begin
      freqX[i] := 0;
      freqY[i] := 0;
   end;

   for i := 1 to n do begin
      readln( x[i], y[i] );
      freqX[ x[i] ] := freqX[ x[i] ] + 1;
      freqY[ y[i] ] := freqY[ y[i] ] + 1;
   end;

   ret := 0;
   for i := 1 to n do
      ret := ret + int64(freqX[ x[i] ]-1) * int64(freqY[ y[i] ]-1);

   writeln( ret );
end.
