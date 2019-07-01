(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Multidrink                                    *
 *   Autor:                Przemyslaw Horban                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe,                         *
 *                         programowanie dynamiczne                      *
 *                                                                       *
 *************************************************************************)

type
  ListaLiczb = ^ElementListy;

  ElementListy = record
    liczba: LongInt;
    nastepnik: ListaLiczb;
  end;


const
  MAKS_NUMER = 500000;

var
  liczbaKrawedzi: LongInt;
  krawedz: array[1..MAKS_NUMER, 0..1] of LongInt;

  rozmiar, ostatni: LongInt;
  E: array[1..MAKS_NUMER] of ListaLiczb;
  podlistki: array[1..MAKS_NUMER] of ListaLiczb;
  glownyListek: array[1..MAKS_NUMER] of LongInt;

  stopien: array[1..MAKS_NUMER] of LongInt;

  dlugoscSrednicy, dlugoscSciezki: LongInt;
  sciezka, srednica: array[1..MAKS_NUMER] of LongInt;
  odwiedzony: array[1..MAKS_NUMER] of Boolean;

  priorytet: array[1..MAKS_NUMER] of LongInt;


(* Wczytuje krawedzie do tablicy krawedz oraz
   ustawia zmienna rozmiar (ostatni := rozmiar). *)
procedure wczytajKrawedzie;
var
  n, i: LongInt;
begin
  readln(n);
  rozmiar := n;
  ostatni := n;
  liczbaKrawedzi := n - 1;

  for i := 1 to liczbaKrawedzi do
    readln(krawedz[i][0], krawedz[i][1]);
end;

(* Wyznacza stopnie wierzcholkow drzewa i zapisuje
   w tablicy stopien *)
procedure wyznaczStopnieDrzewa;
var
  i, u: LongInt;
begin
  for i := 1 to liczbaKrawedzi do
  begin
    u := krawedz[i][0];
    stopien[u] := stopien[u] + 1;

    u := krawedz[i][1];
    stopien[u] := stopien[u] + 1;
  end;
end;

procedure zamien(var a, b: LongInt);
var
  tmp: LongInt;
begin
  tmp := a;
  a := b;
  b := tmp;
end;

procedure dodajElement(var lista: ListaLiczb; liczba: LongInt);
var
  nowyElement: ^ElementListy;
begin
  new(nowyElement);
  nowyElement^.nastepnik := lista;
  nowyElement^.liczba := liczba;
  lista := nowyElement;
end;

function niepusta(liczby: ListaLiczb): Boolean;
begin
  niepusta := (liczby <> nil);
end;

function glowa(liczby: ListaLiczb): LongInt;
begin
  glowa := liczby^.liczba;
end;

function ogon(liczby: ListaLiczb): ListaLiczb;
begin
  ogon := liczby^.nastepnik;
end;

(* Dodaje krawedz do list sasiadow E *)
procedure dodajKrawedz(u, v: LongInt);
begin
  dodajElement(E[u], v);
  dodajElement(E[v], u);
end;

(* Dodaj pod-listek do list podlistkow *)
procedure dodajPodListek(listekGlowny, podlistek: LongInt);
begin
  dodajElement(podlistki[listekGlowny], podlistek);
end;

(* Buduje drzewo skompresowane:
   - gdy napotykamy krawedz (u, v) taka, ze stopien[u] = 1
     to patrzymy czy glownyListek[v] = -1, jesli tak,
     ustawiamy tam u i dodajemy je do grafu
     jesli nie to dodajemy u do inneListki[u] ale nie do grafu
   - w.p.p. dodajemy krawedz do grafu
   - nie robimy tego dla koncow srednicy - czyli 1 i ostatni
*)
procedure zbudujDrzewoSkompresowane;
var
  i, u, v: LongInt;
