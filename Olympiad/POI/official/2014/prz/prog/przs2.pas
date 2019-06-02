(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Przestepcy                                    *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000001;
	MAX_K = 1000001;
var
	N, K, solSize, i, j, l: longint;
	t: array[0..MAX_N] of longint;
	col: array[0..1,0..MAX_K] of longint;
	s, finalRes, p: array[0..1] of longint;
	solution: array[0..MAX_N] of longint;
	ok: boolean;

function min(a, b: longint): longint;
begin
	if (a < b) then
		min := a
	else
		min := b;
end;

function max(a, b: longint): longint;
begin
	if (a < b) then
		max := b
	else
		max := a;
end;

procedure exchange(var a, b: longint);
var
	tmp: longint;
begin
	tmp := a;
	a := b;
	b := tmp;
end;

begin
	solSize := 0;

	readln(N, K);

	finalRes[0] := N;
	finalRes[1] := 0;

	for i:=0 to N-1 do
	begin
		read(t[i]);
		dec(t[i]);
	end;

	readln(s[0], s[1]);

	for i:=0 to 1 do
		for j:=1 to s[i] do
		begin
			read(col[i][j]);
			dec(col[i][j]);
		end;
	
	for i:=0 to K-1 do
	begin
		ok := false;

		col[0][0] := i;
		col[1][0] := i;
		p[0] := 0;
		p[1] := 0;

		for l:=0 to N-1 do
		begin
			if ((p[0] <= s[0]) and (col[0][p[0]] = t[l])) then
				inc(p[0]);
			if (p[0] = s[0]+1) then
			begin
				p[0] := l;
				ok := true;
				break;
			end;
		end;
		if (not ok) then
			p[0] := N;

		ok := false;
		for l:=N-1 downto 0 do
		begin
			if ((p[1] <= s[1]) and (col[1][p[1]] = t[l])) then
				inc(p[1]);
			if (p[1] = s[1]+1) then
			begin
				p[1] := l;
				ok := true;
				break;
			end;
		end;
		if (not ok) then
			p[1] := 0;

		if (p[0] <= p[1]) then
		begin
			finalRes[0] := min(finalRes[0], p[0]);
			finalRes[1] := max(finalRes[1], p[1]);
		end;
	end;

	for j:=finalRes[0] to finalRes[1] do
		if (t[j] = col[0][s[0]]) then
		begin
			solution[solSize] := j;
			inc(solSize);
		end;
	
	writeln(solSize);
	for i:=0 to solSize-1 do
		write(solution[i]+1, ' ');
	writeln;
end.
