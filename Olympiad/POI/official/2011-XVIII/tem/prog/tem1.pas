(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n)                                             *
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
    kolejka : array [0..MN] of Para;
    i,a,b,n,naj,wynik : longint;

    ostatni:longint;
    pierwszy:longint;

begin
    kolejka[0].temperatura := 0;
    ostatni := 0;
    pierwszy := 0;
    wynik := 0;
    read(n);
    (* inicjalizacja struktur danych *)
    for i := 0 to n-1 do
        begin
            read(a,b);
            naj := i;
            while (ostatni<>pierwszy) and (kolejka[ostatni-1].temperatura <= a) do
            begin
                naj := min(naj, kolejka[ostatni-1].pozycja);
                dec(ostatni);
            end;
            kolejka[ostatni].temperatura := a;
            kolejka[ostatni].pozycja := naj;
            inc(ostatni);
            while (ostatni<>pierwszy) and (kolejka[pierwszy].temperatura > b) do
            begin
                wynik := max(wynik, i-kolejka[pierwszy].pozycja);
                inc(pierwszy);
            end;
        end;
        while (ostatni<>pierwszy) do
        begin
            wynik := max(wynik, n-kolejka[pierwszy].pozycja);
            inc(pierwszy);
        end;
        writeln(wynik);
end.

