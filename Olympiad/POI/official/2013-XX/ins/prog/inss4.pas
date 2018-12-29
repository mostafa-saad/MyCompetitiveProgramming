(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(m^(2n) * n)                                 *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wolne.                            *
 *                         Generujemy wszystkie mozliwe godziny przyjscia*
 *                         oraz wyjscia wszystkich informatykow.         *
 *                                                                       *
 *************************************************************************)

program zbrs4;

const
	MAXN = 100;

var
test, tests : Integer;
N, M : Integer;
T, K, II, L, R, X : array[0..MAXN] of Integer;
i, res : Integer;

procedure gen(act : Integer);
var
i, j, ok : Integer;
begin
	if act = (N + 1) then
	begin
		for i := 0 to M do
			X[i] := 0;
		for i := 1 to N do
			for j := L[i] to R[i] do
				X[j] := X[j] + 1;
		ok := 0;
		for i := 1 to M do
			if not(X[T[i]] = II[i] + 1) or (R[K[i]] < T[i]) or (L[K[i]] > T[i]) then
					break
				else
					ok := ok + 1;
		if ok > res then
			res := ok;
	end
	else
	begin
		L[act] := 0;
		R[act] := 0;
		gen(act+1);
		for i := 1 to M do
			for j := i to M do
			begin
				L[act] := i;
				R[act] := j;
				gen(act+1);
			end;
	end;
end;

begin
	Read(tests);
	for test := 1 to tests do
	begin
		Read(N);
		Read(M);
		for i := 1 to M do
		begin
			Read(T[i]);
			Read(K[i]);
			Read(II[i]);
		end;
		
	res := 0;
	gen(1);
	Writeln(res);
	end;
end.
