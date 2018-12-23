(* Slower solution of TRA/jlac012
 * Brutal O(m * min(west, east)) solution with an optimisation,
 * we search the reversed graph when there is more east than west junctions
 * Author: Mateusz Baranowski
 *)

const MAXN = 300000;

type
  pair_t = record
    first, second : longint;
  end;

  elem_p = ^elem_t;
  elem_t = record
    x : longint;
    nx : elem_p;
  end;

procedure push(var el : elem_p; x : longint);
var
  tmp : elem_p;
begin
  new(tmp);
  tmp^.nx := el;
  tmp^.x := x;
  el := tmp;
end;

function pop(var el : elem_p) : longint;
var
  tmp : elem_p;
begin
  if el <> nil then
  begin
    tmp := el^.nx;
    pop := el^.x;
    dispose(el);
    el := tmp;
  end;
end;

var
  n, m, A, B : longint;
  east_size, west_size : longint;
  i, l : longint;
  tmp1, tmp2 : longint;
  edges : array[0..MAXN] of elem_p; (* junctions in road network *)
  final : array[0..MAXN] of longint; (* equals 1 when junction lies on the east bank *)
  west : array[0..MAXN] of pair_t; (* junctions on west riverbank *)
  visited, east : array[0..MAXN] of longint;
  tab : array[0..MAXN] of pair_t;

procedure merge_sort(l, r : longint);
var
  m, a, b, c : longint;
begin
  m := l + (r - l + 1) div 2;
  if r > l + 1 then
  begin
    merge_sort(l, m);
    merge_sort(m, r);
    a := l;  b := m;  c := l;
    while (a < m) or (b < r) do
    begin
      if (a < m) and ((b = r) or (west[a].first < west[b].first)) then
      begin
        tab[c] := west[a];
        a := a + 1;
      end else begin
        tab[c] := west[b];
        b := b + 1;
      end;
      c := c + 1;
    end;
    for i := l to r-1 do west[i] := tab[i];
  end;
end;

procedure read_input;
begin
  east_size := 0; west_size := 0;
  readln(n, m, A, B);
  for i := 1 to n do
  begin
    readln(tmp1, tmp2);
    final[i] := 0;
    edges[i] := nil;
    if tmp1 = 0 then
    begin
      west[west_size].first := tmp2;
      west[west_size].second := i;
      west_size := west_size + 1;
    end else if tmp1 = A then
    begin
      east[east_size] := i;
      east_size := east_size + 1;
    end;
  end;
  merge_sort(0, west_size);
  if west_size > east_size then
  begin
    for i := 0 to west_size - 1 do final[west[i].second] := 2;
    while m > 0 do
    begin
      m := m - 1;
      readln(tmp1, tmp2, i);
      push(edges[tmp2], tmp1);
      if i = 2 then push(edges[tmp1], tmp2);
    end;
  end else begin
    for i := 0 to east_size - 1 do final[east[i]] := 1;
    while m > 0 do
    begin
      m := m - 1;
      readln(tmp1, tmp2, i);
      push(edges[tmp1], tmp2);
      if i = 2 then push(edges[tmp2], tmp1);
    end;
  end;
end;

function reachable(v : longint) : longint;
var
  q, tmp : elem_p;
begin
  reachable := 0;
  q := nil;
  push(q, v);
  while q <> nil do
  begin
    i := pop(q);
    if final[i] = 1 then reachable := reachable + 1
    else if final[i] > 1 then final[i] := final[i] + 1;
    tmp := edges[i];
    while tmp <> nil do
    begin
      l := tmp^.x;
      if visited[l] <> v then
      begin
        visited[l] := v;
        push(q, l);
      end;
      tmp := tmp^.nx;
    end;
  end;
end;

procedure generate_output;
begin
  for i := 1 to n do visited[i] := 0;
  if west_size > east_size then
  begin
    while east_size > 0 do
    begin
      east_size := east_size - 1;
      reachable(east[east_size]);
    end;
    while west_size > 0 do
    begin
      west_size := west_size - 1;
      writeln (final[west[west_size].second] - 2);
    end;
  end else
    while west_size > 0 do
    begin
      writeln(reachable(west[west_size-1].second));
      west_size := west_size - 1;
    end;
end;

Begin
  read_input;
  generate_output;
End.
