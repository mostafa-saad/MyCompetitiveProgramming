(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                najs4.pas                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne, ale sprytniejsze.    *
 *                        Zlozonosc O(n^2(n+m)).                         *
 *                                                                       *
 *************************************************************************)

program najs4;

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

 { Faza liczenia tablicy t 
   Dla kazdej przekatnej liczymy te na lewo i te na prawo }
procedure licz_t;
var a,b,x,i:  longint;
begin
  for a:=0 to n-1 do
    for b:=0 to a-1 do
      for i:=0 to m-1 do begin
        x := sgndet(b,a,i);
        if x > 0 then  t[b,a] := t[b,a] + fw[i]
        else if x < 0 then t[a,b] := t[a,b] + fw[i];
      end;
end;

{ Faza liczenia wyniku }
procedure licz_wynik;
var wynik,a,b,c,x: longint;
begin
  wynik := -2000*1000*1000;
  for a:=0 to n-1 do
    for b:=0 to a-1 do
      for c:=0 to b-1 do begin
        x := suma - t[b,a] - t[c,b] - t[a,c];
        if x > wynik then
          wynik := x;
      end;
  writeln(wynik);
end;
  
begin
  wczyt;
  licz_t;
  licz_wynik;
end.
