{ BOI 2010, day 1                                                           }
{ Task: PCB                                                                 }
{ Solution: Ahto Truu                                                       }

{ Efficient solution that reduces the problem to finding the longest        }
{ decreasing subsequence and then solves the latter in O(N log W).          }

const
   maxn = 100000;
   maxw = 1000000;
   maxz = 1048576; { lowest power of 2 > maxw }

var
   f : text;
   n : longint;
   xb, xt : array [1..maxn] of longint;
   z : array [1..2*maxz] of longint;
   i, t, k : longint;

{ exchanges the connectors i and j }
procedure exch(i, j : longint);
var t : longint;
begin
   t := xb[i]; xb[i] := xb[j]; xb[j] := t;
   t := xt[i]; xt[i] := xt[j]; xt[j] := t;
end;

{ lowers the connector i to its correct position in the binary heap }
{ where connectors with larger xb values are on top }
procedure down(i, n : longint);
var t : longint;
begin
   while true do begin
      t := i;
      if 2 * i <= n then
         if xb[t] < xb[2 * i] then
            t := 2 * i;
      if 2 * i + 1 <= n then
         if xb[t] < xb[2 * i + 1] then
            t := 2 * i + 1;
      if i = t then
         break;
      exch(i, t);
      i := t;
   end;
end;

{ sets the value of the leaf i in the binary tree in z }
{ then updates the nodes towards the root to be maximums of subtrees }
procedure setval(i, a : longint);
begin
   i := maxz + i; z[i] := a;
   while i > 1 do begin
      if i mod 2 = 0 then begin { sibling is on the right }
         if z[i] > z[i + 1] then
            z[i div 2] := z[i];
      end else begin { sibling is on the left }
         if z[i] > z[i - 1] then
            z[i div 2] := z[i];
      end;
      i := i div 2;
   end;
end;

{ gets the maximal value among the leaves >= i in the binary tree in z }
function getmax(i : longint) : longint;
var a : longint;
begin
   i := maxz + i; a := z[i];
   while i > 1 do begin
      if i mod 2 = 0 then { sibling is on the right }
         if a < z[i + 1] then
            a := z[i + 1];
      i := i div 2;
   end;
   exit(a);
end;

begin
   assign(f, 'pcb.in'); reset(f);
   readln(f, n);
   for i := 1 to n do
      readln(f, xb[i], xt[i]);
   close(f);

   { order by xb using heapsort, of course any O(N log N) sort will do }
   for i := n downto 1 do
      down(i, n);
   for i := n downto 1 do begin
      exch(1, i);
      down(1, i - 1);
   end;

   { find longest decreasing subsequence in xt }
   k := 1;
   for i := 1 to n do begin
      t := getmax(xt[i] + 1) + 1;
      setval(xt[i], t);
      if k < t then
         k := t;
   end;

   assign(f, 'pcb.out'); rewrite(f);
   writeln(f, k);
   close(f);
end.
