(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Maciej Andrejczuk                                *
 *   Zlozonosc czasowa: O(n * (MAXX - MINX))                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

program tem;

const MAXX = 50;
const MINX = -50;

var
    t : array[0..1, MINX..MAXX] of longint;
    n, ret, i, j, curr, prev, a, b : longint;

begin
    readln(n);
    ret := 0;
    for i := 0 to n - 1 do
    begin
        readln(a, b);
        curr := i mod 2;
        prev := 1 - curr;
        for j := MINX to a - 1 do
            t[curr][j] := 0;
        for j := a to b do
        begin
            t[curr][j] := 1;
            if (j > MINX) and (t[curr][j - 1] > t[curr][j]) then
                t[curr][j] := t[curr][j - 1];
            if t[prev][j] + 1 > t[curr][j] then
                t[curr][j] := t[prev][j] + 1;
        end;
        for j := b + 1 to MAXX do
            t[curr][j] := t[curr][j - 1];
        if t[curr][MAXX] > ret then
            ret := t[curr][MAXX];
    end;
    writeln(ret);
end.
