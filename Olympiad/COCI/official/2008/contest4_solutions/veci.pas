program veci;

var
   x, y : longint;
   freq : array[0..9] of longint;

function sameDigits( x, y : longint ) : boolean;
var
   i : longint;
begin
   for i := 0 to 9 do freq[i] := 0;

   while x > 0 do begin inc(freq[x mod 10]); x := x div 10; end;
   while y > 0 do begin dec(freq[y mod 10]); y := y div 10; end;

   sameDigits := true;
   for i := 0 to 9 do
      if freq[i] <> 0 then
         sameDigits := false;
end;

begin
   readln( x );

   y := x+1;
   while (y-x < 1000000) and not sameDigits( x, y ) do inc( y );

   if y-x >= 1000000 then writeln( '0' ) else writeln( y );
end.
