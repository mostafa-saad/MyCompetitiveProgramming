(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs2.pas                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie wykladnicze z mala optymalizacja              *
 *                                                                       *
 *                                                                       *
 *************************************************************************)

const MAX_N = 100000;
const MAX_NUM = 100;

var x, y : array [1..MAX_N] of LongInt;
var ile_x, ile_y : array [1..MAX_NUM] of LongInt;

function f(px, kx, py, ky : LongInt) : Boolean;
var rozne_x, rozne_y, ostatni_x, ostatni_y, i, pierwszy_x, pierwszy_y : LongInt;
    czy_rozne : Boolean;
begin
    for i := 1 to MAX_NUM do
    begin
        ile_x[i] := 0;
        ile_y[i] := 0;
    end;
    rozne_x := 0;
    rozne_y := 0;
    ostatni_x := 1;
    ostatni_y := 1;
    for i := px to kx do
    begin
        if ile_x[x[i]] = 0 then
        begin
            rozne_x := rozne_x + 1;
            ostatni_x := i;
        end;
        ile_x[x[i]] := ile_x[x[i]] + 1;
    end;
    for i := py to ky do
    begin
        if ile_y[y[i]] = 0 then
        begin
            rozne_y := rozne_y + 1;
            ostatni_y := i;
        end;
        ile_y[y[i]] := ile_y[y[i]] + 1;
    end;
    
    czy_rozne := (rozne_x <> rozne_y);
    for i := 1 to MAX_NUM do
        if (ile_x[i]<>0) <> (ile_y[i]<>0) then
            czy_rozne := true;
    
    if czy_rozne then
        f := false
    else if rozne_x = 1 then
        f := true
    else
    begin
        pierwszy_x := px;
        pierwszy_y := py;
        while ile_x[x[pierwszy_x]] > 1 do
        begin
            ile_x[x[pierwszy_x]] := ile_x[x[pierwszy_x]] - 1;
            pierwszy_x := pierwszy_x + 1;
        end;
        while ile_y[y[pierwszy_y]] > 1 do
        begin
            ile_y[y[pierwszy_y]] := ile_y[y[pierwszy_y]] - 1;
            pierwszy_y := pierwszy_y + 1;
        end;
        
        f := f(px, ostatni_x-1, py, ostatni_y-1) and f(pierwszy_x+1, kx, pierwszy_y+1, ky);
    end;
end;

var n, m, k, i : LongInt;
begin
    Read(k);
    while k<>0 do
    begin
        k := k - 1;
        Read(n, m);
        for i := 1 to n do
            Read(x[i]);
        for i := 1 to m do
            Read(y[i]);
        if f(1, n, 1, m) then
            WriteLn('1')
        else
            WriteLn('0');
    end;
end.
