{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skas4.pas                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie wolniejsze od wzorcowego, o zlozonosci         *}
{*            obliczeniowej O(n^2).                                      *}
{*                                                                       *}
{*************************************************************************}
const 
  MAX_N=1000000;
  MAX_WAGA=2000;
  MAX_ZAKRES=1000000000;
  MIN_ZAKRES=0;
var
n : longint; {liczba kamieni}
x, y, waga: array[0..MAX_N-1] of longint; {wspolrzedne oraz wagi kamieni}
przestaw: array[0..MAX_N-1] of longint; {wektor przestawien dla najlepszego dotychczas
                                         znalezionego wyniku}
koszt_przestawiania, obwod : longint; {najlepsze znalezione rozwiazanie}
stan: array[0..MAX_N-1] of longint; {aktualny wektor przestawien}
prog: array[0..2*MAX_N-1] of longint; {tablica pomocnicza ze wszystkimi wspolrzednymi}

procedure wczytaj;
var i: longint;
begin
  read(n);
  for i:=0 to n-1 do
    read(x[i],y[i],waga[i]);
end;

{jesli liczba b jest ujemna, zamieniamy liczbe b na -b+1}
function pomiedzy(x,a,b : longint):boolean;
begin
  if (b<0) then b:=-b-1;
  if (x>=a) and (x<=b) then pomiedzy:=true
  else pomiedzy:=false;
end;

procedure zamien(var a,b : longint);
begin
  a:=a xor b;
  b:=b xor a;
  a:=a xor b;
end;

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

{w procedurze probujemy przestawiac kamienie (bez wzgledu na koszt) tak,
aby miescily sie w prostokacie (x1,y1) (x2,y2), ale jedna z liczb x2,y2
(ktora jako podawana jako argument jest ujemna) ma nieustalona wartosc,
ktora chcemy zminimalizowac}
procedure probuj(x1,x2,y1,y2 : longint);
var i, a, b: longint;
begin
  for i:=0 to n-1 do
    if (not (pomiedzy(x[i],x1,x2) and pomiedzy(y[i],y1,y2))
        and not (pomiedzy(y[i],x1,x2) and pomiedzy(x[i],y1,y2))) then
    begin
      a:=x[i];
      b:=y[i];
      if (a>b) then zamien(a,b);
      if (x2<0) then
      begin
        if (a>=x1) and pomiedzy(b,y1,y2) then x2:=-a-1
        else if (b>=x1) and pomiedzy(a,y1,y2) then x2:=-b-1
        else exit;
      end 
      else begin
        {y2<0}
        if (a>=y1) and pomiedzy(b,x1,x2) then y2:=-a-1
        else if (b>=y1) and pomiedzy(a,x1,x2) then y2:=-b-1
        else exit;
      end
    end;
  if (x2<0) then x2:=-x2-1;
  if (y2<0) then y2:=-y2-1;
  obwod:=min(obwod,x2-x1+y2-y1);
end;

{w procedurze probujemy minimalnym kosztem przestawiac kamienie, aby miescily sie
w prostokacie o rogach (x1,y1) (x2,y2)}
procedure ustaw(x1,x2,y1,y2:longint);
var 
  i, koszt : longint;
begin
  koszt:=0;
  for i:=0 to n-1 do
  begin
    if (pomiedzy(x[i],x1,x2) and pomiedzy(y[i],y1,y2)) then
      stan[i]:=0
    else if (pomiedzy(y[i],x1,x2) and pomiedzy(x[i],y1,y2)) then
    begin
      stan[i]:=1;
      koszt:=koszt+waga[i];
      if (koszt>=koszt_przestawiania) then exit;
    end else exit;
  end;
  koszt_przestawiania:=koszt;
  for i:=0 to n-1 do
    przestaw[i]:=stan[i];
end;

procedure licz;
var
  i, minimum, maksimum : longint;
begin
  minimum:=x[0];
  maksimum:=x[0];
  for i:=0 to n-1 do
  begin
    prog[2*i]:=x[i];
    prog[2*i+1]:=y[i];
  end;

  for i:=0 to 2*n-1 do
  begin
    minimum:=min(minimum,prog[i]);
    maksimum:=max(maksimum,prog[i]);
  end;

  {najpierw obliczamy obwod optymalnego ustawienia}
  obwod:=2*(MAX_ZAKRES+1);
  for i:=0 to 2*n-1 do
  begin
    probuj(minimum,maksimum,prog[i],-prog[i]-1);
    probuj(prog[i],-prog[i]-1,minimum,maksimum);
    probuj(minimum,-minimum-1,prog[i],maksimum);
    probuj(prog[i],maksimum,minimum,-minimum-1);
  end;

  {teraz obliczamy minimalny koszt przestawienia,
  przy zachowaniu minimalnego obwodu}
  koszt_przestawiania:=MAX_N*(MAX_WAGA+1);
  for i:=0 to 2*n-1 do
  begin
    ustaw(minimum,maksimum,prog[i],prog[i]+(obwod-(maksimum-minimum)));
    ustaw(prog[i],prog[i]+(obwod-(maksimum-minimum)),minimum,maksimum);
    ustaw(minimum,minimum+(obwod-(maksimum-prog[i])),prog[i],maksimum);
    ustaw(prog[i],maksimum,minimum,minimum+(obwod-(maksimum-prog[i])));
  end
end;

procedure wypisz;
var i: longint;
obwod2 : longword;
begin
  obwod2:=obwod;
  obwod2:=obwod2*2;
  writeln(obwod2,' ',koszt_przestawiania);
  for i:=0 to n-1 do
    write(przestaw[i]);
  writeln;
end;

begin
  wczytaj;
  licz;
  wypisz;
end.
