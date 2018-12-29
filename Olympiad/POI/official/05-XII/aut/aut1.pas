(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                aut1.pas                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe (bez uzycia STL)          *
 *                        zamiast struktur slownikowych uzyto            *
 *                        statycznego drzewa binarnego.                  *
 *                        Zlozonosc obliczeniowa O(k*log k),             *
 *                        a pamieciowa O(k).                             *
 *                                                                       *
 *************************************************************************)

program autobus;

const  MAXK=100000;
const  BASE=1024*128; {liczba lisci w drzewie (musi bys >=MAXK)}

type przystanek=record
                x,y,p:longint {polozenie oraz liczba pasazerow}
                end;

var
n,m,k:longint; {wymiary miasta oraz liczba przystankow}
drzewo:array[0..2*BASE-1] of longint; {tablica w ktorej przechowywane jest statyczne drzewo}
przys:array[0..MAXK-1] of przystanek;{przystanki}
t:array[0..MAXK-1] of longint; {tablica pomocnicza do przenumerowania wspolrzednych}
ile:longint; {liczba elementow tablicy t}

procedure czytaj;
var i:longint;
begin
  readln(n,m,k);
  {wczytywanie przystankow}
  for i:=0 to k-1 do
    readln(przys[i].x,przys[i].y,przys[i].p);
end;

{funkcja porownujaca do sortowania przystankow}
function kryt(a,b:przystanek):boolean;
begin
 if (a.x<>b.x) then
   kryt:=a.x<b.x
 else
   kryt:=a.y<b.y;
end;

procedure quicksort(l,r:longint);
var 
  a,b:longint;
  x,y:przystanek;
begin
 a:=l; b:=r; x:=przys[(a+b) div 2];
 repeat
  while kryt(przys[a],x) do inc(a);
  while kryt(x,przys[b]) do dec(b);
  if a<=b then begin
   y:=przys[a]; przys[a]:=przys[b]; przys[b]:=y;
   inc(a); dec(b);
  end;
 until a>b;
 if a<r then quicksort(a,r);
 if l<b then quicksort(l,b);
end;

{sortowanie liczb calkowitych w tablicy t}
procedure quicksort2(l,r:longint);
var 
  a,b:longint;
  x,y:longint;
begin
 a:=l; b:=r; x:=t[(a+b) div 2];
 repeat
  while t[a]<x do inc(a);
  while x<t[b] do dec(b);
  if a<=b then begin
   y:=t[a]; t[a]:=t[b]; t[b]:=y;
   inc(a); dec(b);
  end;
 until a>b;
 if a<r then quicksort2(a,r);
 if l<b then quicksort2(l,b);
end;

function max(a,b:longint):longint;
begin
  if (a>=b) then
    max:=a
  else
    max:=b;
end;

{obliczanie wartosci w danym lisciu,
wiaze sie to z przejsciem sciezki od 
liscia do korzenia drzewa}
function val(x:longint):longint;
var wynik:longint;
begin
  x:=x+BASE; 
  wynik:=drzewo[x];
  while (x>1) do
  begin
    x:=x div 2;
    wynik:=max(wynik,drzewo[x]);
  end;
  val:=wynik;
end;


{wyszukiwanie binarne}
function szukaj(l,r,x:longint):longint;
var m:longint;
begin
  if (l=r) then 
    szukaj:=l
  else
  begin
    m:=(l+r) div 2;
    if (x<=t[m]) then
      szukaj:=szukaj(l,m,x)
    else
      szukaj:=szukaj(m+1,r,x);
  end;
end;

{usuwanie powtorzen z posortowanej tablicy t majacej ile elementow}
procedure usun_powtorzenia; 
var noweile,last,i:longint;
begin
  noweile:=0;
  last:=-1;
  for i:=0 to ile-1 do
    if (t[i]<>last) then
    begin
      last:=t[i];
      t[noweile]:=t[i];
      inc(noweile);
    end;
  ile:=noweile;
end;

{przeskalowanie wspolrzednych przystankow}
procedure przenumeruj_wspolrzedne1(var n:longint);
var i:longint;
begin
  ile:=k;
  for i:=0 to k-1 do
    t[i]:=przys[i].x;
  quicksort2(0,k-1);
  usun_powtorzenia();
  n:=ile;
  for i:=0 to k-1 do
    przys[i].x:=szukaj(0,ile-1,przys[i].x);
end;

{przeskalowanie wspolrzednych przystankow}
procedure przenumeruj_wspolrzedne2(var n:longint);
var i:longint;
begin
  ile:=k;
  for i:=0 to k-1 do
    t[i]:=przys[i].y;
  quicksort2(0,k-1);
  usun_powtorzenia();
  n:=ile;
  for i:=0 to k-1 do
    przys[i].y:=szukaj(0,ile-1,przys[i].y);
end;

{poprawianie wartosci w wezlach}
procedure przerob(wezel,l,r,a,b,x:longint);
var m:longint;
begin
  if (a<=l) and (r<=b) then
  begin
    drzewo[wezel]:=max(drzewo[wezel],x); 
  end else
  begin
    drzewo[wezel*2]:=max(drzewo[wezel],drzewo[wezel*2]);
    drzewo[wezel*2+1]:=max(drzewo[2*wezel+1],drzewo[wezel]);
    m:=l+((r-l) div 2);
    {sprawdzam czy trzeba poprawic lewe poddrzewo}
    if (a<=m) then
      przerob(2*wezel,l,m,a,b,x); 
    {sprawdzam czy trzeba poprawic prawe poddrzewo}
    if (b>m) then
      przerob(2*wezel+1,m+1,r,a,b,x);
  end;
end;

{uaktualniam wartosci na przedziale [a,b]
biorac dla kazdego punktu z tego przedzialu
maksimum z wartosci dotychczasowej oraz x}
procedure zamien(a,b,x:longint);
begin
  przerob(1,0,BASE-1,a,b,x);
end;

procedure licz;
var i,ilu:longint;
begin
  quicksort(0,k-1); {sortuje przystanki}
  przenumeruj_wspolrzedne1(n); 
  przenumeruj_wspolrzedne2(m); 
  for i:=0 to k-1 do
  begin
    ilu:=val(przys[i].y)+przys[i].p;
    zamien(przys[i].y,m-1,ilu);
  end;
  writeln(val(m-1));
end;

begin
  czytaj;
  licz;
end.
