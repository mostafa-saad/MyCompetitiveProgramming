program tri;

var
   a, b, c : longint;
begin
   readln( a, b, c );

   if a = b+c then writeln( a, '=', b, '+', c )
   else if a = b-c then writeln( a, '=', b, '-', c )
   else if a = b*c then writeln( a, '=', b, '*', c )
   else if a = b div c then writeln( a, '=', b, '/', c )
   else if a+b = c then writeln( a, '+', b, '=', c )
   else if a-b = c then writeln( a, '-', b, '=', c )
   else if a*b = c then writeln( a, '*', b, '=', c )
   else if a div b = c then writeln( a, '\', b, '=', c );
end.
