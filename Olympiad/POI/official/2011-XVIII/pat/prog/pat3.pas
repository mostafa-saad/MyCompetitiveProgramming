(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe wariant 2                   *
 *                                                                       *
 *************************************************************************)

program Patyczki;

const
	INF = 1000000001;
	MAXN = 1000000;

var
	p_dl: array[1..MAXN+1] of longint;
	p_kol: array[1..MAXN+1] of integer; {p_dl i p_kol: długosci i kolory kolejnych patyczków}
	np_dl: array[1..3] of longint;
	np_kol: array[1..3] of integer;{trzy najlepsze patyczki}
	n, k, m: longint; {n - ilość patczyków, k - ilość kolorów, m - ilość patczyków danego koloru}
	i, j: longint; {zmienne dla pętli for}
	index: longint; {index pomozniczy, do wczytywania}
	done: boolean; {czy mamy już wynik}

procedure sprawdz(i : longint);{sprawdza, czy można zbudować trójkąt z np i p[i]}
var
	p1, p2: longint;
begin
	p1 := 2;
	p2 := 3; {są to dwa najdłuższe patyczki z np}
	if np_kol[2] = p_kol[i] then p1 := 1;{jeśli któryś jest tego samego koloru co p[i] to musimy wziąć np[1]}
	if np_kol[3] = p_kol[i] then p2 := 1;
	if (np_dl[p1] + np_dl[p2]) > p_dl[i] then begin
		writeln(p_kol[i], ' ', p_dl[i], ' ', np_kol[p1], ' ', np_dl[p1], ' ', np_kol[p2], ' ', np_dl[p2]);
		done := true;
	end;
end;

procedure swapnp(i, j: integer); {zamienia miejscami np[i] z np[j]}
var
	pom: longint;
begin
	pom := np_dl[i];
	np_dl[i] := np_dl[j];
	np_dl[j] := pom;
	pom := np_kol[i];
	np_kol[i] := np_kol[j];
	np_kol[j] := pom;
end;

procedure popraw(i : longint); {poprawia trzy najlepsze patyczki}
var
	pw : longint;
begin
	pw := 1;
	if np_kol[2] = p_kol[i] then pw := 2;
	if np_kol[3] = p_kol[i] then pw := 3;
	np_kol[pw] := p_kol[i];
	np_dl[pw] := p_dl[i];
	{sortowanie ich}
	if np_dl[1] > np_dl[3] then swapnp(1, 3);
	if np_dl[2] > np_dl[3] then swapnp(2, 3);
	if np_dl[1] > np_dl[2] then swapnp(1, 2);
end;

{Sortowanie p}
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
			if p_dl[i] < q then begin
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
	p_dl[n + 1] := INF;
	sort(1, n); {sortujemy patyczki}
	
	for i := 1 to 3 do begin
		np_kol[i] := -i;
		np_dl[i] := -INF;
	end;
	
	{Algorytm właściwy}
	for i := 1 to n do begin
		if (done = false) then sprawdz(i);
		popraw(i);
	end;
	if (done = false) then writeln('NIE');
end.
