(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tess7.pas                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie powolne.                             *
 *   Złożoność czasowa: O(m * n + l)                                     *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************)

const
    MAX_M = 1000000; // maksymalna długość ciągu a_i
    MAX_A = 1000000; // maksymalny wyraz ciągu

var
    m, n, k, p, emp, i, j, l, r : longint;
    a, b : array [0..MAX_M - 1] of longint;
    ind, beg, pos : array [0..MAX_A - 1] of longint;
    cou : array[0..MAX_A - 1, 0..1] of longint;
    ok : boolean;

begin

    for i := 0 to MAX_A - 1 do
    begin
        cou[i][0] := 0;
        cou[i][1] := 0;
        beg[i] := -1;
        pos[i] := 0;
    end;

    readln(m);
    for i := 0 to m - 1 do
    begin
        read(a[i]);
        dec(a[i]);
        inc(cou[a[i]][0]);
    end;
    readln;

    emp := 0;
    for i := 0 to MAX_A - 1 do
    begin
        if cou[i][0] > 0 then
        begin
            beg[i] := emp;
            pos[i] := emp;
        end;
        inc(emp, cou[i][0]);
        cou[i][0] := 0;
    end;
  
    for i := 0 to m - 1 do
    begin
        ind[beg[a[i]] + cou[a[i]][0]] := i;
        inc(cou[a[i]][0]);
    end;

    readln(n);
	for i := 0 to n - 1 do
    begin
        readln(k);
		p := -1;
		ok := true;
		for j := 0 to k - 1 do
        begin
            read(b[j]);
			dec(b[j]);
            inc(cou[b[j]][1]);
            if cou[b[j]][0] < cou[b[j]][1]  then
                ok := false;
        end;
		for j := 0 to k - 1 do
        begin
			if (not ok) or (beg[b[j]] = -1) then
            begin
				ok := false;
				break;
			end;
			l := pos[b[j]];
            r := beg[b[j]] + cou[b[j]][0];
			while (l < r) and (ind[l] <= p) do
                inc(l);
            pos[b[j]] := l + 1;
			if l = r then
				ok := false
			else
				p := ind[l];
		end;
        readln;
        for j := 0 to k - 1 do
        begin
            pos[b[j]] := beg[b[j]];
            cou[b[j]][1] := 0;
        end;
        if ok then
            writeln('TAK')
        else
            writeln('NIE');
	end;
end.
