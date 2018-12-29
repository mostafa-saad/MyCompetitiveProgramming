(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego zapytania oblicza ile jest        *
 *                         elementow kazdego typu.                       *
 *                                                                       *
 *************************************************************************)
 
const
	MAXN = 500005;

var
	t, count: array[0..MAXN-1] of longint;
	n, m, a, b, i, j, maxIdx, maxCount: longint;

begin
	readln(n, m);
	for i:=0 to n-1 do
		read(t[i]);
	
	for i:=0 to m-1 do
	begin
		readln(a, b);
		dec(a);
		dec(b);

		for j:=1 to n do
			count[j] := 0;
		for j:=a to b do
			inc(count[t[j]]);

		maxIdx := -1;
		maxCount := -1;
		for j:=1 to n do
			if (count[j] > maxCount) then
			begin
				maxCount := count[j];
				maxIdx := j;
			end;

		if (maxCount > (b-a+1) div 2) then
			writeln(maxIdx)
		else
			writeln(0);
	end;
end.
