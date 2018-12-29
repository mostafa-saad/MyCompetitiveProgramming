{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kols2.pas                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie za wolne, zlozonosc O(n^3).                    *}
{*                                                                       *}
{*************************************************************************}
const MAXN=1000; //max. liczba wierzch.
const MAXM=1000000; //max. liczba kraw.
const INF=1000000000; //liczba wieksza niz max koszt N krawedzi

type edge = record
  from, edge_to, cost: LongInt;
end;

var
  n,m:LongInt; //liczba wierzcholkow i krawedzi
  edges: array[1..MAXN,1..MAXN] of LongInt; //tablica najkrotszych sciezek
  prev:array[1..MAXN,1..MAXN] of LongInt; //tablica nastepnikow do sciezek
  used:array[1..MAXN,1..MAXN] of LongInt; //czy dana krawedz zostala uzyta(1-tak,0-nie)
  e:array[0..( (MAXN*(MAXN-1)) div 2)] of edge; //sciezki, posortowane zwn. dlugosc
  stays:array[1..MAXN] of LongInt; //czy wierzcholek musi pozostac (1-tak/0-nie)
  st:LongInt; //ile wierzcholkow ma zostac
  conn:array[1..MAXN] of LongInt; //numer rodzica wierzcholka w drzewie find-union skladowych
  cost,cnt: LongInt; //laczny koszt, liczba uzytych krawedzi
  left: LongInt; //ile jest rozlacznych 'czarnych' skladowych

(************************ wejscie / wyjscie *************************)

procedure input();
var
  v1,v2,c: LongInt;
  i,j: LongInt;
begin
  ReadLn(n,m);
  if (n>MAXN) then while (true) do begin end; //i tak sie nie zmiesci
  for i:=1 to n do
    for j:=1 to n do begin
      edges[i][j]:=INF;
      prev[i][j]:=-1;
    end;
  for i:=1 to n do begin
    edges[i][i]:=0;
    prev[i][i]:=i;
  end;
  for i:=0 to m-1 do begin
    ReadLN(v1,v2,c);
    edges[v1][v2]:=c;
    prev[v1][v2]:=v2;
    edges[v2][v1]:=c;
    prev[v2][v1]:=v1;
  end;
  Read(st);
  for i:=1 to n do stays[i]:=0;
  for i:=0 to st-1 do begin
    Read(v1);
    stays[v1]:=1;
  end;
end;

procedure write();
var
  i,j:LongInt;
begin
    Writeln(cost, ' ', cnt);
    for i:=1 to n do
      for j:=i+1 to n do
        if (used[i][j]=1) then Writeln(i, ' ', j);
end;

(******************************************************************)

function find(a:LongInt):LongInt;
begin
  if (conn[a]=-1) then find:=a
  else begin
    conn[a] := find(conn[a]);
    find:=conn[a];
  end
end;

procedure connect(a:LongInt; b:LongInt);
begin
    conn[find(a)]:=find(b);
end;

procedure min_dist();
var i,j,k:LongInt;
begin
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        if (edges[i][k]+edges[k][j]<edges[i][j]) then begin
          edges[i][j]:=edges[i][k]+edges[k][j];
          prev[i][j]:=prev[i][k];
        end;
end;

procedure add_path(v1:LongInt; v2:LongInt);
var
  k: LongInt;
begin
  if (v1<>v2) then begin
    k:=prev[v1][v2];
    if (k<>-1) then begin
      if (used[v1][k]=0) then begin
        used[v1][k]:=1;
        used[k][v1]:=1;
        cost:=cost+edges[v1][k];
        cnt:=cnt+1;
      end;
      add_path(k,v2);
    end;
  end;
end;

procedure heapify(num: LongInt; size: LongInt);
var
  l: LongInt; //pozycja najwiekszego elem.
  tmp1, tmp2, tmp3: LongInt;
begin
  l:=num;
  if (2*num+1<size) and (e[2*num+1].cost>e[num].cost) then l:=2*num+1;
  if (2*num+2<size) and (e[2*num+2].cost>e[l].cost) then l:=2*num+2;
  if (l<>num) then begin
    tmp1:=e[l].from; tmp2:=e[l].edge_to; tmp3:=e[l].cost;
    e[l].from:=e[num].from; e[l].edge_to:=e[num].edge_to; 
    e[l].cost:=e[num].cost;
    e[num].from:=tmp1; e[num].edge_to:=tmp2; e[num].cost:=tmp3;
    heapify(l,size);
  end;
end;

procedure heap_sort(size: LongInt);
var
  i: LongInt;
  tmp1, tmp2, tmp3: LongInt;
begin
  for i:=(size div 2) downto 0 do heapify(i,size); //budowanie kopca
  for i:=size-1 downto 1 do begin
    tmp1:=e[0].from; tmp2:=e[0].edge_to; tmp3:=e[0].cost;
    e[0].from:=e[i].from; e[0].edge_to:=e[i].edge_to; 
    e[0].cost:=e[i].cost;
    e[i].from:=tmp1; e[i].edge_to:=tmp2; e[i].cost:=tmp3;
    heapify(0,i);
  end;
end;

procedure find_tree();
var
  act: LongInt;
  i,j: LongInt;
  v1,v2: LongInt;
begin
  act:=0;
  for i:=1 to n do
    for j:=i+1 to n do
      if (stays[i]=1) and (stays[j]=1) then begin
          e[act].from:=i;
          e[act].edge_to:=j;
          e[act].cost:=edges[i][j];
          act:=act+1;
      end;
  heap_sort(act);  //sortuje act elementow tablicy e
  left:=st-1;
  for i:=1 to n do conn[i]:=-1;
  for i:=1 to n do for j:=1 to n do used[i][j]:=0;
  for i:=0 to act-1 do begin
  v1 := e[i].from;
        v2 := e[i].edge_to;
  if (find(v1)<>find(v2)) then begin
      connect(v1,v2);
            add_path(v1,v2);
            left:=left-1;
            if (left=0) then break;
  end;
  end;
end;


begin
  cost:=0;
  cnt:=0;
  input(); //wczytanie krawedzi
  if (st=1) then begin
    Writeln(0,' ',0);
  end
  else begin
    min_dist(); //obliczenie min. odl. miedzy kazda para wierzchoklow
    find_tree(); //znalezienie drzewa rozpinajacego
    write();
  end;
end.
