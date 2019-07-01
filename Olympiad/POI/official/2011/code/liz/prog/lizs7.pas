(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * m * lg(n))                                 *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie przez bisekcje, dla kazdej nieznanej *
 *                      kwoty wykonujemy wyszukiwanie binarne            *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000000;
	MAX_K = 2000000;

var
	n, m	: longint;	{ ilosc segmentow lizaka i ilosc rozwazanych cen }
	sum		: array[0..MAX_N]of longint; { sum[i] cena fragmentu [1, i] }
	i, l, k	: longint;
	a, b, c	: longint; { poczatek, koniec i srodek rozwazanego przedzialu }
	wa, wb	: array[1..MAX_K]of longint; { przedzial wynikowy }
	s		: ansistring;	{ opis lizaka }

begin
	readln(n, m);
	readln(s);

	sum[0] := 0;
	for i := 1 to n do
	begin
		if s[i] = 'W' then
			sum[i] := sum[i - 1] + 1
		else
			sum[i] := sum[i - 1] + 2;

		wa[2*i - 1] := -1;
		wa[2*i] := -1;
	end;
	
	for i := 1 to m do
	begin
		readln(k);
		l := 0;
		{ zaczynamy przeszukiwanie jezeli nie znamy przedzialu o koszcie k }
		while (wa[k] = -1) and (sum[n] - sum[l] >= k)do
		begin
			{ przeszukiwanie binarne konca przedzialu dla poczatku l }
			a := l;
			b := n;
			while a < b do
			begin
				c := (a + b) div 2;
				if sum[c] - sum[l] < k then
					a := c + 1
				else if sum[c] - sum[l] > k then
					b := c - 1
				else begin
					a := c;
					b := c;
				end;
			end;

			if sum[a] - sum[l] = k then
			begin
				wa[k] := l + 1;
				wb[k] := a;
			end;
			l := l + 1;
		end;

		if wa[k] = -1 then
			wa[k] := 0;

		if wa[k] <> 0 then
			writeln(wa[k], ' ', wb[k])
		else
			writeln('NIE');
	end;
end.
