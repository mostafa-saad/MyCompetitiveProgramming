(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Dzia³ka                                        *
 *   Plik:                dzi.pas                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************)
const NMax=2000;
      nazwa='dzi';
      
type Punkt =
  record
    wspolrzedna,glebokosc:Longint;
  end;

{ Stos punktów -> }
var stos:array[1..2*NMax] of Punkt;
    rozmiar:Integer;

procedure InicjujStos;
begin
  rozmiar:=0;
end;

function GoraStosu:Punkt;
begin
  GoraStosu:=stos[rozmiar];
end;

procedure NaStos(p:Punkt);
begin
  Inc(rozmiar);
  stos[rozmiar]:=p;
end;

function ZdejmijZeStosu:Punkt;
begin
  ZdejmijZeStosu:=stos[rozmiar];
  Dec(rozmiar);
end;
{ <- Stos punktów }
  
var glebokosc:array[0..NMax+1] of Longint;
    wejscie,wyjscie:Text;
    n,max:Longint;

procedure Kandydat(obszar:Longint);
begin
  if obszar>max then max:=obszar;
end;

{Wczytuje wiersz i poprawia tablicê g³êboko¶ci}
procedure WczytajWiersz;
var j,zakazane:Longint;
begin
  for j:=1 to n do begin
    Read(wejscie,zakazane);
    if zakazane=1 then glebokosc[j]:=0
    else Inc(glebokosc[j]);
  end;
end;

{Szuka maksymalnego prostok±ta w tablicy g³êboko¶ci}
procedure SzukajMaxa;
var j,start:Longint;
    p:Punkt;
begin
  InicjujStos;
  p.glebokosc:=0;
  p.wspolrzedna:=0;
  NaStos(p);
  for j:=1 to n+1 do begin
    start:=j;
    while glebokosc[j]<GoraStosu.glebokosc do begin
      p:=ZdejmijZeStosu;
      Kandydat(p.glebokosc*(j-p.wspolrzedna));
      start:=p.wspolrzedna;
    end;
    if GoraStosu.glebokosc<glebokosc[j] then begin
      p.wspolrzedna:=start;
      p.glebokosc:=glebokosc[j];
      NaStos(p);
    end;
  end;
end;

var i:Longint;
begin
  Assign(wejscie,nazwa+'.in');
  Reset(wejscie);
  Read(wejscie,n);
  for i:=0 to n+1 do
    glebokosc[i]:=0;
  max:=0;
  for i:=1 to n do begin
    WczytajWiersz;
    SzukajMaxa;
  end;    
  Close(wejscie);
  Assign(wyjscie,nazwa+'.out');
  Rewrite(wyjscie);
  Writeln(wyjscie,max);
  Close(wyjscie);
end.
