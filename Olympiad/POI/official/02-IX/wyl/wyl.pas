(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Wyliczanka                                     *
 *   Plik:                wyl.pas                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************)
const NAME = 'wyl';
      MAXN = 20;

function Prime(k:Integer):Boolean;
{czy liczba k pierwsza}
var i:Integer;
begin
  for i:=2 to k-1 do
    if k mod i = 0 then begin
      Prime := False;
      Exit;
    end;
  Prime := True;
end;

function Extend(x1,b1,x2,b2:Longint):Longint;
{argumenty: 0<=x1<b1; 0<=x2<b2; b1 i b2 wzglednie pierwsze}
{wynik: liczba x taka, ze 0<=x<b1*b2, x=x1(mod b1), x=x2(mod b2)}
var solution:Longint;
begin
  solution:=x1;
  while solution mod b2 <> x2 do
    Inc(solution,b1);
  Extend:=solution;
end;

{****************** pomocnicza struktura danych ************************}
{sluzy do znajdowania kongruencji}
var A:array[1 .. MAXN] of Boolean;
    size,act:Integer;

procedure Init(k:Integer);
var i:Integer;
begin
  for i:=1 to k do A[i]:=True;
  size:=k;
  act:=1;  
end;

function Wait(k:Integer):Integer;
var counter:Integer;
begin
  counter:=0;
  repeat
    if A[act] then begin
      Inc(counter);
      if act=k then begin
        A[act]:=False;
        Break;
      end;      
    end;
    if act=size then
      act:=1
    else
      Inc(act);
  until False;
  Wait:=counter;
end;

{**********************************************************************}

function MaxPower(a,b:Integer):Integer;
{argumenty: 1<a<=b}
{wynik: najwieksza potega a mniejsza od b}
var tmp:Integer;
begin
  tmp:=a;
  while tmp<=b do tmp:=tmp*a;
  MaxPower:=tmp div a;
end;

var ModArr:array [1..MAXN] of Integer; {tablica kongruencji}

function Correct(x:Longint;n:Integer):Boolean;
{sprawdzenie poprawnosci kandydata na rozwiazanie}
var i:Integer;
begin
  for i:=1 to n do
    if x mod i <> ModArr[i] then begin
      Correct:=False;
      Exit;
    end;
  Correct:=True;
end;

var input,output:Text;
    n,i,k,max:Integer;
    x,base:Longint;
    Out:array[1..MAXN] of Integer;
begin
  Assign(input,NAME+'.in');
  Assign(output,NAME+'.out');
  Reset(input);
  Rewrite(output);
  {wczytanie danych}
  Readln(input,n);
  for i:=1 to n do begin
    Read(input,k);
    Out[n+1-k]:=i;
  end;
  {oblicznie kongruencji}
  Init(n);
  for i:=n downto 1 do
    ModArr[i]:=Wait(Out[i]) mod i;
  {znaleznienie x - kandydata na k}
  base:=1;
  x:=0;
  for i:=2 to n do
    if Prime(i) then begin
      max:=MaxPower(i,n);
      x:=Extend(x,base,ModArr[max],max);
      base:=base*max;
    end;
  {sprawdzenie poprawnosci i zapisanie wyniku}
  if Correct(x,n) then begin
    if x=0 then x:=base;
    Writeln(output,x);
  end
  else
    Writeln(output,'NIE');
  Close(input);
  Close(output);
end.
