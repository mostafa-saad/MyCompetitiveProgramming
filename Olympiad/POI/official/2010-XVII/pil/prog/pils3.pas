(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils3.pas                                        *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie powolne - brutalne kwadratowe.       *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *                                                                       *
 *************************************************************************)
const 
    max_n = 3003000; 
var
    a : array[0..max_n] of longint; 
    n, t, i, last_added, res : longint; 

function min(a, b : longint) : longint; 
    begin 
        if a < b then min := a
        else min := b
    end; 

function max(a, b : longint) : longint; 
    begin 
        if a > b then max := a
        else max := b
    end; 
    

function get_diff(st, en : longint) : longint; 
    var mn, mx, i : longint; 
    begin        
        mn := min(a[st], a[en]); 
        mx := max(a[st], a[en]); 
        for i := st + 1 to en - 1 do 
            begin                 
                mn := min(mn, a[i]);
                mx := max(mx, a[i]);
            end;                         
        get_diff := mx - mn; 
    end; 

begin
    readln(t, n);   
    for i := 0 to n - 1 do read(a[i]); 
                   
    last_added := -1; 
    res := 0; 

    for i := 0 to n - 1 do 
        begin
            while (last_added + 1 < n) and (get_diff(i, last_added + 1) <= t) do
                inc(last_added); 
            res := max(res, last_added + 1 - i); 
        end; 
    writeln(res);         
end. 
