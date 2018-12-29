(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla1.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n) (na stosie).                    *
 *                                                                       *
 *************************************************************************)
program plakatowanie;

var stos:array[1..270000] of longint;
    i,n,ssize,dump,result,k:longint;
    
begin
    readln(n);
    result:=0; ssize:=0;
    for i:=1 to n do
    begin
        read(dump); readln(k);
        while ((ssize>0) and (stos[ssize]>k)) do dec(ssize);
        if ((ssize=0) or (stos[ssize]<k)) then
        begin
            inc(ssize); inc(result);
            stos[ssize]:=k;
        end;
    end;
    writeln(result);
end.