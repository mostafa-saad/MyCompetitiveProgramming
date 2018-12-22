program lektira;

var
   s, t, ret : string;
   n, i, j, k : longint;

begin
   readln( s );
   n := length( s );

   ret := '~';

   for i := 1 to n-2 do begin
      for j := i+1 to n-1 do begin
         t := '';

         for k := i downto 1 do t := t + s[k];
         for k := j downto i+1 do t := t + s[k];
         for k := n downto j+1 do t := t + s[k];

         if t < ret then ret := t;
      end;
   end;

   writeln( ret );
end.
