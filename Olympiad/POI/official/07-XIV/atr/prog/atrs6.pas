{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atrs6.pas                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe O(k*(m+n^2) + k^2*2^k)                *}
{*            (implementacja rozwiazania wzorcowego z generatorem        *}
{*            wszystkich podzbiorow w czasie O(n logn) i przy uzyciu     *}
{             algorytmu Dijkstry z uzyciem prostej listy).               *}
{*                                                                       *}
{*************************************************************************}
const INF = 1000000001;
const MaxK=20;
const MaxN=20000;
const MaxM=1000000;
const TabSize=2000001;
const BufS=351200;

type DW = record
  t, s : longint;
end;

var
  sol : array[0..BufS-1,0..MaxK-1] of longint;
  kol : array[0..BufS-1] of longint;
  kolhead : longint;
  bf : array[0..TabSize-1] of longint;
  zb : array[0..TabSize-1] of longint;
  wie : array[0..TabSize] of integer;
  kra : array[0..MaxN] of longint;
  ks : longint;
  ilezb : array[0..MaxK+1] of longint;
  odl : array[0..MaxK+2,0..MaxK+2] of longint;
  ogr : array[0..MaxK+2] of longint;
  n, m, k : longint;
  res : array[0..MaxN+1] of DW;
  h,p : array[0..MaxN+1] of longint;


function min(a, b : longint) : longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

procedure Dodaj(p,k,l : longint);
begin
  Inc(ks);
  wie[ks] := k;
  bf[ks] := l;
  zb[ks] := kra[p];
  kra[p] := ks;
end;

procedure sort(p,k : longint);
var x,i,j,y : longint;
begin
  if p < k then
  begin
    x := zb[p];
    i := p-1;
    j := k+1;
    while (true) do
    begin
      repeat
        Dec(j);
      until zb[j] <= x;
      repeat
        Inc(i);
      until zb[i] >= x;
      if i < j then 
      begin
        y := zb[i];
        zb[i] := zb[j];
        zb[j] := y;
      end else
      begin
        sort(p,j);
        sort(j+1,k);
        exit;
      end;
    end;
  end;
end;

function Bity(x : longint) : longint;
begin
    Bity := 0;
    while(x > 0) do
    begin
  Inc(Bity);
  x := x and (x-1);
    end;
end;

procedure GenZb;
var x : longint;
begin
  for x := 1 to 1 shl k do zb[x-1] := x + (Bity(x) shl MaxK);
  sort(0,(1 shl k)-1);
  for x := (1 shl k) - 1 downto 0 do zb[x] := zb[x] and ((1 shl MaxK) - 1);
end;

procedure InicjujBufor;
var x : longint;
begin
  kolhead := 0;
  for x := 0 to BufS-1 do kol[x] := x+1;
  for x := 0 to 1 shl k do bf[x] := -1;
end;

procedure DajBufor(nr : longint);
var x : longint;
begin
  if bf[nr] = -1 then
  begin
    bf[nr] := kolhead;
    for x := 0 to MaxK-1 do sol[kolhead][x] := INF;
    kolhead := kol[kolhead];
  end;
end;

procedure ZwolnijBufor(nr : longint);
begin
  if bf[nr] <> -1 then
  begin
    kol[bf[nr]] := kolhead;
    kolhead := bf[nr];
  end;
end;

procedure WczytajDane;
var x : longint;
  pk, kk, wa, g : longint;
begin
  for x := 0 to MaxN do kra[x] := -1;
  Readln(n, m, k);
  for x := 0 to m-1 do 
  begin
    Readln(pk, kk, wa);
    Dodaj(pk, kk, wa);
    Dodaj(kk, pk, wa);
  end;
  for x := 0 to k+1 do ogr[x] := 0;
  Readln(g);
  for x := 0 to g-1 do
  begin
    Readln(pk, kk);
    ogr[kk-1] := ogr[kk-1] OR (1 shl (pk-2));
  end;
end;

procedure XCh(a, b : longint);
var tmp : longint;
begin
  tmp := h[a];
  h[a] := h[b];
  h[b] := tmp;
  tmp := p[h[a]];
  p[h[a]] := p[h[b]];
  p[h[b]] := tmp;
end;

procedure Dijkstra(s : longint);
var hs,e,u,x,a : longint;
begin
  hs := n;
  for x := n downto 1 do
  begin
    h[x] := x;
    p[x] := x;
    res[x].t := INF;
  end;
  res[s].t := 0;
  XCh(1, s);
  while (hs > 1) do
  begin
    u := h[1];
    XCh(hs, 1);
    Dec(hs);
    a := 1;
    while (a shl 1) <= hs do
    begin
      a := a shl 1;
      if (a < hs) AND (res[h[a+1]].t < res[h[a]].t) then Inc(a); 
      if res[h[a shr 1]].t <= res[h[a]].t then break;
      XCh(a,a shr 1);
    end;
    x := kra[u];
    while x <> -1 do
    begin
      e := wie[x];
      if res[e].t > res[u].t + bf[x] then
      begin
        res[e].t := res[u].t + bf[x];
        res[e].s := u;
        e := p[e];
        while (e > 1) AND (res[h[e]].t < res[h[e shr 1]].t) do 
        begin
          XCh(e,e shr 1);
          e := e shr 1;
        end;
      end;
    x := zb[x];
    end;
  end;
end;

procedure LiczOdl;
var x,y : longint;
begin
  for x := 0 to k+1 do
  begin
    if x = k+1 then
      Dijkstra(n)
    else
      Dijkstra(x+1);
    for y := 0 to k+1 do 
      if y = k+1 then
        odl[x][y] := res[n].t
      else
        odl[x][y] := res[y+1].t;
  end;
end;

function Rozwiaz : longint;
var zak,x,y,z,it : longint;
begin
  zak := (1 shl k) - 1;
  for x := 0 to k-1 do if ogr[x+1] = 0 then
  begin
    DajBufor(1 shl x);
    sol[bf[1 shl x]][x] := odl[0][x+1];
  end;
  for it := 0 to zak - 1 do
  begin
    x := zb[it];
    if bf[x] <> -1 then
    begin
      for y := 0 to k-1 do if ((x AND (1 shl y)) = 0) AND ((ogr[y+1] OR x) = x) then
      begin
        for z := 0 to k-1 do if (x AND (1 shl z)) <> 0 then
        begin
          DajBufor(x OR (1 shl y));
          sol[bf[x OR (1 shl y)]][y] := min(sol[bf[x OR (1 shl y)]][y], odl[z+1][y+1] + sol[bf[x]][z]);
        end;
      end;
      if x <> zak then ZwolnijBufor(x);
    end;
  end;
  Rozwiaz := INF;
  for x := 0 to k-1 do Rozwiaz := min(Rozwiaz, sol[bf[zak]][x]+odl[x+1][k+1]);
end;

begin
  ks := 0;
  WczytajDane;
  LiczOdl;
  if k = 0 then
    WriteLn(odl[0][1])
  else
  begin
    GenZb;
    InicjujBufor;
    Writeln(Rozwiaz);
  end;
end.
