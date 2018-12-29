(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Zliczamy inwersje przez Mergesort                *
 *                                                                       *
 *************************************************************************)

Program litery;
const 
  MAXN = 1000005;
var
  n, i: longint;
  wynik : int64;
  tab_u : array['A' .. 'Z'] of array[0..MAXN] of longint;
  ind_u, ind_w : array['A' .. 'Z'] of longint;
  u, w : array[0..MAXN] of char;
  c : char;
  p, ciag : array[1..MAXN] of longint;

procedure merge(a, c, b : longint);
var
  k1, k2, i1, i2, i : longint;
begin
  k1 := c - a + 1; k2 := b - c;
  i1 := 1; i2 := 1;
  while (i1 <= k1) or (i2 <= k2) do begin
    if (i1 > k1) then begin
      ciag[i1 + i2 - 1] := p[c + i2];
      inc(i2);
    end else if (i2 > k2) then begin
      inc(wynik, i2 - 1);
      ciag[i1 + i2 - 1] := p[a - 1 + i1];
      inc(i1);
    end else if (p[a - 1 + i1] < p[c + i2]) then begin
      inc(wynik, i2 - 1);
      ciag[i1 + i2 - 1] := p[a - 1 + i1];
      inc(i1);
    end else begin
      ciag[i1 + i2 - 1] := p[c + i2];
      inc(i2);
    end;
  end;
  for i := a to b do p[i] := ciag[i + 1 - a];
end;

procedure mergesort(a, b : longint);
var
  c : longint;
begin
  if a <> b then begin
    c := (a + b) div 2;
    mergesort(a, c);
    mergesort(c + 1, b);
    merge(a, c, b);
  end;
end;

begin
  n := 0; wynik := 0;
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

  mergesort(1, n);

  writeln(wynik);
end.
