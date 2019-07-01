(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Sprawdzamy klopotliwy przypadek oddzielnie tzn.  *
 *                      gdy mniej liczne litery sa w liczbie 1, potem    *
 *                      dynamicznie wyliczamy minimalne prefiksy dla     *
 *                      kazdej pary i z tego otrzymujemy maksymalna sume *
 *                                                                       *
 *************************************************************************)

program roznica;

const 
	MAXN = 1000005;		
	MAXK = 26;

var
	slowo : array[0..MAXN - 1] of longint;		// tablica z wczytanym slowem
	licznik : array[0..MAXK - 1] of longint;		// tymczasowa tablica trzymajaca liczby poszczegolnych liter
	pref : array[0..MAXK - 1, 0..MAXK - 1] of longint;	// roznica pomiedzy liczba liter na najgorszym mozliwym prefiksie
	n, temp, maks, i, j, k : longint;
	c : char;
	ok : boolean;
	oki : array[0..MAXK - 1, 0..MAXK - 1] of boolean;	// tablica oki oznacza czy pomiedzy najgorszym mozliwym prefiksem a aktualnym indeksem jest mniejliczna litera ok analogicznie dla szczegolnego przypadku

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
	for i := 0 to MAXK - 1 do
		for j := 0 to MAXK - 1 do
		begin
			oki[i][j] := false;
			pref[i][j] := 0;
		end;


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

	//czyszczenie
	for j := 0 to MAXK - 1 do	
		licznik[j] := 0;


	// dynamik na biezaco uaktualnia najgorsze mozliwe prefiksy
	for j := 0 to n - 1 do
	begin
		temp := slowo[j];
		inc(licznik[temp]);

		for k := 0 to MAXK - 1 do
			if (oki[temp][k]) then
				maks := max(maks, licznik[temp] - licznik[k] - pref[temp][k]);
		for k := 0 to MAXK - 1 do
		begin
			oki[k][temp] := true;
			if (pref[k][temp] > licznik[k] - licznik[temp]) then
			begin
				pref[k][temp] := licznik[k] - licznik[temp];
				oki[k][temp] := false;
			end;
		end;

	end;

	// wypisanie wyniku
	writeln(maks);

end.
