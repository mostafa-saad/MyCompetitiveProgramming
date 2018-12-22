program jabuke;

type
   point = record x, y : longint; end;

function area( A, B, C : point ) : longint;
begin
   area := abs( A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y-B.y) );
end;

var
   A, B, C, P : point;
   i, n, trees : longint;
begin
   readln( A.x, A.y );
   readln( B.x, B.y );
   readln( C.x, C.y );

   readln( n );
   trees := 0;
   for i := 1 to n do begin
      readln( P.x, P.y );

      if area(A,B,P) + area(A,C,P) + area(B,C,P) = area(A,B,C) then
         trees := trees + 1;
   end;

   writeln( area(A,B,C) / 2 : 3 : 1 );
   writeln( trees );
end.
