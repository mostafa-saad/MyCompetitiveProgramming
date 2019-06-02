(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Zliczamy inwersje metoda "parzyste-nieparzyste"  *
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
  p : array[1..MAXN] of longint;
  Nieparzyste : array[0..MAXN] of longint;

function inwersje : int64;
var
  wynik : int64;
  ile_zer : longint;
  i : longint;
begin
  wynik := 0;
  ile_zer := 0;
  while ile_zer < n do begin
    for i := 0 to n do Nieparzyste[i] := 0;
    ile_zer := 0;
    for i := 1 to n do begin
      if p[i] mod 2 = 1 then inc(Nieparzyste[p[i]])
      else inc(wynik, Nieparzyste[p[i] + 1]);
      p[i] := p[i] div 2;
      if p[i] = 0 then inc(ile_zer);
    end;
  end;
  inwersje := wynik;
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
    p[tab_u[w[i]][ind_w[w[i]]]] := i;
    inc(ind_w[w[i]]);
  end;

  writeln(inwersje);
end.
