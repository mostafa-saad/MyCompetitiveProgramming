(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo5.pas                                                  *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Alternatywne rozwiazanie wzorcowe. Zachlannie przegladamy *
 *             wierzcholki wkolejnosci nierosnacych stopni i             *
 *             przyporzadkowujemy im dowolne krawedzie. Zlozonosc O(n+m) *
 *                                                                       *
 *************************************************************************)
const
  MAXN = 100000;
  MAXM = 200000;

type
  Edge = record
      a,b:LongInt;
      isUsed:boolean;
    end;

  Vertex = record
     degree: LongInt;
     prev,next: LongInt;
     adj:LongInt;
     e:LongInt;
   end;

  VertEdge = record
      edge:LongInt;
      next:LongInt;
    end;

var
  edges: array[0..MAXM-1] of Edge;
  degrees: array[0..MAXM-1] of LongInt;
  vertices: array[0..MAXN-1] of Vertex;
  vertEdges: array[0..MAXM*2-1] of VertEdge;
  vertEdgesNum: LongInt;
  n,m: LongInt;
  i: LongInt;
  a,b:LongInt;
  mindeg: LongInt;
  isPossibe:Boolean;
  adj,v,k,degree: LongInt;

procedure dodaj(degree, v : LongInt);inline;
var
  next:LongInt;
  begin
    next := degrees[degree];
    vertices[v].next := next;
    vertices[v].prev := -1;
    if -1 <> next then vertices[next].prev := v;
    degrees[degree] := v;
  end;

procedure usun(v:LongInt) ; inline;
var
  prev,next: LongInt;
  begin
    prev := vertices[v].prev;
    next := vertices[v].next;
    if -1 <> prev then vertices[prev].next := next;
    if -1 <> next then vertices[next].prev := prev;
  end;

function findFree(v:LongInt):LongInt; inline;
var
  akt: LongInt;
  begin
    akt := vertices[v].e;
    findFree := -1;
    while -1 <> akt do
    begin
      if edges[vertEdges[akt].edge].isUsed
        then akt := vertEdges[akt].next
        else
          begin
            findFree := vertEdges[akt].edge;
            break;
          end;
    end;
  end;

begin
  vertEdgesNum := 0;
  ReadLn(n,m);

  for i:=0 to n-1 do
    begin
      vertices[i].e := -1;
      vertices[i].adj := -1;
    end;

  for i:=0 to m-1 do
    begin
      ReadLn(a,b);
      Dec(a); Dec(b);
      edges[i].a := a;
      edges[i].b := b;
      Inc(vertices[a].degree);
      Inc(vertices[b].degree);

      with vertEdges[vertEdgesNum] do
      begin
        next := vertices[a].e;
        edge := i;
      end;
      vertices[a].e := vertEdgesNum;
      Inc(vertEdgesNum);

      with vertEdges[vertEdgesNum] do
      begin
        next := vertices[b].e;
        edge := i;
      end;
      vertices[b].e := vertEdgesNum;
      Inc(vertEdgesNum);
    end;
  for i:=0 to m-1 do
    degrees[i] := -1;

  mindeg := m;
  isPossibe := true;

  for i:=0 to n-1 do
    begin
      degree := vertices[i].degree;
      if degree < mindeg then mindeg := degree;
      dodaj(degree,i);
    end;
  for i:=0 to n-1 do
    begin
      if  -1 <> degrees[0] then
        begin
          isPossibe := false;
          break;
        end;
      v := degrees[mindeg];
      degrees[mindeg] := vertices[degrees[mindeg]].next;
      usun(v);
      k := findFree(v);
      if edges[k].a = v
        then adj := edges[k].b
        else adj := edges[k].a;
      vertices[v].adj := adj;
      if -1 = vertices[adj].adj then
       begin
         usun(adj);
         if degrees[vertices[adj].degree] = adj then begin
           degrees[vertices[adj].degree] := vertices[adj].next;
         end;
         Dec(vertices[adj].degree);
         if vertices[adj].degree < mindeg then mindeg := vertices[adj].degree;
         dodaj(vertices[adj].degree, adj);
       end;
      edges[k].isUsed := true;
      while (mindeg < n) and (-1 = degrees[mindeg]) do begin
        Inc(mindeg);
      end;
    end;
  if isPossibe then
    begin
      WriteLn('TAK');
      for i:=0 to n-1 do WriteLn(vertices[i].adj + 1);
    end
  else WriteLn('NIE');
end.
