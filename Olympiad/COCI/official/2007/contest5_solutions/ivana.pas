
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task IVANA
  Programming language Pascal
*)

program ivana;

const MAXN = 100;

var
   n, x, L, i, j, rj : integer;
   f                 : array[1..2*MAXN, 1..2*MAXN] of integer;

function max(a, b : integer):integer;
begin
   if a > b then
      max := a
   else
      max := b;
end;

begin
   readln(n);
   for i:=1 to n do begin
      read(x);
      f[i, i] := x mod 2;
      f[i+n, i+n] := x mod 2;
   end;

   for L:=2 to n do
      for i:=1 to 2*n do begin
         j := i+L-1;
         if j > 2*n then
            break;

         f[i, j] := max( f[i, i] - f[i+1, j], f[j, j] - f[i, j-1] );
      end;

   rj := 0;
   for i:=1 to n do
      if f[i, i] - f[i+1, i+n-1] > 0 then
         rj := rj + 1;
   writeln(rj);
end.
