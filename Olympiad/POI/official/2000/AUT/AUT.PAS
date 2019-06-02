{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: AUTOMORFIZMY                                   *}
{*   Plik:                AUT.PAS                                        *}
{*   Autor:               Krzysztof Sobusiak                             *}
{*************************************************************************}

program Automorfizmy;

const MAXN = 10000;
      MAXC = 100; { max liczba r¢¾nych nieparzystych dˆugo˜ci cykli }
      ID = 'aut';

var P : array [1..MAXN] of Word; { dana permutacja }
    C : array [1..MAXN] of Word; { liczno˜ci cykli poszczeg¢lnych dˆugo˜ci }
    K : array [1..MAXC] of record { skompresowana informacja o cyklach }
                             dlug : Word; { dˆugo˜† }
                             ile  : Word  { liczba cykli tej dˆugo˜ci }
                           end;
    n : Word;

function WyznaczCykle : Boolean;
{ wyznacza cykle permutacji, }
{ zwraca FALSE wtw gdy istnieje cykl parzystej dˆugo˜ci }
var i,j,l : Word;
begin
  WyznaczCykle:=False;
  for i:=1 to n do
    C[i]:=0;
  for i:=1 to n do
    if P[i]<>0 then begin { nowy cykl }
      l:=0;
      while P[i]<>0 do begin { przechodzimy elementy cyklu }
        j:=P[i];
        P[i]:=0;
        i:=j;
        Inc(l)
      end;
      if not Odd(l) { sprawdzamy parzysto˜† dˆugo˜ci cyklu }
        then Exit;
      Inc(C[l])
    end;
  WyznaczCykle:=True
end;

function KompresujCykle : Word;
{ kompresuje informacje o cyklach, }
{ zwraca liczb© r¢¾nych dˆugo˜ci cykli }
var i,m : Word;
begin
  m:=0;
  for i:=1 to n do
    if C[i]>0 then begin
      Inc(m);
      K[m].dlug:=i;
      K[m].ile:=C[i]
    end;
  KompresujCykle:=m
end;

function NWD(a,b : Word) : Word;
{ NWD liczony algorytmem Euklidesa }
var c : Word;
begin
  while b<>0 do begin
    c:=b;
    b:=a mod b;
    a:=c
  end;
  NWD:=a
end;

function Potega(m : LongInt) : Word;
{ wylicza 2^m mod 1000 }
const ILE_MAX = 1000;
var Cyfry : array [0..ILE_MAX-1] of Integer; { 2^Cyfry[i] mod 1000 = i }
    i,p : Word;
begin
  for i:=0 to ILE_MAX-1 do
    Cyfry[i]:=-1;
  i:=0;
  p:=1; { p = 2^i mod 1000 }
  repeat
    Cyfry[p]:=i; { zaznaczamy, ¾e p ju¾ wyst¥piˆo }
    Inc(i);
    p:=(2*p) mod ILE_MAX { namna¾amy p }
  until (i=m) { do osi¥gni©cia zadanej pot©gi }
     or (Cyfry[p]>=0); { lub do zap©tlenia }
  if i<m then { zap©tlili˜my si© }
    for i:=1 to (m-Cyfry[p]) mod (i-Cyfry[p]) do
               { wi©c trzeba przej˜† tylko kawaˆek po cyklu }
      p:=(2*p) mod ILE_MAX;
  Potega:=p
end;

var F : Text;
    i,j,cykle : Word;
    skl : LongInt;
begin
  Assign(F,ID+'.in');
  Reset(F);
  Readln(F,n);
  for i:=1 to n do
    Read(F,P[i]);
  Close(F);
  Assign(F,ID+'.out');
  Rewrite(F);
  if WyznaczCykle then begin
    skl:=0; { liczba skˆadowych }
    cykle:=KompresujCykle;
    for i:=1 to cykle do begin
      with K[i] do
        Inc(skl,LongInt(ile)*(dlug-1) div 2+
                   { oba elementy w tym samym cyklu }
                LongInt(ile)*(ile-1) div 2*dlug);
                   { elementy w r¢¾nych cyklach tej samej dˆugo˜ci }
      for j:=1 to i-1 do { elementy w cyklach o r¢¾nej dˆugo˜ci }
        Inc(skl,LongInt(K[i].ile)*K[j].ile*NWD(K[i].dlug,K[j].dlug))
    end;
    Writeln(F,Potega(skl))
  end
  else
    Writeln(F,0);
  Close(F)
end.
