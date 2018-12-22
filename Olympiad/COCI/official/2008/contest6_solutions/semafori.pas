program semafori;

var
   N, D : longint;
   i, x, t : longint;
   L, C, Z : longint;

begin
   readln( N, D );

   x := 0;
   t := 0;
   for i := 1 to N do begin
      readln( L, C, Z );
      t := t + L-x;
      x := L;
      while t mod (C+Z) < C do t := t + 1;
   end;
   t := t + D-x;
   x := D;

   writeln( t );
end.
