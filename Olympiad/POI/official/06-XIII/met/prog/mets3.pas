(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                mets3.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Program wyznaczajacy najdluzsza sciezke        *
 *                        w czasie kwadratowym.                          *
 *                        Zlozonosc obliczeniowa: O(n^2)                 *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

type
  Pedge = ^Edge;
  Edge = record
    v : LongInt;
    n : Pedge;
  end; {record}
  Para = record
    first, second : LongInt;
  end; {record}

var
  n, l, i, j, a, b : LongInt;
  mlen , mw , res : LongInt;
  g : array[0..MAXN] of Pedge;
  used, lin : array[0..MAXN] of Boolean;
  prev, deg : array[0..MAXN] of LongInt;
  kol : array[0..MAXN] of Para;
  kol1 : array[0..MAXN + 10] of LongInt;
  head, tail : LongInt;


procedure add(a, b : LongInt);
var kr : Pedge;
begin
  New(kr);
  kr^.n := g[a]^.n;
  kr^.v := b;
  g[a]^.n := kr
end; {add}

function make_pair(a, b : LongInt) : Para;
var
  p : Para;
begin
  p.first := a;
  p.second := b;
  make_pair := p
end; {make_pair}

procedure push(p : Para);
begin
  kol[tail] := p;
  if tail = MAXN then
    tail := 0
  else
    Inc(tail)
end; {push}

function pop : Para;
var
  p : Para;
begin
  p := kol[head];
  if head = MAXN then
    head := 0
  else
    Inc(head);
  pop := p
end; {pop}

procedure push1(p : LongInt);
begin
  kol1[tail] := p;
  if tail = MAXN then
    tail := 0
  else
    Inc(tail)
end; {push1}

function pop1 : LongInt;
var
  p : LongInt;
begin
  p := kol1[head];
  if head = MAXN then
    head := 0
  else
    Inc(head);
  pop1 := p
end; {pop}


function bfs(w : LongInt) : LongInt;
var
  last, i : LongInt;
  p : Para;
  kr : Pedge;
begin
  last := 0;
  for i := 0 to n - 1 do
    used[i] := FALSE;
  used[w] := TRUE;
  head := 0; tail := 0;
  push(make_pair(w, 0));
  while head <> tail do
  begin
    p := pop;
    last := p.second;
    kr := g[p.first];
    while kr^.n <> NIL do
    begin
      kr := kr^.n;
      if not used[kr^.v] then
      begin
        used[kr^.v] := TRUE;
        push(make_pair(kr^.v, p.second + 1))
      end {if}
    end {while}
  end; {while}
  bfs := last
end; {bfs}

procedure getpath(v : LongInt);
var
  last, w, i : LongInt;
  kr : Pedge;
begin
  w := v;
  for i := 0 to n - 1 do
    used[i] := FALSE;
  used[w] := TRUE;
  head := 0; tail := 0;
  push1(w);
  prev[w] := -1;
  while head <> tail do
  begin
    w := pop1;
    last := w;
    kr := g[w];
    while kr^.n <> NIL do
    begin
      kr := kr^.n;
      if not used[kr^.v] then
      begin
        prev[kr^.v] := w;
        used[kr^.v] := TRUE;
        push1(kr^.v)
      end {if}
    end {while}
  end; {while}
  while last <> -1 do
  begin
    lin[last] := TRUE;
    last := prev[last]
  end {while}
end; {getpath}

function getlen(v : LongInt) : LongInt;
var
  res, w : LongInt;
begin
  res := 0; w := v;
  while not lin[w] do
  begin
    Inc(res);
    w := prev[w]
  end; {while}
  getlen := res
end; {getlen}

procedure addpath(v : LongInt);
var
  w : LongInt;
begin
  w := v;
  while not lin[w] do
  begin
    lin[w] := TRUE;
    w := prev[w]
  end {while}
end; {addpath}

begin
  mlen := 0; mw := 0;
  Read(n, l);
  if l = 0 then 
  begin
    WriteLn(0);
    Exit
  end; {if}
  for i := 0 to n - 1 do
  begin
    New(g[i]);
    g[i]^.n := NIL
  end; {for}
  for i := 0 to n - 1 do
    deg[i] := 0;
  for i := 0 to n - 2 do
  begin
    Read(a, b);
    Dec(a); Dec(b);
    add(a, b); add(b, a);
    Inc(deg[a]); Inc(deg[b])
  end; {for}
  
  for i := 0 to n - 2 do
  begin
    res := bfs(i);
    if mlen < res then
    begin
      mlen := res; mw := i
    end {if}
  end; {for}
  for i := 0 to n - 1 do
    lin[i] := FALSE;
  getpath(mw);
  
  for j := 0 to l * 2 - 3 do
  begin
    mlen := 0; mw := 0;
    for i := 0 to n - 1 do
      if deg[i] = 1 then
      begin
        res := getlen(i);
        if res > mlen then
        begin
          mlen := res; mw := i
        end {if}
      end; {if}
    addpath(mw)
  end; {for}

  res := 0;
  for i := 0 to n - 1 do
    if lin[i] then
      Inc(res);
  WriteLn(res);
end. {program}
