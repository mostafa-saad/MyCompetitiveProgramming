{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n*a) time, O(a) space, optimized time on average }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxa = 1000000;                                   { maximal sample value }

type
   buffer = record
      m : longint;                              { actual size of the buffer }
      n : longint;                         { number of elements seen so far }
      a : array [0..maxa] of longint;       { when each value was last seen }
      min, max : longint;                      { cached minimum and maximum }
   end;

{ initializes the history }
procedure init(var b : buffer; m : longint);
var i : longint;
begin
   b.m := m; b.n := 0;
   for i := 0 to maxa do
      b.a[i] := 0;
   b.min := maxa; b.max := 0;
end;

{ adds a new element to the history }
procedure push(var b : buffer; x : longint);
begin
   b.n := b.n + 1;
   b.a[x] := b.n;
   if b.min > x then
      b.min := x;
   if b.max < x then
      b.max := x;
end;

{ computes the minimal value among the last m }
function min(var b : buffer) : longint;
var i : longint;
begin
   assert(b.n >= b.m);
   for i := b.min to maxa do
      if b.a[i] > b.n - b.m then begin
         b.min := i;
         exit(i);
      end;
   assert(false);
end;

{ computes the maximal value in the buffer }
function max(var b : buffer) : longint;
var i : longint;
begin
   assert(b.n >= b.m);
   for i := b.max downto 0 do
      if b.a[i] > b.n - b.m then begin
         b.max := i;
         exit(i);
      end;
   assert(false);
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
