(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Binarnie wyszukujemy minimalnego czasu, w ktorym *
 *                      mozemy wysadzic ladunki                          *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 300000;

type
	kolejka_statyczna = record 
		w		: array[0..MAX_N] of longint;	{ wartosci kolejki }
		p, k	: longint;		{ poczatek i koniec kolejki }
	end;

var
	n, m	: longint;
	{ ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont }
	d	: array[1..MAX_N] of boolean;	{ czy w i-tej komorze jest dynamit }
	korytarze	: array[0..2 * MAX_N] of longint;	
	{ tablica opisujaca siec komor }
	koniec		: array[0..MAX_N] of longint;	
	{ koniec listy sasiedztwa dla i-tej komory }
	ilosc		: array[1..MAX_N] of longint;	
	{ ilosc elementow w i-tej liscie sasiedztwa }

	q	: kolejka_statyczna;	{ pomocnicza kolejka }
	a, b, c, i, j, p, x	: longint;	{ zmienne pomocnicze }
	z	: array[0..MAX_N] of longint;	{ tablice pomocnicze }
	min_tab, max_tab	: array[1..MAX_N] of longint;
	{ ile minimalnie w dol, ile maksymalnie w gore }

{ wczytaj() - wczytuje dane i zmienia reprezentacje sieci komor.
  t[] bedzie zawierala listy sasiedztw kolejnych komor.
  Konce kolejnych list zapamietamy w k[]. }
procedure wczytaj;
begin
	readln (n, m);
	x := 0;
	for i := 1 to n do
	begin
		read (a);
		d[i] := (a = 1);
		ilosc[i] := 0;
		x := x + a;
	end;
	
	for i := 1 to n - 1 do
	begin
		readln (min_tab[i], max_tab[i]);
		ilosc[min_tab[i]] := ilosc[min_tab[i]] + 1;
		ilosc[max_tab[i]] := ilosc[max_tab[i]] + 1;
	end;

	koniec[0] := 0;
	for i := 1 to n do
	begin
		koniec[i] := ilosc[i] + koniec[i - 1];
		z[i] := koniec[i - 1];
	end;

	for i := 1 to n - 1 do
	begin
		korytarze[z[min_tab[i]]] := max_tab[i];
		z[min_tab[i]] := z[min_tab[i]] + 1;
		korytarze[z[max_tab[i]]] := min_tab[i];
		z[max_tab[i]] := z[max_tab[i]] + 1;
	end;
end;


{ sprawdz(x) - sprawdza, czy jestesmy w stanie wysadzic wszystkie
  dynamity w x jednostkach czasu. }
function  sprawdz (czas : longint) : boolean;
begin
	{ wyznaczamy liscie i wrzucamy na statyczna kolejke q }
	q.p := 0;	q.k := 0;
	for i := 1 to n do
	begin
		min_tab[i] := 0;
		max_tab[i] := 0;
		z[i] := ilosc[i];
		if z[i] = 1 then
		begin
			q.w[q.k] := i;
			q.k := q.k + 1;
		end;
	end;
	
	j := m;
	{ wyznaczamy miejsca, w ktorych musimy podpalic lont }
	while (j >= 0) and (q.p < q.k) do
	begin
		p := q.w[q.p];
		q.p := q.p + 1;
		if max_tab[p] > -min_tab[p] then { zapali sie od poprzedniego lontu }
			min_tab[p] := 0
		else if min_tab[p] = -czas then { musimy podpalic lont }
		begin
			j := j - 1;
			max_tab[p] := czas + 1;
			min_tab[p] := 0;
		end;

		for i := koniec[p - 1] to koniec[p] - 1 do
		begin
			x := korytarze[i];
			if z[x] > 0 then
			begin
				if max_tab[x] < max_tab[p] - 1 then
					max_tab[x] := max_tab[p] - 1;
				if (min_tab[p] < 0) or ((max_tab[p] = 0) and d[p]) then
					if min_tab[x] > min_tab[p] - 1 then
						min_tab[x] := min_tab[p] - 1;
				z[x] := z[x] - 1;
				if z[x] = 1 then
				begin
					q.w[q.k] := x;
					q.k := q.k + 1;
				end;
			end;
		end;
	end;

	{ sprawdzamy, czy w ostatnim rozwazanym wierzcholku nalezy zapalic lont }
	if j >= 0 then
	begin
		p := q.w[q.p - 1];
		if (min_tab[p] < 0) or ((max_tab[p] = 0) and d[p]) then
			j := j - 1;
	end;
	
	{ jezeli nie podpalilismy za duzo lontow i przetworzylismy cale drzewo
	  to mozna w [czas] jednostek czasu podpalic wszystkie dynamity }
	sprawdz :=  (j >= 0) and (q.p = q.k); 
end;


{*****************************  MAIN  ************************************}
Begin
	wczytaj;
	
	if x <= m then
		writeln (0)
	else begin
		{ binarne wyszukiwanie wyniku }
		a := 1;
		b := n div 2;
		while a < b do
		begin
			c := (a + b) div 2;
			
			if sprawdz (c) then
				b := c
			else
				a := c + 1;
		end;

		writeln (a);
	end;
End.
