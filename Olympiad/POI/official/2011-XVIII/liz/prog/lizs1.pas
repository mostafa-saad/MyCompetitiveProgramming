(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * n * m)                                     *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000000;

var
	n, m		: longint; { ilosc segmentow, ilosc rozwazanych cen }
	i, l, j		: longint; { iteratory }
	k, sum 		: longint;
	s			: ansistring; { opis lizak }

begin
	readln(n, m);
	readln(s);
			
	for j := 1 to m do
	begin
		readln(k);
		i := 0;
		while (k <> 0) and (i < n) do
		begin
			sum := 0;
			i := i + 1;
			l := i - 1;
			while (k <> 0) and (l < n) do
			begin
				l := l + 1;
				if s[l] = 'W' then
					sum := sum + 1
				else
					sum := sum + 2;

				if sum = k then
					k := 0;
			end;
		end;

		if k <> 0 then
			writeln('NIE')
		else
			writeln(i, ' ', l);
	end;
end.
