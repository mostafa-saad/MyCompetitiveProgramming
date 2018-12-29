(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

program Impreza;

const
	MAXN = 3001;

var
	kmatrix: array[0..MAXN] of array[0..MAXN] of boolean; {macierz sąsiedztwa}
	erased: array[0..MAXN] of boolean; {czy usunięty?}
	n, m, a, b: longint; {jak w treści}
	i, j: longint; {zmienne dla fora}
	left: longint; {ile zostało do wypisania}
	
{Poczatek programu}
begin
	{Wczytywanie danych}
	readln(n, m);
	for i := 0 to (n-1) do begin
		erased[i] := false;
		for j := 0 to (n-1) do kmatrix[i][j] := false;
	end;
	for i := 0 to (m-1) do begin
		readln(a, b);
		kmatrix[a-1][b-1] := true;
		kmatrix[b-1][a-1] := true;
	end;
	{Algorytm właściwy}
	for i := 0 to (n-1) do begin
		for j := (i+1) to (n-1) do begin
			if (erased[i] = false) and (erased[j] = false) and (kmatrix[i][j] = false) then begin {jeśli i,j nieusunięte i niepołączone}
				erased[i] := true; {to je usuwamy}
				erased[j] := true;
			end;
		end;
	end;
	left := (n div 3);
	for i := 0 to (n-1) do begin
		if (left > 0) and (erased[i] = false) then begin {wypisujemy pierwsze n/3 nieusuniętych osób}
			left := left - 1;
			write((i + 1), ' ');
		end;
	end;
	writeln();
end.
