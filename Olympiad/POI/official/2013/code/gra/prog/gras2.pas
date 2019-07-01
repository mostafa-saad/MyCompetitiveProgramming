(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O((n+m) * liczba_losowan)                     *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Losuje rozmieszczenie wiez do skutku          *
 *                                                                       *
 *************************************************************************)

const MAXN =  500000;
const MAXM = 1000000;
var
n, m, k, i, j, a, b, c, kk : Longint;
edges, perm : array[0..MAXN+1] of Longint;
safe : array[1..MAXN] of Boolean;
next, v : array[0..2*MAXM+7] of Longint; {listy sasiedztwa}
ok : Boolean;

begin
	{inicjalizacja}
	c := 0;
	for i := 1 to MAXN do
	begin
		safe[i] := False;
		edges[i] := 0;
	end;
	{wejscie}
	Read(n);
	Read(m);
	Read(kk);
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
		perm[i] := i;
	while True do
	begin
		for i := n downto 2 do
		begin
			j := 1 + random(i);
			k := perm[i];
			perm[i] := perm[j];
			perm[j] := k;
		end;
		for i := 1 to n do
			safe[i] := False;
		for i := 1 to kk do
			begin
				safe[perm[i]] := True;
				j := edges[perm[i]];
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
			ok := True;
			for i := 1 to n do
				if not safe[i] then
					ok := False;
			{wyjscie}
			if ok then
			begin
				Writeln(kk);
				for i := 1 to kk do
				begin
					Write(perm[i]);
					Write(' ');
				end;
				Exit();
			end;
		end;
end.
