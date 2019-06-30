(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              ant1.pas                                         *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *                      Rozwiazanie uzywa algorytmu Manachera,           *
 *                      zmienionego w jednym miejscu.                    *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************)

var wynik:int64;
    x:array[0..500011] of char;
	r:array[0..500011] of longint;
    rsize,i,n:longint;

procedure manacher;
var i,j,k:longint;
begin
rsize:=-1;
i:=0; j:=0;
  while (i<=n-1) do
  begin
  	while ((i-j>=0) and (x[i-j]<>x[i+j+1]) and (i+j+1<n)) do inc(j);
	inc(rsize); r[rsize]:=j; wynik+=j;
   	k:=1;
    while (i-k>=0) and (r[i-k]<>r[i]-k) and (k <= j) do
	begin
      inc(rsize); r[rsize]:=r[i-k]; if (r[rsize]>r[i]-k) then r[rsize]:=r[i]-k;
	  wynik+=r[rsize];
      inc(k);
    end;
	if (j-k<0) then j:=0 else j:=j-k;
	i:=i+k;
   end;
end;

begin
readln(n);
for i:=0 to n-1 do read(x[i]);
manacher;
writeln(wynik);
end.
