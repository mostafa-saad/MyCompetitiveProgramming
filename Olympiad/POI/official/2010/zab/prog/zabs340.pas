(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs340.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * log Z * log m).   *
 *             Skakanie zabki symulujemy w czasie O(n).                  *
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

type
  para = record
    x, y : longint;
  end;

var 
  cykl : array [0 .. MAX_N - 1] of para;
  v2c : array [0 .. MAX_N - 1] of para;
  dzieci : array [0 .. MAX_N - 1] of para;
  stan : array [0 .. MAX_N - 1] of longint;
  pom : array [0 .. MAX_N - 1] of longint;
  pam : array [0 .. MAX_N - 1] of longint;
  wynik : array [0 .. MAX_N - 1] of longint;
  pam_nr : longint = 0;

procedure znajdz_cykle;
var
  i, j, cykl_nr, top, v, b : longint;
begin
  for i := 0 to n - 1 do begin
    stan[i] := -1; v2c[i].x := -1;
  end;
  cykl_nr := 0;
  for i := 0 to n - 1 do begin
    if stan[i] < 0 then begin
      top := 0; v := i;
      while stan[v] < 0 do begin
        stan[v] := i;
        pom[top] := v; inc(top);
        v := kty[v];
      end;
      if stan[v] = i then begin
        b := top - 1;
        while pom[b] <> v do dec(b);
        cykl[cykl_nr].x := pam_nr; cykl[cykl_nr].y := top - b;
        for j := b to top - 1 do begin
          v := pom[j]; pam[pam_nr] := v; inc(pam_nr);
          v2c[v].x := cykl_nr; v2c[v].y := j - b;
        end;
        inc(cykl_nr);
      end;
    end;
  end;
end;

procedure zbuduj_las;
var
  i : longint;
begin
  for i := 0 to n - 1 do pom[i] := 0;
  for i := 0 to n - 1 do
    if v2c[i].x < 0 then inc(pom[kty[i]]);
  for i := 0 to n - 1 do begin
    dzieci[i].x := pam_nr; dzieci[i].y := pam_nr;
    pam_nr := pam_nr + pom[i];
  end;
  for i := 0 to n - 1 do
    if v2c[i].x < 0 then begin
      pam[dzieci[kty[i]].y] := i;
      inc(dzieci[kty[i]].y);
    end;
end;

procedure rozwiaz_las;
var
  i, c, b, p, d, top, v : longint;
begin
  zbuduj_las;
  for i := 0 to n - 1 do stan[i] := -1;
  for i := 0 to n - 1 do begin
    if v2c[i].x >= 0 then begin
      c := v2c[i].x; b := cykl[c].x; p := v2c[i].y; d := cykl[c].y;
      top := 0;
      pom[top] := i; inc(top);
      while top > 0 do begin
        v := pom[top - 1];
        if stan[v] < 0 then begin
          stan[v] := dzieci[v].x;
          if m > top - 1 then
            wynik[v] := pam[b + ((p + (m - top + 1)) mod d)]
          else
            wynik[v] := pom[top - 1 - m];
        end;
        if stan[v] < dzieci[v].y then begin
          pom[top] := pam[stan[v]]; inc(top);
          inc(stan[v]);
        end else
          dec(top);
      end;
    end;
  end;
end;

procedure skacz;
var
  i : longint;
begin
  znajdz_cykle;
  rozwiaz_las;
  for i := 0 to n - 1 do
    if i < n - 1 then
      write(wynik[i] + 1, ' ')
    else
      writeln(wynik[i] + 1);
end;

var
  i : longint;

begin
  readln(n, k, m);
  for i := 0 to n - 1 do read(p[i]);
  oblicz_kte;
  skacz;
end.

