(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs4.pas                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie dynamiczne O(n^5)                             *
 *                                                                       *
 *                                                                       *
 *************************************************************************)

const MAX_NUM = 100;
const MAX_N = 100000;

var wynik_tab : array [0..8000000] of LongInt;
x, y : array [1..MAX_N] of LongInt;
ile_x, ile_y : array [1..MAX_NUM] of LongInt;
n, m : LongInt;

function get_wynik(px, kx, py, ky : LongInt) : Boolean;
var klucz, ind, bit : LongInt;
begin
    klucz := (px-1)*n*m*m + (kx-1)*m*m + (py-1)*m + ky-1;
    ind := klucz div 32;
    bit := klucz mod 32;
    get_wynik := (wynik_tab[ind] and (1 shl bit)) <> 0;
end;

procedure set_wynik(px, kx, py, ky : LongInt; wartosc : Boolean);
var klucz, ind, bit : LongInt;
begin
    klucz := (px-1)*n*m*m + (kx-1)*m*m + (py-1)*m + ky-1;
    ind := klucz div 32;
    bit := klucz mod 32;
    if wartosc then
        wynik_tab[ind] := wynik_tab[ind] or (1 shl bit)
    else
        wynik_tab[ind] := wynik_tab[ind] xor (wynik_tab[ind] and (1 shl bit));
end;

function licz(px, kx, py, ky : LongInt) : Boolean;
var rozne_x, ostatni_x, pierwszy_x, rozne_y, ostatni_y, pierwszy_y, i : LongInt;
    czy_rozne : Boolean;
begin
    rozne_x := 0;
    rozne_y := 0;
    ostatni_x := 0;
    ostatni_y := 0;
    for i := 1 to MAX_NUM do
    begin
        ile_x[i] := 0;
        ile_y[i] := 0;
    end;
    
    for i := px to kx do
    begin
        if ile_x[x[i]] = 0 then
        begin
            rozne_x := rozne_x + 1;
            ostatni_x := i - 1;
        end;
        ile_x[x[i]] := ile_x[x[i]] + 1;
    end;
    
    for i := py to ky do
    begin
        if ile_y[y[i]] = 0 then
        begin
            rozne_y := rozne_y + 1;
            ostatni_y := i - 1;
        end;
        ile_y[y[i]] := ile_y[y[i]] + 1;
    end;
    
    czy_rozne := (rozne_y <> rozne_x);
    for i := 1 to MAX_NUM do
        if (ile_x[i]<>0) <> (ile_y[i]<>0) then
            czy_rozne := true;
    
    pierwszy_x := px;
    while ile_x[x[pierwszy_x]] > 1 do
    begin
        ile_x[x[pierwszy_x]] := ile_x[x[pierwszy_x]] - 1;
        pierwszy_x := pierwszy_x + 1;
    end;
    pierwszy_x := pierwszy_x + 1;
    pierwszy_y := py;
    while ile_y[y[pierwszy_y]] > 1 do
    begin
        ile_y[y[pierwszy_y]] := ile_y[y[pierwszy_y]] - 1;
        pierwszy_y := pierwszy_y + 1;
    end;
    pierwszy_y := pierwszy_y + 1;
    
    licz := (not czy_rozne) and ((rozne_x = 1) or
        (get_wynik(px, ostatni_x, py, ostatni_y) (* f(p(x), p(y)) *)
        and get_wynik(pierwszy_x, kx, pierwszy_y, ky))); (* f(s(x), s(y)) *)
end;

var k, i, j, px, dl_x, py, dl_y : LongInt;
begin
    Read(k);
    while k<>0 do
    begin
        k := k - 1;
        for i := 1 to MAX_NUM do
        begin
            ile_x[i] := 0;
            ile_y[i] := 0;
        end;
        Read(n, m);
        for i := 1 to n do
            Read(x[i]);
        for i := 1 to m do
            Read(y[i]);
        
        for dl_x := 1 to n do
            for dl_y := 1 to m do
                for px := 1 to n-dl_x+1 do
                    for py := 1 to m-dl_y+1 do
                        set_wynik(px, px+dl_x-1, py, py+dl_y-1, licz(px, px+dl_x-1, py, py+dl_y-1));
        
        if get_wynik(1, n, 1, m) then
            WriteLn('1')
        else
            WriteLn('0');
    end;
end.
