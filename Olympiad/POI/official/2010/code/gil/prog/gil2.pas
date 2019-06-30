(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gildie (GIL)                                              *
 *   Plik:     gil2.pas                                                  *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************)


program gil;

const MN = 200100;
const MM = 500100;

type TEdge = record
    v: longint;                (* wierzcholek docelowy *)
    next: longint;        (* indeks nastepnego elementu listy lub -1 *)
end;

var
    edge: array [0..2*MM] of TEdge;
    firstEdge: array [0..MN] of longint;
    odw: array [0..MN] of longint;
    i,a,b,n,m,l: longint;
procedure go(a,gildia: longint);
var
    b:longint;
begin
    if odw[a] <> 0 then exit;
    odw[a]:=gildia;
    b:=firstEdge[a];
    while b<>-1 do
    begin
        go(edge[b].v, 3-gildia);
        b:=edge[b].next;
    end;
end;

begin
    read(n, m);
    (* inicjalizacja struktur danych *)
    for i := 0 to n do
        begin
            firstEdge[i] := -1;
            odw[i] := 0;
        end;

    l:=0;
    for i := 0 to m - 1 do
        begin
            read(a,b);
            edge[l].v := b;
            edge[l].next := firstEdge[a];
            firstEdge[a] := l;
            inc(l);
            edge[l].v := a;
            edge[l].next := firstEdge[b];
            firstEdge[b] := l;
            inc(l);
        end;
    for i := 1 to n do
        begin
            if firstEdge[i] = -1 then
            begin
                writeln('NIE');
                exit;
            end;
            go(i, 1);
        end;
    writeln('TAK');
    for i := 1 to n do
        begin
            if odw[i] = 1 then
                writeln('K')
            else
                writeln('S');
            end;
end.

