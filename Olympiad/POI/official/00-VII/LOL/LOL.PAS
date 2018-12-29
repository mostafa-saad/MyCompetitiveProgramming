{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: LOLLOBRYGIDA                                   *}
{*   Plik:                LOL.PAS                                        *}
{*   Autor:               Marcin Sawicki                                 *}
{*************************************************************************}


{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T+,V+,X+,Y+}
{$M 16384,0,655360}

{w zaproponowanym rozwi¥zaniu wykorzystano algorytm Hore'a}

const
  RozmTabBit = 13;
    {dane przechowujemy w tablicy, kt¢rej ka¾dy fragment zawiera 2^13=8192
     liczb typu LongInt}
  RozmTab = 1 shl RozmTabBit; {8192}
  MaxN = 100000;
  IleTab = (MaxN + RozmTab - 1) div RozmTab; {13}
    {potrzebujemy 13 fragment¢w, z kt¢rych ostatni b©dzie mniejszy}
  MaskaTab = not ($FFFFFFFF shl RozmTabBit);
    {maska do obliczania indeksu w danym fragmencie tablicy}
type
  TabLInt = array [0..RozmTab - 1] of LongInt;

var
  Dane: array [0..IleTab - 1] of ^TabLInt;
  d, dd: Integer;
  n: LongInt;
  f, o: Text;

procedure InicjujDane;
var
  i: Integer;
begin
  for i := 0 to IleTab - 2 do
    New (Dane [i]);
  GetMem (Dane [IleTab - 1],
    SizeOf (LongInt) * (MaxN - (IleTab - 1) * RozmTab));
end;

procedure CzytajDane;
var
  i: LongInt;
begin
  ReadLn (f, n);
  for i := 0 to n - 1 do
    ReadLn (f, Dane [i shr RozmTabBit]^[i and MaskaTab]);
end;

procedure ZamienElementy (i1, i2: LongInt);
var
  p: LongInt;
begin
  p := Dane [i1 shr RozmTabBit]^[i1 and MaskaTab];
  Dane [i1 shr RozmTabBit]^[i1 and MaskaTab] := Dane [i2 shr RozmTabBit]^[i2 and MaskaTab];
  Dane [i2 shr RozmTabBit]^[i2 and MaskaTab] := p;
end;

function RozdzielElementy (Pocz, Kon, IndeksT: LongInt): LongInt;
var
  t, w: LongInt;
  d, g, i: LongInt;
  Srodek: LongInt;
begin
  t := Dane [IndeksT shr RozmTabBit]^[IndeksT and MaskaTab];
  d := Pocz;
  g := Kon;
    {indeks ostatniego elementu, nie musi byc dokˆadnie r¢wny Kon}
  i := Pocz;
  while i <= g do
  begin
    {niezmiennik: tablica zawiera permutacj© pocz¥tkowej swojej zawarto˜ci
     oraz:
       pod indeksami Pocz <= k < d  znajduj¥ si© elementy < t,
       pod indeksami d <= k < i znajduj¥ si© elementy = t,
       pod indeksami g < k <= Kon znajduj¥ si© elementy > t
     oraz
       Pocz <= d <= i, g <= Kon
     oraz
       d, i, g wskazuj¥ jedne z rozpatrywanych element¢w tablicy Dane,
                  tzn. d = g = i = Pocz (mod Krok) }
    w := Dane [i shr RozmTabBit]^[i and MaskaTab];
    if w = t then
      Inc (i)
    else
    if w < t then
    begin
      ZamienElementy (d, i); {mo¾e by† d = i, te¾ dziaˆa!}
      Inc (i);
      Inc (d);
    end
    else {w > t}
    begin
      ZamienElementy (i, g); {mo¾e by† g = i, te¾ dziaˆa i zaraz skoäczymy!}
      Dec (g);
    end;
  end;

  Srodek := Pocz + (Kon - Pocz) div 2;
  {Szukamy indeksu w tablicy, zawieraj¥cego t
     i mo¾liwie bliskiego ˜rodka tablicy.
   Elementy r¢wne t wypeˆniaj¥ sp¢jny obszar tablicy od d do g wˆ¥cznie.}
  if Srodek <= d then
    RozdzielElementy := d
  else
  if Srodek >= g then
    RozdzielElementy := g
  else
    RozdzielElementy := Srodek; {bo d < Srodek < g}
end;

{mediana ci¥gu posortowanego x(0)<=x(1)<=...<=x(m) to liczba x(m div 2)}

function LiczMedianePoz (Pocz, Kon, Poz: LongInt): LongInt; forward;

function LiczMediane (Pocz, Kon: LongInt): LongInt;
begin
  LiczMediane := LiczMedianePoz (Pocz, Kon, (Kon - Pocz + 1) div 2);
end;

function LongRandom (k: LongInt): LongInt;
begin
  LongRandom := (LongInt (Random (MaxInt)) +
    LongInt (MaxInt) * LongInt (Random (MaxInt))) mod k;
end;

function LiczMedianePoz (Pocz, Kon, Poz: LongInt): LongInt;
var
  m, s: LongInt;
  i: LongInt;
  IndeksT: LongInt;
  Srodek, SrPoz: LongInt;
begin
  m := Kon - Pocz + 1;
  if m = 1 then
    LiczMedianePoz := Pocz
  else
  begin
    IndeksT := LongRandom (m) + Pocz;
    Srodek := RozdzielElementy (Pocz, Kon, IndeksT);
    SrPoz := Srodek - Pocz;
    if SrPoz = Poz then
      LiczMedianePoz := Srodek
    else
    if SrPoz < Poz then
      LiczMedianePoz :=
        LiczMedianePoz (Srodek + 1, Kon, Poz - SrPoz - 1)
    else
      LiczMedianePoz :=
        LiczMedianePoz (Pocz, Srodek - 1, Poz);
  end;
end;

{--------}

var
  Med: LongInt;
  WMed: LongInt;
  IleRazy: LongInt;
  SaMniejsze: Boolean;
  SaWieksze: Boolean;
  k, w: LongInt;

begin
  Randomize;
  InicjujDane;
  Assign (f, 'LOL.IN');
  Reset (f);
  Assign (o, 'LOL.OUT');
  ReWrite (o);
  ReadLn (f, d);
  for dd := 1 to d do
  begin
    CzytajDane;
    Med := LiczMediane (0, n - 1);
    WMed := Dane [Med shr RozmTabBit]^[Med and MaskaTab];
    IleRazy := 0;
    SaMniejsze := False;
    SaWieksze := False;
    for k := 0 to n - 1 do
    begin
      w := Dane [k shr RozmTabBit]^[k and MaskaTab];
      if w = WMed then
        Inc (IleRazy)
      else
      if w > WMed then
        SaWieksze := True
      else
        SaMniejsze := True;
    end;
    if (IleRazy <= n div 2) or
      ((IleRazy = n div 2 + 1) and (n mod 2 = 1) and
        not (SaWieksze and SaMniejsze)) then
          WriteLn (o, 'TAK')
    else
      WriteLn (o, 'NIE');
  end;
  Close (f);
  Close (o);
end.
