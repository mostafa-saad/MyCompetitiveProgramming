{ BOI 2010, day 1                                                           }
{ Task: PCB                                                                 }
{ Solution: Ahto Truu                                                       }

{ Slightly inefficient solution that reduces the problem to finding the     }
{ longest decreasing subsequence and then solves the latter in O(N^2).      }

const
   maxn = 100000;

var
   f : text;
   n : longint;
   xb, xt, z : array [1..maxn] of longint;
   i, j, k : longint;

begin
   assign(f, 'pcb.in'); reset(f);
   readln(f, n);
   for i := 1 to n do
      readln(f, xb[i], xt[i]);
   close(f);

   { order by xb }
   for i := 1 to n do
      for j := i + 1 to n do
         if xb[i] > xb[j] then begin
            k := xb[i]; xb[i] := xb[j]; xb[j] := k;
            k := xt[i]; xt[i] := xt[j]; xt[j] := k;
         end;

   { find longest decreasing subsequence in xt }
   k := 1;
   for i := 1 to n do begin
      z[i] := 1;
      for j := 1 to i - 1 do
         if xt[i] < xt[j] then
            if z[i] < z[j] + 1 then
               z[i] := z[j] + 1;
      if k < z[i] then
         k := z[i];
   end;

   assign(f, 'pcb.out'); rewrite(f);
   writeln(f, k);
   close(f);
end.
