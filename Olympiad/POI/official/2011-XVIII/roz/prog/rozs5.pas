(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(k * n ^ 2)                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Zliczamy liczbe wystapien poszczegolnych liter   *
 *                      na prefiksach slowa a nastepnie rozpatrujemy     *
 *                      kazdy segment                                    *
 *                                                                       *
 *************************************************************************)

program roznica;

const
	MAXN = 1000005;

var
	slowo : array[0..MAXN - 1] of longint;		// tablica z wczytanym slowem
	pref : array[0..MAXN - 1, 0..25] of longint;		// oznacza liczbe przeczytanych liter do danego indeksu
licznik : array[0..25] of longint;		// tymczasowa tablica trzymajaca liczbe poszczegolnych liter
	n, i, j, k, maks, mini, wynik : longint;
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
	// wczytanie slowa i przesuniecie
	readln(n);
	for i := 0 to n - 1 do
	begin	
		read(c);
		slowo[i] := byte(c) - 97;
	end;
	maks := 0;
	wynik := 0;

	for i := 0 to MAXN - 1 do
		for j := 0 to 25 do
			pref[i][j] := 0;

	// obliczam liczbe poszczegolnych liter do danego momentu
	for i := 1 to n do
	begin
		for j := 0 to 25 do
			pref[i][j] := pref[i - 1][j];
		inc(pref[i][slowo[i - 1]]);
	end;

	// wyliczamy najlepszy fragment dla kazdych koncow
	for i := 0 to n - 1 do
		for j := i + 1 to n - 1 do
		begin
			// ustawienie licznika na wybranym segmencie
			for k := 0 to 25 do
				licznik[k] := pref[j + 1][k] - pref[i][k];
			
			// szukamy max i min
			maks := 0;
			mini := MAXN;
			for k := 0 to 25 do
			begin
				maks := max(maks, licznik[k]);
				if (licznik[k] > 0) then
					mini := min(mini, licznik[k]);
			end;
			
			wynik := max(wynik, maks - mini);
		end;

	writeln(wynik);
end.
