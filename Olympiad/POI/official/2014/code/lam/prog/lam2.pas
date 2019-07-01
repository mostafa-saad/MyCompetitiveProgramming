(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n log^2 n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program Lampy;

uses Math;

const MAXN = 200000;

var
  n, i, temp32 : LongInt;
  x1, y1, x2, y2, temp64, a, b : Int64;
  x, y : array[0..MAXN] of Int64;
  k, p, res, tree, merge : array[0..MAXN] of LongInt;


procedure Distort;
var
  m, d : Int64;
begin
  m := Max(Max(x2, -x2), Max(y2, -y2));
  d := (2 * 1000 * 1000 * 1000 + 2 + m - 1) div m;
  x2 := x2 * d + 1;
  y2 := y2 * d;
end;


procedure MergeSort(first, last : LongInt);
var mid, it, jt : LongInt;
begin
  if last - first = 1 then
    Exit;
  mid := (first + last) div 2;
  MergeSort(first, mid);
  MergeSort(mid, last);
  it := first;
  jt := mid;
  while (it < mid) or (jt < last) do
  begin
    if (it = mid) or ((jt < last) and 
        ((x[p[it]] > x[p[jt]]) or 
         ((x[p[it]] = x[p[jt]]) and (y[p[it]] > y[p[jt]]))))  then
    begin
      merge[it - first + jt - mid] := p[jt];
      jt := jt + 1;
    end else begin
      merge[it - first + jt - mid] := p[it];
      it := it + 1;
    end;
  end;
  for i := first to last - 1 do
    p[i] := merge[i - first];
end;


procedure TreeAdd(key, value : LongInt);
begin
  while key < n do
  begin
    tree[key] := tree[key] + value;
    key := key or (key + 1);
  end;
end;


function TreeQuery(key : LongInt) : LongInt;
begin
  TreeQuery := 0;
  while key >= 0 do
  begin
    TreeQuery := TreeQuery + tree[key];
    key := (key and (key + 1)) - 1;
  end;
end;


procedure Solve(first, last, min_result, max_result : LongInt);
var mid_result, mid, query_result : LongInt;
begin
  if first = last then
    Exit;
  if max_result - min_result = 1 then
  begin
    for i := first to last - 1 do
      res[p[i]] := min_result;
    Exit;
  end;
  mid_result := (min_result + max_result) div 2;
  MergeSort(first, last);
  mid := first;
  for i := first to last - 1 do
  begin
    query_result := TreeQuery(y[p[i]]);
    if (p[i] < mid_result) or (query_result >= k[p[i]]) then
    begin
      TreeAdd(y[p[i]], 1);
      temp32 := p[i];
      p[i] := p[mid];
      p[mid] := temp32;
      mid := mid + 1;
    end else begin
      k[p[i]] := k[p[i]] - query_result;
    end;
  end;
  for i := first to mid - 1 do
    TreeAdd(y[p[i]], -1);
  Solve(first, mid, min_result, mid_result);
  Solve(mid, last, mid_result, max_result);
end;


begin
  ReadLn(n);
  ReadLn(x1, y1, x2, y2);
  if x1 * y2 = x2 * y1 then
    Distort;
  if x1 * y2 < x2 * y1 then
  begin
    temp64 := x1;
    x1 := x2;
    x2 := temp64;
    temp64 := y1;
    y1 := y2;
    y2 := temp64;
  end;
  for i := 0 to n - 1 do
  begin
    ReadLn(a, b);
    x[i] := x1 * b - y1 * a;
    y[i] := y2 * a - x2 * b;
  end;
  for i := 0 to n - 1 do
    Read(k[i]);
  
  for i := 0 to n - 1 do
    p[i] := i;
  MergeSort(0, n);
  for i := 0 to n - 1 do
  begin
    x[p[i]] := y[p[i]];
    y[p[i]] := i;
  end;
  
  for i := 0 to n - 1 do
    tree[i] := 0;
  Solve(0, n, 0, n);

  for i := 0 to n - 1 do
  begin
    if i > 0 then
      Write(' ');
    Write(1 + res[i]);
  end;
  WriteLn;
end.
