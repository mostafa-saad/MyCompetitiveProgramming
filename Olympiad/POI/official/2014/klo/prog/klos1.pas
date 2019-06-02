(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Szymon Stankiewicz                            *
 *   Zlozonosc czasowa:    O(n!)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program Klocki;

var k,n,p,q: Longint;
     tab: array[1..1000007] of Longint;
     out: array[1..1000007] of Longint;

function generate(pop, rozm: Longint): Boolean;
var i:Longint;
begin
    generate:=false;
    if rozm=n then
        if pop=q then
        begin
            out[rozm]:=q;
            generate:=true;
        end
        else begin
            generate:=false;
        end;
    if rozm=0 then
    begin
        tab[p]:=tab[p]-1;
        generate:=generate(p, 1);
    end;
    if (rozm > 0) and (rozm < n) then
        for i:=1 to k do begin
            if (tab[i] > 0) and (i <> pop) then
            begin
                out[rozm]:=pop;
                tab[i]:=tab[i]-1;
                if generate(i, rozm+1) then
                begin
                    generate:=true;
                    break;
                end
                else
                    tab[i]:=tab[i]+1;
            end;
        end;
end;

var i:Longint;

begin
    n:=0;
    read(k, p, q);
    for i:=1 to k do
    begin
        read(tab[i]);
        n:=n+tab[i];
    end;
    if generate(0, 0) then
        for i:=1 to n do
            write(out[i], ' ')
    else
        write(0);
end.
