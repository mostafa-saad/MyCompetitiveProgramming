{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n) time, O(m) space }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxm = 10000;                               { maximal size of the buffer }

type
   buffer = record
      m : longint;                              { actual size of the buffer }
      c : longint;                         { number of elements seen so far }
      f : longint;           { position of the oldest element in the buffer }
      e : longint;                       { number of elements in the buffer }
      a : array [1..maxm] of longint;      { values of the current elements }
      i : array [1..maxm] of longint;     { indices of the current elements }
   end;

{ initializes an empty buffer of given size }
procedure init(var b : buffer; m : longint);
begin
   assert(m <= maxm);
   b.m := m; b.c := 0;
   b.f := 1; b.e := 0;
end;

{ adds a new element to the buffer, possibly pushing out an older one }
procedure push(var b : buffer; x : longint);
var i : longint;
begin
   b.c := b.c + 1;
   { push out the oldest element if it's too old }
   if b.e > 0 then
      if b.i[b.f] = b.c - b.m then begin
         b.f := b.f mod b.m + 1; b.e := b.e - 1;
      end;
   { push out the newer elements that are too small }
   while b.e > 0 do begin
      i := (b.f + b.e - 1) mod b.m;
      if i = 0 then
         i := b.m;
      if b.a[i] > x then
         break;
      b.e := b.e - 1;
   end;
   { append the new element to the list }
   i := (b.f + b.e) mod b.m;
   if i = 0 then
      i := b.m;
   b.a[i] := x; b.i[i] := b.c;
   b.e := b.e + 1;
   assert (b.e <= b.m);
end;

{ computes the maximal value in the buffer }
function max(var b : buffer) : longint;
begin
   assert(b.c >= b.m);
   exit(b.a[b.f]);
end;

var
   ifile, ofile : text;
   n, m, c : longint;
   bmax, bmin : buffer;
   i, k, x : longint;
begin
   assign(ifile, iname); reset(ifile);
   assign(ofile, oname); rewrite(ofile);
   readln(ifile, n, m, c);
   init(bmax, m); init(bmin, m);
   k := 0;
   for i := 1 to n do begin
      read(ifile, x);
      push(bmax, x); push(bmin, -x);
      if i >= m then
         if max(bmax) + max(bmin) <= c then begin
            writeln(ofile, i - m + 1);
            k := k + 1;
         end;
   end;
   if k = 0 then
      writeln(ofile, 'NONE');
   close(ifile);
   close(ofile);
end.
