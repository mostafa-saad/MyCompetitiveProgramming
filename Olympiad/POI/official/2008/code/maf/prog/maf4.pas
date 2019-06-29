(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     maf4.pas                                                  *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Rozwiazanie alternatywne o zlozonosci czasowej O(n^2),    *
 *             przepisane z maf3.cpp na Pascala.                         *
 *                                                                       *
 *************************************************************************)

program Mafia;

const MAX = 1000000;

var
  n : LongInt;
  s : array[1..MAX] of LongInt;
  tmp : array[1..MAX] of LongInt;
  indeg : array[1..MAX] of LongInt;
  visited : array[1..MAX] of Boolean;


function find_maximum : LongInt;
var
  nlisci : LongInt;
  ncykli_niesamobojczych : LongInt;
  i, j : LongInt;
begin
  nlisci := 0;
  ncykli_niesamobojczych := 0;

  { zliczanie stopni wejściowych }
  for i := 1 to n do indeg[i] := 0;
  for i := 1 to n do inc(indeg[s[i]]);

  { resetowanie tablicy visited[] }
  for i := 1 to n do visited[i] := false;

  { zliczanie lisci lacznie z wykreslaniem wierzcholkow
   z nich osiagalnych }
  for i := 1 to n do begin
    if indeg[i] = 0 then begin
      inc(nlisci);
      j := i;
      while not visited[j] do  begin
        visited[j] := true;
        j := s[j];
      end;
    end;
  end;

  { teraz pozostaly juz tylko cykle proste  }

  { zliczanie cyklow dlugosci >= 2 }
  for i := 1 to n do begin
    if (not visited[i]) and (s[i] <> i) then begin
      inc(ncykli_niesamobojczych);
      j := i;
      while not visited[j] do begin
        visited[j] := true;
        j := s[j];
      end;
    end;
  end;

  find_maximum := n - nlisci - ncykli_niesamobojczych;
end;


{ znajduje w grafie tymczasowym liscia (tzn. wierzcholka o stopniu wejsciowym zero,
 ktory nie celuje do mafioza o nr -1) lub zwraca -1, jesli takiego nie ma }
function find_leaf : LongInt;
var
  i : LongInt;
begin
  { obliczanie stopni wejsciowych }
  for i := 1 to n do indeg[i] := 0;
  for i := 1 to n do
    if tmp[i] <> -1 then
      inc(indeg[tmp[i]]);

  { znalezienie liscia }
  for i := 1 to n do
    if (tmp[i] <> -1) and (indeg[i] = 0) then begin
      find_leaf := i;
      exit;
    end;

  { jesli sie nie uda... }
  find_leaf := -1;
end;


{ dokonuje transformacji na wierzcholku v }
procedure transform(v : LongInt);
begin
  tmp[tmp[v]] := tmp[v];
  tmp[v] := -1;
end;


function find_minimum : LongInt;
var
  i, j, candidate : LongInt;
  nsamobojcow : LongInt;
begin
  { przepisanie grafu s[] na graf tmp[] na ktorym bedziemy
   dokonywac transformacji }
  for i := 1 to n do tmp[i] := s[i];

  { transformacje do skutku }
  while true do begin
    { znajdz kandydata do transformacji (najpierw szukaj liscia) }
    candidate := find_leaf();

    { jesli sie nie udalo to szukaj dowolnego niesamobojcy ... }
    j := 1;
    while (j <= n) and (candidate = -1) do begin
      if (j <> tmp[j]) and (tmp[j] <> -1) then candidate := j;
      inc(j);
    end;

    { jesli nadal sie nie udalo to zakoncz }
    if candidate = -1 then break;

    { w przeciwnym wypadku dokonaj transformacji }
    transform(candidate);
  end;

  { jako wynik zwroc liczbe samobojcow po wszystkich transformacjach }
  nsamobojcow := 0;
  for i := 1 to n do
    if tmp[i] = i then
       inc(nsamobojcow);

  find_minimum := nsamobojcow;
end;


var
  minimum : LongInt;
  maximum : LongInt;
  i : LongInt;

begin
  read(n);
  for i := 1 to n do read(s[i]);

  maximum := find_maximum();
  minimum := find_minimum();

  writeln(minimum, ' ', maximum);
end.
