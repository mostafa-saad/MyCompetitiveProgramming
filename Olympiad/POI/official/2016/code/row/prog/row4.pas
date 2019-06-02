(******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Rownowazne programy                                *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(nk)                                              *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************)

var
	na,i,j,n,m,k,a,b:Longint;
	ile,x,c_sum:Int64;
	nieprze: array[0..1001,0..1001] of Longint;
	nieprze_siz: array[0..1001] of Longint;
	licz: array[0..1001] of Longint;
begin
	read(n,k,m);
	for i := 0 to k do
		nieprze_siz[i]:=0;
	for i := 1 to m do
	begin
		read(a,b);
		nieprze[a,nieprze_siz[a]]:=b;
		nieprze[b,nieprze_siz[b]]:=a;
		nieprze_siz[a]:=nieprze_siz[a]+1;
		nieprze_siz[b]:=nieprze_siz[b]+1;
	end;
	c_sum:=0;
	for na:=0 to 1 do
	begin
		for i:=0 to k do
			licz[i]:=0;
		for i:=0 to n-1 do
		begin
			read(x);
			ile:=0;
			for j:=0 to nieprze_siz[x]-1 do
				ile:=ile+licz[nieprze[x][j]];
			c_sum:=c_sum+(ile+42)*x*(x+3);
			licz[x]:=licz[x]+1;
		end;
		c_sum:=-c_sum;
	end;
	if c_sum=0 then
		Writeln('TAK')
	else
		Writeln('NIE');
end.

