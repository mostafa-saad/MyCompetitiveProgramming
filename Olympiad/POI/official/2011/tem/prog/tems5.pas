(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

program tem;

const MN = 1000100;

type Para = record
    temperatura: longint;
    pozycja: longint;
end;

function min(a, b : longint) : longint;
begin
    if a < b then
    min := a
    else
    min := b;
end;

function max(a, b : longint) : longint;
begin
    if a > b then
    max := a
    else
    max := b;
end;


var
    Tmin, Tmax : array [0..MN] of longint;
    temp,i,k,n,wynik : longint;

begin
    wynik := 0;
    read(n);
    for i := 0 to n-1 do
        read(Tmin[i],Tmax[i]);

    for i := 0 to n-1 do begin
        temp := Tmin[i];
        k := i+1;
        while (k<n) and (temp<=Tmax[k]) do
        begin
            temp := max(temp, Tmin[k]);
            inc(k);
        end;
        wynik := max(wynik, k-i);
    end;
    writeln(wynik);
end.

