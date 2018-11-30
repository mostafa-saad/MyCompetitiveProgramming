{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n*log(m)) time, O(m) space }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxm = 10000;                               { maximal size of the buffer }
   maxz = 16384;                                { lowest power of 2 >= maxm }

type
   buffer = record
      m : longint;                              { actual size of the buffer }
      z : longint;                                 { lowest power of 2 >= m }
      f : longint;           { position of the oldest element in the buffer }
      e : longint;                       { number of elements in the buffer }
      min, max : array [1..2*maxz] of longint;  { the min-heap and max-heap }
   end;

{ initializes an empty buffer of given size }
procedure init(var b : buffer; m : longint);
var i : longint;
begin
   assert(m <= maxm);
   b.m := m; b.z := 1;
   while b.z < b.m do
      b.z := 2 * b.z;
   b.f := 1; b.e := 0;
   for i := 1 to 2 * b.z do begin
      b.min[i] := MAXLONGINT;
      b.max[i] := -MAXLONGINT;
   end;
end;

{ adds a new element to the buffer, possibly pushing out an older one }
procedure push(var b : buffer; x : longint);
var i, j : longint;
begin
   if b.e < b.m then begin
      { the buffer is not yet full, just add the new element }
      b.e := b.e + 1; i := b.e;
   end else begin
      { the buffer is full, overwrite the oldest element }
      i := b.f; b.f := b.f mod b.m + 1;
   end;
   { update the min-heap up to the root }
   j := b.z + i - 1; b.min[j] := x;
   while j > 1 do begin
      j := j div 2; b.min[j] := MAXLONGINT;
      if b.min[j] > b.min[2 * j] then
         b.min[j] := b.min[2 * j];
      if b.min[j] > b.min[2 * j + 1] then
         b.min[j] := b.min[2 * j + 1];
   end;
   { update the max-heap up to the root }
   j := b.z + i - 1; b.max[j] := x;
   while j > 1 do begin
      j := j div 2; b.max[j] := -MAXLONGINT;
      if b.max[j] < b.max[2 * j] then
         b.max[j] := b.max[2 * j];
      if b.max[j] < b.max[2 * j + 1] then
         b.max[j] := b.max[2 * j + 1];
   end;
end;

{ computes the minimal value in the window }
function min(var b : buffer) : longint;
begin
   assert(b.e = b.m);
   exit(b.min[1]);
end;

{ computes the maximal value in the window }
function max(var b : buffer) : longint;
begin
   assert(b.e = b.m);
   exit(b.max[1]);
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
