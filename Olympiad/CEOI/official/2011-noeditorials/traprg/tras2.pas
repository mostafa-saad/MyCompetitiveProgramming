(* Slower solution of TRA/jlac012
 * Brutal O(n^2) solution, for each west junction search the whole graph
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
  n, m, A, B, west_size : longint;
  i, l : longint;
  tmp1, tmp2 : longint;
  edges : array[0..MAXN] of elem_p;(* junctions in road network *)
  eastern : array[0..MAXN] of longint; (* equals 1 when junction lies on the east bank *)
  west : array[0..MAXN] of pair_t; (* junctions on west riverbank *)
  visited : array[0..MAXN] of longint;
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
  west_size := 0;
  readln(n, m, A, B);
  for i := 1 to n do
  begin
    readln(tmp1, tmp2);
    eastern[i] := 0;
    edges[i] := nil;
    if tmp1 = 0 then
    begin
      west[west_size].first := tmp2;
      west[west_size].second := i;
      west_size := west_size + 1;
    end else if tmp1 = A then eastern[i] := 1;
  end;
  merge_sort(0, west_size);
  while m > 0 do
  begin
    m := m - 1;
    readln(tmp1, tmp2, i);
    push(edges[tmp1], tmp2);
    if i = 2 then push(edges[tmp2], tmp1);
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
    reachable := reachable + eastern[i];
    tmp := edges[i];
    while tmp <> nil do
    begin
      l := tmp^.x;
      if visited[l] <> west_size then
      begin
        visited[l] := west_size;
        push(q, l);
      end;
      tmp := tmp^.nx;
    end;
  end;
end;

procedure generate_output;
begin
  for i := 1 to n do visited[i] := 0;
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
