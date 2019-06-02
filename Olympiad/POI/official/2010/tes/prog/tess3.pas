(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tess3.pas                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie powolne.                             *
 *   Złożoność czasowa: O(m + l * log m + |A|)                           *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************)

const
    MAX_M = 1000000; { maksymalna długość ciągu a_i }
    MAX_A = 1000000; { maksymalny wyraz ciągu }

var
    m, n, k, b, p, emp, i, j, l, c, r : longint;
    a : array [0..MAX_M - 1] of longint;
    cou, ind, beg : array [0..MAX_A - 1] of longint;
    ok : boolean;

begin

    for i := 0 to MAX_A - 1 do
    begin
        cou[i] := 0;
        beg[i] := -1;
    end;

    readln(m);
    for i := 0 to m - 1 do
    begin
        read(a[i]);
        dec(a[i]);
        inc(cou[a[i]]);
    end;
    readln;

    emp := 0;
    for i := 0 to MAX_A - 1 do
    begin
        if cou[i] > 0 then
            beg[i] := emp;
        inc(emp, cou[i]);
        cou[i] := 0;
    end;
  
    for i := 0 to m - 1 do
    begin
        ind[beg[a[i]] + cou[a[i]]] := i;
        inc(cou[a[i]]);
    end;

    readln(n);
	for i := 0 to n - 1 do
    begin
        readln(k);
		p := -1;
		ok := true;
		for j := 0 to k - 1 do
        begin
            read(b);
			dec(b);
			if (not ok) or (beg[b] = -1) then
            begin
				ok := false;
				continue;
			end;
			l := beg[b];
            r := beg[b] + cou[b];
			while l < r do
            begin
				c := (l + r) div 2;
				if ind[c] <= p then
					l := c + 1
				else
					r := c;
			end;
			if l = (beg[b] + cou[b]) then
				ok := false
			else
				p := ind[l];
		end;
        if ok then
            writeln('TAK')
        else
            writeln('NIE');
	end;
end.
