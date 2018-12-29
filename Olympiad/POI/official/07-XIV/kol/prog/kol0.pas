{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kol0.pas                                                   *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************}
const MAXN=5000; //max. liczba wierzch.
const MAXM=1000000; //max. liczba kraw.
const INF=1000000000; //liczba wieksza niz max koszt N krawedzi

type edge = record
  edge_to: LongInt; //wierzch. docelowy
  wei: LongInt; //waga krawedzi
  next: LongInt; //kolejny wierzcholek na liscie sasiedztwa
end;

var
  n,m: LongInt; //liczba wierzcholkow i krawedzi
  edges: array[0..2*MAXM] of edge; //lista sasiedztwa
  v: array[1..MAXN] of LongInt; //lista sasiedztwa
  stays: array[1..MAXN] of LongInt; //czy wierzcholek musi pozostac (1-tak/0-nie)
  st: LongInt; //ile wierzcholkow ma zostac

  dist: array[1..MAXN] of LongInt; //odleglosci od aktualnego drzewa
  heap_pos: array[1..MAXN] of LongInt; //pozycja w kopcu
  heap: array[0..MAXN] of LongInt; //kopiec
  heap_size: LongInt; //akt. rozmiar kopca
  prev: array[1..MAXN] of LongInt; //skad przyszlismy do danego wierzcholka
  found_obligatory: LongInt; //ile obowiazkowych wierzcholkow znaleziono
  found_from: array[0..MAXN] of LongInt;
  found_to: array[0..MAXN] of LongInt; //znalezione krawedzie
  found_edges: LongInt; //liczba znalezionych krawedzi
  sum: LongInt; //suma wag dodanych krawedzi
  k:LongInt;

(************************** parsowanie wejscia **************************)

procedure input();
var
  a,b,u: LongInt;
  tmp: LongInt; //kolejna wolna poz. na l.sasiedztwa
  i: LongInt;
begin
  tmp:=0;
  ReadLn(n,m);

  for i:=1 to n do v[i]:=-1;
  for i:=0 to m-1 do begin
    ReadLn(a,b,u);
    edges[tmp].edge_to:=b;
    edges[tmp].wei:=u;
    edges[tmp].next:=v[a];
    v[a]:=tmp;
    tmp:=tmp+1;
    edges[tmp].edge_to:=a;
    edges[tmp].wei:=u;
    edges[tmp].next:=v[b];
    v[b]:=tmp;
    tmp:=tmp+1;
  end;
  Read(st);
  for i:=1 to n do stays[i]:=0;
  for i:=0 to st-1 do begin
    Read(a);
    stays[a]:=1;
  end;
end;

(************************* operacje na kopcu ************************)

//zmniejszenie odleglosci, jezeli poprzednia byla wieksza
procedure decrease_key(nr: LongInt; val: LongInt; from: LongInt);
var
  tmp: LongInt;
begin
  if (val < dist[nr]) then begin
    dist[nr]:=val;
    prev[nr]:=from;
    if (heap_pos[nr]=-1) then begin 
      heap_pos[nr]:=heap_size;
      heap[heap_size]:=nr;
      heap_size:=heap_size+1;
    end;
    tmp:=heap_pos[nr];
    while (tmp>0) and (val<dist[heap[(tmp-1) div 2]]) do begin
      heap_pos[heap[(tmp-1) div 2]]:=tmp;
      heap[tmp]:=heap[(tmp-1) div 2];
      tmp:=(tmp-1) div 2;
    end;
    heap_pos[nr]:=tmp;
    heap[tmp]:=nr;
  end;
end;

//usuniecie elementu o najmniejszej odleglosci, zwraca numer wierzcholka
function del_min(): LongInt;
var
  vv: LongInt;
  tmp: LongInt;
  nr: LongInt;
  is_end: Boolean;
  val,smallest: LongInt;
begin
  vv:=heap[0];
  heap_pos[vv]:=-1;
  heap_size:=heap_size-1;
  if (heap_size>0) then begin
    tmp:=0;
    nr:=heap[heap_size];
    is_end:=false;
    while (is_end=false) do begin
      val:=dist[nr];
      smallest:=tmp;
      if (2*tmp+1<heap_size) then
         if (dist[heap[2*tmp+1]]<val) then begin
            val:=dist[heap[2*tmp+1]];
            smallest:=2*tmp+1;
         end;
      if (2*tmp+2<heap_size) then
         if (dist[heap[2*tmp+2]]<val) then begin
          val:=dist[heap[2*tmp+2]];
          smallest:=2*tmp+2;
         end;
      if (smallest=tmp) then is_end:=true
      else begin
        heap[tmp]:=heap[smallest];
        heap_pos[heap[tmp]]:=tmp;
        tmp:=smallest;
      end;
    end;
    heap[tmp]:=nr;
    heap_pos[nr]:=tmp;
  end;
  del_min:=vv;
end;

(********************************************)


//dodaje dany wierzcholek (lub cala sciezke) do drzewa
procedure add_to_tree(nr: LongInt);
var
  next_neigh: LongInt;
begin
  if (prev[nr]<>-1) and (dist[prev[nr]]<>0) then add_to_tree(prev[nr]);
  dist[nr]:=0;
  //ewentualnie usuwa wierzcholek z kopca
  if (heap_pos[nr]<>-1) then begin
    decrease_key(nr,-1,prev[nr]);
    del_min();
    dist[nr]:=0;
  end;
  //dodaje krawedz do listy krawedzi
  if (found_obligatory>0) then begin
    found_from[found_edges]:=prev[nr];
    found_to[found_edges]:=nr;
    found_edges:=found_edges+1;
  end;
  if (stays[nr]=1) then found_obligatory:=found_obligatory+1;
  next_neigh := v[nr];
  while (next_neigh<>-1) do begin
    decrease_key(edges[next_neigh].edge_to,edges[next_neigh].wei, nr);
    next_neigh:=edges[next_neigh].next;
  end;
end;

//znajduje kolejne krawedzie do drzewa rozpinajacego
procedure find_tree();
var
  min, next_neigh: LongInt;
begin
  while (found_obligatory<st) do begin 
    min:=del_min();
    if (stays[min]=1) then begin //to byl wierzcholek 'obowiazkowy'
      sum:=sum+dist[min];
      add_to_tree(min);
    end
    else begin //to byl wierzcholek opcjonalny
      next_neigh := v[min];
      while (next_neigh<>-1) do begin
        decrease_key(edges[next_neigh].edge_to,dist[min]+edges[next_neigh].wei, min);
        next_neigh:=edges[next_neigh].next;
      end;
    end;
  end;
end;

procedure start();
var
  i,tmp: LongInt;
begin
  //inicjowanie kopca/odlegolsci itp.
  for i:=1 to n do dist[i]:=INF;
  for i:=1 to n do heap_pos[i]:=i-1;
  for i:=0 to n-1 do heap[i]:=i+1;
  heap_size:=n;
  found_edges:=0;
  found_obligatory:=0;
  sum:=0;
  tmp:=1;
  while (stays[tmp]=0) do tmp:=tmp+1;
  prev[tmp]:=-1;
  decrease_key(tmp,0,-1);
  find_tree();
end;

begin
  input();
  if (st=1) then begin 
     Writeln(0,' ',0);
  end
  else begin
    start();
    Writeln(sum,' ',found_edges);
    for k:=0 to found_edges-1 do
      Writeln(found_from[k],' ',found_to[k]);
  end;
end.
