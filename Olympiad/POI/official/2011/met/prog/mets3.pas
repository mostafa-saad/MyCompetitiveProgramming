(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O(k * m)                                         *
 *   Opis:              Rozwiazanie powolne, silowe                      *
 *                                                                       *
 *************************************************************************)

program met;

const CN = 300007;

var n, m, a, lo, l, r, w, i, nr : Longint;
  pot, wl, wyn : Array[0..CN-1] of Longint;

procedure zrzuc(nr, l, r, w : Longint);
  var i, p, wli : Longint;
begin
  for i := l to r do
  begin
    wli := wl[i];
    p := pot[wli];
    if p > 0 then 
    begin
      Dec(pot[wli], w);
      if p <= w then
        wyn[wli] := nr;
    end;
  end;
end;

begin
	Readln(n, m);
  { Wczytanie danych. }
  for i := 0 to m-1 do
  begin
    Read(a);
    wl[i] := a-1;
  end;
  for i := 0 to n-1 do
  begin
    Read(pot[i]);
  end;
 
  { Wczytywanie i przetwarzanie opadów. }
  Readln(lo);
  for nr := 1 to lo do
  begin
    Readln(l, r, w);
    Dec(l);
    Dec(r);
    if l <= r then
      zrzuc(nr, l, r, w) 
    else 
    begin
      zrzuc(nr, 0, r, w);
      zrzuc(nr, l, m-1, w);
    end;
  end;

  { Wypisanie wyniku. }
  for i := 0 to n-1 do
  begin
    if (wyn[i] > 0) then
      Writeln(wyn[i])
    else
      Writeln('NIE');
  end;
end.
