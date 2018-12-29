(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo1.pas                                         *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n * m)                                         *
 *                                                                       *
 *************************************************************************)


program klocki;

var n,m,pc,sc,i,j:longint;
    k:int64;
      H:array[0..1000999] of int64;
     SH:array[0..1000999] of int64;
    pre:array[0..1000999] of longint;
    suf:array[0..1000999] of longint;

function oblicz():longint;
var c,best:longint;
    b:int64;
begin
    SH[0]:=0;
    for i:=0 to n-1 do
	SH[i+1]:=SH[i]+H[i]-k;
    pc:=0;
    sc:=0;
    b:= 1000*1000*1000*1000*1000;
    for i:=0 to n do if b>SH[i] then
    begin
	pre[pc]:=i;
	b:=SH[i];
	inc(pc);
    end;
    b:=-1000*1000*1000*1000*1000;
    for i:=n downto 0 do if b<SH[i] then
    begin
	suf[sc]:=i;
	b:=SH[i];
	inc(sc);
    end;
    c:=sc-1;
    best:=0;
    for i:=0 to pc-1 do
    begin
	while (c>=0) and (SH[suf[c]]>=SH[pre[i]]) do dec(c);
	if (c+1<sc) and (SH[suf[c+1]]>=SH[pre[i]]) and (best<suf[c+1]-pre[i]) then
	    best:=suf[c+1]-pre[i];
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
