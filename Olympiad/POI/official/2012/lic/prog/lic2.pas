(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n log^3 n)                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************)

uses pliclib;

const MAXN=30000;
const MAX_IND=250;
const MAX_2=16;

var n: longint;
var pozycja: array[0..MAXN, 0..MAX_IND] of longint;
var optymalny_ruch: array[0..MAXN, 0..MAX_IND] of longint;
var pula, stawka: longint;

function oblicz_indeks(staw: longint): longint;
var
    i2, i3: longint;
begin
    i2 := 0;
    i3 := 0;
    while(staw mod 2 = 0) do begin
        inc(i2);
        staw := staw div 2;
    end;
    while(staw mod 3 = 0) do begin
        inc(i3);
        staw := staw div 3;
    end;
    oblicz_indeks := i3 * MAX_2 + i2;
end;

procedure wykonaj_ruch(x: longint);
begin
    if x = 1 then begin
        pula := pula + stawka;
        stawka := 1
    end else if x = 2 then begin
        stawka := stawka * 2
    end else if x = 3 then begin
        stawka := stawka * 3
    end;
end;

function spr_poz(apula: longint; astawka: longint): longint;
var
    ruch1, ruch2, ruch3: longint;
    istawka: longint;
begin
    if apula + astawka >= n then begin
        spr_poz := 1
    end else begin
        istawka := oblicz_indeks(astawka);
        if pozycja[apula][istawka] > 0 then begin
            spr_poz := pozycja[apula][istawka]
        end else begin
            ruch1 := spr_poz(apula + astawka, 1);
            ruch2 := spr_poz(apula, astawka * 2);
            ruch3 := spr_poz(apula, astawka * 3);
            if (ruch1 = 1) or (ruch2 = 1) or (ruch3 = 1) then begin
                pozycja[apula][istawka] := 2;
                if ruch1 = 1 then
                    optymalny_ruch[apula][istawka] := 1
                else if ruch2 = 1 then
                    optymalny_ruch[apula][istawka] := 2
                else if ruch3 = 1 then
                    optymalny_ruch[apula][istawka] := 3;
                spr_poz := 2
            end else begin
                pozycja[apula][istawka] := 1;
                spr_poz := 1
            end;
        end;
    end;
end;

procedure wybierz_ruch();
var
    x: longint;
begin
    spr_poz(pula, stawka);
    x := optymalny_ruch[pula][oblicz_indeks(stawka)];
    wykonaj_ruch(x);
    alojzy(x);
end;

begin
    n := inicjuj();
    stawka := 1;
    while true do begin
        wybierz_ruch();
        wykonaj_ruch(bajtazar());
    end;
end.
