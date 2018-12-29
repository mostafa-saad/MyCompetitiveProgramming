(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O((n+sum(x_i)) * log(max(x_i)))                  *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;
const MAXX = 1000000;
const INF = 1000000001;

function min(a, b : longint) : longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b : longint) : longint;
begin
  if a > b then
    max := a
  else
    max := b;
end;

var  front, back, Smintop, Sminbot : longint;
    sum : int64;
    T : array[0..MAXN] of int64;
    Smin : array[0..MAXN] of int64;
procedure clear;
begin
  front := 0;
  back := 0;
  Smintop := 0;
  Sminbot := 0;
  sum := 0;
end;
procedure push(v : int64);
begin
  sum += v;
  T[back] := v;
  inc(back);
  while (Smintop <> Sminbot) and (Smin[Smintop-1] > v) do
  begin
    dec(Smintop);
  end;
  Smin[Smintop] := v;
  inc(Smintop);
end;
function pop : int64;
begin
  sum -= T[front];
  if Smin[Sminbot] = T[front] then
    inc(Sminbot);
  pop := T[front];
  inc(front);
end;
function getMin : int64;
begin
  getMin := Smin[Sminbot];
end;

var   n, h, p, q, r : longint;
    m, sumx : int64;
    x : array[0..MAXN] of longint;
    dp : array[0..MAXX] of longint;
    lewa : array[0..MAXN+1] of longint;
    prawa : array[0..MAXN+1] of longint;

procedure kop(p : longint; odlewej : boolean);
var  i, j : longint;
begin
  for i:=0 to x[1] do
    dp[i] := x[1]-i;
  if odlewej then
    lewa[1] := dp[0]
  else
    prawa[1] := dp[0];
  for i:=2 to n do
  begin
    clear();
    for j:=0 to min(p, x[i-1]) do
      push(dp[j]);
    for j:=0 to min(x[i], x[i-1]+p) do
    begin
      dp[j] := x[i]-j + getMin();
      if j+p+1 <= x[i-1] then
        push(dp[j+p+1]);
      if j >= p then
        pop();
    end;
    for j:=x[i-1]+p+1 to x[i] do
      dp[j] := INF;
    if odlewej then
      lewa[i] := dp[0]
    else
      prawa[i] := dp[0];
  end;
end;

function gdzie_kopac(p : longint) : longint;
  var   i, j, tmp : longint;
begin
  kop(p, true);
  i := 1;
  j := n;
  while i < j do
  begin
    tmp := x[i];
    x[i] := x[j];
    x[j] := tmp;
    inc(i);
    dec(j);
  end;
  kop(p, false);
  i := 1;
  j := n;
  while i < j do
  begin
    tmp := x[i];
    x[i] := x[j];
    x[j] := tmp;
    inc(i);
    dec(j);
  end;
  for i:=1 to n do
  begin
    if lewa[i] + prawa[n-i+1] - x[i] <= m then
    begin
      gdzie_kopac := i;
      exit;
    end;
  end;
  gdzie_kopac := -1;
end;

var i : longint;

begin
  read(n, m);
  h := 0;
  sumx := 0;
  for i:=1 to n do
  begin
    read(x[i]);
    sumx := sumx + x[i];
    h := max(h, x[i]);
  end;
  if sumx <= m then
  begin
    writeln('1 0');
    halt;
  end;
  
  p := 1;
  q := h;
  while p < q do
  begin
    r := (p+q) div 2;
    if gdzie_kopac(r) = -1 then
      p := r + 1
    else
      q := r;
  end;
  writeln(gdzie_kopac(p), ' ', p);
end.
