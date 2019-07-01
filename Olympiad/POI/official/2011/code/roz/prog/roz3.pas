(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Badamy od poczatku i konca mozliwe slowa         *
 *                      dynamicznie uaktualniajac liczbe liter           *
 *                      ktore sie pojawily i mialy sens                  *
 *                                                                       *
 *************************************************************************)

program Roznica;

const MAXN = 1000005;	

var
	slowo : array[0..MAXN - 1] of Longint;		// tablica z wczytanym slowem
	licznik : array[0..25] of Longint;		// tymczasowa tablica trzymajaca liczby poszczegolnych liter
	ok : array[0..25] of Boolean;			// prawda oznacza ze potrzebujemy jeszcze dodatkowej liter na poczatku lub na koncu segmentu zlozonego z badanej litery
	n, licz, maks, i, j, k : Longint;
	c : char;

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

	// wyliczamy najlepszy fragment dla kazdej litery 
	for i := 0 to 25 do
	begin
		
		// czyszczenie
		for j := 0 to 25 do
		begin
			ok[j] := false;
			licznik[j] := 0;
		end;
		licz := 0;

		// petla po slowie od poczatku, gdy trafimy na badana litere zwiekszamy
		// jej liczbe i sprawdzamy czy max sie poprawil
		// w drugim przypadku zwiekszamy liczbe innej litery o ile ma to sens
		for j := 0 to n - 1 do
			if slowo[j] = i then
			begin
				inc(licz);
				for k := 0 to 25 do
					if (licz - licznik[k] > maks) and (licznik[k] > 0) then
							maks := max(maks, licz - licznik[k]);
			end
			else
			begin
				if licznik[slowo[j]] < licz + 1 then
					inc(licznik[slowo[j]]);
				if licznik[slowo[j]] > licz then
					ok[slowo[j]] := true
				else
					if ok[slowo[j]] = true then
					begin
						ok[slowo[j]] := false;
						dec(licznik[slowo[j]]);
						maks := max(maks, licz - licznik[slowo[j]]);
					end;
			end;

		// czyszczenie
		for j := 0 to 25 do
		begin
			ok[j] := false;
			licznik[j] := 0;
		end;
		licz := 0;

		// petla po slowie od konca
		for j := n - 1 downto 0 do
			if slowo[j] = i then
			begin
				inc(licz);
				for k := 0 to 25 do
					if (licz - licznik[k] > maks) and (licznik[k] > 0) then
							maks := max(maks, licz - licznik[k]);
			end
			else
			begin
				if licznik[slowo[j]] < licz + 1 then
					inc(licznik[slowo[j]]);
				if licznik[slowo[j]] > licz then
					ok[slowo[j]] := true
				else
					if ok[slowo[j]] = true then
					begin
						ok[slowo[j]] := false;
						dec(licznik[slowo[j]]);
						maks := max(maks, licz - licznik[slowo[j]]);
					end;
			end;
	end;


	// wypisanie wyniku
	writeln(maks);

end.
