(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n ^ 3)                                         *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzamy kazdy mozliwy segment                 *
 *                                                                       *
 *************************************************************************)

program roznica;

const
	MAXN = 1000005;

var
	slowo : array[0..MAXN - 1] of longint;		// tablica z wczytanym slowem
	licznik : array[0..25] of longint;		// tymczasowa tablica trzymajaca liczbe poszczegolnych liter
	i, j, k, n,  maks, mini, wynik : longint;
	c : char;

function max(a, b : longint) : longint;
begin
	if a > b then 
		max := a
	else
		max := b;
end;

function min(a, b : longint) : longint;
begin
	if a > b then 
		min := b
	else
		min := a;
end;

begin
	readln(n);
	for i := 0 to n - 1 do
	begin	
		read(c);
		slowo[i] := byte(c) - 97;
	end;
	maks := 0;
	wynik := 0;

	// wyliczamy najlepszy fragment dla kazdych koncow
	for i := 0 to n - 1 do
		for j := i + 1 to n - 1 do
		begin
			// czyszczenie licznika
			for k := 0 to 25 do
				licznik[k] := 0;

			// petla po segmencie
			for k := i to j do
				inc(licznik[slowo[k]]);
			
			// szukamy max i min
			maks := 0;
			mini := MAXN;
			for k := 0 to 25 do
			begin
				maks := max(maks, licznik[k]);
				if licznik[k] > 0 then
					mini := min(mini, licznik[k]);
			end;
			
			wynik := max(wynik, maks - mini);
			
		end;

	writeln(wynik);
end.
