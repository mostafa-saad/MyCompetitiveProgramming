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
    kolejka : array [0..MN] of Para;
    i,j,a,b,n,naj,wynik : longint;

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
            naj := 0;
            while (ostatni<>pierwszy) and (kolejka[ostatni-1].temperatura <= a) do
            begin
                naj := max(naj, kolejka[ostatni-1].pozycja);
                dec(ostatni);
            end;
            kolejka[ostatni].temperatura := a;
            kolejka[ostatni].pozycja := naj;
            inc(ostatni);
            while (ostatni<>pierwszy) and (kolejka[pierwszy].temperatura > b) do
            begin
                wynik := max(wynik, kolejka[pierwszy].pozycja);
                inc(pierwszy);
            end;
            for j := pierwszy to ostatni-1 do
                inc(kolejka[j].pozycja);
        end;
        while (ostatni<>pierwszy) do
        begin
            wynik := max(wynik, kolejka[pierwszy].pozycja);
            inc(pierwszy);
        end;
        writeln(wynik);
end.

