(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((m*sqrt(k)+k)*lg(m))                           *
 *   Opis:              Rozwiazanie powolne, sztuczka z pierwiastkiem    *
 *                                                                       *
 *************************************************************************)

program met;

const INF = 1000000000;
const CN = 300007;

{-----   Statyczne drzewo przedzia³owe   -----}

const CWD = 1048677;

type Drzewo = object
  w : Array [1..CWD] of Longint;
  wd : Longint;
  procedure czysc(n : Longint);
  function znajdz_wartosc(a : Longint) : Longint;
  procedure dodaj_przedzial(l, r, wart : Longint);
  procedure dodaj_przedzial(wierz, l, r, wart, bl, br : Longint);
  end;

procedure Drzewo.czysc(n : Longint);
  var i : Longint;
begin
  wd := 1;
  while wd < n do
    wd := wd * 2;
  for i := 1 to 2*wd-1 do { Moze to mozna wyciac }
    w[i] := 0;
end;

function Drzewo.znajdz_wartosc(a : Longint) : Longint;
  var wyn : Longint;
begin
  a := a + wd;
  wyn := 0;
  while a > 0 do
  begin
    wyn := wyn + w[a];
    if wyn > INF then
    begin
      wyn := INF;
      break;
    end;
    a := a div 2;
  end; 
  znajdz_wartosc := wyn;
end;

procedure Drzewo.dodaj_przedzial(l, r, wart : Longint);
begin
  dodaj_przedzial(1, l, r, wart, 0, wd-1);
end;

procedure Drzewo.dodaj_przedzial(wierz, l, r, wart, bl, br : Longint);
  var sr : Longint;
begin
  if (l <= br) and (bl <= r) then { Przedzia³y siê przecinaj±. }
  begin
    if (l <= bl) and (br <= r) then
    begin
      { Przedzia³ bazowy jest zawarty w dodawanym przedziale. }
      w[wierz] := w[wierz] + wart;
      if w[wierz] > INF then
        w[wierz] := INF;
    end
    else
    begin
      sr := (bl+br) div 2;
      dodaj_przedzial(2*wierz, l, r, wart, bl, sr);
      dodaj_przedzial(2*wierz+1, l, r, wart, sr+1, br);
    end;
  end;
end;

{---------------------------------------------}

type Zapytanie = object
  l, r, a : Longint;
  end;

{---------------------------------------------}

var dpm : Drzewo;
    n, m, z, i, j, sqrtz, suma, wsk, a, nzest, pop, nrp : Longint;
    pot, pStacje, nStacje, pPanstwa, nPanstwa, przed, odp : Array[0..CN-1] of Longint;
    zap : Array[0..CN-1] of Zapytanie;

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
  
  { Wczytywanie zapytañ }
  Read(z);
  for i := 0 to z-1 do
  begin
    Read(zap[i].l, zap[i].r, zap[i].a);
    Dec(zap[i].l);
    Dec(zap[i].r);
  end;

  for i := 0 to n-1 do
  begin
    przed[i] := -1;
    odp[i] := -1;
  end; 

  { Pierwsza symulacja - wyznaczenie tablicy przed. } 
  dpm.czysc(m);
  { Licznik wskazuj±cy co sqrt(z) zapytanie. }
  sqrtz := Trunc(Sqrt(z));
  for i := 0 to z-1 do {TODO do z to troche daleko?, tak, ale nie szkodzi}
    pPanstwa[i] := -1;
  for i := 0 to z-1 do
  begin
    if zap[i].l <= zap[i].r then
      dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a)
    else
    begin
      dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
      dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
    end;
    if (i+1) mod sqrtz = 0 then
    begin
      { W nastêpnym obrocie pêtli zmieni siê przedzia³. }
      nrp := i div sqrtz;
      for j := 0 to n-1 do
        if przed[j] = -1 then
        begin
          suma := 0;
          wsk := pStacje[j];
          while wsk <> -1 do
          begin
            Inc(suma, dpm.znajdz_wartosc(wsk));
            if suma >= INF then
              break;
            wsk := nStacje[wsk];
          end;
          if suma >= pot[j] then
          begin
            przed[j] := nrp; 
            nPanstwa[j] := pPanstwa[nrp];
            pPanstwa[nrp] := j;
          end;
        end;
    end;
  end;
  nrp := (z-1) div sqrtz;
  for j := 0 to n-1 do
    if przed[j] = -1 then
    begin
      suma := 0;
      wsk := pStacje[j];
      while wsk <> -1 do
      begin
        Inc(suma, dpm.znajdz_wartosc(wsk));
        if suma >= INF then
          break;
        wsk := nStacje[wsk];
      end;
      if suma >= pot[j] then
      begin
        przed[j] := nrp; 
        nPanstwa[j] := pPanstwa[nrp];
        pPanstwa[nrp] := j;
      end;
    end;

  { Druga symulacja - wyznaczanie dok³adnych odpowiedzi }
  dpm.czysc(m);
  nzest := 0;
  for i := 0 to z-1 do
  begin
    if i mod sqrtz = 0 then
      nzest := i div sqrtz;
    if zap[i].l <= zap[i].r then
      dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a)
    else
    begin
      dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
      dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
    end;

    pop := -1;
    wsk := pPanstwa[nzest];
    while wsk <> -1 do { Przegladamy pañstwa z danego zestawu }
    begin
      suma := 0;

      a := pStacje[wsk];
      while a <> -1 do
      begin
        Inc(suma, dpm.znajdz_wartosc(a));
        if suma >= INF then
          break;
        a := nStacje[a];
      end;

      if suma >= pot[wsk] then
      begin
        odp[wsk] := i;
        { Pañstwo mo¿na usun±æ z listy przetwarzanej. }
        if pop <> -1 then
          nPanstwa[pop] := nPanstwa[wsk]
        else
          pPanstwa[nzest] := nPanstwa[wsk];
      end
      else
        pop := wsk;
      wsk := nPanstwa[wsk];
    end;
  end;
  
  { Wypisanie wyniku }
  for i := 0 to n-1 do
  begin
    if odp[i] <> -1 then
      Writeln(odp[i]+1)
    else
      Writeln('NIE');
  end; 
end.
