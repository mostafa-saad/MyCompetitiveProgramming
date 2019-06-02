(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gass1.pas                                                 *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie wykladnicze O(n^n). Kazdemu wierzcholkowi     *
 *             przyporzadkowuje wierzcholek w ktorym znajduje sie        *
 *             gasnica ktora go zabezpiecza.                             *
 *                                                                       *
 *************************************************************************)

const
    nmx=100;

var
    n, s, k, i, j, a, b, p, result : Longint;
    E : array [0..nmx-1, 0..nmx-1] of Longint;
    ST : array [0..nmx-1] of Longint;

procedure fun(x, u : Longint);
var
    t,r : Longint;
begin
	if result <= u then
        exit;
	if x=n then
    begin
		result := u;
		exit;
	end;
    for t:=0 to n-1 do
        if E[x][t]<=k then
        begin
            Inc(ST[t]);
            if (ST[t]-1) mod s = 0 then
                r:=1
            else
                r:=0;
            fun(x+1, u+r);
            Dec(ST[t]);
        end;
end;

function min(a, b : int64) : int64;
begin
    if a<b then
        min:=a
    else
        min:=b;
end;

begin
    readln(n,s,k);
	result:=n;
    for i:=0 to n-1 do
        for j:=0 to n-1 do
            E[i][j]:=n+1;
	for i:=0 to n-1 do
        E[i][i]:=1;
    for i:=0 to n-2 do
    begin
        readln(a,b);
        Dec(a); Dec(b);
        E[b][a]:=1;
        E[a][b]:=1;
    end;
    for p:=0 to n-1 do
        for a:=0 to n-1 do
            for b:=0 to n-1 do
                E[a][b]:=min(E[a][b],E[a][p]+E[p][b]);
    if s>1 then
        fun(0,0);
    writeln(result);
end.
