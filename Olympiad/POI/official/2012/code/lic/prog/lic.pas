(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n log^2 n)                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

uses pliclib;

const MAXN = 30000;
const MAX_OSIAGALNYCH = 250;
(* oszacowanie na maksymalna ilosc osiagalnych wartosci stawki *)

var n: longint;
var indeks_stawki : array[0..MAXN] of longint;
var pozycja: array[0..MAXN + 1, 1..MAX_OSIAGALNYCH] of byte;
var optymalny_ruch: array[0..MAXN + 1, 1..MAX_OSIAGALNYCH] of byte;
var pula, stawka: longint;

procedure oblicz_indeks_stawki(max : longint);
var
    i : longint;
begin
    for i := 2 to max do indeks_stawki[i] := 0;
    indeks_stawki[1] := 1;
    for i := 1 to (max div 2) do
        if indeks_stawki[i] = 1 then
        begin
            indeks_stawki[2*i] := 1;
            if 3*i <= max then indeks_stawki[3*i] := 1;
        end;
    for i := 2 to max do
        indeks_stawki[i] := indeks_stawki[i] + indeks_stawki[i-1];
end;

procedure wykonaj_ruch(x: longint);
begin
    if x = 1 then
    begin
        pula := pula + stawka;
        stawka := 1
    end else
        stawka := stawka * x
end;

function spr_poz(apula: longint; astawka: longint): longint;
var
    ruch1, ruch2, ruch3: longint;
    indeks : longint;
begin
    if apula + astawka >= n then
        spr_poz := 1
    else begin
        indeks := indeks_stawki[astawka];
        if pozycja[apula][indeks] > 0 then
            spr_poz := pozycja[apula][indeks]
        else begin
            ruch1 := spr_poz(apula + astawka, 1);
            ruch2 := spr_poz(apula, astawka * 2);
            ruch3 := spr_poz(apula, astawka * 3);
            if (ruch1 = 1) or (ruch2 = 1) or (ruch3 = 1) then
            begin
                pozycja[apula][indeks] := 2;
                if ruch1 = 1 then
                    optymalny_ruch[apula][indeks] := 1
                else if ruch2 = 1 then
                    optymalny_ruch[apula][indeks] := 2
                else if ruch3 = 1 then
                    optymalny_ruch[apula][indeks] := 3;
                spr_poz := 2
            end else begin
                pozycja[apula][indeks] := 1;
                spr_poz := 1
            end;
        end;
    end;
end;

procedure wybierz_ruch;
var
    x : longint;
begin
    spr_poz(pula, stawka);
    x := optymalny_ruch[pula][indeks_stawki[stawka]];
    wykonaj_ruch(x);
    alojzy(x);
end;

begin
    n := inicjuj();
    stawka := 1;
    oblicz_indeks_stawki(n);
    while true do
    begin
        wybierz_ruch();
        wykonaj_ruch(bajtazar());
    end;
end.
