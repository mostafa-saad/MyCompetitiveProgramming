(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Straz pozarna (STR)                                       *
 *   Plik:     strs2.pas                                                 *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie nieefektywne O(p*z). Dla kazdej pary stacji   *
 *             po prostu iteruje po wszystkich zabytkach                 *
 *                                                                       *
 *************************************************************************)


const ZZ = 100000;

var n,m,z,p: longint;
    x,y:array[1..ZZ] of longint;

var i,j,a,b,c,d,w,AA,CC:longint;
begin
    readln(n,m,z,p);
    for i:=1 to z do
        read(x[i],y[i]);
    for j:=1 to p do
        begin
            AA:=0;
            CC:=0;
            read(a,b,c,d);
            for i:=1 to z do
                begin
                    w := ( abs(x[i]-a) + abs(y[i]-b) ) - ( abs(x[i]-c) + abs(y[i]-d) );
                    if w<0 then
                        inc(AA)
                    else if w>0 then
                        inc(CC);
                end;
            writeln(AA,' ',CC,' ',z-AA-CC);
        end;
end.
