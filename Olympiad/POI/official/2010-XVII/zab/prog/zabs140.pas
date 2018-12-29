(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs140.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n^2 * log n).         *
 *             Skakanie zabki symulujemy w czasie O(n).                  *
 *                                                                       *
 *************************************************************************)

program zab;
const
  MAX_N = 1000000;

type
  para = record
    x : int64;
    y : longint;
  end;

var 
  n, k : longint;
  m : int64;
  p : array [0 .. MAX_N - 1] of int64;
  kty : array [0 .. MAX_N - 1] of longint;

function myabs(x : int64) : int64;
begin
  if x >= 0 then myabs := x else myabs := -x;
end;

var
  pom0 : array [0 .. MAX_N - 1] of para;

procedure sort(lewy, prawy : longint);
var
  l, p : longint;
  v, tmp : para;
begin
  l := lewy; p := prawy;
  v := pom0[(l + p) div 2];
  repeat
    while (pom0[l].x < v.x) or ((pom0[l].x = v.x) and (pom0[l].y < v.y)) do inc(l);
    while (pom0[p].x > v.x) or ((pom0[p].x = v.x) and (pom0[p].y > v.y)) do dec(p);
    if l <= p then begin
      tmp := pom0[l]; pom0[l] := pom0[p]; pom0[p] := tmp;
      inc(l); dec(p);
    end;
  until l > p;
  if lewy < p then sort(lewy, p);
  if l < prawy then sort(l, prawy);
end;

procedure oblicz_kte();
var
  i, j : longint;
begin
  for i := 0 to n - 1 do begin
    for j := 0 to n - 1 do begin
      pom0[j].x := myabs(p[i] - p[j]);
      pom0[j].y := j;
    end;
    sort(0, n - 1);
    if pom0[k].x = pom0[k - 1].x then pom0[k].y := pom0[k - 1].y;
    kty[i] := pom0[k].y;
  end;
end;

type
  para2 = record
    x, y : longint;
  end;

var 
  cykl : array [0 .. MAX_N - 1] of para2;
  v2c : array [0 .. MAX_N - 1] of para2;
  dzieci : array [0 .. MAX_N - 1] of para2;
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

