
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task DEBUG
  Programming language Pascal
*)

program debug;

const
   dr : array[0..3] of integer = ( 1, 0, -1, 0 );
   dc : array[0..3] of integer = ( 0, 1, 0, -1 );

var
   n, m       : integer;
   a          : array[0..299, 0..300] of char;
   mask       : array[0..301, 0..301, 0..3] of int64; (* pamti 64 bita od pozicije (r,s) u smjeru d *)
   r, c, x    : integer;
   max_odavde : integer;
   size, ret  : integer;

procedure init;
(* inicijalizira mask[r][c][d] *)
var r, c, d, rr, cc : integer;
begin
   for r:=n-1 downto 0 do
      for c:=m-1 downto 0 do
         for d:=0 to 1 do begin
            rr := r+dr[d];
            cc := c+dc[d];

            if ( rr >= 0 ) and ( rr < n ) and ( cc >= 0 ) and ( cc < m ) then
               mask[r, c, d] := mask[rr, cc, d] shl 1
            else
               mask[r, c, d] := 0;

            if a[r, c] = '1' then
               mask[r, c, d] := mask[r, c, d] or 1;
         end;

   for r:=0 to n-1 do
      for c:=0 to m-1 do
         for d:=2 to 3 do begin
            rr := r+dr[d];
            cc := c+dc[d];

            if ( rr >= 0 ) and ( rr < n ) and ( cc >= 0 ) and ( cc < m ) then
               mask[r, c, d] := mask[rr, cc, d] shl 1
            else
               mask[r, c, d] := 0;

            if a[r, c] = '1' then
               mask[r, c, d] := mask[r, c, d] or 1;
         end;
end;

function check(r, c, size : integer): boolean;
var
   d, r1, c1, r2, c2, s : integer;
   x, y                 : int64;
begin
   if ( r < 0 ) or ( r+size >= n ) or
      ( c < 0 ) or ( c+size >= m ) then
   begin
      check := false;
      exit;
   end;

   for d:=0 to 1 do begin
      r1 := r; r2 := r+size;
      c1 := c; c2 := c+size;

      s := size+1;
      while s > 0 do begin
         x := mask[r1, c1, d];
         y := mask[r2, c2, d+2];

         if s >= 64 then begin
            if x xor y <> 0 then begin
               check := false;
               exit;
            end;
         end else begin
            if ((x xor y) and ((int64(1) shl s)-1)) <> 0 then begin
               check := false;
               exit;
            end;
         end;

         r1 := r1 + 64*dr[d];
         c1 := c1 + 64*dc[d];
         r2 := r2 - 64*dr[d];
         c2 := c2 - 64*dc[d];
         s := s - 64;
      end;
   end;

   check := true;
end;

function min(a, b : integer): integer;
begin
   if a < b then
      min := a
   else
      min := b;
end;

begin
   readln(n, m);
   for r:=0 to n-1 do begin
      for c:=0 to m-1 do
         read( a[r, c] );
      readln;
   end;

   init;
   ret := 0;

   for r:=0 to n-1 do
      for c:=0 to m-1 do
         for x:=0 to 1 do begin
            max_odavde := min( min( r+1, c+1 ), min( n-r, m-c ) );
            if 2*max_odavde+x <= ret then begin
               (* Nema smisla pokusavati se siriti iz ovog polja jer je
                  najveci moguci kvadrat nije vec vec nadenog ubojice *)
               continue;
            end;

            size := x;
            while ( check( r - size div 2, c - size div 2, size ) ) do
               size := size + 2;

            if size-1 > ret then
               ret := size-1;
         end;

   if ret > 1 then
      writeln(ret)
   else
      writeln(-1);
end.
