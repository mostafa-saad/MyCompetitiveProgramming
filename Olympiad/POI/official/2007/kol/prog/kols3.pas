{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kols3.pas                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie za wolne, zlozonosc wykladnicza.               *}
{*                                                                       *}
{*************************************************************************}
const MAXN=1000; //max. liczba wierzch.
const MAXM=1000000; //max. liczba kraw.
const INF=1000000000; //liczba wieksza niz max koszt N krawedzi

type edge = record
    u,v,c:LongInt;
end;

var
  n,m: LongInt; //wierzcholki,krawedzie
  e:array[0..MAXM] of edge;
  stays:array[1..MAXN] of LongInt; //czy wierzcholek musi pozostac (1-tak/0-nie)
  st:LongInt; //ile wierzcholkow ma zostac
  not_obligatory:array[0..MAXN] of LongInt; //numery wierzcholkow, ktore nie musza byc w drzewie
  act_vertices:LongInt; //akt. liczba wierzcholkow
  cnt, min_cnt, cost, min_cost:LongInt;
  used:array[0..MAXM-1] of LongInt;
  min_used:array[0..MAXM-1] of LongInt; //numery uzytych krawedzi
  conn:array [0..MAXN] of LongInt; //numer rodzica wierzcholka w drzewie find-union skladowych


procedure input();
var
  i,tmp:LongInt;
begin
  ReadLn(n,m);
  if (n>MAXN) then while (true) do begin end; //i tak sie nie zmiesci
  for i:=1 to n do stays[i]:=0;
  for i:=0 to m-1 do Readln(e[i].u, e[i].v, e[i].c);
  Read(st);
  for i:=0 to st-1 do begin
    Read(tmp);
    stays[tmp]:=1;
  end;
  tmp:=0;
  for i:=1 to n do 
    if (stays[i]=0) then begin
      not_obligatory[tmp]:=i; 
      tmp:=tmp+1;
    end;
  act_vertices:=st;
end;

//generuje nastepny podzbior, 1-ok/0-koniec
function next_subset():LongInt;
var
  tmp: LongInt;
begin
  tmp:=0;
  while (tmp<n-st) and (stays[not_obligatory[tmp]]=2) do begin
    stays[not_obligatory[tmp]]:=0; 
    tmp:=tmp+1; 
    act_vertices:=act_vertices-1;
  end;
  if (tmp>=n-st) then next_subset:=0 //koniec
  else begin
    stays[not_obligatory[tmp]]:=2;
    act_vertices:=act_vertices+1;
    next_subset:=1;
  end;
end;

function find(a:LongInt):LongInt;
begin
  if (conn[a]=-1) then find:=a
  else begin
    conn[a] := find(conn[a]);
    find:=conn[a];
  end;
end;

procedure connect(a:LongInt; b:LongInt);
begin
  conn[find(a)]:=find(b);
end;

procedure go();
var
  left, i, u,v,c:LongInt;
begin
  min_cost:=INF; min_cnt:=0;
  while (true) do begin
    for i:=1 to n do conn[i]:=-1;
    cnt:=0;
    cost:=0;
    left:=act_vertices-1;
    for i:=0 to m-1 do begin
      u:= e[i].u; v := e[i].v; c := e[i].c;
      if (stays[u]<>0) and (stays[v]<>0) and (find(u)<>find(v)) then begin
        connect(u,v);
        used[cnt]:=i;
        cnt:=cnt+1;
        cost:=cost+c;
            left:=left-1;
      end;
    end;
    //czy to bylo optymalne rozwiazanie (o ile bylo)
    if (left=0) and (cost<min_cost) then begin
      min_cost:=cost;
      min_cnt:=cnt;
      for i:=0 to cnt-1 do min_used[i]:=used[i];
    end;
    //kolejny krok
    if (next_subset()=0) then break;
  end;
end;

procedure write();
var
  i:LongInt;
begin
    Writeln(min_cost,' ', min_cnt);
    for i:=0 to min_cnt-1 do Writeln(e[min_used[i]].u,' ', e[min_used[i]].v);
end;

procedure heapify(num: LongInt; size: LongInt);
var
  l: LongInt; //pozycja najwiekszego elem.
  tmp1, tmp2, tmp3: LongInt;
begin
  l:=num;
  if (2*num+1<size) and (e[2*num+1].c>e[num].c) then l:=2*num+1;
  if (2*num+2<size) and (e[2*num+2].c>e[l].c) then l:=2*num+2;
  if (l<>num) then begin
    tmp1:=e[l].u; tmp2:=e[l].v; tmp3:=e[l].c;
    e[l].u:=e[num].u; e[l].v:=e[num].v; 
    e[l].c:=e[num].c;
    e[num].u:=tmp1; e[num].v:=tmp2; e[num].c:=tmp3;
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
    tmp1:=e[0].u; tmp2:=e[0].v; tmp3:=e[0].c;
    e[0].u:=e[i].u; e[0].v:=e[i].v; e[0].c:=e[i].c;
    e[i].u:=tmp1; e[i].v:=tmp2; e[i].c:=tmp3;
    heapify(0,i);
  end;
end;


begin
  input();
  if (st=1) then begin
    Writeln(0,' ',0);
  end
  else begin
    heap_sort(m);
    go();
    write();
  end;
end.
