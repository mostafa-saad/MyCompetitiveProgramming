(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pil2.pas                                         *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************)

type 
    pair = record
                FI, SE : longint; 
            end;                 
const 
    max_n = 3003000; 
var
    a : array[0..max_n] of longint; 
    q : array[0..1, 0..max_n] of pair; 
    head, tail : array[0..1] of longint; 
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
   
procedure pop_front(a, pos:longint); 
    begin 
        if q[a][head[a]].SE = pos then 
            inc(head[a]); 
    end; 

procedure add_elem(a, val, pos:longint); 
    begin 
        while (head[a] <> tail[a]) and (q[a][tail[a] - 1].FI > val) do 
            dec(tail[a]); 
         with q[a][tail[a]] do begin
            FI := val; 
            SE := pos; 
         end; 
         inc(tail[a]); 
    end; 

function get_min(a:longint):longint; 
    begin 
        get_min := q[a][head[a]].FI; 
    end;     
            
begin
    head[0] := 0; head[1] := 0; 
    tail[0] := 0; tail[1] := 0; 

    readln(t, n);   
    for i := 0 to n - 1 do read(a[i]); 
    a[n] := a[n - 1] - t; 
                   
    last_added := -1; 
    res := 0; 

    for i := 0 to n - 1 do 
        begin
            if i = last_added + 1 then 
                begin 
                    add_elem(0, a[i], i); 
                    add_elem(1, -a[i], i); 
                    inc(last_added); 
                end;                     

            while (last_added < n) and (-get_min(1) - get_min(0) <= t) do
                begin
                    inc(last_added); 
                    add_elem(0, a[last_added], last_added); 
                    add_elem(1, -a[last_added], last_added); 
                end; 
            res := max(res, last_added - i); 
            pop_front(0, i);  pop_front(1, i); 
        end; 
    writeln(res);         
end. 
