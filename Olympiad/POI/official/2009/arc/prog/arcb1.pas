{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb1.pas                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O((n po k) * n * k)                *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Sprawdza wszystkie k elementowe podzbiory.                 *}
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

const
    MAX_K = 1000000;
const
    MAX_N = 1000000;

var
    n, k, i : longint;
    sub, tmp : array [0..MAX_K - 1] of longint;
    seq : array [0..MAX_N] of longint;

procedure check(iss, ele : longint);
var
    i, j : longint;
begin
    if (n - iss) < ele then
        exit;
    if ele = 0 then
    begin
        for i := 0 to k - 1 do
        begin
            if sub[i] < tmp[i] then
            begin
                for j := 0 to k - 1 do
                    sub[j] := tmp[j];
                break;
            end;
            if sub[i] > tmp[i] then
                break;
        end;
        exit;
    end;
    tmp[k - ele] := seq[iss];
    check(iss + 1, ele - 1);
    check(iss + 1, ele);
end;

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
    for i := 0 to k - 1 do
        sub[i] := 0;
    check(0, k);
    for i := 0 to k - 1 do
        wypisz(sub[i]);
end.

