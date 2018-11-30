(*
   Model solution (verification)
   Task: hac
   Complexity: O(n)
   Author: Bartosz Kostka, Jakub Radoszewski
*)

const MAXN = 500007;
var INF : Int64;
  n : LongInt;
  tab : array[0 .. MAXN - 1] of LongInt;
  pref, res : array[0 .. MAXN - 1] of Int64;
  i, op : LongInt;
  Q : array[1 .. 2 * MAXN] of LongInt;
  head, tail : LongInt;
  ans : Int64;

function sum(a, b : LongInt) : Int64;
var
  res : Int64;
begin
  res := 0;
  if a <= b then
    res := pref[b]-pref[a]
  else
    res := pref[n] - pref[a] + pref[b];
  sum := res;
end;

function insegment(x, a, b : LongInt) : Boolean;
begin
  if a < b then
    insegment := (a <= x) and (x < b)
  else
    insegment := not ((b <= x) and (x < a));
end;

function max(a, b : Int64) : Int64;
begin
  if a > b then
    max := a
  else
    max := b;
end;

begin
  INF := 1 shl 30;
  INF := INF * (1 shl 30);
  ReadLn(n);
  op := (n + 1) div 2;
  for i := 1 to n do
    Read(tab[i]);
  pref[0] := 0;
  for i := 1 to n do
    pref[i] := pref[i - 1] + tab[i];
  ans := 0;

  for i := 0 to n - 1 do
    res[i] := sum(i, (i + op) mod n);

  head := 1; tail := 2;
  Q[head] := 0;
  for i := 1 to op - 1 do
  begin
    while (head < tail) and (res[i] < res[Q[tail - 1]]) do
      Dec(tail);
    Q[tail] := i;
    Inc(tail);
  end;
  for i := op to op + n - 1 do
  begin
    ans := max(ans, res[Q[head]]);
    if (i - op) mod n = Q[head] then
      Inc(head);
    while (head < tail) and (res[i mod n] < res[Q[tail - 1]]) do
      Dec(tail);
    Q[tail] := i mod n;
    Inc(tail);
  end;
  WriteLn(ans);
end.
