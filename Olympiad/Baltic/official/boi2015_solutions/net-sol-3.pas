(*
  Task: net
  Random solution
  With O(n) bridge finding
  Author: Bartosz Kostka, Jakub Radoszewski
*)

const MAXN = 500007;

type PKraw = ^Kraw;
  Kraw = record
    v : LongInt;
    next : PKraw;
  end;

var
  n : LongInt;
  G : array[0 .. MAXN] of PKraw;
  Gsize : array[0 .. MAXN] of LongInt;
  L : array[1 .. 2 * MAXN] of LongInt;
  tail : LongInt;
  d, low, par : array[0 .. MAXN] of LongInt;
  vis : array[0 .. MAXN] of Boolean;

function min(a, b : LongInt) : LongInt;
begin
  if a > b then
    min := b
  else
    min := a;
end;

procedure dfs(v : LongInt);
var
  k : PKraw;
  multiple : Boolean;
  w : LongInt;
begin
  vis[v] := true;
  k := G[v];
  while k^.next <> NIL do
  begin
    k := k^.next;
    w := k^.v;
    if not vis[w] then
    begin
       par[w] := v;
       d[w] := d[v] + 1;
       dfs(w);
     end;
  end;
  low[v] := d[v];
  multiple := false;
  k := G[v];
  while k^.next <> NIL do
  begin
    k := k^.next;
    w := k^.v;
    { jest moim synem }
    if par[w] = v then
    begin
      low[v] := min(low[v], low[w]);
      continue;
    end;
    
    { jest moim ojcem }
    if (w = par[v]) and (not multiple) then
    begin
      multiple := true;
      continue;
    end;

    { jest krawedzia wtorna }
    low[v] := min(low[v], d[w]);
  end;
end;

function bridges : Boolean;
var
  i : LongInt;
begin
  for i := 1 to n do begin
    vis[i] := false;
    low[i] := 0;
    par[i] := 0;
    d[i] := 0;
  end;
  dfs(1);
  bridges := false;
  for i := 1 to n do
    if (d[i] = low[i]) and (d[i] <> 0) then
      bridges := true;
end;

procedure print;
var
  i : LongInt;
begin
  WriteLn(tail div 2);
  for i := 1 to tail div 2 do
    WriteLn(L[2 * i - 1], ' ', L[2 * i]);
end;

procedure add_edge(a, b : LongInt);
var
  k : PKraw;
begin
  New(k);
  k^.v := b;
  k^.next := G[a]^.next;
  G[a]^.next := k;

  New(k);
  k^.v := a;
  k^.next := G[b]^.next;
  G[b]^.next := k;

  Inc(Gsize[a]);
  Inc(Gsize[b]);
end;

procedure del_edge(a, b : LongInt);
begin
  G[a]^.next := G[a]^.next^.next;
  G[b]^.next := G[b]^.next^.next;
  { Memory leak, sorry }
  Dec(Gsize[a]);
  Dec(Gsize[b]);
end;

procedure Swap(var a, b : LongInt);
var
  c : LongInt;
begin
  c := a;
  a := b;
  b := c;
end;

procedure random_shuffle;
var
  i : LongInt;
begin
  for i := 2 to tail - 1 do
    Swap(L[Random(i - 1) + 1], L[i]);
end;

var
  i, a, b, w : LongInt;

begin
  RandSeed := 42;
  tail := 1;
  ReadLn(n);
  for i := 0 to n do
  begin
    New(G[i]);
    G[i]^.next := NIL;
    Gsize[i] := 0;
  end;
  for i := 1 to n - 1 do
  begin
    ReadLn(a, b);
    add_edge(a, b);
  end;
  for i := 1 to n do
  begin
    if Gsize[i] = 1 then
    begin
      L[tail] := i;
      Inc(tail);
    end
    else
      w := i;
  end;

  if (tail + 1) mod 2 = 1 then
  begin
    L[tail] := w;
    Inc(tail);
  end;

  while true do
  begin
    random_shuffle;
    for i := 1 to tail div 2 do
    begin
      a := L[2 * i - 1];
      b := L[2 * i];
      add_edge(a, b);
    end;
    if not bridges then
    begin
      print;
      break;
    end;
    for i := 1 to tail div 2 do
    begin
      a := L[2 * i - 1];
      b := L[2 * i];
      del_edge(a, b);
    end;
  end;
end.
