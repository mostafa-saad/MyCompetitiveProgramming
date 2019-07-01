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
	N, K, solSize, i, j, curPos: longint;
	t, col, next, seq: array[0..MAX_N] of longint;
	pos: array[0..MAX_K] of longint;
	f, result: array[0..2,0..MAX_N] of longint;
	s, finalRes: array[0..2] of longint;
	solution: array[0..MAX_N] of longint;

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
	
	for i:=0 to N-1 do
	begin
		read(t[i]);
		dec(t[i]);
	end;

	readln(s[0], s[1]);

	for i:=0 to 1 do
	begin
		curPos := 0;

		for j:=0 to K-1 do
			pos[j] := N;
		for j:=N-1 downto 0 do
		begin
			next[j] := pos[t[j]];
			pos[t[j]] := j;
		end;

		for j:=1 to s[i] do
		begin
			read(col[j]);
			dec(col[j]);
		end;

		for j:=1 to s[i] do
		begin
			while ((pos[col[j]] < curPos) and (pos[col[j]] < N)) do
				pos[col[j]] := next[pos[col[j]]];
			curPos := pos[col[j]];
			seq[j] := curPos;
		end;

		for j:=0 to N-1 do
		begin
			curPos := 0;
			seq[0] := j;

			while (curPos <= s[i]) do
			begin
				while ((seq[curPos] >= seq[curPos+1]) and (seq[curPos+1] < N)) do
					seq[curPos+1] := next[seq[curPos+1]];
				inc(curPos);
			end;

			f[i][j] := seq[s[i]];
		end;

		if (i = 0) then
		begin
			for j:=0 to N-1 do
				result[0][j] := N;
			for j:=0 to N-1 do
				result[0][t[j]] := min(result[0][t[j]], f[0][j]);
		end;
		if (i = 1) then
		begin
			for j:=0 to N-1 do
				result[1][t[j]] := max(result[1][t[j]], N-1-f[1][j]);
		end;

		for j:=0 to (N-1) div 2 do
			exchange(t[j], t[N-j-1]);
	end;

	finalRes[0] := N;
	for i:=0 to K do
		if (result[0][i] <= result[1][i]) then
		begin
			finalRes[0] := min(finalRes[0], result[0][i]);
			finalRes[1] := max(finalRes[1], result[1][i]);
		end;

	for j:=finalRes[0] to finalRes[1] do
		if (t[j] = col[s[1]]) then
		begin
			solution[solSize] := j;
			inc(solSize);
		end;

	writeln(solSize);
	for i:=0 to solSize-1 do
		write(solution[i]+1, ' ');
	writeln;
end.
