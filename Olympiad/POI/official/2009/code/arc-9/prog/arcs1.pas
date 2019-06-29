{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcs1.pas                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo.                          *}
{*            Szukajac najwiekszego leksykograficznie podciagu dlugosci  *}
{*            k sprawdza wszystkie podciagi dlugosci k - 1.              *}
{*            Zlozonosc obliczeniowa: O(n * k ^ 2)                       *}
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

const
    MAX_K = 1000000; // maksymalna dlugosc szukanego podciagu

var
    k, a, i, j, l : longint;
    sub : array [0..MAX_K - 1] of longint;
    tmp : array [0..MAX_K - 1, 0..1] of longint; 

begin
    k := inicjuj();
    for  i := 0 to k - 1 do
        sub[i] := 0;
    a := wczytaj();
    while(a <> 0)do
    begin
        for i := 0 to k - 1 do
            tmp[i][0] := sub[i];
        for i := 0 to k - 1 do
        begin
            for j := 0 to i - 1 do
                tmp[j][1] := sub[j];
            for j := i + 1 to k - 1 do
                tmp[j - 1][1] := sub[j];
            tmp[k - 1][1] := a;
            for j := 0 to k - 1 do
            begin
                if tmp[j][0] < tmp[j][1] then
                begin
                    for l := 0 to k - 1 do
                        tmp[l][0] := tmp[l][1];
                    break;
                end;
                if tmp[j][0] > tmp[j][1] then
                    break;
            end;
        end;
        for i := 0 to k - 1 do
            sub[i] := tmp[i][0];
        a := wczytaj();
    end;
    for i := 0 to k - 1 do
        wypisz(sub[i]);
end.
