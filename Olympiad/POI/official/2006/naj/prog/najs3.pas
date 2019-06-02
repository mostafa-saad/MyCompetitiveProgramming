(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                najs3.pas                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Rozwiazanie brutalne - zlozonosc O(n^3 m).     *
 *                                                                       *
 *************************************************************************)

program najs3;

const MAXN=600;
const MAXM=10000;
{ Wielokat }
var wx,wy: array[0..MAXN-1] of longint;
{ Fabryki }
    fx,fy,fw: array[0..MAXM-1] of longint;
    wynik, a, b, c, i, s, n, m: longint;
 
{ Wczytanie danych }
procedure wczyt;
begin
  readln(n);
  for i:=0 to n-1 do
    readln(wx[i], wy[i]);
  readln(m);
  for i:=0 to m-1 do
    readln(fx[i], fy[i], fw[i]);
end;
    
{ Znak iloczynu skalarnego wierzcholka a, wierzcholka b oraz punktu p }
function sgndet(a,b,p:longint) : longint;
begin
  sgndet := (wx[b]-wx[a]) * (fy[p]-wy[a]) - (wy[b]-wy[a]) * (fx[p]-wx[a]);
end;

begin
  wynik := -2000 * 1000 * 1000;
  wczyt;
  for a:=0 to n-1 do
    for b:=0 to a-1 do
      for c:=0 to b-1 do begin
        s:=0;
        for i:=0 to m-1 do
          if (sgndet(b,a,i) <= 0) and (sgndet(c,b,i) <= 0) and (sgndet(a,c,i) <= 0) then
             s := s + fw[i];
        if wynik < s then
          wynik := s;
      end;
  writeln(wynik);
end.
