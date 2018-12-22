program crne;

var
   n, v, h : longint;

begin
   readln( n );

   h := n div 2;
   v := n - h;

   writeln( (h+1)*(v+1) );
end.
