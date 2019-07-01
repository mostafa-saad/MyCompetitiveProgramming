(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * (n po m)                                   *
 *   Opis:              Rozwiazanie powolne, silowe                      *
 *                      Ustawiamy punkty zapalenia lontow i sprawdzamy   *
 *                      czas podpalenia dynamitow                        *
 *                                                                       *
 *************************************************************************)

const 
	MAX_N = 300000;

type
	kolejka_statyczna = record
		w	: array[0..MAX_N] of longint;	{ wartosci kolejki }
		p, k	: longint;		{ poczatek i koniec kolejki }
	end;

var
	n, m	: longint;	
	{ ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont }
	d	: array[0..MAX_N] of boolean;
	{ d[i] == 0 wtw., gdy w i-tej komorze nie ma dynamitu }
	korytarze	: array[0..2 * MAX_N] of longint;
	{ tablica opisujaca siec komor }
	koniec	: array[0..MAX_N] of longint;
	{ koniec listy sasiedztwa dla i-tej komory }
	ilosc	: array[0..MAX_N] of longint;
	{ ilosc elementow w i-tej liscie sasiedztwa }

	podpalone	: array[0..MAX_N] of longint;
	{ komory, ktorych lonty beda podpalona }
	w, x	: longint;
	{ dotychczasowe minimum i czas aktualnie rozwazanego ustawienia }
	i, l, k	: longint;	{ zmienne pomocnicze }
	q		: array[0..1] of kolejka_statyczna;	{ kolejka pomocnicza }
	uzyte	: array[0..MAX_N] of longint; 
	{ uzyte[i]==0 gdy nie zapalil sie lont do i-tej komory }
	z		: array[0..MAX_N] of longint; { tablica pomocnicza }
	dil		: longint; { ilosc dynamitow }

{ wczytaj() - wczytuje dane i zmienia reprezentacje sieci komor.
  t[] bedzie zawierala listy sasiedztw kolejnych komor.
  Konce kolejnych list zapamietamy w k[]. }
procedure wczytaj;
begin
	readln (n, m);
	dil := 0;
	for i := 1 to n do
	begin
		read (w);
		d[i] := (w = 1);
		ilosc[i] := 0;
		dil := dil + w;
	end;
	
	for i := 1 to n - 1 do
	begin
		readln (podpalone[i], uzyte[i]);
		ilosc[podpalone[i]] := ilosc[podpalone[i]] + 1;
		ilosc[uzyte[i]] := ilosc[uzyte[i]] + 1;
	end;

	koniec[0] := 0;
	for i := 1 to n do
	begin
		koniec[i] := ilosc[i] + koniec[i - 1];
		z[i] := koniec[i - 1];
	end;

	for i := 1 to n - 1 do
	begin
		korytarze[z[podpalone[i]]] := uzyte[i];
		z[podpalone[i]] := z[podpalone[i]] + 1;
		korytarze[z[uzyte[i]]] := podpalone[i];
		z[uzyte[i]] := z[uzyte[i]] + 1;
	end;
end;

{ generuj() - generuje nastepna kombinacje podpalen lontow }
function generuj : boolean;
begin
	i := 1;
	while (i <= m) and (podpalone[m - i] = n - i + 1) do
		i := i + 1;
	
	if i > m then
		generuj := false
	else begin
		podpalone[m - i] := podpalone[m - i] + 1;
		while i > 0 do
		begin
			i := i - 1;
			podpalone[m - i] := podpalone[m - i - 1] + 1;
		end;

		generuj := true;
	end;
end;


{ oblicz_czas() - oblicza czas po jakim wszystkie ladunki wybuchna
  przy aktualnej kombinacji podpalen lontow }
function oblicz_czas (ilosc : longint) : longint;
var
	v, z	: longint;
begin
	v := 0;
	z := 0;
	for i := 1 to n do
		uzyte[i] := 0;

	for i := 0 to m - 1 do
	begin
		q[0].w[i] := podpalone[i];
		uzyte[podpalone[i]] := 1;
	end;

	q[0].p := 0;
	q[0].k := m;

	k := 0;
	while (ilosc > 0) and (q[k].p < q[k].k) do
	begin
		k := 1 - k;
		z := z + 1;
		q[k].p := 0;
		q[k].k := 0;
		for i := q[1-k].p to q[1-k].k - 1 do
			for l := koniec[q[1-k].w[i] - 1] to koniec[q[1-k].w[i]] - 1 do
			begin
				x := korytarze[l];
				if uzyte[x] = 0 then
				begin
					uzyte[x] := 1;
					q[k].w[q[k].k] := x;
					q[k].k := q[k].k + 1;
					if d[x] then
					begin
						v := z;
						ilosc := ilosc - 1;
					end;
				end;
			end;
	end;
	
	oblicz_czas := v;
end;


Begin
	wczytaj;

	if dil <= m then
		writeln (0)
	else begin

		for i := 0 to m - 1 do
			podpalone[i] := i + 1;

		podpalone[m - 1] := podpalone[m - 1] - 1;
		
		w := n;
		while (w > 1) and (generuj) do
		begin
			x := oblicz_czas (dil);
			if x < w then
				w := x;
		end;

		writeln (w);
	end;
End.
