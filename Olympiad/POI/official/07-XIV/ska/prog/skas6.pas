{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skas6.pas                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie wolniejsze od wzorcowego, o zlozonosci         *}
{*            obliczeniowej O(n * 2^n)                                   *}
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

procedure wczytaj;
var i: longint;
begin
  read(n);
  for i:=0 to n-1 do
    read(x[i],y[i],waga[i]);
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

procedure licz(poz,koszt,x1,x2,y1,y2:longint);
var i:longint;
begin
  if (x2-x1+y2-y1)>obwod then
    exit;
  if (x2-x1+y2-y1=obwod) and (koszt>koszt_przestawiania) then
    exit;
  if (poz=n) then
  begin
    obwod:=x2-x1+y2-y1;
    koszt_przestawiania:=koszt;
    for i:=0 to n-1 do
      przestaw[i]:=stan[i];  
  end else
  begin
    stan[poz]:=0;
    licz(poz+1,koszt,min(x1,x[poz]),max(x2,x[poz]),min(y1,y[poz]),max(y2,y[poz]));
    stan[poz]:=1;
    licz(poz+1,koszt+waga[poz],min(x1,y[poz]),max(x2,y[poz]),min(y1,x[poz]),max(y2,x[poz]));
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
  wczytaj();
  obwod:=2*(MAX_ZAKRES+1);
  licz(0,0,MAX_ZAKRES,MIN_ZAKRES,MAX_ZAKRES,MIN_ZAKRES);
  wypisz();
end.
