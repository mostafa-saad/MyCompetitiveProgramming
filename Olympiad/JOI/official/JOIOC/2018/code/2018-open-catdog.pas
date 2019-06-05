unit catdog;

interface

procedure initialize(N_: longint; A, B: array of longint);
function cat(v: longint): longint;
function dog(v: longint): longint;
function neightbor(v: longint): longint;

implementation

uses math;

const
  BIG: longint = 100000000;

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

procedure propagate(var seg: SegmentTree; a: longint);
begin
  seg.min[a * 2] += seg.add[a];
  seg.max[a * 2] += seg.add[a];
  seg.add[a * 2] += seg.add[a];
  seg.min[a * 2 + 1] += seg.add[a];
  seg.max[a * 2 + 1] += seg.add[a];
  seg.add[a * 2 + 1] += seg.add[a];
  seg.add[a] := 0;
end;

procedure propagateRecursive(var seg: SegmentTree; a: longint);
begin
  if a > 0 then begin
    propagateRecursive(seg, a div 2);
    if a < seg.n then begin
      propagate(seg, a);
    end;
  end;
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

function getValue(var seg: SegmentTree; a: longint): longint;
begin
  a += seg.n;
  propagateRecursive(seg, a);
  exit(seg.min[a]);
end;

{ min x (>= a) s.t. value at x is not in [p, q] }
function getFirstOutsider(var seg: SegmentTree; a: longint; p, q: longint): longint;
var
  b: longint;
begin
  a += seg.n;
  b := seg.n * 2 - 1;
  propagateRecursive(seg, a);
  while a <= b do begin
    if a mod 2 = 1 then begin
      if ((p <= seg.min[a]) and (seg.max[a] <= q)) then begin
        a += 1;
      end else begin
        while a < seg.n do begin
          p -= seg.add[a];
          q -= seg.add[a];
          a *= 2;
          if ((p <= seg.min[a]) and (seg.max[a] <= q)) then a += 1;
        end;
        exit(a - seg.n);
      end;
    end;
    a := a div 2;
    b := b div 2;
  end;
  exit(seg.n);
end;

{ main }
var
  N: longint;
  deg: array of longint;
  G: array of array of longint;
  par, sz: array of longint;
  L: longint;
  M: array of longint;
  xs, ys: array of longint;
  us: array of array of longint;
  segs: array of SegmentTree;
  colors: array of longint;
  lightCounts: array of array [-1 .. +1] of longint;
  ans: longint;

procedure dfs(u, p: longint);
var
  j, v: longint;
begin
  par[u] := p;
  sz[u] := 1;
  for j := 0 to deg[u] - 1 do begin
    v := G[u][j];
    if v <> p then begin
      dfs(v, u);
      sz[u] += sz[v];
    end;
  end;
  xs[u] := -1;
  for j := 0 to deg[u] - 1 do begin
    v := G[u][j];
    if v <> p then begin
      if sz[u] <= sz[v] * 2 then begin
        xs[u] := xs[v];
        ys[u] := M[xs[u]];
        M[xs[u]] += 1;
      end;
    end;
  end;
  if xs[u] = -1 then begin
    xs[u] := L;
    ys[u] := 0;
    M[L] := 1;
    L += 1;
  end;
end;

{
  s = +1: ++ans for (0, <= -1), --ans for (-1, >= 0)
  s = -1: ++ans for (0, >= +1), --ans for (+1, <= 0)
}
function costIncrease(s, fU, fP: longint): longint;
begin
  if (fU = 0) and (sign(fP) = -s) then exit(+1);
  if (fU = -s) and (sign(fP) <> -s) then exit(-1);
  exit(0);
end;

procedure doIt(u: longint; s: longint);
var
  f0, f1, f2, f3, chainMin, chainMax: longint;
  cont: boolean;
  p, y: longint;
begin
  case s of
    +1: begin chainMin := -1; chainMax :=  0; end;
    -1: begin chainMin :=  0; chainMax := +1; end;
  end;
  while u <> -1 do begin
    y := getFirstOutsider(segs[xs[u]], ys[u], chainMin, chainMax);
    if y >= M[xs[u]] then begin
      y := M[xs[u]] - 1;
      cont := true;
    end else begin
      cont := false;
    end;
    f0 := getValue(segs[xs[u]], ys[u]);
    f2 := getValue(segs[xs[u]], y);
    if ys[u] <= y - 1 then begin
      f1 := getValue(segs[xs[u]], y - 1);
      { cost at us[xs[u]][ys[u] + 1], ..., us[xs[u]][y - 1] }
      ans += s * (f0 - f1);
      { cost at us[xs[u]][y] }
      ans += costIncrease(s, f1, f2);
    end;
    { cost at par[us[xs[u]][y]] }
    p := par[us[xs[u]][y]];
    if p <> -1 then begin
      f3 := getValue(segs[xs[p]], ys[p]);
      ans += costIncrease(s, f2, f3);
    end;
    { light edge counts }
    if (p <> -1) and (xs[u] <> xs[p]) then begin
      lightCounts[p][sign(f2)] -= 1;
      lightCounts[p][sign(f2 + s)] += 1;
    end;
    { add s }
    add(segs[xs[u]], ys[u], y, s);
    { next heavy path }
    if not cont then break;
    u := par[us[xs[u]][M[xs[u]] - 1]];
  end;
