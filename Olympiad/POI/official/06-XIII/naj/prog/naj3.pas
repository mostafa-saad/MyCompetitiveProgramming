(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                naj3.pas                                       *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe O(nm log n + n^3)         *
 *                                                                       *
 *************************************************************************)

program naj3;

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

{ Faza liczenia tablicy t }
procedure licz_t;
var i,j,a,b,c:longint;
begin
  for i:=0 to n-1 do begin
    for j:=0 to m-1 do
      { Wyszukujemy binarnie gdzie wpada fabryka j }
      if sgndet(i,(i-1+n) mod n,j) <> 0 then begin
        a := 1;
        b := n-1;
        while a + 1 < b do begin
          c := (a+b) div 2;
          if sgndet(i,(i+c) mod n,j) > 0 then
            b := c
          else
            a := c;
        end; 
        t[i, (i+a+1) mod n] := t[i, (i+a+1) mod n] + fw[j];
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

