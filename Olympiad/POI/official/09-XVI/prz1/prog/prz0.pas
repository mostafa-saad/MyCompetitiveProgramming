(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     prz0.pas                                                  *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie wzorcowe O(n*K)                               *
 *                                                                       *
 *************************************************************************)
const MAX_NUM = 100;
const MAX_N = 100000;
const X = 0;
const Y = 1;

(* tablice przechowujace wierzcholki *)
var s : array[1..2*MAX_N] of LongInt; (* 0 lub 1 - ktorego slowa (x lub y) tyczy sie dany wierzcholek *)
a, b : array[1..2*MAX_N] of LongInt; (* konce przedzialu *)
pKraw, pWart : array[1..2*MAX_N] of LongInt; (* krawedz przy przejsciu do prefiksu, wartosc przy przejsciu do prefiksu *)
sKraw, sWart : array[1..2*MAX_N] of LongInt; (* krawedz przy przejsciu do sufiksu, wartosc przy przejsciu do sufiksu *)

dl : array[0..1] of LongInt; (* dlugosc ciagu (n, m) *)
tab1, tab2 : array[1..2*MAX_N] of LongInt; (* potrzebne do sortowania przez zliczanie *)
ileWierzch : LongInt;
ile : array[1..2*MAX_N] of LongInt; (* potrzebne do sortowania przez zliczanie *)
rozmiar : LongInt;
maxWart : LongInt; (* maksymalna wartosc nadana przy numerowaniu wierzcholkow *)

slowo : array[0..1, 1..MAX_N] of LongInt;
ilosc : array[0..1, 1..MAX_NUM] of LongInt; (* ilosci danych liczb calkowitych w ciagu *)
rozne : array[0..1] of LongInt; (* ilosc roznych znakow w ciagach *)
najdluzszySufiks : array[0..1, 0..1, 1..MAX_N] of LongInt; (* [poziom][slowo][i]: wartosci dla najdluzszych sufiksow slow [1..i] *)
najdluzszyPrefiks : array[0..1, 0..1, 1..MAX_N] of LongInt; (*[poziom][slowo][i]: wartosci dla najdluzszych prefiksow slow [i..n] *)
poziom : LongInt; (* na ktorym poziomie akurat jestesmy - 0 lub 1 *)

function rowneWierzch(w1, w2 : LongInt) : Boolean;
begin
    rowneWierzch := (pKraw[w1] = pKraw[w2]) and (pWart[w1] = pWart[w2])
        and (sKraw[w1] = sKraw[w2]) and (sWart[w1] = sWart[w2]);
end;

(* operacje na zbiorze, wykorzystuja tablice ile *)
procedure dodaj(a : LongInt);
begin
    if ile[a] = 0 then
        rozmiar := rozmiar + 1;
    ile[a] := ile[a] + 1;
end;

procedure usun(a : LongInt);
begin
    ile[a] := ile[a] - 1;
    if ile[a] = 0 then
        rozmiar := rozmiar - 1;
end;

function zawiera(a : LongInt) : Boolean;
begin
    zawiera := (ile[a] <> 0);
end;

procedure tworzPoziom(sl, ileZnakow : LongInt);
var i, j, poprzedniPoziom, ostatnioDodany : LongInt;
begin
    for i := 1 to MAX_NUM do
        ile[i] := 0;
    rozmiar := 0;
    poprzedniPoziom := poziom xor 1;
    i := 1;
    j := 1;
    
    while j <= dl[sl] do
    begin
        while (j <= dl[sl]) and ((rozmiar < ileZnakow) or zawiera(slowo[sl][j])) do
        begin
            if not zawiera(slowo[sl][j]) then ostatnioDodany := slowo[sl][j];
            dodaj(slowo[sl][j]);
            j := j + 1;
        end;
        
        ileWierzch := ileWierzch + 1;
        s[ileWierzch] := sl;
        a[ileWierzch] := i;
        b[ileWierzch] := j - 1;
        pWart[ileWierzch] := najdluzszyPrefiks[poprzedniPoziom][sl][i];
        sWart[ileWierzch] := najdluzszySufiks[poprzedniPoziom][sl][j - 1];
        pKraw[ileWierzch] := ostatnioDodany;
        while rozmiar = ileZnakow do
        begin
            sKraw[ileWierzch] := slowo[sl][i];
            usun(slowo[sl][i]);
            i := i + 1;
        end;
    end;
end;

