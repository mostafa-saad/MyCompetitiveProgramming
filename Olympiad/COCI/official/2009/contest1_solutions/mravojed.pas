program mravojed;

const MAXN = 100;

var
   n, m : longint;
   l, r, u, d : array[1..MAXN,1..MAXN] of longint;
   grid : array[1..MAXN,1..MAXN] of char;
   size : array[1..MAXN,1..MAXN] of longint;

procedure load;
var
   i, j : longint;
begin
   readln( n, m );
   for i := 1 to n do begin
      for j := 1 to m do read( grid[i,j] );
      readln;
   end;   
end;

procedure init;
var
   i, j : longint;
begin
   for i := 1 to n do begin
      for j := 1 to m do begin
         if grid[i,j] = '.' then continue;

         u[i,j] := 1;
         l[i,j] := 1;
         if i > 1 then u[i,j] := u[i,j] + u[i-1,j];
         if j > 1 then l[i,j] := l[i,j] + l[i,j-1];
      end;
   end;

   for i := n downto 1 do begin
      for j := m downto 1 do begin
         if grid[i,j] = '.' then continue;

         d[i,j] := 1;
         r[i,j] := 1;
         if i < n then d[i,j] := d[i,j] + d[i+1,j];
         if j < m then r[i,j] := r[i,j] + r[i,j+1];
      end;
   end;

   for i := 1 to n do 
      for j := 1 to m do
         size[i,j] := 0;
end;

function min( a, b : longint ) : longint;
begin
   if a < b then min := a else min := b;
end;

procedure solve;
var
   i, j : longint;
   ll, rr, dd, uu : longint;
   kut : longint;
begin
   for i := 1 to n do begin
      for j := 1 to m do begin    
         if grid[i, j] = '.' then continue;
         
         ll := l[i,j];
         rr := r[i,j];
         uu := u[i,j];
         dd := d[i,j];

         kut := 0;
         if ll > 1 then kut := kut + 1;
         if rr > 1 then kut := kut + 1;
         if uu > 1 then kut := kut + 1;
         if dd > 1 then kut := kut + 1;

         if kut < 2 then size[i, j] := 1;
         if kut > 2 then continue;
         
         if (ll > 1) and (uu > 1) then size[ i-min(ll,uu)+1, j-min(ll,uu)+1 ] := min(ll,uu);
         if (ll > 1) and (dd > 1) then size[ i, j-min(ll,dd)+1 ] := min(ll,dd);
         if (rr > 1) and (uu > 1) then size[ i-min(rr,uu)+1, j ] := min(rr,uu);
         if (rr > 1) and (dd > 1) then size[ i, j ] := min(rr,dd);
      end;
   end;
end;

procedure output;
var
   i, j, k : longint;
   ii, jj : longint;
begin
   k := 0;
   for i := 1 to n do begin
      for j := 1 to m do begin
         if size[i,j] > 0 then begin
            writeln( i, ' ', j, ' ', size[ i, j ] );
            ii := i;
            jj := j;
            k := k+1;
         end;
      end;
   end;
   if k = 1 then writeln( ii, ' ', jj, ' ', 1 );
end;

begin
   load;
   init;
   solve;
   output;
end.