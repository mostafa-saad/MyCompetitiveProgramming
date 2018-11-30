{ BOI 2010, day 1                                                           }
{ Task: PCB                                                                 }
{ Solution: Ahto Truu                                                       }

{ Grossly inefficient solution that reduces the problem to graph coloring   }
{ and then solves the latter using iterative deepening.                     }

const
   maxn = 100000;

var
   f : text;
   n : longint;
   xb, xt, z : array [1..maxn] of longint;
   i, k : longint;

{ ok to put connector i in layer t? }
function can_put(i, t : integer) : boolean;
var j : integer;
begin
   for j := 1 to i - 1 do
      if z[j] = t then
         if (xb[j] < xb[i]) <> (xt[j] < xt[i]) then
            exit(false);
   exit(true);
end;

{ can lay connector i and following in k layers? }
function can_lay(i : integer) : boolean;
var j : integer;
begin
   if i > n then
      exit(true);
   for j := 1 to k do
      if can_put(i, j) then begin
         z[i] := j;
         if can_lay(i + 1) then
            exit(true);
      end;
   exit(false);
end;

begin
   assign(f, 'pcb.in'); reset(f);
   readln(f, n);
   for i := 1 to n do
      readln(f, xb[i], xt[i]);
   close(f);

   k := 1;
   while not can_lay(1) do
      k := k + 1;

   assign(f, 'pcb.out'); rewrite(f);
   writeln(f, k);
   close(f);
end.