procedure sortujWierzcholki();
var i : LongInt;
begin
    (* sortuj wg pKraw, wynik zapisz w tab2 *)
    for i := 1 to maxWart do
        ile[i] := 0;
    for i := 1 to ileWierzch do
        ile[pKraw[i]] := ile[pKraw[i]] + 1;
    for i := 2 to maxWart do
        ile[i] := ile[i] + ile[i-1];
    for i := ileWierzch downto 1 do
    begin
        tab2[ile[pKraw[i]]] := i;
        ile[pKraw[i]] := ile[pKraw[i]] - 1;
    end;
    (* sortuj tab2 wg pWart, wynik zapisz w tab1 *)
    for i := 1 to maxWart do
        ile[i] := 0;
    for i := 1 to ileWierzch do
        ile[pWart[tab2[i]]] := ile[pWart[tab2[i]]] + 1;
    for i := 2 to maxWart do
        ile[i] := ile[i] + ile[i-1];
    for i := ileWierzch downto 1 do
    begin
        tab1[ile[pWart[tab2[i]]]] := tab2[i];
        ile[pWart[tab2[i]]] := ile[pWart[tab2[i]]] - 1;
    end;
    (* sortuj tab1 wg sKraw, wynik zapisz w tab2 *)
    for i := 1 to maxWart do
        ile[i] := 0;
    for i := 1 to ileWierzch do
        ile[sKraw[tab1[i]]] := ile[sKraw[tab1[i]]] + 1;
    for i := 2 to maxWart do
        ile[i] := ile[i] + ile[i-1];
    for i := ileWierzch downto 1 do
    begin
        tab2[ile[sKraw[tab1[i]]]] := tab1[i];
        ile[sKraw[tab1[i]]] := ile[sKraw[tab1[i]]] - 1;
    end;
    (* sortuj tab2 wg sWart, wynik zapisz w tab1 *)
    for i := 1 to maxWart do
        ile[i] := 0;
    for i := 1 to ileWierzch do
        ile[sWart[tab2[i]]] := ile[sWart[tab2[i]]] + 1;
    for i := 2 to maxWart do
        ile[i] := ile[i] + ile[i-1];
    for i := ileWierzch downto 1 do
    begin
        tab1[ile[sWart[tab2[i]]]] := tab2[i];
        ile[sWart[tab2[i]]] := ile[sWart[tab2[i]]] - 1;
    end;
end;

procedure numerujWierzcholki();
var aktNumer, i : LongInt;
begin
    aktNumer := 1;
    najdluzszyPrefiks[poziom][s[tab1[1]]][a[tab1[1]]] := aktNumer;
    najdluzszySufiks[poziom][s[tab1[1]]][b[tab1[1]]] := aktNumer;
    for i := 2 to ileWierzch do
    begin
        if not rowneWierzch(tab1[i], tab1[i-1]) then
            aktNumer := aktNumer + 1;
        najdluzszyPrefiks[poziom][s[tab1[i]]][a[tab1[i]]] := aktNumer;
        najdluzszySufiks[poziom][s[tab1[i]]][b[tab1[i]]] := aktNumer;
    end;
    maxWart := MAX_NUM;
    if aktNumer > maxWart then
        maxWart := aktNumer;
end;

var k, sl, i, ileZnakow : LongInt;
    czyRozne : Boolean;
begin
    Read(k);
    while k <> 0 do
    begin
        k := k - 1;
        for sl := X to Y do
            for i := 1 to MAX_NUM do
                ilosc[sl][i] := 0;
        rozne[X] := 0;
        rozne[Y] := 0;
        
        Read(dl[X], dl[Y]);
        for sl := X to Y do
            for i := 1 to dl[sl] do
            begin
                Read(slowo[sl][i]);
                if ilosc[sl][slowo[sl][i]] = 0 then rozne[sl] := rozne[sl] + 1;
                ilosc[sl][slowo[sl][i]] := ilosc[sl][slowo[sl][i]] + 1;
            end;
        
        czyRozne := (rozne[X] <> rozne[Y]);
        for i := 1 to MAX_NUM do
            if (ilosc[X][i]<>0) <> (ilosc[Y][i]<>0) then
                czyRozne := true;
        
        if czyRozne then
        begin (* W(x) != W(y) *)
            WriteLn('0');
            continue;
        end else if rozne[X] = 1 then (* |W(x)| = |W(y)| = 1 *)
        begin
            WriteLn('1');
            continue;
        end;
        
        poziom := 0;
        for sl := X to Y do
            for i := 1 to dl[sl] do
            begin
                najdluzszyPrefiks[poziom][sl][i] := slowo[sl][i];
                najdluzszySufiks[poziom][sl][i] := slowo[sl][i];
            end;
        maxWart := MAX_NUM;
        for ileZnakow := 2 to rozne[X] do
        begin
            poziom := poziom xor 1;
            ileWierzch := 0;
            tworzPoziom(X, ileZnakow);
            tworzPoziom(Y, ileZnakow);
            sortujWierzcholki();
            numerujWierzcholki();
        end;
        
        if najdluzszyPrefiks[poziom][X][1] = najdluzszyPrefiks[poziom][Y][1] then
            WriteLn('1')
        else
            WriteLn('0');
    end;
end.
