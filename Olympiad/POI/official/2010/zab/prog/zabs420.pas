(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs420.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n).                   *
 *             Skakanie zabki symulujemy w czasie O(n^2).                *
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

var
  numer : array [0 .. MAX_N - 1] of longint;
  uzyte : array [0 .. MAX_N - 1] of longint;

procedure skacz;
var
  i, j, poz, nr, top : longint;
  m0 : int64;
begin
  for i := 0 to n - 1 do numer[i] := -1;
  for i := 0 to n - 1 do begin
    poz := i; nr := 0; top := 0;
    numer[poz] := 0;
    uzyte[top] := poz; inc(top);
    while nr < m do begin
      inc(nr);
      poz := kty[poz];
      if numer[poz] <> -1 then break;
      numer[poz] := nr;
      uzyte[top] := poz; inc(top);
    end;
    if nr <> m then begin
      m0 := m;
      m0 :=  m0 - numer[poz];
      m0 :=  m0 mod (nr - numer[poz]);
      while m0 > 0 do begin
        dec(m0);
        poz := kty[poz];
      end;
    end;
    for j := 0 to top - 1 do numer[uzyte[j]] := -1;
    if i < n - 1 then
      write(poz + 1, ' ')
    else
      writeln(poz + 1);
  end;
end;

var
  i : longint;

begin
  readln(n, k, m);
  for i := 0 to n - 1 do read(p[i]);
  oblicz_kte;
  skacz;
end.

