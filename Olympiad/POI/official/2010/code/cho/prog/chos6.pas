(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Chomiki (CHO)                                             *
 *   Plik:     chos6.pas                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie powolne - wzorcowe bez funkcji prefiksowej    *
 *             i bez logarytmicznego mnozenia.                           *
 *                                                                       *
 *************************************************************************)

CONST
	inf : int64 = 100000000000000000;
	
type matrix=array[0..201,0..201] of int64;


VAR 
	names: array[0..200] of ansistring;
	len:   array[0..200] of longint;
	n,m,i,j,k,x,beg,torem: longint;
	mts,mtr: matrix;
	res: int64;
function min(a,b:int64):int64;
begin
	if a<b then
		min:=a
	else
		min:=b;
end;

procedure mnoz(var ma,mb: matrix);
var
	i,j,k:longint;
	w:    int64;
	t: matrix;
begin
	for i:=0 to n-1 do
		for j:=0 to n-1 do begin
			w:=inf;
			for k:=0 to n-1 do 
				w:=min(w,ma[i][k]+mb[k][j]);
			t[i][j]:=w;
		end;
	ma:=t;
end;

BEGIN
	readln(n,m);
	for i:=0 to n-1 do begin
		readln(names[i]);
		len[i]:=length(names[i]);
		names[i]:=names[i]+'$';
	end;
	for i:=0 to n-1 do begin
		for k:=0 to n-1 do begin
			torem:=0;
			for j:=1 to len[k]-1 do begin
				x:=0;
				while (j+x < len[k]) and (names[i][x+1] = names[k][j+x+1]) do
					inc(x);
				if j+x = len[k] then begin
					torem:= x;
					break;
				end;
			end;
			mts[k][i]:=len[i]-torem;		
		end;
		mts[n][i]:=len[i];
		mts[i][n]:=inf;
	end;
	mts[n][n]:=inf;
	inc(n);
	for i:=0 to n-1 do begin
		for j:=0 to n-1 do
			mtr[i][j]:=inf;
	end;
	mtr[n-1][n-1]:=0;
	for i:=0 to m-1 do begin
		mnoz(mtr,mts);
	end;
	res:=inf;
	for i:=0 to n-2 do
		res:=min(res,mtr[n-1][i]);
	writeln(res);
END.
