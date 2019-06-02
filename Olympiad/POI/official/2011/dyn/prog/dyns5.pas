(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * n * lg(n))                                 *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Ukorzeniamy drzewo, binarnie wyszukujemy wynik,  *
 *                      symulujemy odpalenie lontu, wyznaczajac kolejne  *
 *                      optymalne pozycje (najnizej polozone poddrzewo   *
 *                      o wysokosci rownej wynikowi)                     *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 300000;

type
	kolejka_statyczna = record
		w		: array [0..MAX_N] of longint;	{ wartosci kolejki }
		p, k	: longint;		{ poczatek i koniec kolejki }
	end;

	pstos = ^stos;
	stos = record
		w	: longint;	{ wartosc elementu stosu }
		nx	: pstos;	{ wskaznik na nastepny element stosu }
	end;

procedure wrzuc (var s : pstos; x : longint);
var
	tmp : pstos;
begin
	tmp := new (pstos);
	tmp^.w := x;
	tmp^.nx := s;
	s := tmp;
end;

function zdejmij (var s : pstos) : longint;
var
	tmp	: pstos;
	z	: longint;
begin
	if s <> nil then
	begin
		tmp := s;
		z := tmp^.w;
		s := tmp^.nx;
		dispose (tmp);

		zdejmij := z;
	end else
		zdejmij := -1;
end;

var
	n, m	: longint;	
	{ ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont }
	d		: array[0..MAX_N] of longint;	
	{ d[i] == 0 wtw., gdy w i-tej komorze nie ma dynamitu }
	korytarze	: array[0..MAX_N] of pstos;
	{ listy sasiedztwa zrealizowane przy pomocy stosow }
	ilosc	: array[0..MAX_N] of longint;
	{ ilosc elementow w i-tej liscie sasiedztwa }
	ojciec	: array[0..MAX_N] of longint;	{ojciec w ukorzenionym drzewie }

	q		: kolejka_statyczna;	{ pomocnicza kolejka }
	a, b, c, i, j, x	: longint;	{ zmienne pomocnicze }
	v	: array[0..MAX_N] of longint;	{ tablice pomocnicze }
	dynamit	: array[0..MAX_N] of longint;	{ ktore komnaty juz przetworzone }
	wysokosc	: array[0..MAX_N] of pstos;	{ stosy z wierzcholkami na wys. i }


procedure wczytaj;
begin
	readln (n, m);

	for i := 1 to n do
	begin
		read (d[i]);
		korytarze[i] := nil;
		wysokosc[i] := nil;
	end;
	
	for i := 1 to n - 1 do
	begin
		readln (a, b);
		wrzuc (korytarze[a], b);
		wrzuc (korytarze[b], a);
		ilosc[a] := ilosc[a] + 1;
		ilosc[b] := ilosc[b] + 1;
	end;
end;


{ ukorzenia drzewo w wierzcholku nr 1, oblicza tablice ojciec i wysokosc }
procedure ukorzen;
var
	s	: pstos;
	z	: longint;
begin
	s := nil;
	for i := 1 to n do
		dynamit[i] := -1;
	dynamit[1] := 0;
	{ tymczasowo do zapamietania wysokosci na jakiej sa wierzcholki }

	q.p := 0;
	q.k := 1;
	q.w[0] := 1;
	wrzuc (wysokosc[0], 1);
	while q.p < q.k do
	begin
		x := q.w[q.p];
		q.p := q.p + 1;
		s := korytarze[x];
		while s <> nil do
		begin
			z := s^.w;
			s := s^.nx;
			if dynamit[z] = -1 then
			begin
				ojciec[z] := x;
				dynamit[z] := dynamit[x] + 1;
				q.w[q.k] := z;
				q.k := q.k + 1;
				wrzuc (wysokosc[dynamit[z]], z);
			end;
		end;
	end;
end;


{ oznacza podpalenie w wierzcholku [w] dla czasu [czas] }
procedure oznacz (w, czas : longint);
var
	x, k, z	: longint;
	s		: pstos;
begin
	s := nil;
	q.p := 0;
	q.k := 1;
	q.w[0] := w;
	v[w] := w;	{ v[x] == w oznacza juz przetworzylismy x }
	dynamit[w] := 0;
	while (czas > 0) and (q.p < q.k) do
	begin
		czas := czas - 1;
		k := q.k;
		while q.p < k do
		begin
			x := q.w[q.p];
			q.p := q.p + 1;
			s := korytarze[x];
			while s <> nil do
			begin
				z := s^.w;
				s := s^.nx;
				if v[z] <> w then
				begin
					v[z] := w;
					q.w[q.k] := z;
					q.k := q.k + 1;
					dynamit[z] := 0;
				end;
			end;
		end;
	end;
end;


{ sprawdza czy w czasie czas mozna wysadzic wszystkie dynamity }
function sprawdz (czas : longint) : boolean;
var
	z	: longint;
	s	: pstos;
begin
	s := nil;
	z := m;
	for i := 0 to n do
	begin
		dynamit[i] := d[i];
		v[i] := 0;
	end;

	i := n;
	while (i > 0) and (z > -1) do
	begin
		i := i - 1;
		s := wysokosc[i];
		while s <> nil do
		begin
			x := s^.w;
			s := s^.nx;
			if dynamit[x] = 1 then
			begin
				j := czas;
				while (x > 1) and (j > 0) do
				begin
					j := j - 1;
					x := ojciec[x];
				end;

				oznacz (x, czas);
				z := z - 1;
			end;
		end;
	end;

	sprawdz := (z >= 0);
end;

Begin
	wczytaj;
	ukorzen;

	a := 0;
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

	for i := 1 to n do
	begin
		while korytarze[i] <> nil do
			zdejmij (korytarze[i]);
		while wysokosc[i] <> nil do
			zdejmij (wysokosc[i]);
	end;
End.
