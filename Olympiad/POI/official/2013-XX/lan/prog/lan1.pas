(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000 * 1000;

var 
  n, m, d : longint; 
  {dlugosc lancucha, dlugosc opisu, dlugosc ladnego fragmentu}
  ile_niezgodnosci, wynik : longint;
  l, c, lancuch, ile_w_kolorze, ile_ma_byc : array[1..MAXN] of longint;
  i : longint;

procedure akt_kolor(k, dodaj : longint); 
{dodaj = +1 : dodajemy ogniwo w kolorze k, dodaj = -1 : odejmujemy}
begin
  if ile_w_kolorze[k] = ile_ma_byc[k] then
    inc(ile_niezgodnosci);
  ile_w_kolorze[k] := ile_w_kolorze[k] + dodaj;
  if ile_w_kolorze[k] = ile_ma_byc[k] then
    dec(ile_niezgodnosci)
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
  
  ile_niezgodnosci := m;
  for i := 1 to d do
    akt_kolor(lancuch[i], 1);
  if ile_niezgodnosci = 0 then
    inc(wynik);
  for i := d + 1 to n do begin
    akt_kolor(lancuch[i - d], -1);
    akt_kolor(lancuch[i], 1);
    if ile_niezgodnosci = 0 then
      inc(wynik);
  end;
  
  writeln(wynik);
end.

