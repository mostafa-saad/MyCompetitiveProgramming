(* Model solution of task TRA/jlac012
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
  scc_size : longint; (* number of strongly connected components *)
  west, east : array[0..MAXN] of longint; (* junctions on respective river banks *)
  edges : array[0..MAXN] of elem_p; (* streets in road network *)
  edges_rev : array[0..MAXN] of elem_p; (* edges in reversed network *)
  scc : array[0..MAXN] of elem_p; (* vertices in strongly connected component *)
  visited : array[0..MAXN] of boolean; (* was a junction visited *)
  order : array[0..MAXN] of longint; (* dfs post-order of junctions *)
  scc_inv : array[0..MAXN] of longint; (* the scc for given junction *)
  scc_edges : array[0..MAXN] of longint; (* number of edges starting from scc *)
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

procedure reorder(v : longint);
var
  it : elem_p;
begin
  it := edges[v];
  visited[v] := true;
  while it <> nil do
  begin
    if not visited[it^.x] then reorder(it^.x);
    it := it^.nx;
  end;
  order[l] := v;
  l := l + 1;
end;

procedure mark_scc(v : longint);
var
  it : elem_p;
begin
  it := edges_rev[v];
  visited[v] := false;
  push(scc[scc_size], v);
  scc_inv[v] := scc_size;
  while it <> nil do
  begin
    if visited[it^.x] then mark_scc(it^.x);
    it := it^.nx;
  end;
end;

procedure calculate_strongly_connected_components;
var
  it : elem_p;
begin
  for i := 0 to n-1 do visited[i] := false;
  l := 0; scc_size := 0;
  for i := 0 to n-1 do if not visited[i] then reorder(i);
  for i := n-1 downto 0 do if visited[order[i]] then
  begin
    mark_scc(order[i]);
    scc_size := scc_size + 1;
  end;
  for i := 0 to scc_size - 1 do scc_edges[i] := 0;
  for i := 0 to n-1 do
  begin
    it := edges[i];
    while it <> nil do
    begin
      if scc_inv[it^.x] <> scc_inv[i] then scc_edges[scc_inv[i]] := scc_edges[scc_inv[i]] + 1;
      it := it^.nx;
    end;
  end;
end;

procedure add_interval (var a : pair_t; b : pair_t);
begin
  if b.first = -1 then exit;
  if a.first = -1 then begin a := b; exit; end;
  a.first := min(a.first, b.first);
  a.second := max(a.second, b.second);
end;

procedure calculate_reachable_intervals;
var
  it, q : elem_p;
begin
  q := nil;
  for i := 0 to n-1 do visited[i] := false;
  for i := 0 to scc_size-1 do interval[i] := make_pair(-1, -1);
  for j := 0 to east_size-1 do
  begin
    l := scc_inv[east[j]];
    add_interval(interval[l], make_pair(j, j));
  end;
  for l := 0 to scc_size-1 do if scc_edges[l] = 0 then
  begin
    visited[l] := true;
    push(q, l);
  end;
  while q <> nil do begin
    k := pop(q);
    it := scc[k];
    while it <> nil do
    begin
      i := it^.x;
      while edges_rev[i] <> nil do
      begin
        l := scc_inv[pop(edges_rev[i])];
        add_interval(interval[l], interval[k]);
        scc_edges[l] := scc_edges[l] -1;
        if scc_edges[l] = 0 then
        begin
          visited[l] := true;
          push(q, l);
        end;
      end;
      it := it^.nx;
    end;
  end;
end;

procedure mark_reachable_industrial;
begin
  for i := 0 to n-1 do visited[i] := false;
  l := 0;
  for j := 0 to west_size-1 do
    if not visited[west[j]] then reorder(west[j]);
  for i := 0 to n-1 do order[i] := 0;
  if visited[east[0]] then order[0] := 1;
  for j := 1 to east_size-1 do
    if visited[east[j]] then
      order[j] := order[j-1] + 1
    else
      order[j] := order[j-1];
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
    scc[i] := nil;
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
    m := m -1;
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

procedure write_output;
begin
  for l := west_size - 1 downto 0 do
  begin
    tmp1 := interval[scc_inv[west[l]]].first;
    tmp2 := interval[scc_inv[west[l]]].second;
    if tmp1 = -1 then writeln(0)
    else if tmp1 = 0 then writeln(order[tmp2])
    else writeln(order[tmp2] - order[tmp1-1]);
  end;
end;

Begin
  read_input;
  calculate_strongly_connected_components;
  calculate_reachable_intervals;
  mark_reachable_industrial;
  write_output;
End.
