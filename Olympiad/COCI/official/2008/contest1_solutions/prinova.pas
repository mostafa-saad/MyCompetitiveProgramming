program prinova;

var
   i, j, n : longint;
   p : array[1..100] of longint;
   A, B : longint;
   rjesenje : longint;

function racunaj( x : longint ) : longint;
var
   i, ret : longint;
begin
   if x mod 2 = 0 then begin
      racunaj := 0;
   end else begin

      ret := 1000000000;
      for i := 1 to n do
         if abs( x-p[i] ) < ret then
            ret := abs( x-p[i] );

      racunaj := ret;
   end;
end;

procedure probaj( x : longint );
begin
   if (x >= A) and (x <= B) then
      if racunaj(x) > racunaj(rjesenje) then
         rjesenje := x;
end;

begin
   readln( n );

   for i := 1 to n do
      read( p[i] );
   readln;
   readln( A, B );

   rjesenje := 0;

   probaj( A );
   probaj( A + 1 );
   probaj( B );
   probaj( B - 1 );

   for i := 1 to n-1 do
      for j := i+1 to n do begin
         probaj( (p[i]+p[j]) div 2 - 1 );
         probaj( (p[i]+p[j]) div 2 );
         probaj( (p[i]+p[j]) div 2 + 1 );
      end;

   writeln( rjesenje );
end.
