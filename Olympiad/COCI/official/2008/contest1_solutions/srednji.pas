program srednji;

const MAX = 100000;

var
   n, b : longint;
   i, x, delta : longint;
   ret : longint;
   a : array[1..MAX] of longint;
   L, R : array[-MAX..MAX] of longint;

function sgn( x : longint ) : longint;
begin
   if x < 0 then
      sgn := -1
   else if x > 0 then
      sgn := 1
   else
      sgn := 0;
end;

begin
   readln( n, b );

   for i := 1 to n do begin
      read( a[i] );
      if a[i] = b then x := i;
   end;

   for delta := -n to n do begin
      L[delta] := 0;
      R[delta] := 0;
   end;

   delta := 0;
   for i := x downto 1 do begin
      delta := delta + sgn(a[i] - a[x]);
      L[delta] := L[delta] + 1;
   end;

   delta := 0;
   for i := x to n do begin
      delta := delta + sgn(a[i] - a[x]);
      R[delta] := R[delta] + 1;
   end;

   ret := 0;
   for delta := -n to n do
      ret := ret + L[delta] * R[-delta];

   writeln( ret );
end.