end;

function solve(u: longint; colorNew: longint): longint;
var
  f: longint;
  sigF, sigFNew: longint;
  counts: array [-1 .. +1] of longint;
  p: longint;
begin
  f := getValue(segs[xs[u]], ys[u]);
  sigF := sign(f);
  sigFNew := sign(f + (colorNew - colors[u]) * BIG);
  { cost at u }
  counts[+1] := lightCounts[u][+1];
  counts[-1] := lightCounts[u][-1];
  if ys[u] > 0 then begin
    counts[sign(getValue(segs[xs[u]], ys[u] - 1))] += 1;
  end;
  case colors[u] of
    +1: ans -= counts[-1];
    -1: ans -= counts[+1];
     0: ans -= min(counts[+1], counts[-1]);
  end;
  case colorNew of
    +1: ans += counts[-1];
    -1: ans += counts[+1];
     0: ans += min(counts[+1], counts[-1]);
  end;
  { cost at par[u] }
  p := par[u];
  if p <> -1 then begin
    counts[+1] := lightCounts[p][+1];
    counts[-1] := lightCounts[p][-1];
    if ys[p] > 0 then begin
      counts[sign(getValue(segs[xs[p]], ys[p] - 1))] += 1;
    end;
    case colors[p] of
      +1: ans -= counts[-1];
      -1: ans -= counts[+1];
       0: ans -= min(counts[+1], counts[-1]);
    end;
    counts[sigF] -= 1;
    counts[sigFNew] += 1;
    case colors[p] of
      +1: ans += counts[-1];
      -1: ans += counts[+1];
       0: ans += min(counts[+1], counts[-1]);
    end;
  end;
  { light edge counts }
  if (p <> -1) and (xs[u] <> xs[p]) then begin
    lightCounts[p][sigF] -= 1;
    lightCounts[p][sigFNew] += 1;
  end;
  
  add(segs[xs[u]], ys[u], ys[u], (colorNew - colors[u]) * BIG);
  colors[u] := colorNew;
  while sigF < sigFNew do begin doIt(par[u], +1); sigF += 1; end;
  while sigF > sigFNew do begin doIt(par[u], -1); sigF -= 1; end;
  exit(ans);
end;

procedure initialize(N_: longint; A, B: array of longint);
var
  i, u, v, x: longint;
begin
  N := N_;
  setlength(deg, N);
  for u := 0 to N - 1 do begin
    deg[u] := 0;
  end;
  for i := 0 to N - 2 do begin
    u := A[i] - 1;
    v := B[i] - 1;
    deg[u] += 1;
    deg[v] += 1;
  end;
  setlength(G, N);
  for u := 0 to N - 1 do begin
    setlength(G[u], deg[u]);
    deg[u] := 0;
  end;
  for i := 0 to N - 2 do begin
    u := A[i] - 1;
    v := B[i] - 1;
    G[u][deg[u]] := v; deg[u] += 1;
    G[v][deg[v]] := u; deg[v] += 1;
  end;
  
  setlength(par, N);
  setlength(sz, N);
  L := 0;
  setlength(M, N);
  setlength(xs, N);
  setlength(ys, N);
  dfs(0, -1);
  setlength(us, L);
  for x := 0 to L - 1 do begin
    setlength(us[x], M[x]);
  end;
  for u := 0 to N - 1 do begin
    us[xs[u]][ys[u]] := u;
  end;
  setlength(segs, L);
  for x := 0 to L - 1 do begin
    init(segs[x], M[x]);
  end;
  
  setlength(colors, N);
  setlength(lightCounts, N);
  for u := 0 to N - 1 do begin
    colors[u] := 0;
    lightCounts[u][+1] := 0;
    lightCounts[u][-1] := 0;
  end;
  ans := 0;
end;

function cat(v: longint): longint;
begin
  exit(solve(v - 1, +1))
end;

function dog(v: longint): longint;
begin
  exit(solve(v - 1, -1));
end;

function neightbor(v: longint): longint;
begin
  exit(solve(v - 1, 0));
end;

end.
