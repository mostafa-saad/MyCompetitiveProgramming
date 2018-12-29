unit maja;

	{ modu³ graj±cy umo¿liwiaj±cy przetestowanie swojego rozwi±zania }

interface

	function gramy_dalej: longint;
	{ inicjalizuje kolejna gre, 
		zwraca:
			ograniczenie gorne na zgadywane liczby 
			albo 0, jesli juz nie gramy dalej }

	function czy_podzielna_przez(m : longint) : boolean;
	{ zapytanie, czy wymyslona przez Majê liczba jest podzielna przez m }
	{ wej¶cie: m > 0 }
	
	procedure zgaduj(k : longint);
	{ próba zgadniêcia liczby; wolno probowac tylko raz }

implementation

	var l, ile_pytan: longint;
	var gramy : boolean;

	procedure blad(s: string); 
	begin
		writeln('BLAD: ', s);
		halt(1);
	end;

	function gramy_dalej: longint;
	var n: longint;
	begin
		if (gramy) then blad('powinienes sprobowac zgadnac liczbe przed kolejna gra');
		write('Podaj n - ograniczenie górne na liczby w grze (0 - koniec): ');
		readln(n);
		if n <= 0 then gramy_dalej := 0 else begin
			repeat
				write('Podaj liczbe jaka ma wymyslic Maja ');
				readln(l);
				if (l <= 0) or (l > n) then writeln('zle, liczba poza zakresem!');
			until not ((l <= 0) or (l > n));
			gramy_dalej := n;
			ile_pytan := 0;
			gramy := true;
		end;	
	end;

	function czy_podzielna_przez(m : longint) : boolean;
	begin
		if (not gramy) then blad('nie zainicjalizowano gry, zapytanie o podzielnosc');
		if m <= 0 then blad('podano m niedodatnie'); 
		inc(ile_pytan);
		czy_podzielna_przez := ((l mod m) = 0);
	end;
	
	procedure zgaduj(k : longint);
	begin
		if (not gramy) then blad('nie zainicjalizowano gry, proba zgadniecia');
		if (k = l) then writeln('Twoj program zgadl w ',ile_pytan,' pytaniach! ta liczba to ', l)
			else writeln('Twoj program nie zgadl! ta liczba to ', l, ' a nie ', k);
		gramy := false;	
	end;	
	
begin
  { inicjalizacja }
	gramy := false;
end.
