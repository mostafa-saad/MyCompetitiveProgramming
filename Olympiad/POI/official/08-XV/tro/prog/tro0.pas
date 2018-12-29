(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tro0.pas                                                  *
 *   Autor:    Anna Niewiarowska                                         *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************)

const MAXN=3000; //max. liczba punktow

type Point = record
  x, y: LongInt;
end;

var
  n: LongInt; //liczba punktow
  actx, acty: LongInt; //wspolrzedne akt. obrabianego punktu
  t: array[0..MAXN-1] of Point;
  wynik2: Int64;
  j: LongInt;

procedure input;
var i: LongInt;
begin
  readln(n);
  for i:=0 to n-1 do begin
    read(t[i].x);
    readln(t[i].y);
  end;
end;

(*       sortowanie      *)

//funkcja porownawcza - sortowanie biegunowe wzgledem punktu (actx, acty)
//wynik -1 (n1<n2) / 0 (n1=n2) / 1 (n1>n2)
function fpor(n1: LongInt; n2: LongInt) : LongInt;
var
  x1,x2,y1,y2: Real;
  d1,d2: Real;
begin
  x1 := t[n1].x - actx;
  x2 := t[n2].x - actx;
  y1 := t[n1].y - acty;
  y2 := t[n2].y - acty;
  if ( (x1=0) and (x2=0) ) then fpor:=0
  else if (x1=0) then fpor:=-1
  else if (x2=0) then fpor:=1
  else begin
    d1 := y1/x1;
    d2 := y2/x2;
    if (d1 < d2) then fpor:= -1
    else if (d1 > d2) then fpor:= 1
    else fpor:=0;
  end;
end;

//przywracanie wlasnosci kopca w tablicy t[shift]..t[shift+size-1] od pozycji t[shift+top]
procedure heapify(top: LongInt; size: LongInt; shift: LongInt);
var
  l: LongInt; //pozycja najwiekszego elem.
  tmpx, tmpy: LongInt;
begin
  l:=top;
  if (2*top+1<size) and (fpor(2*top+1+shift,top+shift)=1) then l:=2*top+1;
  if (2*top+2<size) and (fpor(2*top+2+shift,l+shift)=1) then l:=2*top+2;
  if (l<>top) then begin
    tmpx:=t[l+shift].x; tmpy:=t[l+shift].y;
    t[l+shift].x:=t[top+shift].x; t[l+shift].y:=t[top+shift].y;
    t[top+shift].x:=tmpx; t[top+shift].y:=tmpy;
    heapify(l,size,shift);
  end;
end;

procedure sort(nr: LongInt); //sortowanie liczb t[nr+1]..t[n-1] wzgledem t[nr]
var
  i: LongInt;
  size: LongInt;
  tmpx, tmpy: LongInt;
begin
  size:=n-nr-1;
  for i:=(size div 2) downto 0 do heapify(i,size,nr+1); //budowanie kopca
  for i:=size-1 downto 1 do begin
    tmpx:=t[nr+1].x; tmpy:=t[nr+1].y;
    t[nr+1].x:=t[nr+i+1].x; t[nr+1].y:=t[nr+i+1].y;
    t[nr+i+1].x:=tmpx; t[nr+i+1].y:=tmpy;
    heapify(0,i,nr+1);
  end;
end;

(*        koniec sortowania      *)

//wartosc bezwzgledna iloczynu wektorowego (wektory zaczepione w punkcie (0,0))
function wekt(p1: Point; p2: Point) : Int64;
var
  tmp : Int64;
  x1,x2,y1,y2 : Int64;
begin
  x1:=p1.x; x2:=p2.x; y1:=p1.y; y2:=p2.y;
  tmp := x1 * y2 - y1 * x2;
  if (tmp<0) then tmp:=tmp*(-1);
  wekt:=tmp;
end;

//oblicza 2 * (pole trojkatow o najmniejszym wierzcholku nr)
function pole(nr: LongInt) : Int64;
var
  wyniktmp: Int64; //wynik tymczasowy
  sl, sp, p: Point; //punkt -- suma wspolrzednych punktow na lewo/prawo
  i: LongInt;
begin
  sl.x:=0; sl.y:=0; sp.x:=0; sp.y:=0;
  wyniktmp:=0;
  for i:=nr+1 to n-1 do
    if (t[i].x>actx) or ( (t[i].x=actx) and (t[i].y<acty) ) then
      begin
        sp.x:=sp.x+t[i].x-actx;
        sp.y:=sp.y+t[i].y-acty;
      end
    else
      begin
        sl.x:=sl.x+t[i].x-actx;
        sl.y:=sl.y+t[i].y-acty;
      end;
  for i:=nr+1 to n-1 do begin
    p.x:=t[i].x-actx; p.y:=t[i].y-acty;
    wyniktmp:=wyniktmp+wekt(p,sl)+wekt(p,sp);
    if (p.x>0) or ( (p.x=0) and (p.y<0) ) then begin //punkt przechodzi z prawej na lewa
      sp.x:=sp.x-p.x; sp.y:=sp.y-p.y;
      sl.x:=sl.x+p.x; sl.y:=sl.y+p.y;
    end else begin //punkt przechodzi z lewej na prawa
      sl.x:=sl.x-p.x; sl.y:=sl.y-p.y;
      sp.x:=sp.x+p.x; sp.y:=sp.y+p.y;
    end
  end;
  pole := wyniktmp div 2; //kazdy trojkat policzony dwa razy
  //wynik jest wciaz zawyzony dwukrotnie: |iloczyn wektorowy| = 2*(pole trojkata)
  //dzieki temu wynik jest calkowity
end;


BEGIN
  input;
  wynik2:=0;
  for j:=0 to n-3 do begin
    actx := t[j].x;
    acty := t[j].y;
    sort(j);
    wynik2:=wynik2+pole(j);
  end;

  if (wynik2 mod 2 = 0) then begin write(wynik2 div 2); writeln('.0'); end
  else begin write(wynik2 div 2); writeln('.5'); end;
END.
