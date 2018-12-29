(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Sprawdzamy jedynie przedzialy zaczynajaca sie na *
 *                      poczatku i konczace na koncu lizaka              *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000000;
	MAX_K = 2000000;

var
	n, m, k	: longint; { ilosc segmentow, rozwazanych wag i rozwazana waga }
	i		: longint;
	sum 	: longint;
	s		: ansistring; { opis lizaka }
	wa, wb	: array[0..MAX_K] of longint;	{ [wa[j], wb[j]] to przedzial o koszcie j }

begin
	readln(n, m);
	readln(s);

	for i := 1 to 2*n do
	begin
		wa[i] := 0;
		wb[i] := 0;
	end;
	
	{ uwzgledniamy przedzialy zaczynajace sie w segmencie nr 1 }
	sum := 0;
	for i := 1 to n do
	begin
		if s[i] = 'W' then
			sum := sum + 1
		else
			sum := sum + 2;

		wa[sum] := 1;
		wb[sum] := i;
	end;
	
	{ uwzgledniamy przedzialy konczace sie w ostatnim segmencie }
	sum := 0;
	for i := n downto 1 do
	begin
		if s[i] = 'W' then
			sum := sum + 1
		else
			sum := sum + 2;

		wa[sum] := i;
		wb[sum] := n;
	end;
			
	for i := 1 to m do
	begin
		readln(k);
		
		if wa[k] = 0 then
			writeln('NIE')
		else
			writeln(wa[k], ' ', wb[k]);
	end;
end.
