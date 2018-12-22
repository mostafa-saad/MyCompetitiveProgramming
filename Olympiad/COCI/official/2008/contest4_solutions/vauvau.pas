program vauvau;

function f( x, a, b : longint ) : longint;
begin
   if (x-1) mod (a+b) < a then f := 1 else f := 0;
end;

procedure solve( x, a, b, c, d : longint );
begin
   if f( x, a, b ) + f( x, c, d ) = 0 then writeln( 'none\n' );
   if f( x, a, b ) + f( x, c, d ) = 1 then writeln( 'one\n' );
   if f( x, a, b ) + f( x, c, d ) = 2 then writeln( 'both\n' );
end;

var
   A, B, C, D : longint;
   P, M, G : longint;

begin
   readln( A, B, C, D );
   readln( P, M, G );

   solve( P, A, B, C, D );
   solve( M, A, B, C, D );
   solve( G, A, B, C, D );

end.
