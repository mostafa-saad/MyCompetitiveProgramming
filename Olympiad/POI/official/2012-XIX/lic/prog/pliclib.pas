(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Biblioteka interaktywna                          *
 *                                                                       *
 *************************************************************************)


{
    Mozliwe strategie:
    S_LOSOWA: gra losowo, dopoki stawka+pula < 1/2 n
    S_POPTYMALNA: gra optymalnie, ale myli sie w 10% przypadkow dopoki stawka+pula < 1/2 n
    S_OPTYMALNA: gra optymalnie
}
unit pliclib;

interface

function inicjuj(): longint;

procedure alojzy(x: longint);

function bajtazar(): longint;

implementation

const S_LOSOWA=0;
const S_POPTYMALNA=1;
const S_OPTYMALNA=2;
const S_OCEN=3;

const OK=1;
const ERR=0;

const MAXN=30000;
const MAX_IND=250;

const WYGRYWAJACA=1;
const PRZEGRYWAJACA=2;
const NIEZNANA=0;

const MAGIC_IN_SUM=74967;
const MAGIC_OUT=756396726;

const Z_ALOJZY=1;
const Z_BAJTAZAR=2;

const PAS=1;
const P2=2;
const P3=3;


var n: longint; // dane
var strategia: longint; // strategia wykorzystywana przez biblioteke
var pozycja: array[0..MAXN, 0..MAX_IND] of longint; // okresla, czy pozycja jest wyrgywajaca czy przegrywajaca
var optymalny_ruch: array[0..MAXN, 0..MAX_IND] of longint; // okresla jaki ruch jest optymalny
var indeks_stawki: array[0..MAXN] of longint; // zamienia wartosc stawki na indeks w tablicach pozycja oraz optymlany_ruch
var zainicjowane: boolean = FALSE; // czy zostalo juz wywolana funkcja inicjuj
var pula, stawka: longint; // aktualna wartosc puli i stawki
var kolej: longint; // aktualny zawodnik
var rand_val: longint; // bardzo pseudo losowa liczba
var ocen_val: longint; // wartosc kolejnego ruchu ocen

function randint(): longint;
begin
    rand_val := (rand_val + 3) * (rand_val + 7);
    rand_val := rand_val mod 100;
    randint := rand_val;
end;

function ruchocen(): longint;
begin
    ocen_val := ocen_val + 1;
    ocen_val := ocen_val mod 3;
    ruchocen := PAS + ocen_val;
end;

{Wypelnia tablice indeks_stawki}
procedure oblicz_indeksy(maxn: longint);
var
    aind: longint;
    i, j: longint;
begin
    aind := 0;
    i := 1;
    while i <= maxn do begin
        j := 1;
        while (i * j) <= maxn do begin
            indeks_stawki[i * j] := aind;
            inc(aind);
            j := j * 3;
        end;
        i := i * 2;
    end;
end;

{Wypisuje wynik}
procedure wypisz_wynik(wynik: longint);
begin
    writeln(MAGIC_OUT); // pierwsza linia: magic out
    writeln(wynik); // druga linia: wynik
end;

{sprawdza rekurencyjnie drzewo gry spamietujac wyniki, ustawia tez optymalny ruch}
function sprawdz_pozycje(pula_poz: longint; stawka_poz: longint): longint;
var
    rPAS, rP2, rP3: longint;
    stawka_ind: longint;
begin
    if pula_poz + stawka_poz >= n then begin
        sprawdz_pozycje := PRZEGRYWAJACA
    end else begin
        stawka_ind := indeks_stawki[stawka_poz];
        if pozycja[pula_poz][stawka_ind] <> NIEZNANA then begin
            sprawdz_pozycje := pozycja[pula_poz][stawka_ind]
        end else begin
            rPAS := sprawdz_pozycje(pula_poz + stawka_poz, 1);
            rP2 := sprawdz_pozycje(pula_poz, stawka_poz * 2);
            rP3 := sprawdz_pozycje(pula_poz, stawka_poz * 3);
            if rPAS = PRZEGRYWAJACA then begin
                pozycja[pula_poz][stawka_ind] := WYGRYWAJACA;
                optymalny_ruch[pula_poz][stawka_ind] := PAS;
                sprawdz_pozycje := WYGRYWAJACA
            end else if rP2 = PRZEGRYWAJACA then begin
                pozycja[pula_poz][stawka_ind] := WYGRYWAJACA;
                optymalny_ruch[pula_poz][stawka_ind] := P2;
                sprawdz_pozycje := WYGRYWAJACA
            end else if rP3 = PRZEGRYWAJACA then begin
                pozycja[pula_poz][stawka_ind] := WYGRYWAJACA;
                optymalny_ruch[pula_poz][stawka_ind] := P3;
                sprawdz_pozycje := WYGRYWAJACA
            end else begin
                pozycja[pula_poz][stawka_ind] := PRZEGRYWAJACA;
                optymalny_ruch[pula_poz][stawka_ind] := PAS + randint() mod 3;
                sprawdz_pozycje := PRZEGRYWAJACA
            end
        end
    end;
