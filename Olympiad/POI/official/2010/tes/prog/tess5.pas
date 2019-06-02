(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tess5.pas                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie powolne.                             *
 *   Złożoność czasowa: O(m * n + l)                                     *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************)

const
    MAX_M = 1000000; // maksymalna długość ciągu a_i
    MAX_A = 1000000; // maksymalny wyraz ciągu

var
    m, n, k, ia, i, j : longint;
    a, b : array [0..MAX_M - 1] of longint;
    cou : array [0..MAX_A - 1, 0..1] of longint;
    ok : boolean;

begin

    for i := 0 to MAX_A - 1 do
        for j := 0 to 1 do
            cou[i][j] := 0;

    readln(m);
    for i := 0 to m - 1 do
    begin
        read(a[i]);
        inc(cou[a[i] - 1][0]);
    end;
    readln;

    readln(n);
    for i := 0 to n - 1 do
    begin
        readln(k);
        ok := true;
        ia := 0;
        for j := 0 to k - 1 do
        begin
            read(b[j]);
            inc(cou[b[j] - 1][1]);
            if cou[b[j] - 1][0] < cou[b[j] - 1][1] then
                ok := false;
        end;
        for j := 0 to k - 1 do
        begin
            if not ok then
                break;
            while (ia < m) and (a[ia] <> b[j]) do
                inc(ia);
            if (ia = m) or (a[ia] <> b[j]) then
                ok := false;
            inc(ia);
        end;
        readln;
        for j := 0 to k - 1 do
            cou[b[j] - 1][1] := 0;

        if ok then
            writeln('TAK')
        else
            writeln('NIE');
    end;
end.
