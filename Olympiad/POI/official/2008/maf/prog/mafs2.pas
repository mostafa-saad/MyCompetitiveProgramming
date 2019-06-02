(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     mafs2.pas                                                 *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Rozwiazanie wolne. Dla kazdej slabo spojnej skladowej     *
 *             probujemy wszystkie permutacje jej wierzcholkow jako      *
 *             kolejnosc strzelania i... strzelamy.                      *
 *                                                                       *
 *************************************************************************)

program Mafia;

const MAX_N = 1000000;
const MIN = 0;
const MAX = 1;

var
  n : LongInt;
  minimum, maximum : LongInt;
  visited : array[1..MAX_N] of Boolean;
  s : array[1..MAX_N] of LongInt;

  { ukryte w tablicy listy ,,slabego'' sasiedztwa }
  sasiad_from : array[1..(2*MAX_N)] of LongInt;
  sasiad_to : array[1..(2*MAX_N)] of LongInt;
  where : array[1..(MAX_N+1)] of LongInt;
  { where[i] to poczatek listy sasiedztwa wierzcholka i w sasiad[] }

  { zmienne tymczasowe potrzebne w komunikacji miedzy
    funkcjami analizuj, permutacje_*, strzelaj}
  skladowa : array[1..MAX_N] of LongInt;
  rozmiar_skladowej : LongInt;
  kolejnosc : array[1..MAX_N] of LongInt;
  taken : array[1..MAX_N] of Boolean;
  alive : array[1..MAX_N] of Boolean;

{ zwraca liczbe zabitych przy danej kolejnosci strzelania }
function strzelaj : LongInt;
var
  i,v : LongInt;
  nzabitych : LongInt;
begin
  { wszyscy na poczatku sa zywi }
  for i := 1 to rozmiar_skladowej do begin
    v := skladowa[kolejnosc[i]];
    alive[v] := true;
  end;

  { potem do siebie strzelaja }
  for i := 1 to rozmiar_skladowej do begin
    v := skladowa[kolejnosc[i]];
    if alive[v] then
      alive[s[v]] := false;
  end;

  { zliczamy poleglych }
  nzabitych := 0;
  for i := 1 to rozmiar_skladowej do begin
    v := skladowa[kolejnosc[i]];
    if not alive[v] then inc(nzabitych);
  end;

  strzelaj := nzabitych;
end;


function permutacje(level, mode : LongInt) : LongInt;
var
  tmp, i, v : LongInt;
  wynik : LongInt;
begin
  if level > rozmiar_skladowej then begin
    permutacje := strzelaj();
    exit;
  end;

  if mode = MIN then
    wynik := n
  else
    wynik := 0;

  for i := 1 to rozmiar_skladowej do begin
    v := skladowa[i];
    if not taken[v] then begin
      taken[v] := true;
      kolejnosc[level] := i;
      tmp := permutacje(level + 1, mode);
      kolejnosc[level] := -1;
      taken[v] := false;

      if (mode = MIN) and (tmp < wynik) then wynik := tmp;
      if (mode = MAX) and (tmp > wynik) then wynik := tmp;
    end;
  end;

  permutacje := wynik;
end;




procedure DFS(v : LongInt);
var
  i : LongInt;
begin
  if visited[v] then exit;
  visited[v] := true;
  inc(rozmiar_skladowej);
  skladowa[rozmiar_skladowej] := v;

  for i := where[v] to where[v+1] - 1 do begin
    if not visited[sasiad_to[i]] then DFS(sasiad_to[i]);
  end;
end;


{ przeglada slabo spojna skladowa wierzcholka v i wykonuje wszystkie
  mozliwe na niej kolejnosci strzelania }
procedure analizuj(v : LongInt);
var
  my_min : LongInt;
  my_max : LongInt;
  i : LongInt;
begin
  if visited[v] then exit;

  { znajdz dana spojna skladowa }
  i := v;
  rozmiar_skladowej := 0;
  DFS(v);

  { wykonaj na niej strzelanie }
  my_min := permutacje(1, MIN);
  my_max := permutacje(1, MAX);

  inc(minimum, my_min);
  inc(maximum, my_max);
