(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs320.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * log Z * log m).   *
 *             Skakanie zabki symulujemy w czasie O(n^2).                *
 *                                                                       *
 *************************************************************************)
program zab;

const
  MAX_N = 1000000;
  MIN_P : int64 = 0;

var 
  n, k : longint;
  m : int64;
  p : array [0 .. MAX_N - 1] of int64;
  kty : array [0 .. MAX_N - 1] of longint;

(* Zwraca najmniejsze j (0 <= j < n), takie �e p[i] - p[j] <= d. *)
function na_lewo(i : longint; d : int64) : longint;
var
  l, r, s : longint;
begin
  l := 0; r := i;
  while l < r do begin
    s := (l + r) div 2;
    if p[i] - p[s] > d then l := s + 1 else r := s;
  end;
  na_lewo := l;
end;

(* Zwraca najwi�ksze j (0 <= j < n), takie �e p[j] - p[i] <= d. *)
function na_prawo(i : longint; d : int64) : longint;
var
  l, r, s : longint;
begin
  l := i; r := n - 1;
  while l < r do begin
    s := (l + r + 1) div 2;
    if p[s] - p[i] > d then r := s - 1 else l := s;
  end;
  na_prawo := l;
end;

procedure oblicz_kte;
var
  i, a, b : longint;
  l, r, s : int64;
begin
  for i := 0 to n - 1 do begin
    l := MIN_P; r := p[n - 1];
    while l < r do begin
      s := (l + r) div 2;
      a := na_lewo(i, s);
      b := na_prawo(i, s);
      if b - a + 1 <= k then l := s + 1 else r := s;
    end;
    a := na_lewo(i, l);
    b := na_prawo(i, l);
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

