(*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Czekolada                                      *
 *   Plik:                cze1.pas                                       *
 *   Autor:               Marcin Kubica                                  *
 *************************************************************************)
const
  maxN = 1000;

type
  linia = record
            koszt    : integer;
            kierunek : (poziomy, pionowy)
          end;
  dane = array [1..2*maxN] of linia;

procedure sort(var d: dane; n: integer);

  procedure qsort(l, p: integer);
  var
    i, j, x : integer;
    y : linia;
  begin
    x := d[random (p - l + 1) + l].koszt;
    i := l;
    j := p;
    repeat
      while d[i].koszt < x do inc(i);
      while d[j].koszt > x do dec(j);
      if i <= j then begin
        y    := d[i];
        d[i] := d[j];
        d[j] := y;
        inc(i);
        dec(j);
      end
    until i > j;
    if l < j then qsort(l, j);
    if i < p then qsort(i, p)
  end;

begin
  randomize;
  qsort(1, n)
end;


var 
  n, m, i, pionowe, poziome : integer;
  d : dane;
  koszt : longint;
begin
  { Wczytanie danych. }
  readln(m, n);
  for i := 1 to m-1 do begin
    readln(d[i].koszt);
    d[i].kierunek := pionowy
  end;
  for i := m to n+m-2 do begin
    readln(d[i].koszt);
    d[i].kierunek := poziomy
  end;
  
  { Obliczenie wyniku. }
  koszt := 0;
  sort (d, n+m-2);
  pionowe := 0;
  poziome := 0;
  { Kolejne linie ³amania, w kolejno¶ci nierosn±cych kosztów. }
  for i := n+m-2 downto 1 do begin
    if d[i].kierunek = pionowy then begin
      { Pionowe prze³amanie. }
      koszt := koszt + (poziome + 1) * d[i].koszt;
      inc(pionowe)
    end else begin
      { Poziome prze³amanie. }
      koszt := koszt + (pionowe + 1) * d[i].koszt;
      inc(poziome)
    end
  end;
  
  { Wypisanie wyniku }
  writeln(koszt)
end.
  
  
  
  
  
  
  
  