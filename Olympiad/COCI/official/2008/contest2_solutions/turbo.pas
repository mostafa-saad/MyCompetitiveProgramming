program turbo;

const MAX = 100000;

var
   i, n : longint;
   mini, maxi : longint;

   numbers : array[1..MAX] of longint;
   position : array[1..MAX] of longint;
   fenwick : array[1..MAX] of longint;

function query( x : longint ) : longint;
var
   ret : longint;
begin
   ret := 0;
   while x > 0 do begin
      ret := ret + fenwick[x];
      x := x - (x and -x);
   end;
   query := ret;
end;

function sum( lo, hi : longint ) : longint;
begin
   sum := query( hi ) - query( lo-1 );
end;

procedure add( x, val : longint );
begin
   while x <= n do begin
      fenwick[x] := fenwick[x] + val;
      x := x + (x and -x);
   end;
end;

begin
   readln( n );
   for i := 1 to n do begin
      readln( numbers[i] );
      position[numbers[i]] := i;
      add( i, 1 );
   end;

   mini := 1;
   maxi := n;

   for i := 1 to n do begin
      if i mod 2 = 1 then begin

         add( position[mini], -1 );
         writeln( sum( 1, position[mini] ) );
         mini := mini + 1;

      end else begin

         add( position[maxi], -1 );
         writeln( sum( position[maxi], n ) );
         maxi := maxi - 1;

      end;
   end;
end.
