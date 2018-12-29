{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Przeprawa                                      *
 *   Plik:                prz.pas                                        *
 *   Autor:               Pawe³ Wolff                                    *
 *   Data:                2003.10.29                                     * 
 *************************************************************************}

program Przeprawa;

const
  MAX_N = 16;
  MAX_T = 50;
  DWA_DO_MAX_N = 65536;


type
  TBajtolaz =
    record
      t: integer;
      w: integer;
    end;
    
  TTabBajtolazow = array [1..MAX_N] of TBajtolaz;
  
  TTabZnacznikow = array [1..MAX_N] of boolean;
  

var
  n: integer; { liczba Bajto³azów }
  b: TTabBajtolazow; { opis Bajto³azów }
  
  w: integer; { maksymalne dopuszczalne obci±¿enie mostu }
  
  obliczonyCzas: array [0..DWA_DO_MAX_N - 1] of integer;
    { tu zapamiêtujemy obliczone ju¿ czasy przeprawy podzbiorów zbioru
      wszystkich Bajto³azów }
  

procedure WczytajDane(var z: TTabZnacznikow);
var
  i: integer;
begin
  Readln(w, n);
  for i := 1 to n do begin
    with b[i] do
      Readln(t, w);
    z[i] := true;
  end;
end;


function NajwolniejszyBajtolaz(var z: TTabZnacznikow): integer;
{ zwraca indeks najwolniejszego nieprzeprawionego Bajto³aza; je¿eli takiego
  nie ma, to zwraca 0 }
var
  i: integer;
  maxT: integer;  
begin
  maxT := 0;
  NajwolniejszyBajtolaz := 0;
  
  for i := 1 to n do
    if z[i] and (b[i].t > maxT) then begin
      NajwolniejszyBajtolaz := i;
      maxT := b[i].t;
    end;
end;


function Indeks(var z: TTabZnacznikow): longint;
{ przekszta³ca tablicê znaczników z na indeks w tablicy obliczonyCzas }
var
  ind: longint;
  i: integer;

begin
  ind := 0;
  for i := 1 to n do begin
    ind := 2 * ind;
    if z[i] then
      Inc(ind);
  end;

  Indeks := ind;
end;

function ZapamietanyWynik(var z: TTabZnacznikow): integer;
{ zwraca zapamiêtany czas przeprawy podzbioru Bajto³azów okre¶lony w tablicy z }
begin
  ZapamietanyWynik := obliczonyCzas[Indeks(z)];
end;

procedure ZapamietajWynik(var z: TTabZnacznikow; wynik: integer);
{ zapisuje (w tablicy obliczonyCzas) minimalny czas (okre¶lony w zmiennej
  wynik) przeprawy podzbioru Bajto³azów okre¶lonego w tablicy z }
begin
  obliczonyCzas[Indeks(z)] := wynik;
end;


function ObliczWynik(var z: TTabZnacznikow): integer;
{ zwraca minimalny czas przeprawy podzbioru Bajto³azów okre¶lonego w tablicy z }

  procedure WydzielGrupe(var z: TTabZnacznikow; var wynik, wagaGrupy: integer;
                         ostatniWGrupie: integer);
  { powiêksza grupê Bajto³azów (zainicjowan± w funkcji ObliczWynik)
    o Bajto³azów z podzbioru okre¶lonego przez tablicê z i o indeksach
    wiêkszych ni¿ ostatniWGrupie; robi to na wszystkie takie sposoby,
    które prowadz± do tego, ¿e wynikowa grupa (o inicjalnej sumarycznej wadze
    wagaGrupy) jest mo¿liwie jak najwiêksza (¶ci¶le rzecz bior±c - maksymalna
    w sensie inkluzji) oraz ¿e jej waga nie przekracza w (dopuszczalnego
    obci±¿enia mostu);
    dla wszystkich tak powiêkszonych grupy oblicza minimalny czas takiej
    przeprawy Bajto³azów (z podzbioru okre¶lonego przez tablicê z), ¿e
    najpierw przeprawiani s± Bajto³azi z grupy, a nastêpnie pozostali;
    przez parametr wynik przekazuje najkrótszy czas przeprawy wykonanej
    wg powy¿szego schematu }
  var
    i, wynikPom: integer;
    
  begin
    i := ostatniWGrupie + 1;
    while i <= n do begin

      { szukamy nastêpnego Bajto³aza w podzbiorze okre¶lonym przez z }
      while (i <= n) and not z[i] do
        Inc(i);
      
      if i <= n then begin { je¶li jeszcze kogo¶ (i-tego Bajto³aza) mo¿na dodaæ
                             do grupy... }
        if wagaGrupy + b[i].w <= w then begin { i na dodatek powiêkszona
	                     o niego grupa nie przeci±¿a mostu, to... }
          { dodajemy i-tego Bajto³aza do przeprawianej grupy }
          z[i] := false;
          Inc(wagaGrupy, b[i].w);
	  
	  WydzielGrupe(z, wynik, wagaGrupy, i);

          { usuwamy i-tego Bajto³aza z przeprawianej grupy }
	  z[i] := true;
          Dec(wagaGrupy, b[i].w);
        end;
        Inc(i); { rozpatrujemy nastêpnego Bajto³aza }
      end
    end;

    { sprawdzamy, czy grupa jest maksymalna... }
    i := 1;
    while (i <= n) and not (z[i] and (wagaGrupy + b[i].w <= w)) do
      Inc(i);

    if i > n then begin
      { grupa jest maksymalna... }
      wynikPom := ObliczWynik(z); { wiêc liczymy minimalny czas przeprawy
                                    reszty Bajto³azów }
      ZapamietajWynik(z, wynikPom);
      if wynikPom < wynik then
        wynik := wynikPom;
    end;
  end;

var
  i, wynik, wagaGrupy: integer;

begin
  wynik := ZapamietanyWynik(z); { mo¿e ju¿ dla takiego podzbioru Bajto³azów
                                  mamy policzony wynik? }
  if wynik <> 0 then { tak, ju¿ go policzyli¶my }
    ObliczWynik := wynik
  else begin
    { nie, teraz bêdziemy go liczyæ }
    i := NajwolniejszyBajtolaz(z);
    if i = 0 then begin { wszyscy s± przeprawieni (z definiuje zbiór pusty) }
      ZapamietajWynik(z, 0);
      ObliczWynik := 0
    end
    else begin
      wynik := MAX_N * MAX_T; { d³u¿ej ju¿ przeprawa trwaæ nie mo¿e }

      wagaGrupy := b[i].w;
      z[i] := false;
      { inicjalnie grupa sk³ada siê z najwolniejszego Bajto³aza, który
        nie zosta³ jeszcze przeprawiony }
      WydzielGrupe(z, wynik, wagaGrupy, 0);
      z[i] := true;

      ObliczWynik := b[i].t + wynik;
    end;
  end;
end;



var
  doPrzeprawienia: TTabZnacznikow; { okre¶la, który z Bajto³azów jest jeszcze
                                     nieprzeprawiony }
  i: longint;
  dwaDoN: longint;

begin
  WczytajDane(doPrzeprawienia);

  { zerujemy tablice obliczonyWynik }
  dwaDoN := 1;
  for i := 1 to n do
    dwaDoN := 2 * dwaDoN;
  for i := 0 to dwaDoN - 1 do
    obliczonyCzas[i] := 0;

  { obliczamy i zapisujemy wynik }
  Writeln(ObliczWynik(doPrzeprawienia));
end.
