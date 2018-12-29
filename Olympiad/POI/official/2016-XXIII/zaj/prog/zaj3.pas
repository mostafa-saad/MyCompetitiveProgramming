(******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Zlozonosc czasowa:    O(n1*n2)                                           *
 *   Opis:                 wzorcowe                                           *
 *****************************************************************************)


program Zajakniecia;

const max_n = 15003;

var
    n1, n2, e, f, tmp, i, j : longint;
    A, B, prevB, memo : array [0..max_n] of longint;
    dp : array [0..1, 0..max_n] of longint;

begin
    Read(n1);
    Read(n2);
    for i := 1 to n1 do
        Read(A[i]);
    for i := 1 to n2 do
        Read(B[i]);

    for i := 1 to n2 do
    begin
        for j := i-1 downto 1 do
        begin
            if B[j] = B[i] then
            begin
                prevB[i] := j;
                break;
            end;
        end;
    end;

    for i := 0 to n2 do
    begin
        dp[0][i] := 0;
        dp[1][i] := 0;
    end;

    for i := 0 to n2 do
        memo[i] := -2;

    e := 0; f := 1;
    for i := 1 to n1 do
    begin
        for j := 1 to n2 do
        begin
            if dp[f][j-1] > dp[e][j] then
                dp[f][j] := dp[f][j-1]
            else
                dp[f][j] := dp[e][j];

            if (A[i] = B[j]) and (memo[ prevB[j] ] + 2 > dp[f][j]) then
                dp[f][j] := memo[ prevB[j] ] + 2;
        end;

        for j := 1 to n2 do
        begin
            if A[i] = B[j] then
                memo[j] := dp[e][j-1];
        end;

        tmp := e;
        e := f;
        f := tmp;
    end;

    Writeln(dp[e][n2]);
end.