end;

{Generuj ruch Bajtazara, biorac pod uwage strategie}
function generuj_ruch(): longint;
begin
    sprawdz_pozycje(pula, stawka);
    if ((strategia <> S_OCEN) and (pula + stawka >= ((n * 5) div 7))) or (strategia = S_OPTYMALNA) or ((strategia = S_POPTYMALNA) and (randint() mod 10 <> 3)) then begin
        generuj_ruch := optymalny_ruch[pula][indeks_stawki[stawka]]
    end else begin
        if (strategia = S_OCEN) then begin
            generuj_ruch := ruchocen()
        end else begin
            generuj_ruch := PAS + randint() mod 3
        end;
    end;
end;

{Inicjuje gre pomiedzy Alojzym i Bajtazarem}
function inicjuj(): longint;
var
    magic: longint;
begin
    if zainicjowane <> false then begin
        wypisz_wynik(ERR);
        writeln( 'Program zawodnika moze wolac funkcje inicjuj tylko raz.');
        halt(0)
    end else begin
        rand_val := 0;
        ocen_val := 2;
        zainicjowane := true;
        read(n, strategia, magic);
        if (n < 1) or (n > MAXN) or (strategia < 0) or (strategia > 3) or (n + strategia + magic <> MAGIC_IN_SUM) then begin
            wypisz_wynik(ERR);
            writeln('Program zawodnika nie moze wczytywac zadanego inputu.');
            halt(0)
        end else begin
            pula := 0;
            stawka := 1;
            kolej := Z_ALOJZY;
            oblicz_indeksy(n);
            inicjuj := n
        end;
    end;
end;

{Aktualizuje pule i stawke, biorac pod uwage ruch X}
procedure wykonaj_ruch(x: longint);
begin
    if x = PAS then begin
        pula := pula + stawka;
        stawka := 1
    end else if x = P2 then begin
        stawka := stawka * 2
    end else if x = P3 then begin
        stawka := stawka * 3
    end;
end;

{Wykonuje ruch gracza}
procedure alojzy(x: longint);
begin
    if zainicjowane = false then begin
        wypisz_wynik(ERR);
        writeln('Program zawodnika nie wywolal funkcji inicjuj.');
        halt(0)
    end else if (x <> PAS) and (x <> P2) and (x <> P3) then begin
        wypisz_wynik(ERR);
        writeln('Nieprawidlowy ruch Alojzego.');
        halt(0)
    end else if kolej <> Z_ALOJZY then begin
        wypisz_wynik(ERR);
        writeln('Ruch Alojzego bez wczeÄšÂniejszego ruchu Bajtazara.');
        halt(0)
    end else if pula + stawka >= n then begin
        wypisz_wynik(ERR);
        writeln('Suma puli i stawki przekroczyla n.');
        halt(0)
    end else begin
        kolej := Z_BAJTAZAR;
        wykonaj_ruch(x)
    end;
end;

{Generuje i wykonuje ruch Bajtazara}
function bajtazar(): longint;
var
    x: longint;
begin
    if zainicjowane = false then begin
        wypisz_wynik(ERR);
        writeln('Program zawodnika nie wywolal funkcji inicjuj.');
        halt(0)
    end else if kolej <> Z_BAJTAZAR then begin
        wypisz_wynik(ERR);
        writeln('Pytanie o ruch Bajtocego przed wykonaniem ruchu Alojzego.');
        halt(0)
    end else if pula + stawka >= n then begin
        wypisz_wynik(OK);
        halt(0)
    end else begin
        x := generuj_ruch();
        kolej := Z_ALOJZY;
        wykonaj_ruch(x);
        bajtazar := x
    end;
end;

end.
