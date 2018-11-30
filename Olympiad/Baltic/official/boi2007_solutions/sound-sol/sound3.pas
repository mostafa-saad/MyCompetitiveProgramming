{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n*c) time, O(m+a) space }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxm = 10000;                               { maximal size of the buffer }
   maxa = 1000000;                                   { maximal sample value }

type
   buffer = record
      m : longint;                              { actual size of the buffer }
      f : longint;           { position of the oldest element in the buffer }
      e : longint;                       { number of elements in the buffer }
      a : array [1..maxm] of longint;                { the current elements }
      c : array [0..maxa] of longint;              { counter for each value }
   end;

{ initializes an empty buffer of given size }
procedure init(var b : buffer; m : longint);
var i : longint;
begin
   assert(m <= maxm);
   b.m := m; b.f := 1; b.e := 0;
   for i := 0 to maxa do
      b.c[i] := 0;
end;

{ adds a new element to the buffer, possibly pushing out an older one }
procedure push(var b : buffer; x : longint);
var y : longint;
begin
   if b.e < b.m then begin
      { the buffer is not yet full, just add the new element }
      b.e := b.e + 1;
      b.a[b.e] := x;
      b.c[x] := b.c[x] + 1;
   end else begin
      { the buffer is full, overwrite the oldest element }
      y := b.a[b.f];
      b.a[b.f] := x;
      b.f := b.f mod b.m + 1;
      b.c[y] := b.c[y] - 1;
      b.c[x] := b.c[x] + 1;
   end;
end;

{ checks if the difference between minimal and maximal is no more than c }
function ok(var b : buffer; x, c : longint) : boolean;
var i, j, k : longint;
begin
   assert(b.e = b.m);
   { minimal j >= 0 such that x + j - c >= 0 }
   if x >= c then j := 0 else j := c - x;
   { establish the base case, counting x + j - c ... x + j }
   k := 0;
   for i := 0 to c do
      k := k + b.c[x + j - i];
   if k = b.m then
      exit(true);
   { now check all other values of j <= c such that x + j <= maxa }
   while (j < c) and (x + j < maxa) do begin
      { compute the new total incrementally from the last one }
      k := k - b.c[x + j - c];
      j := j + 1;
      k := k + b.c[x + j];
      if k = b.m then
         exit(true);
   end;
   exit(false);
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
         if ok(b, x, c) then begin
            writeln(ofile, i - m + 1);
            k := k + 1;
         end;
   end;
   if k = 0 then
      writeln(ofile, 'NONE');
   close(ifile);
   close(ofile);
end.
