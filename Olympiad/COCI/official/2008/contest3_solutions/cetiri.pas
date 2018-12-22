program cetiri;

function min3( a, b, c : longint ) : longint;
begin
   if a < b then
      if a < c then min3 :=a
      else min3 := c
   else
      if b < c then min3 := b
      else min3 := c;
end;

var
   a1, a2, a3, a4, d : longint;

begin
   readln( a1, a2, a3 );

   a4 := min3( a1, a2, a3 );
   d := min3( abs(a1-a2), abs(a1-a3), abs(a2-a3) );

   while (a4 = a1) or (a4 = a2) or (a4 = a3) do a4 := a4 + d;

   writeln( a4 );
end.
