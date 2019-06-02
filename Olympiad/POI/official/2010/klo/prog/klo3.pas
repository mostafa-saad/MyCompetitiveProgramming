(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo3.pas                                         *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Drugie rozwiazanie wzorcowe.                     *
 *   Zlozonosc czasowa: O(n * m)                                         *
 *                                                                       *
 *************************************************************************)

program klocki;

var n,m,i,j:longint;
    k:int64;
      H:array[0..1000999] of int64;
     SH:array[0..1000999] of int64;
    pnt:array[0..1000999] of longint;

function oblicz():longint;
var d,best:longint;
    mx:int64;
begin
    SH[0]:=0;
    for i:=0 to n-1 do
	SH[i+1]:=SH[i]+H[i]-k;
    d:=-1;
    mx:=-1000*1000*1000*1000*1009;
    best:=0;
    for i:=n downto 0 do
    begin
	pnt[i]:=d;
	if SH[i]>mx then
	begin
	    mx:=SH[i];
	    d:=i;
	end;
    end;
    for i:=0 to n do
    begin
	while (pnt[d]>=0) and (SH[pnt[d]]>=SH[i]) do d:=pnt[d];
	if (d-i>best) and (SH[d]>=SH[i]) then best:=d-i;
    end;
    oblicz:=best;
end;

begin
    readln(n,m);
    for i:=0 to n-1 do read(H[i]);
    for j:=0 to m-1 do
    begin
	read(k);
	if j>0 then write(' ');
	write(oblicz());
    end;
    writeln;
end.
