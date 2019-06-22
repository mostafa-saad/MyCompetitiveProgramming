(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                naj4.pas                                       *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe O(nm log n + n^3)         *
 *                                                                       *
 *************************************************************************)

program naj4;

const MAXN=600;
const MAXM=10000;

var {Wielokat i fabryki}
    wx,wy:array[0..MAXN-1] of longint;
    fx,fy,fw:array[0..MAXM-1] of longint;
    n,m:longint;
   { Tablica t --- ile jest w otwartej polowce 
   od a do b (a+1,...,b-1) }
   t:array[0..MAXN-1,0..MAXN-1] of longint;
   { Suma zyskow }
   suma:longint;
   { Wierzcholki do posortowania }
   pom:array[0..MAXM-1] of longint;
   pomcnt,aktstart:longint;

{ Wczytanie danych }
procedure wczyt;
var i:longint;
begin
  read(n);
  for i:=0 to n-1 do
    read(wx[i],wy[i]);
  read(m);
  for i:=0 to m-1 do
  begin
    read(fx[i],fy[i],fw[i]);
    suma := suma + fw[i];
  end;
end;

{ Znak iloczynu skalarnego wierzcholka a, wierzcholka b oraz punktu p }
function sgndet(a,b,p:longint) : longint;
begin
  sgndet := (wx[b]-wx[a]) * (fy[p]-wy[a]) - (wy[b]-wy[a]) * (fx[p]-wx[a]);
end;
{ Oraz wierzcholka a i punktow p1 i p2 }
function sgndet2(a,p1,p2:longint) : longint;
begin
  sgndet2 := (fx[p1]-wx[a]) * (fy[p2]-wy[a]) - (fy[p1]-wy[a]) * (fx[p2]-wx[a]);
end;

procedure zamien(a,b:longint);
var e:longint;
begin
  e := pom[a];
  pom[a] := pom[b];
  pom[b] := e;
end;

procedure qsort(p,k:longint);
var a,b,w:longint;
begin
  w := pom[(p+k) div 2];
  a := p;
  b := k;
  while a <= b do begin
    while sgndet2(aktstart, w, pom[a]) > 0 do inc(a);
    while sgndet2(aktstart, w, pom[b]) < 0 do dec(b);
    if a <= b then begin
      zamien (a,b);
      inc(a);
      dec(b);
    end;
  end;
  if p < b then qsort(p,b);
  if a < k then qsort(a,k);
end;

{ Faza liczenia tablicy t }
procedure licz_t;
var i,j,a:longint;
begin
  for i:=0 to n-1 do begin
    pomcnt:=0;
    aktstart:=i;
    for j:=0 to m-1 do 
      if sgndet(i, (i-1+n) mod n, j) <> 0 then begin
        pom[pomcnt]:=j;
        inc(pomcnt);
      end;
    qsort(0,pomcnt-1);
    a:=2;
    for j:=0 to pomcnt-1 do begin
      while sgndet(i,(i+a) mod n,pom[j]) <= 0 do inc(a);
      t[i, (i+a) mod n] := t[i, (i+a) mod n] + fw[pom[j]];
    end;
    for j:=1 to n-2 do 
      t[i, (i+j+1) mod n] := t[i, (i+j+1) mod n] + t[i, (i+j) mod n];
  end;
end;

{ Faza liczenia wyniku }
procedure licz_wynik;
var wynik,a,b,c,x:longint;
begin
  wynik := -2000*1000*1000;
  for a:=0 to n-1 do
    for b:=0 to a-1 do
      for c:=0 to b-1 do begin
        x := suma - t[b,a] - t[c,b] - t[a,c];
        if wynik < x then
          wynik := x;
      end;
 writeln(wynik);
end;

begin
  wczyt;
  licz_t;
  licz_wynik;
end.

