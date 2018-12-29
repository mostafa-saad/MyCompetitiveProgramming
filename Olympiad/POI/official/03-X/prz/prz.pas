(*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Przemytnicy                                    *
 *   Plik:                prz.pas                                        *
 *   Autor:               Pawe³ Wolff                                    *
 *************************************************************************)
{$I+,R+}
{$M 1000000, 1500000}

program Przemytnicy;


const
  MAX_N = 5000;
  MAX_M = 100000; 

  INF = 2147483647;
  MAX_ODL = 500000001;


type
  TabLongintT = array [1..MAX_N] of longint;

  TabBooleanT = array [1..MAX_N] of boolean;

  { typ opisuj±cy proces przemiany metali }
  PrzemianaT = record
                 a: integer;
                 b: integer;
                 c: longint;
               end;

  TabPrzemianT = array [1..MAX_M] of PrzemianaT;

  { typ opisuj±cy krawed¼ wychodz±c± z wierzcho³ka grafu }
  KrawedzT = record
             v: integer; { numer wierzcho³ka, do którego wchodzi krawed¼ }
             w: longint; { waga krawêdzi }
           end;

  { typ opisuj±cy graf }
  GrafT = record
            poz: array [0..MAX_N] of longint;
              { indeksy w tablicy krawêdzi e; krawêdzie wychodz±ce z i-tego
                wierzcho³ka s± umieszczone pod indeksami
                poz[i-1], .., poz[i] - 1 tablicy e }

            e  : array [1..MAX_M] of KrawedzT;
              { opisy krawêdzi }
          end;


var
  n: integer;

  p: array [1..MAX_N] of longint; { cena poszczególnych metali }

  g1, g2: GrafT;


procedure SkonstruujGraf(var g: GrafT; m: longint; var przemiany: TabPrzemianT);
{ konstruuje graf g reprezentuj±cy m procesów przemian metali
  zapisanych w tablicy przemiany }
var
  i: longint;
  pom: array [1..MAX_N] of longint;
begin
  { wype³nianie tablicy g.poz }
  g.poz[0] := 1;
  for i := 1 to n do
    g.poz[i] := 0;

  for i := 1 to m do
    with przemiany[i] do
      Inc(g.poz[a]);

  for i := 1 to n do begin
    g.poz[i] := g.poz[i] + g.poz[i-1];
    pom[i] := g.poz[i-1];
  end;

  { wype³nianie tablicy g.e }
  for i := 1 to m do
    with przemiany[i] do begin
      with g.e[pom[a]] do begin
        v := b;
        w := c;
      end;
      Inc(pom[a]);
    end;
end;


procedure WczytajDane;
var
  pom: integer;
  i, m: longint;
  przemiany: TabPrzemianT;
begin
  Read(n);

  for i := 1 to n do
    Read(p[i]);

  Read(m);

  for i := 1 to m do
    with przemiany[i] do
      Read(a, b, c);

  SkonstruujGraf(g1, m, przemiany);

  for i := 1 to m do
    with przemiany[i] do begin
      pom := a;
      a := b;
      b := pom;
    end;

  SkonstruujGraf(g2, m, przemiany);
end;



procedure ZapiszWynik(wynik: longint);
begin
  Writeln(wynik);
end;


function WybierzMin(var t: TabLongintT; var flaga: TabBooleanT;
                    n: integer): integer;
{ zwraca indeks w tablicy t, pod którym znajduje siê najmniejsza warto¶æ,
  spo¶ród tych, dla których flaga ustawiona jest na true }
var
  i, min_i: integer;
  min: longint;
begin
  min := MAX_ODL + 1;
  for i := 1 to n do
    if flaga[i] and (t[i] < min) then begin
      min := t[i];
      min_i := i;
    end;

  WybierzMin := min_i;
end;


procedure Dijkstra(var g: GrafT; var odl: TabLongintT);
{ oblicza najkrótsze odleg³o¶ci w grafie g, wychodz±ce z wierzcho³ka
  o numerze 1; wynik przekazywany jest przez tablicê odl, indeksowan±
  numerami wierzcho³ków grafu }
var
  i, j: integer;
  k: longint;
  flaga: TabBooleanT;
begin
  odl[1] := 0;
  flaga[1] := true;
  for i := 2 to n do begin
    odl[i] := MAX_ODL;
    flaga[i] := true;
  end;

  for i := 1 to n do begin
    j := WybierzMin(odl, flaga, n);
    flaga[j] := false;

    if odl[j] <> MAX_ODL then
      for k := g.poz[j-1] to g.poz[j] - 1 do
        if odl[g.e[k].v] > odl[j] + g.e[k].w then
          odl[g.e[k].v] := odl[j] + g.e[k].w;
  end;
end;


function ZnajdzWynik: longint;
var
  i: integer;
  min, cena: longint;
  odl1, odl2: TabLongintT;
begin
  Dijkstra(g1, odl1);
  Dijkstra(g2, odl2);
  min := INF;
  for i := 1 to n do
    if (odl1[i] <> MAX_ODL) and (odl2[i] <> MAX_ODL) then begin
      cena := odl1[i] + (p[i] div 2) + odl2[i];
      if cena < min then
        min := cena;
    end;

  ZnajdzWynik := min;
end;


begin
  WczytajDane;
  ZapiszWynik(ZnajdzWynik);
end.
