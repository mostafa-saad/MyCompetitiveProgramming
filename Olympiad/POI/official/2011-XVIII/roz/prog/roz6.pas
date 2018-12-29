(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
 MAX_L = 26;
 MAX_N = 1000023;
 INF = 1000000123;

var
 i, smaller, bigger, count, n, returnAnswer, v_tail : longint;
 wasSmaller, check:array[0..MAX_L] of boolean;
 current, prevBigger:array[0..MAX_L] of longint;
 v1, v2: array[0..MAX_N] of longint;
 pop, x: char;


begin
readln(n);
returnAnswer := 0;
v_tail := 0;

count := 1;
read(pop);
for i := 1 to n - 1 do
    begin
    read(x);
    if (x <> pop) then
        begin
        v1[v_tail] := byte(pop) - 97;
        v2[v_tail] := count;
        inc(v_tail);
        check[byte(pop) - 97] := true;
        pop := x;
        count := 1;
        end else 
            begin
            inc(count);
            end;
    end;
    v1[v_tail] := byte(pop) - 97;
    v2[v_tail] := count;
    check[byte(pop) - 97] := true;
    inc(v_tail);

    for bigger := 0 to MAX_L - 1 do
        if (check[bigger]) then
            begin
            for i:=0 to MAX_L - 1 do
                begin
                prevBigger[i] := 0;
                current[i] := 0;
                wasSmaller[i] := false;
                end;
            for i:=0 to v_tail - 1 do
                if (v1[i] = bigger) then 
                    begin
                    for smaller:=0 to MAX_L - 1 do
                        if (check[smaller]) and (smaller <> bigger) then
                            begin
                            prevBigger[smaller] := prevBigger[smaller] + v2[i];
                            if (wasSmaller[smaller]) then
                                begin
                                current[smaller] := current[smaller] + v2[i];
                                if (current[smaller] > returnAnswer) then returnAnswer := current[smaller];
                                end;
                            end;
                     end else
                         begin 
                         if (current[v1[i]] = 0) then
                            begin
                            dec(current[v1[i]]);
                            end else 
                                begin
                                current[v1[i]] := current[v1[i]] - v2[i];
                                end;
                        wasSmaller[v1[i]] := true;
                        if (prevBigger[v1[i]] - v2[i] > current[v1[i]]) then
                            begin
                            current[v1[i]] := prevBigger[v1[i]] - v2[i];
                            end;
                        if (current[v1[i]] > returnAnswer) then returnAnswer := current[v1[i]];
                        prevBigger[v1[i]] := 0;
                        end;
            end;
    writeln(returnAnswer);
end.

