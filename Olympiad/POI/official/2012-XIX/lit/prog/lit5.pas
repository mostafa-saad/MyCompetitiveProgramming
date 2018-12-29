(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Zliczamy inwersje metoda "dziel i zwyciezaj"     *
 *                                                                       *
 *************************************************************************)

Program litery;
const 
  MAXN = 1000005;
var
  n, i: longint;
  tab_u : array['A' .. 'Z'] of array[0..MAXN] of longint;
  ind_u, ind_w : array['A' .. 'Z'] of longint;
  u, w : array[0..MAXN] of char;
  c : char;
  p, pom : array[1..MAXN] of longint;

function inwersje(x, y : longint) : int64;
var
  i1, i2, i : longint;
  z : longint;
  wynik : int64;
begin
  if x = y then inwersje := 0
  else begin
    i1 := 0; i2 := 0;
    wynik := 0;
    z := (x + y) div 2;
    for i := x to y do
      if (p[i] <= z) then begin
        inc(wynik, i2);
        pom[x + i1] := p[i];
        inc(i1);
      end else begin
        pom[z + 1 + i2] := p[i];
        inc(i2);
      end;
    for i := x to y do p[i] := pom[i];
    inwersje := wynik + inwersje(x, z) + inwersje(z + 1, y);
  end;
end;

begin
  n := 0;
  for c := 'A' to 'Z' do
    for i := 0 to MAXN do begin
      tab_u[c][i] := 0;
    end;
  for c := 'A' to 'Z' do begin
    ind_u[c] := 0;
    ind_w[c] := 0;
  end;

  readln(n);
  readln(u);
  readln(w);
  for i := n - 1 downto 0 do begin
    tab_u[u[i]][ind_u[u[i]]] := i + 1;
    inc(ind_u[u[i]]);
  end;
  for i := n - 1 downto 0 do begin
    p[tab_u[w[i]][ind_w[w[i]]]] := i + 1;
    inc(ind_w[w[i]]);
  end;

  writeln(inwersje(1, n));
end.
