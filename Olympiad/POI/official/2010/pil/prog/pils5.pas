(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils5.pas                                        *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Drzewo przdziałowe, zoptymalizowane pamieciowo.  *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************)
const 
    max_n = 3003000; 
    max_pow = (1 shl 22); 
var
    a : array[0..max_n] of longint; 
    t_max, t_min : array[0..max_pow] of longint; 
    n, m, t, i, last_added, res : longint; 

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
    var mn, mx : longint; 
    begin
        mn := min(a[st], a[en]); 
        mx := max(a[st], a[en]); 
        if st < en then 
            begin 
                mn := min(mn, min(a[st + 1], a[en - 1])); 
                mx := max(mx, max(a[st + 1], a[en - 1])); 
            end;             

        st := st + m; st := st shr 1; 
        en := en + m; en := en shr 1; 
        while (st shr 1) <> (en shr 1) do 
            begin
                if (st and 1) = 0 then 
                    begin
                        mn := min(mn, t_min[st + 1]);
                        mx := max(mx, t_max[st + 1]);
                    end;                         
                if (en and 1) = 1 then
                    begin
                        mn := min(mn, t_min[en - 1]);
                        mx := max(mx, t_max[en - 1]);
                    end; 
                st := st shr 1; 
                en := en shr 1; 
            end;        
        get_diff := mx - mn; 
    end; 

function f(p:longint) : longint; 
    begin 
        if (p >= n) then f := n - 1 
        else f := p; 
    end;         

begin
    readln(t, n);   
    for i := 0 to n - 1 do read(a[i]); 
    m := 1; 
    while m < n do m := m * 2; 

    for i := m - 1 downto 1 do 
        if i * 2 < m then 
            begin 
                t_max[i] := max(t_max[2 * i], t_max[2 * i + 1]);
                t_min[i] := min(t_min[2 * i], t_min[2 * i + 1]);
            end 
        else 
            begin 
                t_max[i] := max(a[f(2 * i - m)], a[f(2 * i + 1 - m)]); 
                t_min[i] := min(a[f(2 * i - m)], a[f(2 * i + 1 - m)]); 
            end;                 
                    
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
