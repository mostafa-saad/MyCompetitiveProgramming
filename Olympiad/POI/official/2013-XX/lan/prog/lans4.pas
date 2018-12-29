(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n * m)                                      *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Nie wpadamy na pomysl by wykorzystac licznik  *
 *                         zlych kolorow w biezacym fragmencie do        *
 *                         szybkiego sprawdzania jego ladnosci.          *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000 * 1000;

var 
  n, m, d : longint;
  wynik : longint;
  l, c, lancuch, ile_w_kolorze, ile_ma_byc, gdzie : array[1..MAXN] of longint;
  i : longint;

procedure akt_kolor(k, dodaj : longint);
begin
  ile_w_kolorze[k] := ile_w_kolorze[k] + dodaj;
end;

function podciag_zgodny : boolean;
var i : longint;
begin
  for i := 1 to m do 
    if ile_w_kolorze[c[i]] <> ile_ma_byc[c[i]] then begin
      podciag_zgodny := false;
      exit
    end;
  podciag_zgodny := true
end;

begin
  read(n, m);
  {Zerowanie zmiennych i tablic }
  wynik := 0;
  d := 0;
  for i := 1 to n do begin
    ile_ma_byc[i] := 0;
    ile_w_kolorze[i] := 0;
  end;
  for i := 1 to m do begin
    read(l[i]);
    d := d + l[i];
    if d > n then begin
      writeln(0);
      exit
    end
  end;
  for i := 1 to m do 
    read(c[i]);
  for i := 1 to m do
    ile_ma_byc[c[i]] := l[i];
  for i := 1 to n do
    read(lancuch[i]);
  
  for i := 1 to d do
    akt_kolor(lancuch[i], 1);
  if podciag_zgodny then
    inc(wynik);
  for i := d + 1 to n do begin
    akt_kolor(lancuch[i - d], -1);
    akt_kolor(lancuch[i], 1);
    if podciag_zgodny then
      inc(wynik);
  end;
  
  writeln(wynik);
end.

