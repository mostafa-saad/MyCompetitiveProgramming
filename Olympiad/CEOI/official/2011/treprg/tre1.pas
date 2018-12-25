(* Model solution to the task Treasure hunt
 * Author: Jakub Radoszewski
 * Date: 10.06.2011
 * Time complexity: O(#calls * log(#calls)).
 * Description: the explicit nodes are renumbered.
 *)

unit tre;

interface

procedure init;

procedure path(a, s : LongInt);

function dig(a, b : LongInt) : LongInt;

implementation


const
  MAX_CALLS = 400000;
  LOG_2_MAX_CALLS = 20;

(* This node will be created if a path call appears *)
var
  curr : LongInt;



(*****************************************************************************)
(* Data structures *)


(* An (implicit or explicit) node located dist units below the explicit node
 * expl. *)
type node = record
  expl, dist : LongInt;
end;

type ancestor = record
  node, dist : LongInt;
end;

type pair = record
  first, second : LongInt;
end;

var
  (* The ancestors of the nodes (anc[v][i] is the ancestor 2^i edges above)
   * and their depths. *)
  anc : array[0 .. 2 * MAX_CALLS, 0 .. LOG_2_MAX_CALLS] of ancestor;

  (* depth includes implicit nodes, real_depth considers only explicit nodes.*)
  depth, real_depth : array[0 .. 2 * MAX_CALLS] of LongInt;

  (* If v is the upper end of an edge, attached[v] is the node to which
   * it is directly attached. Otherwise attached[v].node == -1. *)
  attached : array[0 .. 2 * MAX_CALLS] of node;

  (* If expl_anc contains a pair (y, x) then x is the explicit ancestor of
   * all the nodes x..y.
   * Initially the vector contains sentinel pairs (0, 0) and (1, 1). *)
  expl_anc : array[0 .. 2 * MAX_CALLS] of pair;
  expl_anc_size : LongInt;


(*****************************************************************************)
(* Simple utility functions *)

function make_pair(a, b : LongInt) : pair;
var
  p : pair;
begin
  p.first := a;
  p.second := b;
  make_pair := p;
end;

(* From a renumbered node to the real node value. *)
function real_node(a : LongInt) : LongInt;
begin
  real_node := expl_anc[a].second;
end;

function get_depth(a : node) : LongInt;
begin
  get_depth := depth[a.expl] + a.dist;
end;

(* Binary search *)
function get_node(a : LongInt) : node;
var
  v : node;
  l, h, c : LongInt;
begin
  l := 0;
  h := expl_anc_size - 1;
  while l < h do
  begin
    c := (l + h) div 2;
    if expl_anc[c].first < a then
      l := c + 1
    else
      h := c;
  end;
  v.expl := l;
  v.dist := a - real_node(v.expl);
  get_node := v;
end;



(*****************************************************************************)
(* Important utility functions *)

(* Computes anc[a], starting with anc[a, 0] = par. *)
procedure compute_anc(a, par, len : LongInt);
var
  v : ancestor;
  i : LongInt;
begin
  v.node := par;
  v.dist := len;
  anc[a, 0] := v;
  for i := 0 to LOG_2_MAX_CALLS - 1 do
  begin
    v.node := anc[anc[a, i].node, i].node;
    v.dist := anc[a][i].dist + anc[anc[a, i].node, i].dist;
    anc[a, i + 1] := v;
  end;
end;


(* Auxiliary function, only on explicit nodes. *)
function go_up(a, h : LongInt) : node;
var
  i : LongInt;
  p : ancestor;
  b, q : node;
begin
  (* Finding the highest explicit node located at most h units above a. *)
  i := 0;
  while (i + 1 < LOG_2_MAX_CALLS) and (anc[a, i + 1].dist <= h) do
    Inc(i);
  while i >= 0 do
  begin
    p := anc[a, i];
    if p.dist <= h then
    begin
      Dec(h, p.dist);
      a := p.node;
    end;
    Dec(i);
  end;

  (* The final touch: finding the potentially implicit node. *)
  if h = 0 then
  begin
    b.expl := a;
    b.dist := 0;
    go_up := b;
  end
  else
  begin
    q := attached[a];
    if (q.expl = -1) then (* a is the lower end of its edge *)
    begin
      b.expl := anc[a, 0].node;
      b.dist := (real_node(a) - real_node(b.expl)) - h;
    end
    else (* a is the upper end of its edge *)
    begin
      Dec(h);
      b.expl := q.expl;
      b.dist := q.dist - h;
    end;
    go_up := b;
  end;
end;

(* Advances the distance h up, starting from the node a. *)
function go_up(a : node; h : LongInt) : node;
begin
  if h <= a.dist then
  begin
    Dec(a.dist, h);
    go_up := a;
  end
  else
    go_up := go_up(a.expl, h - a.dist);
end;

(* Advances h explicit edges up, starting from the node a. *)
function go_up_real(a, h : LongInt) : LongInt;
var
  i : LongInt;
begin
  i := 0;
  while (1 shl (i + 1)) <= h do
    Inc(i);
  while h <> 0 do
  begin
    if (1 shl i) <= h then
    begin
      a := anc[a, i].node;
      Dec(h, (1 shl i));
    end;
    Dec(i);
  end;
  go_up_real := a;
end;

(* O(log(n)) time *)
function lca(a, b : node) : node;
var
  da, db, i : LongInt;
  c, p, q, res : node;
  done : Boolean;
begin
  (* Equalizing depths *)
  da := real_depth[a.expl];
  db := real_depth[b.expl];
  if (da < db) or ((da = db) and (a.dist < b.dist)) then
  begin
    p := a; a := b; b := p;
    i := da; da := db; db := i;
  end;
  if a.expl = b.expl then
    lca := b
  else
  begin
    a.dist := 0;
    done := false;
    if da > db then
    begin
      a.expl := go_up_real(a.expl, da - db - 1);
      if anc[a.expl, 0].node = b.expl then
      begin
        c := attached[a.expl];
        if c.expl = -1 then
          c := b;
        if c.dist <= b.dist then
          lca := c
        else
          lca := b;
        done := true;
      end;
      a.expl := anc[a.expl, 0].node;
    end;

    if not done then
    begin
      b.dist := 0;

      (* Finding LCA *)
      i := 0;
      while anc[a.expl, i].node <> anc[b.expl, i].node do
        Inc(i);
      Dec(i);
      while i >= 0 do
      begin
        a.expl := anc[a.expl, i].node;
        b.expl := anc[b.expl, i].node;
        while (i >= 0) and (anc[a.expl, i].node = anc[b.expl, i].node) do
          Dec(i);
      end;

      p := attached[a.expl];
      q := attached[b.expl];
      if (p.expl = -1) or (q.expl = -1) then
      begin
        res := p;
        if res.expl = -1 then
          res := q;
        if res.expl = -1 then
        begin
          res.expl := anc[a.expl, 0].node;
          res.dist := 0;
        end;
      end
      else
      begin
        res.expl := anc[a.expl, 0].node;
        res.dist := p.dist;
        if q.dist < p.dist then
          res.dist := q.dist;
      end;
      lca := res;
    end;
  end;
end;




(*****************************************************************************)

procedure init;
var
  a : ancestor;
  i : LongInt;
begin
  depth[0] := -1;
  real_depth[0] := -1;
  depth[1] := 0;
  real_depth[1] := 0;
  a.node := 1;
  a.dist := 0;
  for i := 0 to LOG_2_MAX_CALLS do
    anc[1, i] := a;  (* sentinel *)
  expl_anc[0] := make_pair(0, 0);
  expl_anc[1] := make_pair(1, 1);
  expl_anc_size := 2;
  curr := 2;
end;


(*****************************************************************************)

procedure path(a, s : LongInt);
var
  start, eend, real_start, real_end : LongInt;
  v : node;
begin
  v := get_node(a);
  real_start := curr;
  real_end := curr + s - 1;
  start := expl_anc_size;
  eend := start;
  if real_start <> real_end then
    Inc(eend);

  depth[start] := depth[v.expl] + v.dist + 1;
  real_depth[start] := real_depth[v.expl] + 1;
  if start <> eend then
  begin
    depth[eend] := depth[start] + s - 1;
    real_depth[eend] := real_depth[start] + 1;
  end;
  compute_anc(start, v.expl, v.dist + 1);
  if start <> eend then
    compute_anc(eend, start, s - 1);
  attached[start] := v;
  if start <> eend then
    attached[eend].expl := -1;
  if start <> eend then
  begin
    expl_anc[expl_anc_size] := make_pair(real_end - 1, real_start);
    Inc(expl_anc_size);
  end;
  expl_anc[expl_anc_size] := make_pair(real_end, real_end);
  Inc(expl_anc_size);
  curr := real_end + 1;
end;


(*****************************************************************************)

function dig(a, b : LongInt) : LongInt;
var
  da, db, dv, len, ppos : LongInt;
  na, nb, v, res : node;
begin
  na := get_node(a);
  nb := get_node(b);
  v := lca(na, nb);
  da := depth[na.expl] + na.dist;
  db := depth[nb.expl] + nb.dist;
  dv := depth[v.expl] + v.dist;

  len := da + db - 2 * dv;
  ppos := len div 2;
  if ppos <= da - dv then
    res := go_up(na, ppos)
  else
    res := go_up(nb, len - ppos);
  dig := real_node(res.expl) + res.dist;
end;

begin
end.
