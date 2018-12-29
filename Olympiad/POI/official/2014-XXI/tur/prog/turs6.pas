(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Turystyka                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(2^n * (n+m))                                *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

var
	n,m,i,a,b,res,mask,cover,act : Longint;
	c,sas : array[0..30] of Longint;

begin
	res := 1000000000;
	{ wczytanie wejscia }
	Read(n);
	Read(m);
	if n > 30 then
		halt(1);
	for i := 0 to n - 1 do
		begin
			Read(c[i]);
			sas[i] := 0;
		end;
	for i := 1 to m do
	begin
		Read(a);
		Read(b);
		Dec(a);
		Dec(b);
		sas[a] := sas[a] or (1 shl b);
		sas[b] := sas[b] or (1 shl a);
	end;
	{ rozwiazanie }
	for mask := 0 to (1 shl n) - 1 do
	begin
		cover := mask;
		act := 0;
		for i := 0 to n - 1 do
		if (mask and (1 shl i)) > 0 then
			begin
				cover := cover or sas[i];
				act := act + c[i];
			end;
		if cover = (1 shl n) - 1 then
			if act < res then
				res := act;
	end;
	{ wypisanie wyniku }
	Writeln(res);
end.
