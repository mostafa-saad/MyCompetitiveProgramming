{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    ska1.pas                                                   *}
{*   Autor:   Marek Cygan, Jakub Radoszewski                             *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************}
const 
  MAX_N=1000000;
  MAX_W=2000;
  MAX_XY=1000000000;
  MIN_XY=0;

var
n: longint;
x, y, m: array[0..MAX_N-1] of longint;
przestaw: array[0..MAX_N-1] of boolean;
ktore, wyn, i, a, b, xmin, xmax, ymin, ymax, tmp : longint;

{funkcje pomocnicze}
function max(a,b:longint):longint;
begin
  if (a>=b) then max:=a 
  else max:=b;
end;

function min(a,b:longint):longint;
begin
  if (a<=b) then min:=a 
  else min:=b;
end;

procedure zamien(var a,b : longint);
begin
  a:=a xor b;
  b:=b xor a;
  a:=a xor b;
end;


procedure odczyt;
var i:longint;
begin
  read(n);
  for i:=0 to n-1 do
    read(x[i],y[i],m[i]);
end;

function miesci_sie(x, dol, gora : longint) : boolean;
begin
  if (x >= dol) and (x <= gora) then
    miesci_sie:=true
  else
    miesci_sie:=false;
end;

{Funkcja próbuje zach³annie ustawiaæ punkty tak, by zmie¶ci³y
 siê w prostok±cie [amin,amax] x [bmin,bmax].}
function licz(amin, amax, bmin, bmax : longint) : longint;
var i, wyn : longint;
begin
  wyn := 0;
  for i := 0 to n-1 do
  begin
    if miesci_sie(x[i], amin, amax) and miesci_sie(y[i], bmin, bmax) then
    begin
      przestaw[i] := false;
      continue;
    end;
    if miesci_sie(y[i], amin, amax) and miesci_sie(x[i], bmin, bmax) then
    begin
      przestaw[i] := true;
      wyn := wyn + m[i];
      continue;
    end;
    exit(MAX_W * MAX_N + 1); {nie da siê tego ustawienia uzyskaæ}
  end;
  licz:=wyn;
end;

procedure wypisz;
var i: longint;
obwod2: longword;
begin
 obwod2 := (xmax - xmin + ymax - ymin);
 obwod2 := obwod2*2;
 writeln(obwod2,' ',wyn);
  for i := 0 to n-1 do
    write(longint(przestaw[i]));
  writeln;
end;

begin
  odczyt;
  {Wyznaczamy jakiekolwiek rozwi±zanie}
  xmin := MAX_XY;
  xmax := MIN_XY;
  ymin := MAX_XY;
  ymax := MIN_XY;
  for i:=0 to n-1 do
  begin
    a := x[i];
    b := y[i];
    if (a > b) then
      zamien(a, b);
    xmin := min(xmin, a); xmax := max(xmax, a);
    ymin := min(ymin, b); ymax := max(ymax, b);
  end;

  {Szukamy najlepszego rozwi±zania - rozwa¿amy 4 przypadki}
  wyn := licz(xmin, xmax, ymin, ymax);
  ktore := 0;
  tmp := licz(ymin, ymax, xmin, xmax);
  if (tmp < wyn) then
  begin
    ktore := 1; wyn := tmp;
  end;

  tmp := licz(xmin, ymax, ymin, xmax);
  if (tmp < wyn) then
  begin
    ktore := 2; wyn := tmp;
  end;

  tmp := licz(ymin, xmax, xmin, ymax);
  if (tmp < wyn) then
  begin
    ktore := 3; wyn := tmp;
  end;

  case ktore of
    0: licz(xmin, xmax, ymin, ymax);
    1: licz(ymin, ymax, xmin, xmax);
    2: licz(xmin, ymax, ymin, xmax);
    3: licz(ymin, xmax, xmin, ymax);
  end;
 
  wypisz;
end.
