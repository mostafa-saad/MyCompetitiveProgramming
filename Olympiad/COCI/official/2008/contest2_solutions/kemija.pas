program kemija;

const MAX = 10000;

var
   i, n : longint;
   A : array[0..MAX-1] of longint;
   B : array[0..MAX-1] of longint;

procedure add( x, value : longint );
var
   i : longint;
begin
   i := x;
   repeat
      A[i] := A[i] + value;
      i := (i+3) mod n;
   until i = x;
end;

function init( x : longint ) : longint;
var
   i : longint;
   value : longint;
   min_value : longint;
begin
   value := 0;
   min_value := 0;

   i := x;
   repeat
      A[i] := value;
      if value < min_value then min_value := value;
      i := (i+1) mod n;

      value := value - B[i];
      i := (i+1) mod n;

      value := value + B[i];
      i := (i+1) mod n;
   until i = x;

   init := min_value;
end;

begin
   readln( n );
   for i := 0 to n-1 do readln( B[i] );

   if n mod 3 <> 0 then begin

      init( 0 );
      add( 0, (B[1] - A[0] - A[1] - A[2]) div 3 );

   end else begin

      add( 0, 1-init( 0 ) );
      add( 1, 1-init( 1 ) );
      init( 2 );
      add( 2, B[1] - A[0] - A[1] );

   end;

   for i := 0 to n-1 do writeln( A[i] );
end.
