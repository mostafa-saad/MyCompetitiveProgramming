(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo8.pas                                                  *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             DFSa. Zlozonosc O(n+m). Zostalo ono specjalnie zapisane   *
 *             przez mozliwosc przekroczenia glebokosci stosu            *
 *                                                                       *
 *************************************************************************)
const MAXN = 100000;
      MAXM = 200000;

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
    vertEdgesNum:LongInt;

procedure solve2(v: LongInt; adj: LongInt);
var akt: LongInt;
    edge: LongInt;
begin
  vertices[v].adj := adj;
  vertices[v].visited := true;
  akt := vertices[v].e;
  while -1 <> akt do begin
    edge := vertEdges[akt].edge;
    if edge <> adj then begin
      if 0 > vertices[edge].adj then begin
        solve2(edge,v);
      end
    end;
    akt := vertEdges[akt].next;
  end
end;

function solve(v: LongInt): Boolean;
var akt: LongInt;
    prev: LongInt;
    adj: LongInt;
begin
  vertices[v].visited := true;
  vertices[v].adj := -2;
  akt := vertices[v].e;
  prev := vertices[v].prev;
  while -1 <> akt do begin
    adj := vertEdges[akt].edge;
    if adj <> prev then begin
      if -1 = vertices[adj].adj then begin
        vertices[adj].prev := v;
        if solve(adj) then begin
          solve := true;
          exit;
        end
      end else begin
        solve2(adj, v);
        solve := true;
        exit;
      end
    end;
    akt := vertEdges[akt].next;
  end;
  solve := false;
end;

var n, m, i: LongInt;
    isPossibe: Boolean;
    a, b: LongInt;

begin
  vertEdgesNum := 0;
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
