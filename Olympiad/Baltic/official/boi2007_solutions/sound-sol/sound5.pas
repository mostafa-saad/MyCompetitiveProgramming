{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n) time, O(n) space }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxn = 1000000;                         { maximal length of the sequence }
   maxm = 10000;                                { maximal length of silence }

{ computes the minimum of two values }
function min(a, b : longint) : longint;
begin
   if a < b then exit(a) else exit(b);
end;

{ computes the maximum of two values }
function max(a, b : longint) : longint;
begin
   if a > b then exit(a) else exit(b);
end;

var
   ifile, ofile : text;
   n, m, c : longint;
   a : array [1..maxn] of longint;                           { the sequence }
   np, ns : array [1..maxn] of longint;         { min-prefix and min-suffix }
   xp, xs : array [1..maxn] of longint;         { max-prefix and max-suffix }
   i, j, k : longint;
begin
   assign(ifile, iname); reset(ifile);
   readln(ifile, n, m, c);
   for i := 1 to n do
      read(ifile, a[i]);
   close(ifile);

   { compute the prefix tables }
   for i := 1 to n do
      if i mod m = 1 then begin
         np[i] := a[i];
         xp[i] := a[i];
      end else begin
         np[i] := min(np[i - 1], a[i]);
         xp[i] := max(xp[i - 1], a[i]);
      end;
   { compute the suffix tables }
   for i := n - n mod m downto 1 do
      if i mod m = 0 then begin
         ns[i] := a[i];
         xs[i] := a[i];
      end else begin
         ns[i] := min(ns[i + 1], a[i]);
         xs[i] := max(xs[i + 1], a[i]);
      end;

   assign(ofile, oname); rewrite(ofile);
   k := 0;
   for i := m to n do begin
      j := i - m + 1;
      if max(xp[i], xs[j]) - min(np[i], ns[j]) <= c then begin
         writeln(ofile, j);
         k := k + 1;
      end;
   end;
   if k = 0 then
      writeln(ofile, 'NONE');
   close(ofile);
end.
