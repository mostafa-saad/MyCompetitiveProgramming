(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * m * lg(n))                                 *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie przez bisekcje                       *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000000;

var
	n, m	: longint;	{ ilosc sementow lizaka i ilosc rozwazanych cen }
	sum		: array[0..MAX_N]of longint; { sum[i] cena fragmentu [1, i] }
	i, l, k	: longint;
	a, b, c	: longint; { poczatek, koniec i srodek rozwazanego przedzialu }
	wa, wb	: longint; { przedzial wynikowy }
	s		: ansistring;	{ opis lizaka }

begin
	readln(n, m);
	readln(s);

	sum[0] := 0;
	for i := 1 to n do
		if s[i] = 'W' then
			sum[i] := sum[i - 1] + 1
		else
			sum[i] := sum[i - 1] + 2;
	
	for i := 1 to m do
	begin
		readln(k);
		wa := 0;
		if k <= sum[n] then
		begin
			l := 0;
			while (wa = 0) and (l < n) do
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
					wa := l + 1;
					wb := a;
				end;
				l := l + 1;
			end;
		end;

		if wa <> 0 then
			writeln(wa, ' ', wb)
		else
			writeln('NIE');
	end;
end.
