(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O(n * k * lg(k))                                 *
 *   Opis:              Rozwiazanie powolne - dla kazdego panstwa        *
 *                      przegladamy wszystkie opady, wyszukujac          *
 *                      binarnie liczbe "obdarowanych" stacji            *
 *                                                                       *
 *************************************************************************)

program met;

const INF = 1000000000;
const CN = 300007;

{---------------------------------------------}

type Zapytanie = object
  l, r, a : Longint;
  end;

type Para = object
  first, second : Longint;
  end;

{---------------------------------------------}

var n, m, z, i, j, wsk, nr, zostalo, wp : Longint;
    pot, pStacje, nStacje, poczatki, stacje, odp : Array[0..CN] of Longint;
    zap : Array[0..CN-1] of Zapytanie;

{ Funkcja zwraca liczbe stacji pañstwa nr pomiêdzy l i r (wiadomo, ¿e l <= r). }
function przeciecie(nr, l, r : Longint) : Longint;
var pocz, kon, bsl, bsr, il, ir, sr : Longint;
begin
  pocz := poczatki[nr];
  kon := poczatki[nr+1]-1;
{ Write('przeciecie ',nr, ' ', l, ' ', r); }
  if (pocz > kon) or (stacje[pocz] > r) or (stacje[kon] < l) then
    przeciecie := 0
  else
  begin;
    { Wyszukiwanie ir }
    if r > stacje[kon] then
      ir := kon
    else
    begin
      bsl := pocz;
      bsr := kon;
      while bsl < bsr do 
      begin
        sr := (bsl+bsr+1) div 2;
        if stacje[sr] <= r then
          bsl := sr
        else { stacje[sr] > r }
          bsr := sr-1;
      end;
      ir := bsl;
    end;
    { Wyszukiwanie il }
    if l < stacje[pocz] then
      il := pocz
    else
    begin
      bsl := pocz;
      bsr := kon;
      while bsl < bsr do 
      begin
        sr := (bsl+bsr) div 2;
        if stacje[sr] >= l then
          bsr := sr
        else { stacje[sr] < l }
          bsl := sr+1;
      end;
      il := bsl;
    end;
    przeciecie := ir - il + 1;
  end; 
{  writeln('->', przeciecie); }
end;

begin
  { Wczytywanie danych }
  Readln(n, m);
  { pStacje to tablica z pierwszymi stacjami ka¿dego pañstwa,
    a nStacje wskazuje na nastêpn± stacjê tego samego pañstwa }
  for i := 0 to n-1 do
    pStacje[i] := -1;
  for i := 0 to m-1 do
  begin
    Read(z);
    Dec(z);
    nStacje[i] := pStacje[z];
    pStacje[z] := i;
  end;
  for i := 0 to n-1 do
    Read(pot[i]);

  { W tablicy stacje s± numery wszystkich stacji, pogrupowane po pañstwach.
    Pocz±tki sektorów nale¿±cych do danego pañstwa znajduj± siê w tabliczy poczatki
    Wype³niamy te dwie tablice teraz. }
  wsk := m;
  poczatki[n] := wsk; 
  for i := n-1 downto 0 do
  begin
    nr := pStacje[i];
    while nr <> -1 do
    begin
      Dec(wsk);
      stacje[wsk] := nr;
      nr := nStacje[nr];
    end;
    poczatki[i] := wsk;
  end;

{  for i:=0 to m-1 do
    writeln('S ', stacje[i]);
  for i:=0 to n do
    writeln('P ', poczatki[i]); } 

  
  { Wczytywanie zapytañ. }
  Read(z);
  for i := 0 to z-1 do
  begin
    Read(zap[i].l, zap[i].r, zap[i].a);
    Dec(zap[i].l);
    Dec(zap[i].r);
  end;

  { Dla ka¿dego pañstwa obliczamy wielko¶æ kolejnych opadów. }
  for i := 0 to n-1 do
  begin
    zostalo := pot[i];
    odp[i] := z;
    for j :=0 to z-1 do
    begin
      if zap[j].l <= zap[j].r then
        wp := przeciecie(i, zap[j].l, zap[j].r)
      else
        wp := przeciecie(i, 0, zap[j].r) + przeciecie(i, zap[j].l, m-1);
      if wp >= (zostalo + zap[j].a - 1) div zap[j].a then
      begin
        odp[i] := j;
        break;
      end;
      Dec(zostalo, zap[j].a * wp);
    end;
  end;

  { Wypisanie wyniku. }
  for i := 0 to n-1 do
  begin
    if odp[i] < z then
      Writeln(odp[i]+1)
    else
      Writeln('NIE');
  end; 
end.
