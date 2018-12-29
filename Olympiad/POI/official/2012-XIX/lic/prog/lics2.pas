(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne: wzorcowka bez spamietywania *
 *                                                                       *
 *************************************************************************)

uses pliclib;

const MAXN=2000;

var n: integer;
var optymalny_ruch: array[0..MAXN + 1, 0..MAXN + 1] of integer;
var pula, stawka: integer;

procedure wykonaj_ruch(x: integer);
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

function spr_poz(apula: integer; astawka: integer): integer;
var
    ruch1, ruch2, ruch3: integer;
begin
    if apula + astawka >= n then begin
        spr_poz := 1
    end else begin
        ruch1 := spr_poz(apula + astawka, 1);
        ruch2 := spr_poz(apula, astawka * 2);
        ruch3 := spr_poz(apula, astawka * 3);
        if (ruch1 = 1) or (ruch2 = 1) or (ruch3 = 1) then begin
            if ruch1 = 1 then
                optymalny_ruch[apula][astawka] := 1
            else if ruch2 = 1 then
                optymalny_ruch[apula][astawka] := 2
            else if ruch3 = 1 then
                optymalny_ruch[apula][astawka] := 3;
            spr_poz := 2
        end else begin
            spr_poz := 1
        end;
    end;
end;

procedure wybierz_ruch();
var
    x: integer;
begin
    spr_poz(pula, stawka);
    x := optymalny_ruch[pula][stawka];
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
