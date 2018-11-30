{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n*log(a)) time, O(a) space }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxa = 1000000;                                   { maximal sample value }
   maxz = 1048576;                               { lowest power of 2 > maxa }

type
   buffer = record
      m : longint;                              { actual size of the buffer }
      n : longint;                         { number of elements seen so far }
      a : array [1..2*maxz] of longint; { max-heap of the last-seen indices }
   end;

{ initializes the history }
procedure init(var b : buffer; m : longint);
var i : longint;
begin
   b.m := m; b.n := 0;
   for i := 1 to 2 * maxz do
      b.a[i] := 0;
end;

{ adds a new element to the history }
procedure push(var b : buffer; x : longint);
begin
   b.n := b.n + 1;
   x := maxz + x;
   while x > 0 do begin
      b.a[x] := b.n;
      x := x div 2;
   end;
end;

{ computes the minimal value among the last m }
function min(var b : buffer) : longint;
var i : longint;
begin
   assert(b.n >= b.m);
   i := 1;
   while i < maxz do
      if b.a[2 * i] > b.n - b.m then
         i := 2 * i
      else
         i := 2 * i + 1;
   exit(i - maxz);
end;

{ computes the maximal value in the buffer }
function max(var b : buffer) : longint;
var i : longint;
begin
   assert(b.n >= b.m);
   i := 1;
   while i < maxz do
      if b.a[2 * i + 1] > b.n - b.m then
         i := 2 * i + 1
      else
         i := 2 * i;
   exit(i - maxz);
end;

var
   ifile, ofile : text;
   n, m, c : longint;
   b : buffer;
   i, k, x : longint;
begin
   assign(ifile, iname); reset(ifile);
   assign(ofile, oname); rewrite(ofile);
   readln(ifile, n, m, c);
   init(b, m);
   k := 0;
   for i := 1 to n do begin
      read(ifile, x);
      push(b, x);
      if i >= m then
         if max(b) - min(b) <= c then begin
            writeln(ofile, i - m + 1);
            k := k + 1;
         end;
   end;
   if k = 0 then
      writeln(ofile, 'NONE');
   close(ifile);
   close(ofile);
end.
