{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gaz1.pas                                                   *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie wzorcowe. Miotla (NlogN), Y-struktura na       *}
{*            statycznym drzewie przedzialowym                           *}
{*                                                                       *}
{*************************************************************************}

type 
  pPunkt = ^punkt;
  punkt = record
    x,y,zrodlo, numer: longint;
  end;

  {procedure punkt_wypisz( p: pPunkt);
begin
  writeln('x: ',p^.x,'; y: ',p^.y,'; zrodlo: ',p^.zrodlo,'; nr:',p^.numer);
end;}

type 
  pLista = ^lista;
  lista = record
     next: pLista;
    value: longint;
  end;

function lista_push(L: pLista; v: longint): pLista;{zwraca wskaznik do zmodyfikowanej listy}
var n: pLista;
begin
  new(n);
  n^.value := v;
  n^.next := L;
  L := n;
  lista_push :=  L;
end;

function lista_pop(L: pLista): pLista;{zwraca wskaznik do zmodyfikowanej listy}
var n: pLista;
begin
  {  assert(L != NULL);}
  n := L;
  L := L^.next;
  dispose(n);
  lista_pop := L;
end;

procedure lista_print(L: pLista);
var n: pLista;
begin
  write('[');
  n := L;
  while(n <> NIL) do begin
    write(n^.value);
    if(n^.next <> NIL) then write(' ');
    n := n^.next;
  end;
  writeln(']');
end;

type
  pStaticTreeNode=^staticTreeNode;
  staticTreeNode = record
    leaf, left, right: longint;
    L : pLista; 
  end;

const staticTreeSize = (1<<(17+1));
const LEAF = 1;

