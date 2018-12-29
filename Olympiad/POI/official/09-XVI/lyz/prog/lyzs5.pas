(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzs5.pas                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolniejsze O(n*m). Zapamietuje aktualnie      *
 *             najmniejszy rozmiar wolnych lyzew.                        *
 *                                                                       *
 *************************************************************************)

const MAX_N=200000;

function min(a,b:int64):int64;
begin
	if a < b then min := a else min := b;
end;
function max(a,b:int64):int64;
begin
	if a > b then max := a else max := b;
end;

var n, m, k, d:longint;
    t,lyzwy:array[1..MAX_N] of int64;

function spr():boolean;
	var i,j:longint;
	    ile,przydziel:int64;
begin
	for i := 1 to n do lyzwy[i] := k;
	j := 1;
	for i := 1 to n-d do begin
		ile := t[i]; { Lyzwiarze ktorym trzeba jeszcze przydzielic lyzwy }
		j := max(i,j);
		while (ile <> 0) and (j <= i+d) do begin
			przydziel := min(lyzwy[j],ile);
			ile := ile - przydziel; lyzwy[j] := lyzwy[j] - przydziel;
			j := j+1;
		end;
		if (ile <> 0) then begin spr := false; exit; end else j := j-1;
	end;
	spr := true;
end;

var i,r,x:longint;
BEGIN
	read(n); read(m); read(k); read(d);
	for i := 1 to m do begin
		read(r); read(x);
		t[r] := t[r]+x;
		if spr() then writeln('TAK') else writeln('NIE');
	end;
END.
