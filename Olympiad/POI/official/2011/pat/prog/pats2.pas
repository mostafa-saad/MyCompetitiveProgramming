(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n) + k^3 * n)                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

program Patyczki;

const
	INF = 1000000001;
	MAXN = 1000000;
	MAXK = 50;
var
	p: array[1..MAXN+100] of longint;{długości kolejnych patyczków, kolory są określane na podstawie miejsca}
	k_st: array[1..MAXK+2] of longint; {indeksy kolejnych kolorów}
	n, k, m: longint; {n - ilość patczyków, k - ilość kolorów, m - ilość patczyków danego koloru}
	i, j: longint; {zmienne dla pętli for}
	a, b, c: longint; {zmienne dla pętli przy rozwiązaniu}
	index: longint; {index pomozniczy, do wczytywania}
	done: boolean; {czy mamy już wynik}
	
{Sortowanie p}
procedure sortswap(var x: longint; var y: longint);
var pom : longint;
begin
	pom := p[x];
	p[x] := p[y];
	p[y] := pom;
end;

procedure sort(l, r : longint);
var q, i, la : longint;
begin
	if l < r then
	begin
		q := p[random(r - l) + l + 1];
		la := l;
		i := l;
		while (i <= r) do begin
			if p[i] < q then begin
				sortswap(la, i);
				inc(la);
			end;
			inc(i);
		end;
		sort(l, la - 1);
		i := l;
		while (i <= r) do begin
			if p[i] = q then begin
				sortswap(la, i);
				inc(la);
			end;
			inc(i);
		end;
		sort(la, r);
	end;
end;

{funkcja Solve}

procedure Solve(a, b, c : longint);{Sprawdza, czy da się ułożyć trójkąt, gdy najdłuższy patyczek jest koloru a, krótszy b, a najkrótszy c}
var
	ai, bi, ci: longint; {indeksy dla a, b, c}
begin
	bi := k_st[b];
	ci := k_st[c];
	for ai := k_st[a] to (k_st[a + 1] - 2) do begin
		while ((bi + 1) < k_st[b + 1] - 1) and (p[bi + 1] <= p[ai]) do inc(bi);
		while ((ci + 1) < k_st[c + 1] - 1) and (p[ci + 1] <= p[bi]) do inc(ci);
		if (bi >= k_st[b]) and (ci >= k_st[c]) then begin
			if (p[ai] < p[bi] + p[ci]) and (p[bi] < p[ai]) and (p[ci] < p[ai]) and (done = false) then begin
				writeln(a, ' ', p[ai], ' ', b, ' ', p[bi], ' ', c, ' ', p[ci]);
				done := true;
				k_st[a + 1] := 1;
				k_st[b + 1] := 1;
				k_st[c + 1] := 1;
				k := 1;
			end;
		end;
	end;
end;

{Poczatek programu}

begin
	{Wczytywanie danych}
	readln(k);
	n := 0;
	index := 1;
	for i := 1 to k do begin
		k_st[i] := index;
		read(m);
		n := n + m;
		for j := 1 to m do begin
			read(p[index]);
			index := index + 1;
		end;
		p[index] := INF;
		sort(k_st[i], index - 1);
		inc(index);
	end;
	k_st[k + 1] := index;
	p[index] := INF;
	{Algorytm właściwy}
	for a := 1 to (k - 2) do begin
		for b := (a + 1) to (k - 1) do begin
			for c := (b + 1) to k do begin
				{wybrane są trzy kolory a b i c}
				Solve(a, b, c);
				Solve(a, c, b);
				Solve(b, a, c);
				Solve(b, c, a);
				Solve(c, a, b);
				Solve(c, b, a);
				{sprawdzone wszystkie sześć możliwości}
			end;
		end;
	end;
	if (done = false) then writeln('NIE');
end.