type
  pStaticTree = ^staticTree;
  staticTree = record
    t: array[1..2*staticTreeSize] of staticTreeNode; {//t[0] nie zdefiniowane}
  end;

procedure staticTree_initialize(T: pStaticTree);
var s: longint;
begin
  for s := 0 to (staticTreeSize div 2)-1 do 
  begin

    T^.t[s].leaf := 0;
    T^.t[s].left := 0;
    T^.t[s].right := 0;
    T^.t[s].L := NIL;
  end;
  for s := staticTreeSize div 2 to staticTreeSize-1 do
  begin
    T^.t[s].leaf := 1;
    T^.t[s].left := 0;
    T^.t[s].right := 0;
    T^.t[s].L := NIL;
  end;
end;

procedure staticTree_add(T : pStaticTree; y, nr: longint);
var cur, prev: longint;
begin
  y := y + (staticTreeSize div 2);
  T^.t[y].L := lista_push(T^.t[y].L, nr);
  cur := y div 2;
  prev := y;
  while(cur >= 1) do begin
    if((prev mod 2) = 1) then inc(T^.t[cur].right)
    else                inc(T^.t[cur].left);
    prev := cur;
    cur := cur div 2;
  end;
end;

function staticTree_findAndRemove( T: pStaticTree; min: longint):longint ;
var
  cur,prev, ret: longint;
begin
  //zwraca pierwsza z brzegu wartosc z listy odpowiadajacej elementowi tablicy >= min
  
   cur := min+staticTreeSize div 2;
   prev := cur*2;
  if(T^.t[cur].L = NIL) then 
  begin
    {#if DB
      printf("(cur: %d; left:%d; right:%d)\n", cur,T->t[cur].left, T->t[cur].right);
#endif}
    while(cur >= 1) do
    begin
      if((T^.t[cur].right > 0) and  (prev = cur*2)) then  break;
      prev := cur;
      cur := cur div 2;
      {#if DB
      printf("(cur: %d; left:%d; right:%d)\n", cur, T->t[cur].left, T->t[cur].right);
#endif}
    end;
    {    assert(cur > 0);
#if DB
    printf("cur: %d;%d\n", cur, T->t[cur].right);
#endif}
    cur := cur*2+1;
    {#if DB
    printf("(cur: %d; left:%d; right:%d)\n", cur, T->t[cur].left, T->t[cur].right);
#endif}

    while( (T^.t[cur].leaf <> LEAF) ) do 
    begin
      if(T^.t[cur].left > 0) then
        cur := cur *2
      else begin
        {  assert(T->t[cur].right > 0);}
        cur := cur*2+1;
      end;
      {#if DB
    printf("(cur: %d; left:%d; right:%d)\n", cur, T->t[cur].left, T->t[cur].right);
#endif}
    end;
  end;
  {  assert(T->t[cur].L != NULL);}
  ret := T^.t[cur].L^.value;
  T^.t[cur].L := lista_pop(T^.t[cur].L);

  prev := cur;
  cur := cur div 2;
  while( cur >= 1) do 
  begin
    if((prev mod 2) = 1) then begin { assert(T->t[cur].right >0); }dec(T^.t[cur].right); end
    else begin               { assert(T->t[cur].left > 0);  }dec(T^.t[cur].left); end;
      prev := cur;
      cur := cur div 2;
  end;

  staticTree_findAndRemove := ret;
end;

procedure _swap(var P1,P2:punkt) ;
var x: punkt;
begin
  x := P1;
  P1 := P2;
  P2 := x;
end;

function lessEqual(var P1,P2:punkt) : boolean;
begin

  if(P1.x > P2.x) then lessEqual := false
  else
  if(P1.x = P2.x) then 
  begin
    if(P1.y <= P2.y) then lessEqual :=  false
    else lessEqual := true;
  end
  else lessEqual := true;
end;

function partition(var T: array of punkt; p,r:longint): longint; {dzieli T[p..r] wlacznie; zwraca indeks eltu podzialu}
var 
  x: punkt;
  j,i,z: longint;
begin
  j := p-1;
  z:=random(r-p+1)+p;
  _swap(T[r],T[z]);
  x := T[r];
  for i := p to r-1 do
  begin
    if(lessEqual(T[i],x)) then
    begin
      j := j+1;
      _swap(T[i],T[j]);
    end;
  end;
  _swap(T[r], T[j+1]);
  partition := j+1;
end;

procedure qsort(var T: array of punkt; p,r: longint); {sortuje T[p..r] wlacznie}
var q: longint;
begin
  if((r > p) and (r < 2000000)) then
  begin
  q := partition(T,p,r);
  qsort(T,p,q-1);
  qsort(T,q+1,r);
  end;
end;

const MAX_N = 50005;
const MAX_SIZE = 100005;

var
  N,itn:longint;
  V, copyV: array[0..2*MAX_N-1] of punkt;
  T: staticTree;
  W: array[0..MAX_N-1,0..1] of longint;
    wCount,k,nr: longint;
  odl: int64;
  s: longint;
begin

  randseed:=123;
  for s := 1 to (staticTreeSize div 2)-1 do 
  begin
        T.t[s].leaf := 0;
    T.t[s].left := 0;
    T.t[s].right := 0;
    T.t[s].L := NIL;
  end;
  for s := staticTreeSize div 2 to staticTreeSize-1 do
  begin
    T.t[s].leaf := 1;
    T.t[s].left := 0;
    T.t[s].right := 0;
    T.t[s].L := NIL;
  end;
  wCount := 0;
  {wczytaj}

  read(N);
  for itn := 0 to N-1 do
  begin
    read(V[itn].x);
    read(V[itn].y);
    copyV[itn].x := V[itn].x;
    copyV[itn].y := V[itn].y;
    V[itn].zrodlo := 1; copyV[itn].zrodlo := 1;
    copyV[itn].numer := n+1; V[itn].numer := itn+1;
  end;
  for itn := N to 2*N-1 do
  begin
    read(V[itn].x);
    read(V[itn].y);
    copyV[itn].x := V[itn].x;
    copyV[itn].y := V[itn].y;
    copyV[itn].zrodlo := 1; V[itn].zrodlo := 0;
    copyV[itn].numer := itn-N+1; V[itn].numer := itn-N+1;
  end;

    qsort(V,0,2*N-1);
  for k := 0 to 2*N-1 do
  begin
    if(V[k].zrodlo = 1) then
      staticTree_add(@T,V[k].y,V[k].numer)
    else
      begin
      nr := staticTree_findAndRemove(@T,V[k].y);

      W[wCount,0] := nr; 
      W[wCount,1] := V[k].numer;
      inc(wCount);
    end;

  end;
  odl := 0;
  for itn := 0 to N-1 do
  begin
    odl := odl + abs(copyV[W[itn,0]-1].x - copyV[W[itn,1]-1+N].x) + abs(copyV[W[itn,0]-1].y - copyV[W[itn,1]-1+N].y);
  end;
  
  writeln(odl);
  for itn := 0 to N-1 do
  begin
    writeln(W[itn,0],' ',W[itn,1]);
  end;
end.
