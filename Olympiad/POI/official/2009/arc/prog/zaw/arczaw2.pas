{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arczaw2.pas                                                *}
{*   Opis:    Rozwiazanie NIEPOPRAWNE obrazujace sposob uzycia           *}
{*            biblioteki. Wczytuje caly ciag a jako rozwiazanie zwraca   *}
{*            pierwsze k elementow.                                      *}
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

var
    k, a, ip, i : longint;
    p : array [0..999999] of longint;

begin
    k := inicjuj();
    ip := 0;
    while(true)do
    begin
        a := wczytaj();
        if a = 0 then
            break;
        if ip < 1000000 then
        begin
            p[ip] := a;
            inc(ip);
        end;
    end;
    for i := 0 to k - 1 do
        wypisz(p[i]);
end.
