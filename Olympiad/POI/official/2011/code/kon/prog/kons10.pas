{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons10.pas                                                 *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 3)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************}

program kon;

const
  MAX_N = 5000;

var 
	n, k, a, i1, i2, r1, r2, i, j, u, v : Longint;
	e : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of Boolean;
	c : array [0 .. 1, 0 .. MAX_N, 0 .. MAX_N - 1] of Boolean;
	ok : Boolean;

begin
	readln(n);
	for i := 0 to n - 1 do
	begin
		read(k);
		for j := 0 to k - 1 do
		begin
			read(a);
			e[i][a - 1] := true
		end;
		readln()
	end;
	c[0][0][0] := true;
	c[0][1][0] := false;
	r1 := 2;
	i1 := 0;
	i2 := 1;
	for i := 1 to n - 1 do
	begin
		r2 := 0;
		for j := 0 to r1 - 1 do
			for k := 0 to 1 do
			begin
				ok := true;
				for u := 0 to i - 1 do
				begin
					if not ok then
						break;
					if e[i][u] then
						ok := ok and ((k = 0) or (c[i1][j][u] = false))
					else
						ok := (k = 1) or (c[i1][j][u] = true)
				end;
				if ok then
				begin
					for v := 0 to i - 1 do
						c[i2][r2][v] := c[i1][j][v];
					c[i2][r2][i] := (k = 1);
					Inc(r2)
				end
			end;
		i1 := i1 xor i2;
		i2 := i1 xor i2;
		i1 := i1 xor i2;
		r1 := r1 xor r2;
		r2 := r1 xor r2;
		r1 := r1 xor r2
	end;
	if r1 > n then
		Dec(r1);
	writeln(r1)
end.

