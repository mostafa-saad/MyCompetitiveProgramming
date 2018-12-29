(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs230.pas                                               *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * k).               *
 *             Skakanie zabki symulujemy w czasie O(n * log m).          *
 *                                                                       *
 *************************************************************************)

program zab;
const
  MAX_N = 1000000;
  LOG_M = 60;

var 
  n, k : longint;
  m : int64;
  p : array [0 .. MAX_N - 1] of int64;
  kty : array [0 .. MAX_N - 1] of longint;

procedure oblicz_kte;
var
  i, a, b, nr : longint;
begin
  for i := 0 to n - 1 do begin
    a := i; b := i; nr := 0;
    while nr < k do begin
      if a = 0 then inc(b)
      else if b = n - 1 then dec(a)
      else if p[i] - p[a - 1] <= p[b + 1] - p[i] then dec(a)
      else inc(b);
      inc(nr);
    end;
    if a < 0 then kty[i] := b
    else if b >= n then kty[i] := a
    else if p[i] - p[a] >= p[b] - p[i] then kty[i] := a
    else kty[i] := b;
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

