program nered;

const maxn = 100;

var
   n, k, i, j, a, b, sol: longint;
   s, rsum, q: longint;
   grid: array [0..maxn,0..maxn] of longint;

function sum( l, r, c: longint ):longint;
var t: longint;
begin
     sum := 0;
     for t := l to r-1 do sum := sum + grid[t][c];
end;

begin
     read( n, k );
     for i := 1 to k do begin
         read( a, b );
         grid[a-1][b-1] := 1;
     end;

     sol := n * n;
     for i := 0 to n-1 do
         for j := i+1 to n do begin
             if (k mod (j-i)) > 0 then continue; // povrsina pravokutnika mora biti jednaka broju kockica, zato stranica mora biti djeljiva sa k

             s := k div (j-i);
             rsum := 0;

             if s > n then continue;

             for q := 0 to s-1 do rsum := rsum + sum( i, j, q );

             // secemo pravokutnik s lijeva na desno, cijelo vrijeme je gornja stranica redak i, a donja redak j
             // rsum je trenutan broj obuhvacenih kockica
             for q := s to n do begin
                 if sol > k-rsum then sol := k-rsum;

                 // micemo najljeviji stupac pravokutnika i dodajemo novi
                 rsum := rsum - sum( i, j, q-s ) + sum( i, j, q );
             end;

         end;

         writeln( sol );
end.