begin
  for i := 1 to liczbaKrawedzi do
  begin
    u := krawedz[i][0];
    v := krawedz[i][1];

    if stopien[u] > stopien[v] then
      zamien(u, v);

    if stopien[u] > 1 then
      dodajKrawedz(u, v)
    else if (u = 1) or (u = ostatni) then
      dodajKrawedz(u, v)
    else (* stopien[u] = 1 i nie jest na srednicy *)
    begin
      if glownyListek[v] = 0 then
      begin
        glownyListek[v] := u;
        dodajKrawedz(u, v);
      end
      else
        dodajPodListek(glownyListek[v], u);
    end;
  end;
end;


(* Przeglada wszystkie listy sasiedztwa wierzcholkow
   i liczy ich sasiadow, w drziewie skompresowanym.
   Zwraca maksymalny stopien *)
function maksStopienSkompr(): LongInt;
var
  stopien, u: LongInt;
  liczby: ^ElementListy;
begin
  maksStopienSkompr := -1;
  for u := 1 to ostatni do
  begin
    stopien := 0;

    liczby := E[u];
    while niepusta(liczby) do
    begin
      stopien := stopien + 1;
      liczby := ogon(liczby);
    end;

    if maksStopienSkompr < stopien then
      maksStopienSkompr := stopien;
  end;
end;

procedure dodajWezelSrednicy(u: LongInt);
begin
  inc(dlugoscSrednicy);
  srednica[dlugoscSrednicy] := u;
end;

(* Rekurencyjnie szuka trasy do wezla 1. *)
function prowadziDo1(u, poprzedni: LongInt): Boolean;
var
  sasiad: LongInt;
  liczby: ^ElementListy;
begin
  if u = 1 then (* Znalezlismy *)
  begin
    prowadziDo1 := true;
    dodajWezelSrednicy(u);
  end
  else
  begin
    prowadziDo1 := false;

    liczby := E[u];
    while niepusta(liczby) do
    begin
      sasiad := glowa(liczby);
      liczby := ogon(liczby);

      if (sasiad <> poprzedni) and prowadziDo1(sasiad, u) then
      begin
        dodajWezelSrednicy(u);
        prowadziDo1 := true;
        break;
      end;
    end;
  end;
end;

(* Rekurencyjnie szuka trasy do wezla 1 z ostatni
   a gdy znajdzie zapisuje, ja w tablicy srednica,
   ale juz w kolejnosci od 1 do ostatni *)
procedure znajdzSredniceDrzewa;
begin
  prowadziDo1(ostatni, -1);
end;

(* Przeglada potomkow u i ustawia priorytet kazdemu, ktory
   go jeszcze nie ma. Zaklada ze u ma wyznaczony priorytet.  *)
procedure wyznaczPriorytetyPoddrzew(u, glebiaU: LongInt);
var
  sasiad: LongInt;
  liczby: ^ElementListy;
begin
  liczby := E[u];
  while niepusta(liczby) do
  begin
    sasiad := glowa(liczby);
    liczby := ogon(liczby);

    if priorytet[sasiad] = 0 then
    begin
      priorytet[sasiad] := rozmiar + 2 * (glebiaU + 1);

      (* Dla poprawnosci konieczne jest by listki braly priorytet
         nad wiekszymi poddrzewami *)
      if stopien[sasiad] = 1 then
        priorytet[sasiad] := priorytet[sasiad] + 1;

      wyznaczPriorytetyPoddrzew(sasiad, glebiaU + 1);
    end;
  end;
end;

(* Wypelnia tablice priorytetow. Priorytet to:
   - 1 do rozmiar, dla wezlow na srednicy
   - rozmiar + 2 * glebokosc dla wezlow nie bedacych
     listkami
   - rozmiar + 2 * glebokosc + 1 dla wezlow w poddrzewach,
     bedacych listkami

  Innymi slowy, najpierw szukamy najglebiej, potem jesli sie
  da, najpierw listkow. Na koncu probujemy przechodzi srednice
  po kolei bez skokow. *)
procedure wyznaczPriorytety;
var
  i, korzen: LongInt;
begin
  for i := 1 to dlugoscSrednicy do
  begin
    korzen := srednica[i];
    priorytet[korzen] := rozmiar - i + 1;
  end;

  for i := 1 to dlugoscSrednicy do
  begin
    korzen := srednica[i];
    wyznaczPriorytetyPoddrzew(korzen, 0);
  end;
