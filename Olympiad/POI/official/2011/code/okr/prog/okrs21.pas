(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

const MAXN = 200 * 1000 + 100;

var
  tekst: ansistring;
  n, testy, nokresy: longint;
  okresy, p: array[0 .. MAXN-1] of longint;

{ Wypelnia tablice P od pozycji a wlacznie do b wlacznie;
  zaklada ze do pozycji a wylacznie jest juz wypelniona }
procedure generuj_p(a, b: longint);
var x: longint;
begin
  while a <= 1 do begin
    p[a] := 0;
    inc(a);
  end;
  x := p[a-1];
  while a <= b do begin
    while (x > 0) and (tekst[a] <> tekst[x+1]) do
      x := p[x];
    if (x > 0) or (tekst[a] = tekst[1]) then
      inc(x);
    p[a] := x;
    inc(a);
  end;
end;

var x, k, j, i: longint;

begin
  readln(testy);
  while testy > 0 do begin
    dec(testy);
    readln(tekst);
    n := Length(tekst);
    generuj_p(0, n);
    nokresy := 0;
    x := p[n];
    while x > 0 do begin
      okresy[nokresy] := n - x;
      inc(nokresy);
      x := p[x];
    end;
    for i := 1 to n do
      tekst[i] := '0';
    generuj_p(0, n);
    while True do begin
      x := p[n];
      j := 0;
      while (x > 0) and (j < nokresy) do begin
        if okresy[j] <> n - x then
          break;
        x := p[x];
        inc(j);
      end;
      if (x = 0) and (j = nokresy) then
        break;
      k := n;
      while tekst[k] = '1' do begin
        tekst[k] := '0';
        dec(k);
      end;
      tekst[k] := '1';
      generuj_p(k, n);
    end;
    writeln(tekst);
  end;
end.
