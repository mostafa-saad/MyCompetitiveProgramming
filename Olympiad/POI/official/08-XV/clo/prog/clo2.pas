(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo2.pas                                                  *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             BFSa. Zlozonosc O(n+m).                                   *
 *                                                                       *
 *************************************************************************)
const MAXN = 100000;
const MAXM = 200000;

type Vertex = record
        visited: Boolean;
        adj: LongInt;
        prev: LongInt;
        e: LongInt;
      end;

     VertEdge = record
        edge: LongInt;
        next: LongInt;
      end;

var vertices: array[0..MAXN-1] of Vertex;
    vertEdges: array[0..MAXM*2-1] of VertEdge;
    vertEdgesNum: LongInt;
    queue: array[0..MAXN-1] of LongInt;
    queueFirst: LongInt;
    queueLast: LongInt;

function queueIsEmpty: Boolean; inline;
begin
  queueIsEmpty := queueFirst = queueLast;
end;

procedure enqueue(v: LongInt); inline;
begin
  queue[queueLast] := v;
  Inc(queueLast);
  if  MAXN = queueLast then begin
    queueLast := 0;
  end
end;

function dequeue: LongInt; inline;
begin
  dequeue := queue[queueFirst];
  Inc(queueFirst);
  if  MAXN = queueFirst then begin
    queueFirst := 0;
  end
end;

procedure queueInit; inline;
begin
  queueFirst := 0;
  queueLast := 0;
end;

procedure solve2(v: LongInt; adj: LongInt);
var akt: LongInt;
    w: LongInt;
    pom: LongInt;
begin
  vertices[v].adj := adj;
  queueInit;
  akt := vertices[v].e;
  while  -1 <> akt do begin
    w := vertEdges[akt].edge;
    if w <> adj then begin
      enqueue(w);
      vertices[w].adj := v;
    end;
    akt := vertEdges[akt].next;
  end;
  vertices[v].visited := true;
  while not queueIsEmpty do begin
    w := dequeue;
    vertices[w].visited := true;
    akt := vertices[w].e;
    while  -1 <> akt do begin
      pom := vertEdges[akt].edge;
      if 0 > vertices[pom].adj then begin
        vertices[pom].adj := w;
        enqueue(pom);
      end;
      akt := vertEdges[akt].next;
    end
  end
end;

procedure solve(v: LongInt);
var w: LongInt;
    akt: LongInt;
    adj: LongInt;
begin
  queueInit;
  enqueue(v);
  while  not queueIsEmpty do begin
    w := dequeue;
    vertices[w].visited := true;
    akt := vertices[w].e;
    while -1 <> akt do begin
      adj := vertEdges[akt].edge;
      if adj <> vertices[w].prev then begin
        if -1 = vertices[adj].adj then begin
          vertices[adj].adj := -2;
          enqueue(adj);
          vertices[adj].prev := w;
        end else begin
          solve2(adj,w);
          exit;
        end
      end;
      akt := vertEdges[akt].next;
    end
  end
end;

var n,m,i: LongInt;
    isPossibe: Boolean;
    a,b: LongInt;

begin
  vertEdgesNum := 0;
  queueFirst := 0;
  queueLast := 0;
  ReadLn(n, m);
  for i:=0 to n-1 do begin
    vertices[i].e := -1;
    vertices[i].adj := -1;
    vertices[i].visited := false;
    vertices[i].prev := -1;
  end;
  for i:=0 to m-1 do begin
    ReadLn(a, b);
    Dec(a);
    Dec(b);

    vertEdges[vertEdgesNum].next := vertices[a].e;
    vertEdges[vertEdgesNum].edge := b;
    vertices[a].e := vertEdgesNum;
    Inc(vertEdgesNum);

    vertEdges[vertEdgesNum].next := vertices[b].e;
    vertEdges[vertEdgesNum].edge := a;
    vertices[b].e := vertEdgesNum;
    Inc(vertEdgesNum);
  end;
  for i:=0 to n-1 do begin
    if not vertices[i].visited then begin
      solve(i);
    end
  end;
  isPossibe := true;
  for i:=0 to n-1 do begin
    if 0 > vertices[i].adj then begin
      isPossibe := false;
      break;
    end
  end;
  if isPossibe then begin
    WriteLn('TAK');
    for i:=0 to n-1 do begin
      WriteLn(vertices[i].adj + 1);
    end
  end else begin
    WriteLn('NIE');
  end
end.
