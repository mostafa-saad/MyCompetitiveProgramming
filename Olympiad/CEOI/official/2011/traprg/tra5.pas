(* Alternative solution of TRA/jlac012
 * Searching for lowest and highest reachable eastern junction
 * Author: Mateusz Baranowski
 *)

const MAXN = 300001;

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
  if el = nil then pop := -1
  else begin
    tmp := el^.nx;
    pop := el^.x;
    dispose(el);
    el := tmp;
  end;
end;

function max(a, b : longint) : longint;
begin
  if a < b then max := b
  else max := a;
end;

function min(a, b : longint) : longint;
begin
  if a < b then min := a
  else min := b;
end;

function make_pair(a, b : longint) : pair_t;
begin
  make_pair.first := a;
  make_pair.second := b;
end;

var
  n, m, A, B : longint;
  i, l, j, k : longint;
  west_size, east_size : longint;
  tmp1, tmp2 : longint;
  west, east : array[0..MAXN] of longint; (* junctions on respective river banks *)
  edges : array[0..MAXN] of elem_p; (* streets in road network *)
  edges_rev : array[0..MAXN] of elem_p; (* edges in reversed network *)
  visited : array[0..MAXN] of boolean; (* was a junction visited *)
  visited2 : array[0..MAXN] of boolean; (* was a junction visited *)
  eastern : array[0..MAXN] of longint; (* the number of eastern bank junction for node *)
  interval : array[0..MAXN] of pair_t; (* intervals of junctions reachable from junction *)
  tab : array[0..MAXN] of pair_t;

procedure merge_sort(l, r : longint; var tab1: array of pair_t);
var
  m, a, b, c : longint;
begin
  m := l + (r - l + 1) div 2;
  if r = l + 1 then exit;
  merge_sort(l, m, tab1);
  merge_sort(m, r, tab1);
  a := l;  b := m;  c := 0;
  while (a < m) or (b < r) do
  begin
    if (a < m) and ((b = r) or (tab1[a].first < tab1[b].first)) then
    begin
      tab[c] := tab1[a];
      a := a + 1;
    end else begin
      tab[c] := tab1[b];
      b := b + 1;
    end;
    c := c + 1;
  end;
  for i := 0 to r-l-1 do tab1[i + l] := tab[i];
end;

(* check which junctions are reachable from nodes through current_edges *)
procedure visit(size : longint; var nodes : array of longint; var current_edges : array of elem_p);
var
  it, q : elem_p;
begin
  q := nil;
  for i := 0 to n-1 do visited[i] := false;
  for i := 0 to size-1 do
  begin
    visited[nodes[i]] := true;
    push(q, nodes[i]);
  end;
  while q <> nil do
  begin
    i := pop(q);
    it := current_edges[i];
    while it <> nil do
    begin
      l := it^.x;
      if not visited[l] then begin visited[l] := true; push(q, l); end;
      it := it^.nx;
    end;
  end;
end;

(* mark reachable eastern junctions *)
procedure mark_reachable_east;
begin
  visit(west_size, west, edges);
  for i := 0 to n-1 do eastern[i] := -1;
  l := 0;
  for j := 0 to east_size-1 do
  begin
    if visited[east[j]] then
    begin
      eastern[east[j]] := l;
      l := l + 1;
    end;
  end;
end;

procedure read_input;
var
  west_tmp, east_tmp : array[0..MAXN] of pair_t;
begin
  west_size := 0; east_size := 0;
  readln (n, m, A, B);
  for i := 0 to n-1 do
  begin
    edges[i] := nil;
    edges_rev[i] := nil;
    readln (tmp1, tmp2);
    if tmp1 = 0 then
    begin
      west_tmp[west_size] := make_pair(tmp2, i);
      west_size := west_size + 1;
    end else if tmp1 = A then
    begin
      east_tmp[east_size] := make_pair(tmp2, i);
      east_size := east_size + 1;
    end;
  end;
  (* sort junctions according to increasing second coordinates *)
  merge_sort(0, west_size, west_tmp);
  for j := 0 to west_size-1 do west[j] := west_tmp[j].second;
  merge_sort(0, east_size, east_tmp);
  for j := 0 to east_size-1 do east[j] := east_tmp[j].second;
  while m > 0 do
  begin
    m := m-1;
    readln (tmp1, tmp2, i);
    tmp1 := tmp1-1; tmp2 := tmp2-1;
    push(edges[tmp1], tmp2);
    push(edges_rev[tmp2], tmp1);
    if i = 2 then
    begin
      push(edges[tmp2], tmp1);
      push(edges_rev[tmp1], tmp2);
    end;
  end;
end;

(* find northernmost (when k==0 southernmost) eastern junction reachable from v *)
function visit_and_find(v, p : longint) : longint;
var
  q, it : elem_p;
begin
  q := nil;
  push(q, v);
  visited2[v] := true;
  while q <> nil do
  begin
    i := pop(q);
    if ((k = 1) and (eastern[i] > p)) or
       ((k = 0) and (eastern[i] < p) and (eastern[i] <> -1))
    then
      p := eastern[i];
    it := edges[i];
    while it <> nil do
    begin
      l := it^.x;
      if not visited2[l] then begin visited2[l] := true; push(q, l); end;
      it := it^.nx;
    end;
  end;
  visit_and_find := p;
end;

procedure calculate_output;
var
  l : longint;
begin
  (* calculate southernmost reachable eastern bank junction *)
  tmp1 := MAXN;
  k := 0;
  for i := 0 to n-1 do visited2[i] := false;
  for l := west_size-1 downto 0 do if visited[west[l]] then
  begin
    tmp1 := visit_and_find(west[l], tmp1);
    interval[l].first := tmp1;
  end;
  (* calculate northernmost reachable eastern bank junction *)
  tmp1 := -1;
  k := 1;
  for i := 0 to n-1 do visited2[i] := false;
  for j := 0 to west_size-1 do if visited[west[j]] then
  begin
    tmp1 := visit_and_find(west[j], tmp1);
    interval[j].second := tmp1;
  end;
end;

procedure write_output;
begin
  for l := west_size-1 downto 0 do
    if visited[west[l]] then
      writeln(interval[l].second - interval[l].first + 1)
    else
      writeln(0);
end;

Begin
  read_input;
  mark_reachable_east;
  visit(east_size, east, edges_rev);
  calculate_output;
  write_output;
End.
