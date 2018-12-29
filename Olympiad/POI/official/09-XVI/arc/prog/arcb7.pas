{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb7.pas                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego ale wczytuje   *}
{*            caly ciag do pamieci.                                      *} 
{*                                                                       *}
{*************************************************************************}


uses
    parclib;

const
    MAX_K = 1000000;
const
    MAX_N = 7000000;

var
    n, k, iss, i : longint;
    seq : array [0..MAX_N] of longint;
    sub : array [0..MAX_K - 1] of longint;

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
    sub[0] := 0;
    for i := 0 to n - 1 do
    begin
        while((iss > 0) and ((iss + n - i) > k) and (sub[iss - 1] < seq[i]))do
            dec(iss);
        if iss < k then
        begin
            sub[iss] := seq[i];
            inc(iss);
        end;
    end;
    for i := 0 to k - 1 do
        wypisz(sub[i]);
end.

