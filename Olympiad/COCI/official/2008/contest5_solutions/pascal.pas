program pascal;

var
   d, N : longint;
begin
   readln( N );

   d := 1;
   repeat
      d := d + 1;
      if d*d > N then d := N;
   until N mod d = 0;

   writeln( N - N div d );
end.
