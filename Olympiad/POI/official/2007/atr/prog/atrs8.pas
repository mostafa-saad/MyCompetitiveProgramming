{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atrs8.pas                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie alternatywne O(k*n^2 + k*k!), z obcinaniem     *}
{*            szukania permutacji.                                       *}
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
  sol : longint;
  V   : array[0..MaxK] of longint;
        c : array[0..MaxK] of longint;
  pr : array[0..MaxK] of boolean;
  bestDist, curDist, taken : longint;
  perm : array [0..MaxK+3] of longint;


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

procedure CalcZb(v, k, bity : longint);
begin
  Inc(ilezb[bity]);
  if k > 0 then
  begin
    CalcZb(v shl 1, k-1, bity);
    CalcZb((v shl 1)+1, k-1, bity+1);
  end;
end;

procedure GenZb(v, k, bity : longint);
begin
  Dec(ilezb[bity]);
  zb[ilezb[bity]] := v;
  if k > 0 then
  begin
    GenZb((v shl 1)+1, k-1, bity+1);
    GenZb(v shl 1, k-1, bity);
  end;
end;

procedure GenZbN;
var x : longint;
begin
  for x := 1 to k+1 do ilezb[x] := 0;
  ilezb[1] := 1;
  CalcZb(1, k-1, 1);
  for x := 1 to k do Inc(ilezb[x+1], ilezb[x]);
  Dec(ilezb[1]);
  zb[ilezb[1]] := 1 shl k;
  GenZb(1, k-1, 1);
end;

procedure InicjujBufor;
var x : longint;
begin
  kolhead := 0;
  for x := 0 to BufS-1 do kol[x] := x+1;
  for x := 0 to 1 shl k do bf[x] := -1;
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

procedure GenPerm(pos, prev : longint);
var x, tmp : longint;
begin
    if pos = 0 then
    begin
  bestDist := min(bestDist, curDist + odl[prev][k+1]);
    end else
    begin
  for x := 1 to pos do if ((ogr[perm[x]] or taken) = taken) then
  begin
      tmp := perm[x];
      perm[x] := perm[pos];
      perm[pos] := tmp;
      taken := taken or (1 shl (perm[pos]-1));
      Inc(curDist, odl[prev][perm[pos]]);
      GenPerm(pos-1, perm[pos]);
      taken := taken xor (1 shl (perm[pos]-1));
      Dec(curDist,odl[prev][perm[pos]]);
      tmp := perm[x];
      perm[x] := perm[pos];
      perm[pos] := tmp;
  end;
    end;
end;


function Rozwiaz : longint;
var x : longint;
begin
    bestDist := INF;
    curDist := 0;
    taken := 0;
    for x := 0 to k do perm[x] := x;
    GenPerm(k, 0);
    Rozwiaz := bestDist;
end;

begin
  ks := 0;
  WczytajDane;
  LiczOdl;
  if k = 0 then
    WriteLn(odl[0][1])
  else
    Writeln(Rozwiaz);
end.
