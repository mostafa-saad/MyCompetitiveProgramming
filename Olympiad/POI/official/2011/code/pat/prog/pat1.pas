(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe wariant 1                   *
 *                                                                       *
 *************************************************************************)

program Patyczki;

const
	INF = 1000000001;
	MAXN = 1000000;

var
	p_dl: array[0..MAXN+1] of longint;
	p_kol: array[0..MAXN+1] of integer; {p_dl i p_kol: długosci i kolory kolejnych patyczków}
	n, k, m: longint; {n - ilość patczyków, k - ilość kolorów, m - ilość patczyków danego koloru}
	ostkol: integer; {ostatni kolor przetwarzany}
	d_d, d_p: array[1..4] of longint; {d_d - delta, d_p - index pierwszego patyczka delty}
	d_k1, d_k2: array[1..4] of integer; {d_k1, d_k2 - kolory patyczków składających się na deltę}
	i, j: longint; {zmienne dla pętli for}
	index: longint; {index pomozniczy, do wczytywania}
	done: boolean; {czy mamy już wynik}
	
	iln: integer;   {ile nachodzi}
	bd: longint; {najlepsza delta}
	zd: integer; {index najlepszej delty}

function kolnach(j: integer): integer;
var
	r: integer; {wynik}
begin
	r := 0;
	if (d_k1[4] = d_k1[j]) or (d_k1[4] = d_k2[j]) then r := r + 1;
	if (d_k2[4] = d_k1[j]) or (d_k2[4] = d_k2[j]) then r := r + 1;
	kolnach := r;
end;
	
{Sortowanie p (quicksort na podstawie main.edu.pl)}
procedure sortswap(var x: longint; var y: longint);
var pom : longint;
begin
	pom := p_dl[x];
	p_dl[x] := p_dl[y];
	p_dl[y] := pom;
	
	pom := p_kol[x];
	p_kol[x] := p_kol[y];
	p_kol[y] := pom;
end;

procedure sort(l, r : longint);
var q, i, la : longint;
begin
	if l < r then
	begin
		q := p_dl[random(r - l) + l + 1];
		la := l;
		i := l;
		while (i <= r) do begin
			if p_dl[i] > q then begin
				sortswap(la, i);
				inc(la);
			end;
			inc(i);
		end;
		sort(l, la - 1);
		i := l;
		while (i <= r) do begin
			if p_dl[i] = q then begin
				sortswap(la, i);
				inc(la);
			end;
			inc(i);
		end;
		sort(la, r);
	end;
end;

{Poczatek programu}

begin
	done := false;
	{Wczytywanie danych}
	readln(k);
	n := 0;
	index := 1;
	for i := 1 to k do begin
		read(m);
		n := n + m;
		for j := 1 to m do begin
			read(p_dl[index]);
			p_kol[index] := i;
			index := index + 1;
		end;
	end;
	p_dl[0] := INF;
	p_dl[n + 1] := -1;
	sort(1, n); {sortujemy patyczki}
	for i := 1 to 3 do begin {inicjalizowanie początkowych delt}
		d_d[i] := INF;
		d_p[i] := -1;
	end;
	d_k1[1] := 1; d_k2[1] := 2;
	d_k1[2] := 1; d_k2[2] := 3;
	d_k1[3] := 2; d_k2[3] := 3;
	{Algorytm właściwy}
	ostkol := p_kol[1];
	for i := 2 to n do begin
		{Sprawdzenie, czy można zbudować trójkąt}
		d_k1[4] := p_kol[i]; {uzupełniamy kolor w aktualnej delcie}
		d_k2[4] := -1; {drugi kolor ustawiamy na razie tak, żeby nie przeszkadzał}
		for j := 1 to 3 do begin
			if (done = false) and (kolnach(j) = 0) and (d_d[j] < p_dl[i]) then begin{różnica była mniejsza niż dł aktualnego i kolory pasują}
				index := d_p[j];
				write(p_kol[i], ' ',p_dl[i], ' ');
				write(p_kol[index], ' ', p_dl[index], ' ');
				index := index + 1;
				writeln(p_kol[index], ' ', p_dl[index]);
				done := true;
			end;
		end;
		{Poprawianie delt}
		if p_kol[i] <> ostkol then begin {jeśli poprzedni był tego samego koloru i do tego dłuższy, to ten na pewno nie będzie pasował}
			ostkol := p_kol[i]; {aktualizacja ostatniego koloru}
			d_k2[4] := p_kol[i - 1]; {uzupełniamy pozostałe pola aktualnej delty}
			d_d[4] := (p_dl[i - 1] - p_dl[i]);
			d_p[4] := i - 1;
		
			iln := 0;   {ile nachodzi - żeby delty były dobrze wybrane musimy zamienić z taką, w której najwięcej jest wspólnych}
			bd := 0; {dalej musimy wybrać taką, której d jest jak największe, bo je minimalizujemy}
			zd := -1; {a to index wybranej delty do zamiany lub -1, gdy nie opłaca się zamieniać}
			for j := 1 to 3 do begin {szukamy delty z którą możemy i opłaca nam się zamienić aktualną deltę}
				if iln < kolnach(j) then begin {jeśli więcej kolorów nachodzi niż poprzednio, to anulujemy wybór}
					zd := -1;
					bd := 0;
					iln := kolnach(j);
				end;
				if (iln <= kolnach(j)) and (bd <= d_d[j]) then begin {jeśli opłaca się i możemy zamienić z daną deltą, to ją wybieramy}
					iln := kolnach(j);
					bd := d_d[j];
					zd := j;
				end;
			end;
			if (zd <> -1) and (d_d[zd] > d_d[4]) then begin {jeśli ostatecznie opłaca się zamienić, to zamieniamy}
				d_d[zd] := d_d[4];
				d_p[zd] := d_p[4];
				d_k1[zd] := d_k1[4];
				d_k2[zd] := d_k2[4];
			end;
		end; 
	end;
	if done = false then writeln('NIE');
end.
