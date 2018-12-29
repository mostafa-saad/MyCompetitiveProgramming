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
    temp,i,k,a,b,n,naj,wynik : longint;

begin
    wynik := 0;
    read(n);
    for i := 0 to n-1 do
        read(Tmin[i],Tmax[i]);

    i := 0;
    while i<n do begin
        temp := Tmax[i];
        k := i+1;
        while (k<n) and (temp<=Tmax[k]) do
        begin
            temp := max(temp, Tmin[k]);
            inc(k);
        end;
        
        temp := Tmax[k-1];
        a := k-1;
        while (a>=0) and (temp>=Tmin[a]) do
        begin
            temp := min(temp, Tmax[a]);
            dec(a);
        end;

        wynik := max(wynik, k-a-1);
        i := k;
    end;
    writeln(wynik);
end.

