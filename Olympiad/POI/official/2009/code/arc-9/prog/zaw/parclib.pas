{**************************************************************************}
{*                                                                        *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                            *}
{*   Plik:    parclib.pas                                                 *}
{*   Autor:   Bartosz Gorski                                              *}
{*   Opis:    Biblioteka dla zawodnikow.                                  *}
{*                                                                        *}
{**************************************************************************}

unit parclib;

interface

function inicjuj : longint;
function wczytaj : longint;
procedure wypisz(jakoscProjektu : longint);

implementation

const MIN_K = 1;
const MAX_K = 1000000;
const MIN_P = 1;
const MAX_P = 1000000000;

var
    k, p, ile_wypisano_liczb : longint;
    koniec_ciagu, zainicjowano : boolean;

procedure blad(com : String);
begin
    writeln(com);
    halt;
end;

function inicjuj() : longint;
begin
    if zainicjowano then
        blad('Zawodnik moze wywolac funkcje inicjuj tylko raz!!!');
    readln(k);
    if (k < MIN_K) or (k > MAX_K) then
        blad('Niepoprawna wartosc k!!!');
    zainicjowano := true;
    ile_wypisano_liczb := 0;
    koniec_ciagu := false;
    inicjuj := k;
end;

function wczytaj() : longint;
begin
    if not zainicjowano then
        blad('Zawodnik nie wywolal funkcji inicjuj!!!');
    if koniec_ciagu then
        blad('Zawodnik wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!');
    readln(p);
    if p = 0 then
    begin
        koniec_ciagu := true;
        wczytaj := 0;
        exit;
    end;
    if (p < MIN_P) or (p > MAX_P) then
        blad('Nieprawidlowa jakosc projektu');
    wczytaj := p;
end;

procedure wypisz(jakoscProjektu : longint);
begin
    if not zainicjowano then
        blad('Zawodnik nie wywolal funkcji inicjuj!!!');
    writeln(jakoscProjektu);
    inc(ile_wypisano_liczb);
    if ile_wypisano_liczb = k then
        halt;
end;

begin
    zainicjowano := false;
end.
