unit bubblesort2;

interface

type
  ArrayOfLongint = array of longint;

function countScans(A, X, V: ArrayOfLongint): ArrayOfLongint;

implementation

uses math;

{ radix sort }
var
  work: array of longint;
  buckets: array [0 .. $10000] of longint;

procedure radixSort(var v: array of longint; l, r: longint; var w: array of longint);
var
  i, j: longint;
begin
  for j := 0 to $ffff do buckets[j] := 0;
  for i := l to r - 1 do begin j := w[v[i]] and $ffff; buckets[j + 1] += 1; end;
  for j := 1 to $ffff do buckets[j] += buckets[j - 1];
  for i := l to r - 1 do begin j := w[v[i]] and $ffff; work[buckets[j]] := v[i]; buckets[j] += 1; end;
  for j := 0 to $ffff do buckets[j] := 0;
  for i := 0 to r - l - 1 do begin j := w[work[i]] shr 16; buckets[j + 1] += 1; end;
  for j := 1 to $ffff do buckets[j] += buckets[j - 1];
  for i := 0 to r - l - 1 do begin j := w[work[i]] shr 16; v[l + buckets[j]] := work[i]; buckets[j] += 1; end;
end;

{ segment tree }
type
  SegmentTree = record
    n: longint;
    min, max, add: array of longint;
  end;

procedure init(var seg: SegmentTree; n_: longint);
var
  a: longint;
begin
  seg.n := 1;
  while seg.n < n_ do seg.n *= 2;
  setlength(seg.min, seg.n * 2);
  setlength(seg.max, seg.n * 2);
  setlength(seg.add, seg.n * 2);
  for a := 1 to seg.n * 2 - 1 do begin
    seg.min[a] := 0;
    seg.max[a] := 0;
    seg.add[a] := 0;
  end;
end;

procedure refresh(var seg: SegmentTree; a: longint);
begin
  seg.min[a] := seg.add[a] + min(seg.min[a * 2], seg.min[a * 2 + 1]);
  seg.max[a] := seg.add[a] + max(seg.max[a * 2], seg.max[a * 2 + 1]);
end;

procedure add(var seg: SegmentTree; a, b: longint; val: longint);
var
  c, d: longint;
begin
  a += seg.n;
  b += seg.n;
  c := a;
  d := b;
  while a <= b do begin
    if c <> a then refresh(seg, c);
    if d <> b then refresh(seg, d);
    if a mod 2 = 1 then begin seg.min[a] += val; seg.max[a] += val; seg.add[a] += val; a += 1; end;
    if b mod 2 = 0 then begin seg.min[b] += val; seg.max[b] += val; seg.add[b] += val; b -= 1; end;
    a := a div 2;
    b := b div 2;
    c := c div 2;
    d := d div 2;
  end;
  while c > 0 do begin
    refresh(seg, c);
    refresh(seg, d);
    c := c div 2;
    d := d div 2;
  end;
end;

{ main }
const
  BIG: longint = 100000000;

function countScans(A, X, V: ArrayOfLongint): ArrayOfLongint;
var
  N, Q: longint;
  keys, vals, poss: array of longint;
  seg: SegmentTree;
  crt: array of longint;
  i, j: longint;
begin
  N := length(A);
  Q := length(X);
  
  setlength(vals, N + Q);
  setlength(keys, N + Q);
  setlength(poss, N + Q);
  for i := 0 to N - 1 do begin
    vals[i] := A[i];
    poss[i] := i;
    keys[i] := i;
  end;
  for j := 0 to Q - 1 do begin
    vals[N + j] := V[j];
    poss[N + j] := X[j];
    keys[N + j] := N + j;
  end;
  setlength(work, N + Q);
  radixSort(keys, 0, N + Q, poss);
  radixSort(keys, 0, N + Q, vals);
  for i := 0 to N + Q - 1 do begin
    vals[keys[i]] := i;
  end;
  
  init(seg, N + Q);
  add(seg, 0, seg.n - 1, -BIG);
  
  setlength(countScans, Q);
  setlength(crt, N);
  for i := 0 to N - 1 do begin
    crt[i] := vals[i];
    add(seg, crt[i], crt[i], BIG + i);
    add(seg, crt[i] + 1, seg.n - 1, -1);
  end;
  for j := 0 to Q - 1 do begin
    i := X[j];
    add(seg, crt[i], crt[i], -(BIG + i));
    add(seg, crt[i] + 1, seg.n - 1, +1);
    crt[i] := vals[N + j];
    add(seg, crt[i], crt[i], BIG + i);
    add(seg, crt[i] + 1, seg.n - 1, -1);
    countScans[j] := seg.max[1];
  end;
end;

end.
