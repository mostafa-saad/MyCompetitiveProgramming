(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Rozwiazanie bardzo powolne                       *
 *                                                                       *
 *************************************************************************)

program Patyczki;

const
	INF = 1000000001;
	MAXN = 1000000;

var
	p_dl: array[1..MAXN+1] of longint;
	p_kol: array[1..MAXN+1] of integer; {p_dl i p_kol: długosci i kolory kolejnych patyczków}
	n, k, m: longint; {n - ilość patczyków, k - ilość kolorów, m - ilość patczyków danego koloru}
	i, j, a, b, c: longint; {zmienne dla pętli for}
	index: longint; {index pomozniczy, do wczytywania}
	done: boolean; {czy mamy już wynik}

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
			inc(index);
		end;
	end;
	
	{Algorytm właściwy}
	for a := 1 to (n - 2) do begin
		for b := (a + 1) to (n - 1) do begin
			for c := (b + 1) to n do begin
				if (p_kol[a] <> p_kol[b]) and (p_kol[a] <> p_kol[c]) and (p_kol[b] <> p_kol[c])
				and (p_dl[a] + p_dl[b] > p_dl[c]) and (p_dl[a] + p_dl[c] > p_dl[b]) and (p_dl[b] + p_dl[c] > p_dl[a]) and (done = false) then begin
					done := true;
					writeln(p_kol[a], ' ', p_dl[a], ' ', p_kol[b], ' ', p_dl[b], ' ', p_kol[c], ' ', p_dl[c]);
				end;
				if (done=true) then n := 0;
			end;
		end;
	end;
	if done = false then writeln('NIE');
end.
