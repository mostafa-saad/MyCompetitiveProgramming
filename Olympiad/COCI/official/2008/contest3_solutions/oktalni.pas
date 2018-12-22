program oktalni;

var s : string;
    x : longint;

begin
   readln( s );

   while length(s) mod 3 <> 0 do
      s := '0' + s;

   while s <> '' do begin
      x := 0;
      if s[1] = '1' then x := x + 4;
      if s[2] = '1' then x := x + 2;
      if s[3] = '1' then x := x + 1;
      write( x );

      s := copy( s, 4, length(s)-3 );
   end;

   writeln;
end.
