{ BOI 2007 }
{ Task: SOUND }
{ Solution: Ahto Truu }
{ O(n*m) time, O(m) space, optimized time on average }

const
   iname = 'sound.in';                             { name of the input file }
   oname = 'sound.out';                           { name of the output file }
   maxm = 10000;                               { maximal size of the buffer }

type
   buffer = record
      m : longint;                              { actual size of the buffer }
      f : longint;           { position of the oldest element in the buffer }
      e : longint;                       { number of elements in the buffer }
      a : array [1..maxm] of longint;                { the current elements }
      min, max : longint;                 { the current minimum and maximum }
   end;

{ initializes an empty buffer of given size }
procedure init(var b : buffer; m : longint);
begin
   assert(m <= maxm);
   b.m := m; b.f := 1; b.e := 0;
   b.min := MAXLONGINT; b.max := -MAXLONGINT;
end;

{ adds a new element to the buffer, possibly pushing out an older one }
procedure push(var b : buffer; x : longint);
var y, i : longint;
begin
   if b.e < b.m then begin
      { the buffer is not yet full, just add the new element }
      b.e := b.e + 1;
      b.a[b.e] := x;
      { update the current minimum and maximum if necessary }
      if b.min > x then
         b.min := x;
      if b.max < x then
         b.max := x;
   end else begin
      { the buffer is full, overwrite the oldest element }
      y := b.a[b.f];
      b.a[b.f] := x;
      b.f := b.f mod b.m + 1;
      { update the current minimum and maximum if necessary }
      if b.min > x then
         b.min := x
      else if b.min = y then begin
         { do full scan only if we just pushed out the old minimum }
         b.min := MAXLONGINT;
         for i := 1 to b.m do
            if b.min > b.a[i] then
               b.min := b.a[i];
      end;
      if b.max < x then
         b.max := x
      else if b.max = y then begin
         { do full scan only if we just pushed out the old maximum }
         b.max := -MAXLONGINT;
         for i := 1 to b.m do
            if b.max < b.a[i] then
               b.max := b.a[i];
      end;
   end;
end;

{ computes the minimal value in the window }
function min(var b : buffer) : longint;
begin
   assert(b.e = b.m);
   exit(b.min);
end;

{ computes the maximal value in the window }
function max(var b : buffer) : longint;
begin
   assert(b.e = b.m);
   exit(b.max);
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
