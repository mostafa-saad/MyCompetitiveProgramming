(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs410.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n).                   *
 *             Skakanie zabki symulujemy w czasie O(n * m).              *
 *                                                                       *
 *************************************************************************)

program zab;
const
  MAX_N = 1000000;

var 
  n, k : longint;
  m : int64;
  p : array [0 .. MAX_N - 1] of int64;
  kty : array [0 .. MAX_N - 1] of longint;

procedure oblicz_kte;
var
  i, a, b : longint;
begin
  a := 0; b := k; kty[0] := k;
  for i := 0 to n - 1 do begin
    while (b < n - 1) and (p[b + 1] - p[i] < p[i] - p[a]) do begin
      inc(a); inc(b);
    end;
    if p[i] - p[a] >= p[b] - p[i] then kty[i] := a else kty[i] := b;
  end;
end;

procedure skacz();
var
  m0 : int64;
  i, poz : longint;
begin
  for i := 0 to n - 1 do begin
    m0 := m;
    poz := i;
    while m0 > 0 do begin
      poz := kty[poz];
      dec(m0);
    end;
    if i < n - 1 then
      write(poz + 1, ' ')
    else
      writeln(poz + 1)
  end
end;

var
  i : longint;

begin
  readln(n, k, m);
  for i := 0 to n - 1 do read(p[i]);
  oblicz_kte;
  skacz;
end.

