(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************)

const MAXN = 200 * 1000 + 100;

var
  tekst: ansistring;
  n, r, testy: longint;
  psufy, p: array[0 .. MAXN-1] of longint;

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

var s, e, x, i: longint;
var st, k, c: longint;

begin
  readln(testy);
  while testy > 0 do begin
    dec(testy);
    readln(tekst);
    n := Length(tekst);
    generuj_p(0, n);
    x := p[n];
    r := 0;
    while x > 0 do begin
      psufy[r] := x;
      inc(r);
      x := p[x];
    end;
    i := 0;
    while i < r - i - 1 do begin
      e := psufy[i];
      psufy[i] := psufy[r - i - 1];
      psufy[r - i - 1] := e;
      inc(i);
    end;
    psufy[r] := n;
    inc(r);
    for i := 0 to psufy[0] - 1 do
      tekst[i+1] := '0';
    if psufy[0] > 1 then
      tekst[psufy[0]] := '1';
    generuj_p(0, psufy[0]);
    for k := 1 to r - 1 do begin
      if psufy[k-1] * 2 >= psufy[k] then begin
        for i := 2 * psufy[k-1] - psufy[k] to psufy[k-1]-1 do
          tekst[i + psufy[k] - psufy[k-1] + 1] := tekst[i + 1];
        generuj_p(psufy[k-1] + 1, psufy[k]);
      end else begin
        s := psufy[k] - 2 * psufy[k-1];
        for i := 0 to s - 1 do
          tekst[i + psufy[k-1] + 1] := '0';
        generuj_p(psufy[k-1] + 1, psufy[k-1] + s);
        c := p[psufy[k-1] + s];
        while (c > 0) and ((psufy[k-1] + s) mod (psufy[k-1] + s - c) = 0) do begin
          st := s;
          while tekst[st + psufy[k-1]] = '1' do begin
            tekst[st + psufy[k-1]] := '0';
            dec(st);
          end;
          tekst[st + psufy[k-1]] := '1';
          generuj_p(psufy[k-1] + st, psufy[k-1] + s);
          c := p[psufy[k-1] + s];
        end;
        for i := 0 to psufy[k-1] - 1 do
          tekst[i + s + psufy[k-1] + 1] := tekst[i + 1];
        generuj_p(psufy[k-1] + s + 1, psufy[k]);
      end;
    end;
    writeln(tekst);
  end;
end.
