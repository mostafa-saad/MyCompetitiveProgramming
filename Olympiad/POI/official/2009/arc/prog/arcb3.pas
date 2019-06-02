{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb3.pas                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(n * k)                           *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego i wybiera      *}
{*            maksimum z przedzialu w czasie liniowym wzgledem jego      *}
{*            dlugosci.                                                  *} 
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

const
    MAX_N = 8000000;

var
    n, k, iss, il, max_num, i, j : longint;
    seq : array [0..MAX_N] of longint;

begin
    k := inicjuj();
    n := 0;
    seq[n] := wczytaj();
    while(((n + 1) < MAX_N) and (seq[n] <> 0))do
    begin
        inc(n);
        seq[n] := wczytaj();
    end;
    seq[n] := 0;
    iss := 0;
    for i := 0 to k - 1 do
    begin
        max_num := 0;
        for j := iss to n - k + i do
            if seq[j] > max_num then
            begin
                il := j;
                max_num := seq[j];
            end;
        iss := il + 1;
        wypisz(max_num);
    end;
end.
