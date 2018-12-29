{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arc4.pas                                                   *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie alternatywne.                                  *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

const
    MAX_K = 1000000; // maksymalna dlugosc szukanego podciagu

var
    i, a, k, 
    ib, ie, // wskazniki na pierwszy i ostatni element w kolejce
    cou, // ilosc elementow znajdujacych sie w kolejce
    iss // wskaznik na szczyt stosu
    : longint;

    buf, // kolejka reprezentujaca bufor
    sub // stos reprezentujacy szukany podciag
    : array [0..MAX_K - 1] of longint;

    is_end // czy zakonczylismy juz wczytywanie ciagu
    : boolean;

{ Uzupelnia bufor tak aby znajdowalo sie w nim [k] elementow jesli to mozliwe
  (jesli wczytywany ciag jeszcze sie nie skonczyl) }
procedure fill_buffer();
var
    a : longint;
begin
    if((is_end) or (cou = k))then
        exit;
    while(cou < k)do
    begin
        a := wczytaj();
        if a = 0 then
        begin
            is_end := true;
            exit
        end;
        buf[ie] := a;
        inc(ie);
        inc(cou);
        if ie = MAX_K then
            ie := 0;
    end;
end;

begin
    k := inicjuj();
    for i := 0 to k - 1 do
        sub[i] := 0;
    ib := 0;
    ie := 0;
    cou := 0;
    iss := 0;
    is_end := false;
    fill_buffer();
    while(cou > 0)do
    begin
        a := buf[ib];
        inc(ib);
        dec(cou);
        if ib = MAX_K then
            ib := 0;
        while(((iss + cou + 1) > k) and (sub[iss - 1] < a))do
            dec(iss);
        if iss < k then
        begin
            sub[iss] := a;
            inc(iss);
        end;
        fill_buffer();
    end;
    for i := 0 to k - 1 do
        wypisz(sub[i]);
end.
