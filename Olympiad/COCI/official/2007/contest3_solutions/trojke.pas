
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task TROJKE
  Programming language Pascal
*/

program trojke;

var
   a : array [1..100,1..101] of char;
   n, m : integer;
   i, j, k : integer;
   x, y : array [1..26] of integer;
   rjesenje : integer;

begin
   readln( n );

   m := 0;
   for i := 1 to n do begin
      readln( a[i] );
      for j := 1 to n do begin
         if a[i,j] = '.' then continue;
         m := m + 1;
         x[m] := i;
         y[m] := j;
      end;
   end;

   rjesenje := 0;
   for i := 1 to m do
      for j := i+1 to m do
         for k := j+1 to m do
            if x[i]*(y[j]-y[k]) + x[j]*(y[k]-y[i]) + x[k]*(y[i]-y[j]) = 0 then
               rjesenje := rjesenje + 1;
   writeln( rjesenje );
end.
