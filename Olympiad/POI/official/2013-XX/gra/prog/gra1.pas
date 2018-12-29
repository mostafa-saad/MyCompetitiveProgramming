(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n+m)                                        *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAXN =  500000;
const MAXM = 1000000;
var
n, m, k, r, i, j, a, b, c : Longint;
towers, edges : array[0..MAXN+1] of Longint;
safe : array[1..MAXN] of Boolean;
next, v : array[0..2*MAXM+7] of Longint; {listy sasiedztwa}

begin
	{inicjalizacja}
	c := 0;
	r := 0;
	for i := 1 to MAXN do
	begin
		safe[i] := False;
		edges[i] := 0;
	end;
	{wejscie}
	Read(n);
	Read(m);
	Read(k);
	for i := 1 to m do
		begin
			Read(a);
			Read(b);
			Inc(c);
			v[c] := b;
			next[c] := edges[a];
			edges[a] := c;
			Inc(c);
			v[c] := a;
			next[c] := edges[b];
			edges[b] := c;
		end;
	{rozwiazanie}
	for i := 1 to n do
		if not safe[i] then
			begin
				Inc(r);
				towers[r] := i;
				safe[i] := True;
				j := edges[i];
				while not (j = 0) do
				begin
					safe[v[j]] := True;
					k := edges[v[j]];
					while not (k = 0) do
					begin
						safe[v[k]] := True;
						k := next[k];
					end;
					j := next[j];
				end;
			end;
	{wyjscie}
	Writeln(r);
	for i := 1 to r do
	begin
		Write(towers[i]);
		Write(' ');
	end;
end.
