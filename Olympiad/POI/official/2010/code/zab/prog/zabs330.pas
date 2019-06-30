(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs330.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * log Z * log m).   *
 *             Skakanie zabki symulujemy w czasie O(n * log m).          *
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