end;

(* Szuka nieodwiedzonego wezla o najwyzszym priorytecie
   zaczynajac od centrum i skaczac na odleglosc nie
   wieksza niz zasieg *)
procedure najwyzszyPriorytet(centrum, zasieg: LongInt;
                             var najwyzszyZnaleziony,
                                 wezelRealizujacyGo: LongInt);
var
  sasiad, najwyzszyWPoddrzewie, realizujacyWPoddrzewie: LongInt;
  liczby: ^ElementListy;
begin
  najwyzszyZnaleziony := -1;
  wezelRealizujacyGo := 0;

  if not odwiedzony[centrum] then
  begin
    najwyzszyZnaleziony := priorytet[centrum];
    wezelRealizujacyGo := centrum;
  end;

  if zasieg > 0 then
  begin
    liczby := E[centrum];
    while niepusta(liczby) do
    begin
      sasiad := glowa(liczby);
      liczby := ogon(liczby);

      najwyzszyPriorytet(sasiad, zasieg - 1,
                         najwyzszyWPoddrzewie,
                         realizujacyWPoddrzewie);

      if najwyzszyWPoddrzewie > najwyzszyZnaleziony then
      begin
        najwyzszyZnaleziony := najwyzszyWPoddrzewie;
        wezelRealizujacyGo := realizujacyWPoddrzewie;
      end;
    end;
  end;
end;

procedure dodajWezelDoSciezki(u: LongInt);
begin
  odwiedzony[u] := true;
  inc(dlugoscSciezki);
  sciezka[dlugoscSciezki] := u;
end;

(* Sprawdza czy wezel ma podlistki. Jesli tak,
   to dodatkowo dodaje wszystkie z nich do sciezki *)
procedure dodajSkomprWezelDoSciezki(u: LongInt);
var
  listek: LongInt;
  liczby: ^ElementListy;
begin
  dodajWezelDoSciezki(u);

  liczby := podlistki[u];
  while niepusta(liczby) do
  begin
    listek := glowa(liczby);
    liczby := ogon(liczby);
    dodajWezelDoSciezki(listek);
  end;
end;

(* Przechodzi drzewo od wezla 1, szukajac jako nastepnika
   wezla o najwyzszym priorytecie, z posrod nieodwiedzonych
   sasiadow oddalonych o maksymalnie dwie krawedzie *)
procedure zbudujSciezkeZachlannie;
var
  pozycja: LongInt;
  znalezionyPriorytet, realizujacyWezel: LongInt;
begin
  pozycja := 1;
  repeat
    dodajSkomprWezelDoSciezki(pozycja);

    najwyzszyPriorytet(pozycja, 2,
                       znalezionyPriorytet,
                       realizujacyWezel);
    if znalezionyPriorytet > 0 then
      pozycja := realizujacyWezel
    else
      pozycja := -1;
  until pozycja = -1;
end;


(* Sprawdza czy znaleziona sciezka przechodzi
   cale drzewo. Jezeli rozwiazanie istenieje, to
   przegladanie zgodnie z priorytami ja znajdzie *)
function sciezkaJestPoprawna(): Boolean;
begin
  sciezkaJestPoprawna := (sciezka[1] = 1) and
                         (sciezka[ostatni] = rozmiar) and
                         (dlugoscSciezki = rozmiar);
end;


(* Wypisujemy sciezke, po jednym wezle na linie *)
procedure wypiszSciezke;
var
  i: LongInt;
begin
  for i := 1 to dlugoscSciezki do
    writeln(sciezka[i]);
end;

BEGIN
  wczytajKrawedzie;
  wyznaczStopnieDrzewa;
  zbudujDrzewoSkompresowane;

  if maksStopienSkompr() > 5 then
    writeln('BRAK')
  else
  begin
    znajdzSredniceDrzewa;
    wyznaczPriorytety;
    zbudujSciezkeZachlannie;

    if sciezkaJestPoprawna() then
      wypiszSciezke
    else
      writeln('BRAK');
  end;
END.
