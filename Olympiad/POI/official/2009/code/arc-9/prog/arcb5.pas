{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb5.pas                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(k log n)                         *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego i wybiera      *}
{*            maksimum z przedzialu w czasie logarytmicznym wzgledem     *}
{*            jego dlugosci.                                             *} 
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

const
    MAX_N = 2097153;

var
    n, k, it, iss, il, i : longint;
    seq : array [0..MAX_N] of longint;
    tre : array [0..2 * MAX_N + 1] of longint;    

procedure update(a : longint);
var
    tmp1, tmp2 : longint;
begin
    tmp1 := tre[2 * a];
    tmp2 := tre[2 * a + 1];
    if seq[tmp1] >= seq[tmp2] then
        tre[a] := tmp1
    else
        tre[a] := tmp2;
end;

procedure init_tre();
var
    i : longint;
begin
    it := 1;
    while(it < n)do
        it := it * 2;
    for i := 0 to it - 1 do
        if i < n then
            tre[i + it] := i
        else
            tre[i + it] := n;
    for i := it - 1 downto 1 do
        update(i);
end;

function get_max(a, b : longint) : longint;
var
    res : longint;
begin
    res := n;
    a := a + it;
    b := b + it;
    if seq[tre[a]] > seq[res] then
        res := tre[a];
    if seq[tre[b]] > seq[res] then
        res := tre[b];
    while(a div 2 <> b div 2)do
    begin
        if (a mod 2 = 0) and (seq[tre[a + 1]] > seq[res]) then
            res := tre[a + 1];
        if (b mod 2 = 1) and (seq[tre[b - 1]] > seq[res]) then
            res := tre[b - 1];
        b := b div 2;
        a := a div 2;
    end;
    get_max := res;
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
    init_tre();
    iss := 0;
    for i := 0 to k - 1 do
    begin
        il := get_max(iss, n - k + i);
        iss := il + 1;
        wypisz(seq[il]);
    end;
end.
