(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tros1.pas                                                 *
 *   Autor:    Anna Niewiarowska                                         *
 *   Opis:     Rozwiazanie nieoptymalne.                                 *
 *                                                                       *
 *************************************************************************)

const MAXN=3000; //max. liczba punktow

type Point = record
  x, y: LongInt;
end;

var
  n: LongInt; //liczba punktow
  t: array[0..MAXN-1] of Point;
  wynik: Int64;
  j,k,l: LongInt;

procedure input;
var i: LongInt;
begin
  readln(n);
  for i:=0 to n-1 do begin
    read(t[i].x);
    readln(t[i].y);
  end;
end;

function abs(x: Int64) :Int64;
begin
  if (x<0) then x:=(-1)*x;
  abs:=x;
end;

BEGIN
  input;
  wynik:=0;
  for j:=0 to n-1 do
    for k:=j+1 to n-1 do
      for l:=k+1 to n-1 do
        wynik:=wynik+abs((t[k].x - t[j].x) * (t[l].y - t[j].y) -
                   (t[l].x - t[j].x) * (t[k].y - t[j].y));

if (wynik mod 2 = 0) then begin write(wynik div 2); writeln('.0'); end
  else begin write(wynik div 2); writeln('.5'); end;

END.
