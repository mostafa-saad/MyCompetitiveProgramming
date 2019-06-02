{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skas5.pas                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie wolniejsze od wzorcowego, o zlozonosci         *}
{*            obliczeniowej O(n^3)                                       *}
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

function pomiedzy(x,a,b : longint):boolean;
begin
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

{w procedurze probujemy minimalnym kosztem przestawiac kamienie, aby miescily sie
w prostokacie o rogach (x1,y1) (x2,y2)}
procedure probuj(x1,x2,y1,y2:longint);
var i, koszt, nowy_obwod : longint;
begin
  nowy_obwod:=x2-x1+y2-y1;
  if (nowy_obwod>obwod) then exit;
  koszt:=0;
  for i:=0 to n-1 do
    if pomiedzy(x[i],x1,x2) and pomiedzy(y[i],y1,y2) then
      stan[i]:=0
    else if pomiedzy(y[i],x1,x2) and pomiedzy(x[i],y1,y2) then
    begin
      stan[i]:=1;
      koszt:=koszt+waga[i];
      if (nowy_obwod=obwod) and (koszt>=koszt_przestawiania) then exit;
    end else exit;
  obwod:=nowy_obwod;
  koszt_przestawiania:=koszt;
  for i:=0 to n-1 do
    przestaw[i]:=stan[i];
end;

procedure licz;
var
  i, j, minimum, maksimum : longint;
begin
  minimum:=x[0];
  maksimum:=x[0];
  obwod:=2*(MAX_ZAKRES+1);
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
  for i:=0 to 2*n-1 do
    for j:=0 to 2*n-1 do
    begin
      probuj(minimum,maksimum,prog[i],prog[j]);
      probuj(prog[i],prog[j],minimum,maksimum);
      probuj(minimum,prog[i],prog[j],maksimum);
      probuj(prog[i],maksimum,minimum,prog[j]);
    end
end;

procedure wypisz;
var i: longint;
obwod2: longword;
begin
  obwod2:=longword(obwod)*2;
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
