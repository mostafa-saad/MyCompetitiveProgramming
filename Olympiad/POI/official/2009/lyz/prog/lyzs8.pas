(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzs8.pas                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolniejsze O(n*m). Po kazdym wydarzeniu       *
 *             sprawdza warunek istnienia przydzialu od poczatku.        *
 *                                                                       *
 *************************************************************************)

const MAX_N=200000;

var n, m, k, d:longint;
    t:array[1..MAX_N] of int64;

function spr():boolean;
	var i:longint;
	    max,cur:int64;
begin
	max := 0; cur := 0;
	{ Szukanie spojnego podciagu o najwiekszej sumie }
	for i := 1 to n-d do begin
		cur := cur + t[i];
		if (cur > max) then max := cur;
		if (cur < 0) then cur := 0;
	end;
	if max > int64(k) * int64(d) then spr := false else spr := true;
end;

var i,r,x:longint;
BEGIN
	read(n); read(m); read(k); read(d);
	for i := 1 to n-d do t[i] := -k;
	for i := 1 to m do begin
		read(r); read(x);
		t[r] := t[r]+x;
		if spr() then writeln('TAK') else writeln('NIE');
	end;
END.
