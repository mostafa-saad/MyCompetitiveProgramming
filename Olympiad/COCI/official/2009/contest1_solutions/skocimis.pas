program skocimis;

var
   a, b, c : longint;

begin
   readln( a, b, c );
   
   if b-a > c-b then
      writeln( b-a-1 )
   else
      writeln( c-b-1 );
end.