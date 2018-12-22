program peg;

var
   a : array[1..7] of string;
   r, c : longint;
   ret : longint;

begin
   for r := 1 to 7 do readln( a[r] );

   ret := 0;
   for r := 1 to 7 do
      for c := 1 to 7 do begin
         if (r+2 <= 7) and (a[r][c] = 'o') and (a[r+1][c] = 'o') and (a[r+2][c] = '.') then ret := ret+1;
         if (r-2 >= 1) and (a[r][c] = 'o') and (a[r-1][c] = 'o') and (a[r-2][c] = '.') then ret := ret+1;
         if (c+2 <= 7) and (a[r][c] = 'o') and (a[r][c+1] = 'o') and (a[r][c+2] = '.') then ret := ret+1;
         if (c-2 >= 1) and (a[r][c] = 'o') and (a[r][c-1] = 'o') and (a[r][c-2] = '.') then ret := ret+1;
      end;

   writeln( ret );
end.
