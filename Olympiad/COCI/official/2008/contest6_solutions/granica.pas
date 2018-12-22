program granica;

var
   n, i, d, M1, M2, razlika : longint;
   a : array[1..100] of longint;

function ok( M : longint ) : boolean;
var
   i, ostatak : longint;
begin
   ostatak := a[1] mod M;
   ok := true;
   for i := 1 to n do
      if a[i] mod M <> ostatak then
         ok := false;
end;

begin
   readln( n );
   for i := 1 to n do readln( a[i] );

   razlika := abs(a[1]-a[2]);

   d := 1;
   while d*d <= razlika do begin
      if razlika mod d = 0 then begin
         M1 := d;
         M2 := razlika div d;

         if ok( M1 ) and (M1 <> 1) then write( M1, ' ' );
         if ok( M2 ) and (M2 <> M1) then write( M2, ' ' );
      end;
      d := d + 1;
   end;
   writeln;
end.
