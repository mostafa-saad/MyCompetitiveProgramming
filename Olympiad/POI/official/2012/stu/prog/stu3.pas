(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max(x_i)))                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

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
function getSize : longint;
begin
  getSize := back - front;
end;
function getSum : int64;
begin
  getSum := sum;
end;

var   n, h, p, q, r : longint;
    m : int64;
    x : array[0..MAXN] of longint;
    pom : array[0..MAXN] of longint;
    lewa : array[0..MAXN+1] of int64;
    prawa : array[0..MAXN+1] of int64;

procedure kop(p : longint; odlewej : boolean);
var  ruchy, b : int64;
    i : longint;
begin
  clear();
  ruchy := 0;
  b := 0;
  for i:=1 to n do
  begin
    if (i <> 1) and (pom[i-1] + p < pom[i]) then
    begin
      ruchy += pom[i] - (pom[i-1] + p);
      pom[i] := pom[i-1] + p;
    end;
    push(b + pom[i]);
    while getMin() < b do
    begin
      ruchy -= getMin();
      ruchy += pop();
    end;
    if odlewej then
      lewa[i] := ruchy - b*getSize() + getSum()
    else
      prawa[i] := ruchy - b*getSize() + getSum();
    b += p;
  end;
end;

function gdzie_kopac(p : longint) : longint;
  var   i : longint;
begin
  for i:=1 to n do
    pom[i] := x[i];
  kop(p, true);
  for i:=1 to n do
    pom[i] := x[n-i+1];
  kop(p, false);
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
  for i:=1 to n do
  begin
    read(x[i]);
    h := max(h, x[i]);
  end;
  
  p := 0;
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
