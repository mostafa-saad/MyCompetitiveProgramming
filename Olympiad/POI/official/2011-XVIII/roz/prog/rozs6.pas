(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k * k)                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzamy klopotliwy przypadek oddzielnie tzn.  *
 *                      gdy mniej liczne litery sa w liczbie 1,          *
 *                      nastepnie przerabiamy slowo na ciag -1 0 1       *
 *                      i znajdujemy segment o maksymalnej sumie,        *
 *                      ktory zawiera -1                                 *
 *                                                                       *
 *************************************************************************)

program roznica;

const 
	MAXN = 1000005;		
	MAXK = 26;

var
	slowo : array[0..MAXN - 1] of longint;		// tablica z wczytanym slowem
	licznik : array[0..MAXK - 1] of longint;		// tymczasowa tablica trzymajaca liczby poszczegolnych liter
	ciag : array[0..MAXN - 1] of longint;			// wczytane slowo przerabiamy do postaci ciagu -1 0 1
	n, suma, maks, i, j, k : longint;
	c : char;
	ok : boolean;				// ok oznacza czy segment zawiera -1

function max(a, b : longint) : longint;
begin
	if a > b then 
		max := a
	else
		max := b;
end;

begin
	// wczytanie slowa i przesuniecie
	readln(n);
	for i := 0 to n - 1 do
	begin	
		read(c);
		slowo[i] := byte(c) - 97;
	end;
	maks := 0;


	// sprawdzanie czy mniejliczne litery sa jednoelementowe
	for i := 0 to MAXK - 1 do
	begin
		// czyszczenie
		for j := 0 to MAXK - 1 do
			licznik[j] := 0;
		ok := false;
		for j := 0 to n - 1 do
			if slowo[j] = i then
			begin
				ok := true;
				for k := 0 to MAXK - 1 do
				begin
					if (licznik[k] > maks) then
						maks := max(maks, licznik[k] - 1);
					licznik[k] := 0;
				end;
			end
			else
				inc(licznik[slowo[j]]);
				if (ok) then
					for k := 0 to MAXK - 1 do
						if(licznik[k] > maks) then
							maks := max(maks, licznik[k] - 1);
	end;

	for i := 0 to MAXK - 1 do
		for j := 0 to MAXK - 1 do
		begin
			// konwersja ciagu liter do ciagu -1 0 1
			for k := 0 to n - 1 do
			begin
				if slowo[k] = i then
					ciag[k] := 1
				else 
					if slowo[k] = j then
						ciag[k] := -1
					else
						ciag[k] := 0;
			end;
			suma := 0;
			ok := false;

			// wyszukiwanie segmentu o maksymalnej sumie
			for k := 0 to n - 1 do
			begin
				suma := suma + ciag[k];
			
				if suma < 0 then
				begin
					suma := 0;
					ok := false;
				end
				else
					if ciag[k] = -1 then
						ok := true;

				if ok then
					maks := max(maks, suma);
			end;				
	end;

	writeln(maks);
end.

