(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szks2.pas                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                                                                       *
 *************************************************************************)

const SIZE = 200;    { maximal number of schools }
const GSIZE = 2*SIZE+2;    { maximal number of vertices in graph }
const MAX_EDGE = SIZE+1;  { maximal number of edges from 1 vertex }
const EDGESN = SIZE*(SIZE+2);  { maximal number of edges }
const INF : longint = 1000000000;

var 
  ON : longint;
  cur, low, high, score : array [0..SIZE-1] of longint;
  e0, e1, edir, ecost : array [0..EDGESN-1] of longint;
  ecounter : longint;
  edges : array [0..GSIZE-1, 0..MAX_EDGE-1] of longint;
  esize : array [0..GSIZE-1] of longint;
  GN, START, STOP : longint;

procedure add_edge(v0, v1, c : longint);
begin
  edges[v0, esize[v0]] := ecounter; inc(esize[v0]);
  edges[v1, esize[v1]] := ecounter; inc(esize[v1]);
  e0[ecounter] := v0;
  e1[ecounter] := v1;
  edir[ecounter] := 1;
  ecost[ecounter] := c;
  inc(ecounter);
end;

procedure construct_graph;
{ vertices 0 .. ON-1 - schools
  vertices ON .. 2*ON-1 - numbers
  vertex 2*ON - initial vertex, connected with all schools
  vertex 2*ON+1 - last vertex, connected with all numbers }
var a, b : longint;
begin
  GN := 2*ON+2;
  START := 2*ON;
  STOP := 2*ON+1;
  ecounter := 0;
  for a := 0 to GN-1 do
    esize[a] := 0;
  for a := 0 to ON-1 do
  begin
    add_edge(START, a, 0);
    add_edge(a+ON, STOP, 0);
    for b := low[a] to high[a] do
      add_edge(a, b+ON, abs(cur[a]-b)*score[a]);
  end;
end;

var dist, back : array [0..GSIZE-1] of longint;

procedure swap(var a, b : longint);
var c : longint;
begin
  c := a; a := b; b := c;
end;

function find_path : boolean;
var
  a, en, v0, v1, c, xxx : longint;
begin
  for a := 0 to GN-1 do
    dist[a] := INF;
  dist[START] := 0;
  for xxx := 0 to GN-2 do
  begin
    for en := 0 to ecounter-1 do
    begin
      v0 := e0[en]; v1 := e1[en]; c := edir[en]*ecost[en];
      if edir[en]<0 then
        swap(v0, v1);
      c := c+dist[v0];
      if c<dist[v1] then
      begin
        dist[v1] := c;
        back[v1] := en;
      end;
    end;
  end;
  find_path := dist[STOP]<INF;
end;

procedure extend;
var v, en : longint;
begin
  v := STOP;
  while v<>START do
  begin
    en := back[v];
    v := v xor e0[en] xor e1[en];
    edir[en] := -edir[en];
  end;
end;

var a, k : longint;
begin
  read(ON);
  for a := 0 to ON-1 do
  begin
    read(cur[a], low[a], high[a], score[a]);
    dec(cur[a]); dec(low[a]); dec(high[a]);
  end;
  construct_graph();
  for a := 0 to ON-1 do
  begin
    if not find_path then
    begin
      writeln('NIE');
      halt(0);
    end;
    extend;
  end;
  k := 0;
  for a := 0 to ecounter-1 do
    if edir[a]<0 then
      k := k+ecost[a];
  writeln(k);
end.
