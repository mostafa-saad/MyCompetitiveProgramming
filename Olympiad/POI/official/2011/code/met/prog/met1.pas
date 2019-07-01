(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((n*lg(n)+(m+k)*lg(m))*lg(k))                   *
 *   Opis:              Rozwiazanie wzorcowe                             *
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
  Inc(a, wd); {  a := a + wd; }
  wyn := 0;
  while a > 0 do
  begin
    Inc(wyn, w[a]); {wyn := wyn + w[a];}
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
      Inc(w[wierz], wart); {w[wierz] := w[wierz] + wart;}
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

type Para = object
  first, second : Longint;
  end;

{---------------------------------------------}


procedure QuickSort(var A: Array of Para; Lo, Hi: Longint);

procedure Sort(l, r: Longint);
var
  i, j: Longint;
  x, y: Para;
begin
  i := l; j := r; x := a[l+Random(r-l+1)];
  repeat
    while a[i].first < x.first do i := i + 1;
    while x.first < a[j].first do j := j - 1;
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;

begin {QuickSort};
  Sort(Lo,Hi);
end;

procedure Sort(var tab : Array of Para; l : Longint);

var tmp : Array [0..CN-1] of Para;

  procedure Mergesort(p, k : Longint);
  var sr, i, j, l : Longint;
  begin
    if p < k then
    begin
      sr := (p+k) div 2;
      Mergesort(p, sr);
      Mergesort(sr+1, k);

      {-- Scalanie --}
      i := p;
      j := sr+1;
      l := 0;
      while (i <= sr) and (j <= k) do
      begin
        if tab[i].first <= tab[j].first then
        begin
          tmp[l] := tab[i];
          Inc(i);
        end
        else
        begin
          tmp[l] := tab[j];
          Inc(j);
        end;
        Inc(l);
      end;
      while i <= sr do
      begin
        tmp[l] := tab[i];
        Inc(i);
        Inc(l);
      end;
      while j <= k do
      begin
        tmp[l] := tab[j];
        Inc(j);
        Inc(l);
      end;
      {-- Przepisanie --}
      for i:=0 to l-1 do
      begin
        tab[p+i] := tmp[i];
      end;
    end; 
  end;

begin
  Mergesort(0, l-1);
end;

{---------------------------------------------}

var dpm : Drzewo;
    n, m, z, i, l, wsk, suma, nr, tmp : Longint;
    pot, pStacje, nStacje : Array[0..CN-1] of Longint;
    zap : Array[0..CN-1] of Zapytanie;
    przed, srodki : Array[0..CN-1] of Para;

begin
  Randomize;
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

  { Wspólne wyszukiwanie binarne }
  for i := 0 to n-1 do
  begin
    przed[i].first := 0;
    przed[i].second := z;
  end;
  
  while true do
  begin
    l := 0;
    for i := 0 to n-1 do
      if przed[i].first <> przed[i].second then 
      begin
        srodki[l].first := (przed[i].first + przed[i].second) div 2;
        srodki[l].second := i;
        Inc(l);
      end;
    if l = 0 then
      break;
    QuickSort(srodki, 0, l-1); 
    wsk := 0;
    { Symulacja }
    dpm.czysc(m); 
    i := 0;
    while (i < z) and (wsk < l) do
    begin

      if zap[i].l <= zap[i].r then
        dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a)
      else
      begin
        dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
        dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
      end;
      while (wsk < l) and (srodki[wsk].first = i) do { jak ktos tu napisze if to trzeba go wyciac }
      begin
        tmp := srodki[wsk].second;
        suma := 0;
        nr := pStacje[tmp];
        while nr <> -1 do
        begin
          Inc(suma, dpm.znajdz_wartosc(nr));
          if suma >= INF then
            break;
          nr := nStacje[nr];
        end;
        if pot[tmp] <= suma then { Liczba meteorytów jest nie mniejsza ni¿ potrzebna pañstwu nr. }
          przed[tmp].second := i
        else
          przed[tmp].first := i+1;
        Inc(wsk);
      end; 
    Inc(i);
    end;
  end; 

  { Wypisanie wyniku }
  for i := 0 to n-1 do
  begin
    if przed[i].first < z then
      Writeln(przed[i].first+1)
    else
      Writeln('NIE');
  end; 
end.
