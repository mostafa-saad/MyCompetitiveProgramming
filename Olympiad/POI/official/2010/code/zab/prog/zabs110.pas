(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs110.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n^2 * log n).         *
 *             Skakanie zabki symulujemy w czasie O(n * m).              *
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
  pom : array [0 .. MAX_N - 1] of para;

procedure sort(lewy, prawy : longint);
var
  l, p : longint;
  v, tmp : para;
begin
  l := lewy; p := prawy;
  v := pom[(l + p) div 2];
  repeat
    while (pom[l].x < v.x) or ((pom[l].x = v.x) and (pom[l].y < v.y)) do inc(l);
    while (pom[p].x > v.x) or ((pom[p].x = v.x) and (pom[p].y > v.y)) do dec(p);
    if l <= p then begin
      tmp := pom[l]; pom[l] := pom[p]; pom[p] := tmp;
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
      pom[j].x := myabs(p[i] - p[j]);
      pom[j].y := j;
    end;
    sort(0, n - 1);
    if pom[k].x = pom[k - 1].x then pom[k].y := pom[k - 1].y;
    kty[i] := pom[k].y;
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