end;



var
  { dwie tablice tymczasowe do przepisywania w algorytmie quicksort }
  tmp_to : array[1..(2*MAX_N)] of LongInt;
  tmp_from : array[1..(2*MAX_N)] of LongInt;

{ sortuje przedzial [poczatek, koniec] w parze tablic
  sasiad_from[], sasiad_to[] porownujac po sasiad_from }
procedure quicksort(poczatek, koniec : LongInt);
var
  granica : LongInt; { punkt graniczny dla podzialu }
  ile_mniejszych : LongInt;
  ile_rownych : LongInt;
  ile_wiekszych : LongInt;
  wsk1, wsk2, wsk3 : LongInt;
  i : LongInt;
begin
  granica := sasiad_from[random(koniec - poczatek + 1) + poczatek];

  { zliczamy ile jest mniejszych, rownych i wiekszych }
  ile_mniejszych := 0;
  ile_wiekszych := 0;
  ile_rownych := 0;
  for i := poczatek to koniec do begin
    if sasiad_from[i] < granica then inc(ile_mniejszych)
    else if sasiad_from[i] = granica then inc(ile_rownych)
    else inc(ile_wiekszych);
  end;

  { porzadkujemy elementy przepisujac je do tmp_*[] }
  wsk1 := poczatek;
  wsk2 := wsk1 + ile_mniejszych;
  wsk3 := wsk2 + ile_rownych;

  for i := poczatek to koniec do begin
    if sasiad_from[i] < granica then begin
      tmp_from[wsk1] := sasiad_from[i];
      tmp_to[wsk1] := sasiad_to[i];
      inc(wsk1);
    end;
    if sasiad_from[i] = granica then begin
      tmp_from[wsk2] := sasiad_from[i];
      tmp_to[wsk2] := sasiad_to[i];
      inc(wsk2);
    end else
    if sasiad_from[i] > granica then begin
      tmp_from[wsk3] := sasiad_from[i];
      tmp_to[wsk3] := sasiad_to[i];
      inc(wsk3);
    end;
  end;

  { przepisujemy z powrotem do sasiad_*[] }
  for i := poczatek to koniec do begin
    sasiad_from[i] := tmp_from[i];
    sasiad_to[i] := tmp_to[i];
  end;

  { wywolujemy porzadkowanie rekurencyjnie }
  if ile_mniejszych > 0 then quicksort(poczatek, poczatek + ile_mniejszych - 1);
  if ile_wiekszych > 0 then quicksort(koniec - ile_wiekszych + 1, koniec);
end;




var
  i, j : LongInt;
  from : LongInt; { wskaznik potrzebny przy obliczaniu tablicy where[] }

begin
  read(n);
  for i := 1 to n do read(s[i]);

  for i := 1 to n do visited[i] := false;
  for i := 1 to n do taken[i] := false;
  for i := 1 to n do alive[i] := false;
  minimum := 0;
  maximum := 0;

  { tworzenie list sasiedztwa }

  { zapisywanie krawedzi do tablicy }
  for i := 1 to n do begin
    sasiad_from[i] := i;
    sasiad_to[i] := s[i];
  end;
  for i := 1 to n do begin
    sasiad_from[n + i] := s[i];
    sasiad_to[n + i] := i;
  end;
  { sortowanie tablicy }
  quicksort(1, 2 * n);

  { obliczenie wskaznikow where[] }
  where[1] := 1; { nie ma w tym grafie wierzcholkow izolowanych }
  from := 1;
  for i := 2 to 2 * n do begin
    if sasiad_from[i] <> sasiad_from[i - 1] then begin
      inc(from);
      where[from] := i;
    end;
  end;
  where[n + 1] := 2 * n + 1; { wartownik }

  for i := 1 to n do analizuj(i);

  writeln(minimum, ' ', maximum);

end.
