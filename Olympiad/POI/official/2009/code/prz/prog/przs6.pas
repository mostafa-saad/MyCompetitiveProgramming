(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs6.pas                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie dynamiczne O(n^3*K)                           *
 *                                                                       *
 *************************************************************************)

const MAX_NUM = 100;
const MAX_N = 100000;

var wynik_tab : array[0..8000000] of LongInt;
x, y : array[1..MAX_N] of LongInt;
ile_x, ile_y : array[1..MAX_NUM] of LongInt;
n, m : LongInt;

function get_wynik(a, b, ile_znakow : LongInt) : Boolean;
var klucz, ind, bit : LongInt;
begin
    klucz := (ile_znakow-1) * n * m + (b-1) * n + a-1;
    ind := klucz div 32;
    bit := klucz mod 32;
    get_wynik := (wynik_tab[ind] and (1 shl bit)) <> 0;
end;

procedure set_wynik(a, b, ile_znakow : LongInt; wartosc : Boolean);
var klucz, ind, bit : LongInt;
begin
    klucz := (ile_znakow-1) * n * m + (b-1) * n + a-1;
    ind := klucz div 32;
    bit := klucz mod 32;
    if wartosc then
        wynik_tab[ind] := wynik_tab[ind] or (1 shl bit)
    else
        wynik_tab[ind] := wynik_tab[ind] xor (wynik_tab[ind] and (1 shl bit));
end;

function licz(px, py, ile_znakow : LongInt) : Boolean;
var rozne_x, pierwszy_x, rozne_y, pierwszy_y, i : LongInt;
    czy_rozne : Boolean;
begin
    rozne_x := 0;
    for i := 1 to MAX_NUM do
        ile_x[i] := 0;
    for i := px to n do
    begin
        if (rozne_x = ile_znakow) and (ile_x[x[i]] = 0) then
            break;
        if ile_x[x[i]] = 0 then
            rozne_x := rozne_x + 1;
        ile_x[x[i]] := ile_x[x[i]] + 1;
    end;
    pierwszy_x := px;
    while ile_x[x[pierwszy_x]] > 1 do
    begin
        ile_x[x[pierwszy_x]] := ile_x[x[pierwszy_x]] - 1;
        pierwszy_x := pierwszy_x + 1;
    end;
    pierwszy_x := pierwszy_x + 1;
    
    rozne_y := 0;
    for i := 1 to MAX_NUM do
        ile_y[i] := 0;
    for i := py to m do
    begin
        if (rozne_y = ile_znakow) and (ile_y[y[i]] = 0) then
            break;
        if ile_y[y[i]] = 0 then
            rozne_y := rozne_y + 1;
        ile_y[y[i]] := ile_y[y[i]] + 1;
    end;
    pierwszy_y := py;
    while ile_y[y[pierwszy_y]] > 1 do
    begin
        ile_y[y[pierwszy_y]] := ile_y[y[pierwszy_y]] - 1;
        pierwszy_y := pierwszy_y + 1;
    end;
    pierwszy_y := pierwszy_y + 1;
    
    czy_rozne := (rozne_x <> rozne_y);
    for i := 1 to MAX_NUM do
        if (ile_x[i]<>0) <> (ile_y[i]<>0) then
            czy_rozne := true;
    
    licz := (rozne_x = ile_znakow) and (not czy_rozne)
        and get_wynik(px, py, ile_znakow-1) (* f(p(x), p(y)) *)
        and get_wynik(pierwszy_x, pierwszy_y, ile_znakow-1); (* f(s(x), s(y)) *)
end;

var k, i, j, rozne_x, rozne_y, ile_znakow : LongInt;
czy_rozne : Boolean;
begin
    Read(k);
    while k <> 0 do
    begin
        k := k - 1;
        Read(n, m);
        rozne_x := 0;
        rozne_y := 0;
        for i := 1 to MAX_NUM do
        begin
            ile_x[i] := 0;
            ile_y[i] := 0;
        end;
        
        for i := 1 to n do
        begin
            Read(x[i]);
            if ile_x[x[i]] = 0 then
                rozne_x := rozne_x + 1;
            ile_x[x[i]] := ile_x[x[i]] + 1;
        end;
        for i := 1 to m do
        begin
            Read(y[i]);
            if ile_y[y[i]] = 0 then
                rozne_y := rozne_y + 1;
            ile_y[y[i]] := ile_y[y[i]] + 1;
        end;
        
        czy_rozne := (rozne_y <> rozne_x);
        for i := 1 to MAX_NUM do
            if (ile_x[i]<>0) <> (ile_y[i]<>0) then
                czy_rozne := true;
        
        if czy_rozne then
        begin (* W(x) != W(y) *)
            WriteLn('0');
            continue;
        end else if rozne_x = 1 then (* |W(x)| = |W(y)| = 1 *)
        begin
            WriteLn('1');
            continue;
        end;
        
        for i := 1 to n do
            for j := 1 to m do
                set_wynik(i, j, 1, x[i]=y[j]);
        
        for ile_znakow := 2 to rozne_x do
            for i := 1 to n do
                for j := 1 to m do
                    set_wynik(i, j, ile_znakow, licz(i, j, ile_znakow));
        
        if get_wynik(1, 1, rozne_x) then
            WriteLn('1')
        else
            WriteLn('0');
    end;
end.
