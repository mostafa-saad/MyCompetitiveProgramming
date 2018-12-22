program cetvrta;

var
   x1, y1, x2, y2, x3, y3 : longint;

begin
   readln( x1, y1 );
   readln( x2, y2 );
   readln( x3, y3 );

   if x1 = x2 then write( x3, ' ' );
   if x1 = x3 then write( x2, ' ' );
   if x2 = x3 then write( x1, ' ' );

   if y1 = y2 then writeln( y3 );
   if y1 = y3 then writeln( y2 );
   if y2 = y3 then writeln( y1 );
end.
