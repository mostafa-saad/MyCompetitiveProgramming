(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * n + m)                                     *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000000;
	MAX_K = 2000000;

var
	n, m		: longint; { ilosc segmentow, ilosc rozwazanych cen }
	i, l, sum	: longint; { iteratory i zmienna pomocnicza }
	s			: ansistring; { opis lizaka }
	wa, wb		: array[1..MAX_K] of longint; { [wa[j], wb[j]] to przedzial o koszcie j }

begin
	readln(n, m);
	readln(s);
	
	for i := 1 to n do
	begin
		wa[2*i - 1] := 0;
		wa[2*i] := 0;
	end;

	{ sprawdzamy wszystkie przedzialy i wypelniamy tablice wa[], wb[] }
	for i := 1 to n do
	begin
		sum := 0;
		for l := i to n do
		begin
			if s[l] = 'T' then
				sum := sum + 2
			else
				sum := sum + 1;

			wa[sum] := i;
			wb[sum] := l;
		end;
	end;

	{ odpowiadamy na zapytania korzystajac z tablic wa[] i wb[] }
	for i := 1 to m do
	begin
		readln(sum);
		if wa[sum] = 0 then
			writeln('NIE')
		else
			writeln(wa[sum], ' ', wb[sum]);
	end;
end.
