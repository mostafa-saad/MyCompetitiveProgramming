(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs130.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n^2 * log n).         *
 *             Skakanie zabki symulujemy w czasie O(n * log m).          *
 *                                                                       *
 *************************************************************************)

program zab;
const
  MAX_N = 1000000;
  LOG_M = 60;

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

var
  perm : array [0 .. 1] of array [0 .. MAX_N - 1] of longint;
	res : array [0 .. MAX_N - 1] of longint;

procedure skacz;
var
	i, i1, i2 : longint;
	p2 : int64;
begin
	i1 := 0;
	i2 := 1;
	for i := 0 to n - 1 do
	begin
		perm[0][i] := kty[i];
		res[i] := i;
	end;
	p2 := 1;
	while (p2 <= m) do
	begin
		if (p2 and m) = p2 then
			for i := 0 to n - 1 do
				res[i] := perm[i1][res[i]];
		for i := 0 to n - 1 do
			perm[i2][i] := perm[i1][perm[i1][i]];
		i1 := i1 xor i2;
		i2 :=	i2 xor i1;
		i1 := i1 xor i2;
		p2 := p2 * 2;		
	end;
	for i := 0 to n - 1 do
	begin
		write(res[i] + 1);
		if i + 1 < n then
			write(' ')
		else
			writeln();
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

