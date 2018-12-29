program glasnici;

var
   N : longint;
   K : real;
   D : array[1..100000] of real;
   lo, hi, mid : real;
   i, iter : longint;

function ok( T : real ) : boolean;
var
   x : real;
   i : longint;
begin
   x := D[1] + T;
   ok := true;
   for i := 2 to N do begin
     if D[i]-T > x+K then ok := false;

     if x + K < D[i] + T then x := x + K else x := D[i] + T;
   end;
end;

begin
   readln( K );
   readln( N );
   for i := 1 to N do readln( D[i] );

   lo := 0;
   hi := 1000000000;
   for iter := 1 to 100 do begin
      mid := (lo+hi) / 2;

      if ok( mid ) then hi := mid else lo := mid;
   end;
   writeln( lo:3:3 );
end.
