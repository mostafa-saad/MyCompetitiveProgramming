(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs8.pas                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie generujace graf bezposrednio O(n^2*K)         *
 *                                                                       *
 *************************************************************************)

const MAX_N = 100000;
const MAX_NUM = 100;
const TAB_SIZE = 100000;

var tab : array[0..MAX_N-1] of LongInt;
ile : array[1..MAX_NUM] of LongInt;
sufiks, prefiks, sufiksKraw, prefiksKraw, wierzcholek : array[0..TAB_SIZE] of LongInt;
ile_wierzch : LongInt;

function wierzch(pozycja, rozmiar, poziom : LongInt) : LongInt;
begin
    wierzch := poziom*rozmiar + pozycja;
end;

function budujGraf(n, p, dl, poziom : LongInt) : LongInt;
var akt_wierzch, sufiksPoz, i, poz : LongInt;
begin
    if wierzcholek[wierzch(p, n, poziom)]<>0 then
        budujGraf := wierzcholek[wierzch(p, n, poziom)]
    else
    begin
        ile_wierzch := ile_wierzch + 1;
        akt_wierzch := ile_wierzch;
        wierzcholek[wierzch(p, n, poziom)] := akt_wierzch;
        sufiks[akt_wierzch] := -1;
        prefiks[akt_wierzch] := -1;
        for i := 1 to MAX_NUM do
            ile[i] := 0;
        for i := 0 to dl-1 do
            ile[tab[p+i]] := ile[tab[p+i]] + 1;
        poz := 0;
        while ile[tab[p+poz]] > 1 do
        begin
            ile[tab[p+poz]] := ile[tab[p+poz]] - 1;
            poz := poz + 1;
        end;
        sufiksKraw[akt_wierzch] := tab[p+poz];
        sufiksPoz := poz;
        for i := 0 to poz-1 do
            ile[tab[p+i]] := ile[tab[p+i]] + 1;
        poz := dl - 1;
        while ile[tab[p+poz]] > 1 do
        begin
            ile[tab[p+poz]] := ile[tab[p+poz]] - 1;
            poz := poz - 1;
        end;
        prefiksKraw[akt_wierzch] := tab[p+poz];
        if poz > 0 then
            prefiks[akt_wierzch] := budujGraf(n, p, poz, poziom+1);
        if sufiksPoz < dl-1 then
            sufiks[akt_wierzch] := budujGraf(n, p+sufiksPoz+1, dl-sufiksPoz-1, poziom+1);
        budujGraf := akt_wierzch;
    end;
end;

function porownajGrafy(vx, vy : LongInt) : Boolean;
begin
    if (vx = -1) or (vy = -1) then
        porownajGrafy := (vx=vy)
    else
        porownajGrafy := (sufiksKraw[vx]=sufiksKraw[vy]) and (prefiksKraw[vx]=prefiksKraw[vy]) and porownajGrafy(sufiks[vx], sufiks[vy]) and porownajGrafy(prefiks[vx], prefiks[vy]);
end;

var n, m, k, i, korzen_x, korzen_y : LongInt;
begin
    Read(k);
    while k <> 0 do
    begin
        k := k - 1;
        Read(n, m);
        ile_wierzch := 0;
        for i := 0 to TAB_SIZE do
            wierzcholek[i] := 0;
        for i := 0 to n-1 do
            Read(tab[i]);
        korzen_x := budujGraf(n, 0, n, 0);
        for i := 0 to m-1 do
            Read(tab[i]);
        for i := 0 to TAB_SIZE do
            wierzcholek[i] := 0;
        korzen_y := budujGraf(m, 0, m, 0);
        
        if porownajGrafy(korzen_x, korzen_y) then
            WriteLn('1')
        else
            WriteLn('0');
    end;
end.
