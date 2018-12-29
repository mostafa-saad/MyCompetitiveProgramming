(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(mn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Kopiuje i sortuje przedzial, a nastepnie      *
 *                         sprawdza maksymalna liczbe wystapien.         *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 500005;

var
	t, p, tmp: array[0..MAXN-1] of longint;
	n, m, a, b, i, j, maxIdx, maxOccur, curOccur: longint;

procedure Merge(start, center, stop: longint);
var
	posLeft, posRight, posTmp: longint;
begin
	posLeft := start;
	posRight := center+1;
	posTmp := posLeft;

	while ((posLeft <= center) and (posRight <= stop)) do
	begin
		if (p[posLeft] <= p[posRight]) then
		begin
			tmp[posTmp] := p[posLeft];
			inc(posLeft);
			inc(posTmp);
		end
		else
		begin
			tmp[posTmp] := p[posRight];
			inc(posRight);
			inc(posTmp);
		end;
	end;
	while (posLeft <= center) do
	begin
		tmp[posTmp] := p[posLeft];
		inc(posLeft);
		inc(posTmp);
	end;
	while (posRight <= stop) do
	begin
		tmp[posTmp] := p[posRight];
		inc(posRight);
		inc(posTmp);
	end;

	for posTmp := start to stop do
		p[posTmp] := tmp[posTmp];
end;

procedure MergeSort(start, stop: longint);
var
	center: longint;
begin
	if (start <> stop) then
	begin
		center := (start+stop) div 2;
		MergeSort(start, center);
		MergeSort(center+1, stop);
		Merge(start, center, stop);
	end;
end;

begin
	readln(n, m);
	for i:=0 to n-1 do
		read(t[i]);
	
	for i:=0 to m-1 do
	begin
		readln(a, b);
		dec(a);
		dec(b);

		for j:=a to b do
			p[j] := t[j];
		MergeSort(a, b);

		maxIdx := p[a];
		maxOccur := 1;
		curOccur := 1;

		for j:=a+1 to b do
		begin
			if (p[j] = p[j-1]) then
			begin
				inc(curOccur);
				if (curOccur > maxOccur) then
				begin
					maxIdx := p[j];
					maxOccur := curOccur;
				end;
			end
			else
				curOccur := 1;
		end;
		if (curOccur > maxOccur) then
			maxOccur := curOccur;

		if (maxOccur > (b-a+1) div 2) then
			writeln(maxIdx)
		else
			writeln(0);
	end;
end.
