{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: £AÑCUCH                                        *}
{*   Plik:                LAN.PAS                                        *}
{*   Autor:               PAWEL WOLFF                                    *}
{*************************************************************************}

{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+}

program Lancuch;

{ Rozwiazanie wzorcowe zadania LAN }
{ Autor: Pawel Wolff               }
{ Data : 08.01.2001                }

const
  PLIK_WE = 'LAN.IN';
  PLIK_WY = 'LAN.OUT';

  MAX_DL   = 1000;
  MAX_CYFR = 40;

  PODSTAWA = 1000000000; { 10^9 }

type
  DLiczba = array [1..MAX_CYFR] of longint;
    { DLiczba[1] - najmniej znaczaca cyfra }


procedure Przypisz(var l: DLiczba; cyfra: longint);
var i: integer;
begin
  l[1] := cyfra;
  for i := 2 to MAX_CYFR do
    l[i] := 0
end;

procedure DodajJeden(var l: DLiczba);
var i: integer;
    przenies: boolean;
begin
  i := 1;
  przenies := true;
  while przenies do begin
    Inc(l[i]);
    if l[i] >= PODSTAWA then
      l[i] := 0
    else
      przenies := false;
    Inc(i)
  end
end;

procedure Dodaj(var l1: DLiczba; var l2: DLiczba);
{ dziala takze wtedy, gdy l1 i l2 sa ta sama liczba (np. przy wywolaniu
  Dodaj(l, l) ) }
var i: integer;
    przenies: boolean;
begin
  przenies := false;
  for i := 1 to MAX_CYFR do begin
    Inc(l1[i], l2[i]);
    if przenies then
      Inc(l1[i]);
    if l1[i] >= PODSTAWA then begin
      Dec(l1[i], PODSTAWA);
      przenies := true
    end
    else
      przenies := false
  end
end;

procedure Odejmij(var l1: DLiczba; var l2: DLiczba);
{ musi byc: l1 >= l2 ! }
var i: integer;
    przenies: boolean;
begin
  przenies := false;
  for i := 1 to MAX_CYFR do begin
    Dec(l1[i], l2[i]);
    if przenies then
      Dec(l1[i]);
    if l1[i] < 0 then begin
      Inc(l1[i], PODSTAWA);
      przenies := true
    end
    else
      przenies := false
  end
end;

procedure ZapiszWynik(var p: text; var l: DLiczba);

  procedure ZapiszCyfre(var p: text; c: longint);
  var i: integer;
      d: longint;
  begin
    d := PODSTAWA div 10;
    while c < d do begin
      Write(p, '0');
      d := d div 10
    end;
    if c > 0 then
      Write(p, c)
  end;

var i: integer;
begin
  i := MAX_CYFR;
  while (i > 1) and (l[i] = 0) do
    Dec(i);
  Write(p, l[i]);
  Dec(i);
  while i > 0 do begin
    ZapiszCyfre(p, l[i]);
    Dec(i)
  end;
  Writeln(p)
end;


var we, wy: text;
    o, i, n: integer;
    dodawac: boolean;
    wynik, potega2, jedynka: DLiczba;

begin
  Assign(we, PLIK_WE);
  Reset(we);
  Readln(we, n);
  dodawac := false;
  Przypisz(wynik, 0);
  Przypisz(potega2, 1);
  for i := 1 to n do begin
    if dodawac then
      Dodaj(wynik, potega2);
    Dodaj(potega2, potega2);
    Read(we, o);
    if o = 1 then
      dodawac := not dodawac
  end;
  Close(we);
  Assign(wy, PLIK_WY);
  Rewrite(wy);
  if dodawac then begin
    DodajJeden(wynik);
    Odejmij(potega2, wynik);
    ZapiszWynik(wy, potega2)
  end
  else
    ZapiszWynik(wy, wynik);
  Close(wy)
end.
