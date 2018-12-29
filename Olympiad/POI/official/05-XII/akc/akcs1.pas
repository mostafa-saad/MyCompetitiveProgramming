(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AKC (Akcja Komandosów)                         *
 *   Plik:                akcs1.pas                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Z³o¿ono¶æ obliczeniowa wynosi O(n^3),          *
 *                        natomiast pamiêciowa O(n). U¿yto arytmetyki    *
 *                        zmiennopozycyjnej typu double.                 *
 *                                                                       *
 *************************************************************************)

Program Akcja_komandosow_s1;
type typ=double; {typ danych zmiennoprzecinowych}

const MAXN=2000; {maksymalna liczba kol}
const epsilon=1E-5;

type punkt=record
             x,y:typ;
           end;

type kolo=record
          x,y,r:longint; {polozenie i promien}
end;

var kola:array[0..MAXN] of kolo;
n:longint; {liczba kol}
punkty:array[0..1000000] of punkt;
l_punktow:longint; {liczba_punktow w tablicy punkty}


function sqr(x:typ):typ;
begin
  sqr:=x*x;
end;

function llsqr(x:longint):longint;
begin
  llsqr:=x*x;
end;


{wartosc bezwzgledna}
function abs(x:longint):longint;
begin
  if (x>=0) then
    abs:=x
  else
    abs:=-x;
end;

{wczytywanie polozenia i promieni kolejnych kol}
procedure czytaj;
var i:longint;
begin
  readln(n);
  for i:=0 to (n-1) do
    readln(kola[i].x,kola[i].y,kola[i].r);
end;

{
   procedura to oblicza punkty przeciecia dwoch okregow,
   zakladajac ze okregi te sie przecinaja
}
procedure oblicz_przeciecie(a1,b1,r1,a2,b2,r2:longint);
var x,z,q,alfa,beta,gamma,x1,x2,y1,y2,delta:typ;
nowy:punkt;
begin
  if (b1=b2) then
  begin
    x:=(sqr(r1)-sqr(r2)+sqr(a2)-sqr(a1))/(2.0*(a2-a1));
    z:=sqrt(sqr(r1)-sqr(x-a1));
    punkty[l_punktow].x:=x;
    punkty[l_punktow].y:=b1+z;
    inc(l_punktow);
    punkty[l_punktow].x:=x;
    punkty[l_punktow].y:=b1-z;
    inc(l_punktow);
  end else
  begin
    {sprowadzenie ukladu równañ do równania kwadratowego}
    z:=(sqr(r1)-sqr(r2)+sqr(b2)-sqr(b1)+sqr(a2)-sqr(a1))/(2.0*(b2-b1));
    q:=(a1-a2)/(b2-b1);
    beta:=-2.0*a1+2.0*(z-b1)*q;   
    alfa:=1+sqr(q);
    gamma:=sqr(a1)+sqr(z-b1)-sqr(r1);
    delta:=sqr(beta)-4.0*alfa*gamma;
  
    {rozwi±zywanie równania kwadratowego}
    x1:=(-beta+sqrt(delta))/(2.0*alfa);
    x2:=(-beta-sqrt(delta))/(2.0*alfa);
    y1:=z+q*x1;
    y2:=z+q*x2;
    {wybieram skrajnie prawy punkt przeciecia 2 kol}
    nowy.x:=x1; nowy.y:=y1;
    punkty[l_punktow]:=nowy;
    inc(l_punktow);
    nowy.x:=x2; nowy.y:=y2;
    punkty[l_punktow]:=nowy;
    inc(l_punktow);
  end;
end;


{funkcja ta sprawdza czy kola o numerach i oraz j sie przecinaja,
  a jesli tak, to dopisuje punkty przeciecia do tablicy punkty
}
procedure przeciecie(i,j:longint);
var  a1,b1,r1,a2,b2,r2,dist:longint;
begin
  a1:=kola[i].x; b1:=kola[i].y; r1:=kola[i].r;
  a2:=kola[j].x; b2:=kola[j].y; r2:=kola[j].r;
  {kwadrat odleglosci miedzy srodkami okregow}
  dist:=llsqr(a1-a2)+llsqr(b1-b2);
  if (dist<=llsqr(r1+r2)) and (dist>llsqr(r1-r2)) then
    oblicz_przeciecie(a1,b1,r1,a2,b2,r2);
end;


procedure dodaj_przeciecia(i:longint);
var j:longint;
begin
  {dodaje srodek i-tego kola}
  punkty[l_punktow].x:=kola[i].x;
  punkty[l_punktow].y:=kola[i].y;
  inc(l_punktow);
  {przeciecia z wczesniejszymi kolami}
  for j:=0 to (i-1) do
    przeciecie(j,i);
end;

{funkcja ta sprawdza, czy punkt p nalezy do n-tego kola}
function nalezy(p:punkt; n:longint):boolean;
begin
   nalezy:=(sqr(p.x-kola[n].x)+sqr(p.y-kola[n].y)<=sqr(kola[n].r)+epsilon);
end;

{funkcja ta sprawdza, czy punkt p nalezy do pierwszych n kó³}
function nieNalezy(p:punkt; n:longint):boolean;
var i:longint;
b:boolean;
begin
  b:=true;
  i:=0;
  while (b and (i<n)) do
  begin
    if (not nalezy(p,i)) then 
    b:=false;
    inc(i);
  end;
  nieNalezy:=not b;
end;

{glowna procedura programu}
procedure rozwiaz;
var i,j,k:longint;
begin
  l_punktow:=1; 
  punkty[0].x:=kola[0].x;
  punkty[0].y:=kola[0].y;
  i:=1;
  while ((l_punktow>0) and (i<n)) do
  begin
    k:=0; {nowa liczba punktow}
    for j:=0 to (l_punktow-1) do
      if (nalezy(punkty[j],i)) then 
      begin
        punkty[k]:=punkty[j];
        inc(k);
      end;
    l_punktow:=k;
    dodaj_przeciecia(i);
    for j:=k to (l_punktow-1) do
      if (not nieNalezy(punkty[j],i)) then
      begin 
        punkty[k]:=punkty[j];
        inc(k);
      end;
    l_punktow:=k;
    inc(i);
  end;
  if (l_punktow>0) then
    writeln('NIE')
  else
    writeln(i);
end;

begin
  czytaj();
  rozwiaz();
end.
