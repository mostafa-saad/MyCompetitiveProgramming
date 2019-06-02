(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * 2^n)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

program Impreza;

const
	MAXN = 3001;
 
var
	kmatrix: array[0..MAXN] of array[0..MAXN] of boolean; {macierz sąsiedztwa}
	used: array[0..MAXN] of boolean; {czy użyty?}
	n, m, a, b: longint; {jak w treści}
	done: boolean; {czy mamy wynik?}
	i, j: longint; {zmienne dla fora}

procedure Find(act, left: longint);{rekurencyjny backtracking}
var
	cb:boolean; {czy można dodać act?}
begin
	if(done = false)then begin
		if(left = 0) then begin {jeśli mamy n/3 wybranych to je wypisujemy}
			for i := 0 to n do 
				if(used[i]=true) then write(i+1, ' ');
			writeln();
			done := true;
		end
		else if(act < n) then begin
			cb := true;
			for i := 0 to (act-1) do {sprawdzamy, czy mając wybrane, można dodać act}
				if(used[i]=true)and(kmatrix[i][act]=false) then cb := false;
			if(cb=true) then begin
				used[act] := true;
				Find(act + 1, left - 1); {jeśli tak, to próbujemy dodać}
				used[act] := false;
			end;
			Find(act + 1, left); {jak się nie udało to nie dodajemy}
		end;
	end;
end;

{Poczatek programu}
begin
	{Wczytywanie danych}
	readln(n, m);
	for i := 0 to (n-1) do begin
		for j := 0 to (n-1) do kmatrix[i][j] := false;
	end;
	for i := 0 to (m-1) do begin
		readln(a, b);
		kmatrix[a-1][b-1] := true;
		kmatrix[b-1][a-1] := true;
	end;
	{Algorytm właściwy}
	Find(0, (n div 3));
end.
