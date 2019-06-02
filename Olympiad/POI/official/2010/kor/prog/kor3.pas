(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Korale (KOR)                                  *
 *   Plik:                 kor3.pas                                      *
 *   Autor:                Wojciech Tyczynski                            *
 *   Opis:                 Rozwiazanie alternatywne.                     *
 *   Zlozonosc czasowa:    O(n * log n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************)


program Korale;

const MAX_N = 200000;
const MAX_LOG = 19;
const P = 1000000007;


var n : longint;
	 T : array [0..MAX_N] of longint;
	 hasz : array [0..2,0..MAX_N] of longint;
	 E : array [0..MAX_N] of longint;
	 pot : array [0..MAX_N] of longint;
	 i,j,co,ile : longint;
	 res,w : longint;
	 wynik : array [0..MAX_N] of longint;


function min(a,b:longint):longint;
begin
	if (a<b) then min:=a
	else min:=b;
end;


function KMR(p:longint; dl:longint):longint;
	var a,b:longint;
begin
	a:=hasz[0][p+dl-1];
	if (p>0) then a:=a-hasz[0][p-1]*pot[dl];
	b:=hasz[1][p];
	if (p<n-1) then b:=b-hasz[1][p+dl]*pot[dl];
	KMR:=min(a,b);
end;
	

procedure sort(l,r:longint);
	var i,j:longint;
		 tmp,p:longint;
begin
	i:=l; j:=r;
	p:=E[(l+r) div 2];
	repeat
		while (E[i]<p) do inc(i);
		while (p<E[j]) do dec(j);
		if (i<=j) then begin
			tmp:=E[i];
			E[i]:=E[j];
			E[j]:=tmp;
			inc(i); dec(j);
		end;
	until (i>j);
	if (l<j) then sort(l,j);
	if (i<r) then sort(i,r);
end;


begin
	read(n);
	for i:=0 to n-1 do
		read(T[i]);
	
	pot[0]:=1;
	for i:=1 to n do
		pot[i]:=pot[i-1]*P;

	hasz[0][0]:=T[0];
	for i:=1 to n-1 do
		hasz[0][i]:=hasz[0][i-1]*P+T[i];
	hasz[1][n-1]:=T[n-1];
	for i:=n-2 downto 0 do
		hasz[1][i]:=hasz[1][i+1]*P+T[i];

	res:=0;
	w:=0;
	for i:=1 to n do begin
		for j:=0 to ((n div i)-1) do
			E[j]:=KMR(i*j,i);
		sort(0,(n div i)-1);
		ile:=1;
		for j:=1 to ((n div i)-1) do
			if (E[j]<>E[j-1]) then inc(ile);
		if (res<ile) then begin
			res:=ile; w:=0;
		end;
		if (res=ile) then begin
			wynik[w]:=i; inc(w);
		end;
	end;

	writeln(res,' ',w);
	for i:=0 to w-2 do
		write(wynik[i],' ');
	writeln(wynik[w-1]);
end.
