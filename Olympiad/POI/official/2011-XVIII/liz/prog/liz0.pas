(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 1000000;
	MAX_K = 2000000;

var
	n, m		: longint;	{ ilosc segmentow lizaka i ilosc rozwazanych cen }
	wa, wb		: array[0..MAX_K] of longint;	{ [wa[j], wb[j]] to przedzial o koszcie j }
	i, l, sum	: longint;
	max			: array[0..1] of longint;	{ najwieksza cena parzysta i nieparzysta }
	s			: ansistring;	{ opis lizaka }

{ funkcja obliczajaca wa[x], wb[x] dla (x <= sum) i ((sum + x) mod 2 = 0) }
procedure oblicz_przedzialy (sum : longint);
begin
	wa[sum] := i;
	wb[sum] := l;

	while (sum > 2) do
	begin
		while (sum > 2) and (s[i] = 'T') do
		begin
			i := i + 1;
			sum := sum - 2;
			wa[sum] := i;
			wb[sum] := l;
		end;

		while (sum > 2) and (s[l] = 'T') do
		begin
			l := l - 1;
			sum := sum - 2;
			wa[sum] := i;
			wb[sum] := l;
		end;
		
		if sum > 2 then
		begin
			i := i + 1;
			l := l - 1;
			sum := sum - 2;
			wa[sum] := i;
			wb[sum] := l;
		end;
	end;
end;

begin
	readln(n, m);
	readln(s);

	sum := 0;
	for l := 1 to n do
		if s[l] = 'T' then
			sum := sum + 2
		else
			sum := sum + 1;
	
	i := 1;
	l := n;
	max[sum mod 2] := sum;

	oblicz_przedzialy(sum); 

	{ szukamy 'W' najblizszego krawedzi lizaka by wyznaczyc najwiekszy 
	  fragment, ktorego cena ma inna parzystosc niz cena calego lizaka }
	i := 1;
	while (i < n) and (s[i] = 'T') do
		i := i + 1;

	l := 1;
	while (i < n - l + 1) and (s[n - l + 1] = 'T') do
		l := l + 1;
	
	if s[i] = 'T' then { brak smaku waniliowego }
		max[1] := 0
	else begin
		if i < l then { 'W' blizej lewego konca }
		begin
			sum := sum - (2 * i - 1);
			max[sum mod 2] := sum;
			i := i + 1;
			l := n;
		end else begin { 'W' blizej prawego konca (lub rownie blisko) }
			sum := sum - (2 * l - 1);
			max[sum mod 2] := sum;
			i := 1;
			l := n - l;
		end;
		oblicz_przedzialy(sum);
	end;

	{ odpowiadamy na zapytania korzystajac z tablic wa[] i wb[] }
	for i := 1 to m do
	begin
		readln(sum);

		if max[sum mod 2] < sum then
			writeln('NIE')
		else
			writeln(wa[sum], ' ', wb[sum]);
	end;
end.
