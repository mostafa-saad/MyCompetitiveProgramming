(* Alternative solution of Balloons
 * Author: Mateusz Baranowski
 * Uses binary search to find the maximal radius (uses Extended).
 *)

const MAX = 200000;
const EPS = 0.00000001;

var
  x, r : array[1..MAX] of Extended;
  n, i, l : Longint;
  maxr, xi : Extended;

function square(x : Extended) : Extended;
begin
  square := x * x;
end;

function min(a, b : Extended) : Extended;
begin
  if a + EPS < b then min := a else min := b;
end;

function find_radius : Extended;
var
  a, b, c : Extended;
  i : Longint;
begin
  a := 0.0;
  b := maxr;
  {while b-a > EPS + 0.000001 do}
  for i := 1 to 70 do
  begin
    c := (a + b) / 2;
    if square(x[l] - xi) + square(r[l] - c) + EPS < square(r[l] + c) then
      b := c
    else
      a := c;
  end;
  find_radius := a;
end;

Begin
  readln(n);
  l := 0;
  for i := 1 to n do
  begin
    readln(xi, maxr);
    while l > 0 do
    begin
      maxr := min(maxr, find_radius);
      if r[l] < maxr then l := l - 1 else break;
    end;
    l := l + 1;
    x[l] := xi;
    r[l] := maxr;
    writeln(maxr:0:3);
  end;
End.
