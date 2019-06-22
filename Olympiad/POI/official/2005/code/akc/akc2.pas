(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AKC (Akcja Komandosów)                         *
 *   Plik:                akc2.pas                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z³o¿ono¶æ obliczeniowa wynosi O(n*n),          *
 *                        natomiast pamiêciowa O(n). U¿yto arytmetyki    *
 *                        zmiennopozycyjnej typu extended.               *
 *                                                                       *
 *************************************************************************)

program akcja_komandosow;

type typ=extended; //typ danych zmiennoprzecinowych

const MAXN=2000; //maksymalna liczba kol
const epsilon=1E-5;

type punkt= record
            x,y:typ;
            end;

type kolo=record
             x,y,r:longint {polozenie i promien}
          end;
var kola:array [0..MAXN] of kolo;

n:longint; //liczba kol

function sqr(x:typ):typ;
begin
  sqr:=x*x;
end;

function llsqr(x:longint):longint; 
begin
  llsqr:=x*x;
end;

//aktualizuje skrajnie lewy punkt
procedure poprawPunkt(x,y:typ; var lewy:punkt);
begin
  if (x<lewy.x) then
  begin
    lewy.x:=x;
    lewy.y:=y;
  end;
end;

{
   procedura to oblicza punkty przeciecia dwoch okregow,
   zakladajac ze okregi te sie przecinaja
}
procedure dodajPrzeciecie(a1,b1,r1,a2,b2,r2:longint; var lewy:punkt);
var z,q,alfa,beta,gamma,delta,x1,x2,y1,y2:typ;
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
  if (x1>x2) then
    poprawPunkt(x1,y1,lewy)
  else
    poprawPunkt(x2,y2,lewy);
end;

//wartosc bezwzgledna
function abs(x:longint):longint; 
begin
  if (x>=0) then
    abs:=x
  else
    abs:=-x;
end;

{funkcja ta sprawdza czy kola o numerach i oraz j sie przecinaja,
  a jesli tak, to aktualizuje "lewy" punkt
}
function przeciecie(i,j:longint; var lewy:punkt):boolean;
var a1,a2,b1,b2,r1,r2,dist:longint;
begin
  a1:=kola[i].x; b1:=kola[i].y; r1:=kola[i].r;
  a2:=kola[j].x; b2:=kola[j].y; r2:=kola[j].r;
  {kwadrat odleglosci miedzy srodkami okregow}
  dist:=llsqr(a1-a2)+llsqr(b1-b2);
  {kola sa rozlaczne}
  if (dist>llsqr(r1+r2)) then
  begin
    przeciecie:=false;
  end else
  begin
    {sprawdzam skrajne prawe punkty kol}
    if (llsqr(a1+r1-a2)+llsqr(b1-b2)<=llsqr(r2)) then poprawPunkt(a1+r1,b1,lewy) else
    if (llsqr(a2+r2-a1)+llsqr(b2-b1)<=llsqr(r1)) then poprawPunkt(a2+r2,b2,lewy) else
    dodajPrzeciecie(a1,b1,r1,a2,b2,r2,lewy);
    przeciecie:=true;
  end;
end;

{wczytywanie polozenia i promieni kolejnych kol}
procedure czytaj;
var i:longint;
begin
  readln(n);
  for i:=0 to (n-1) do  
    readln(kola[i].x,kola[i].y,kola[i].r);
end;

{funkcja ta sprawdza, czy punkt p nalezy do pierwszych n kó³}
function nieNalezy(p:punkt;n:longint): boolean;
var i:longint;
begin
  for i:=0 to n-1 do
    if (sqr(p.x-kola[i].x)+sqr(p.y-kola[i].y)>sqr(kola[i].r)+epsilon) then
      exit(true);
  exit(false);
end;

{glowna procedura programu}
procedure rozwiaz;
var puste:boolean;
i,j:longint;
lewy:punkt; {najbardziej "lewy" punkt, ze wszystkich kandydatow}
begin
  puste:=false; {zmienna zawiera informacje, czy aktualne przeciecie wszystkich kol jest puste}
  i:=1;
  lewy.x:=kola[0].x+kola[0].r; 
  lewy.y:=kola[0].y;
  while ((not puste) and (i<n))  do
  begin
    for j:=0 to (i-1) do 
     if (not przeciecie(j,i,lewy)) then puste:=true; //kola sie nie przecinaja
    {wybrany punkt nie nalezy do wszystkich okregow}
    if (nieNalezy(lewy,i)) then  puste:=true;
    inc(i);
  end;
  if (not puste) then
    writeln('NIE')
  else
    writeln(i);
end;

begin
  czytaj();
  rozwiaz();
end.
