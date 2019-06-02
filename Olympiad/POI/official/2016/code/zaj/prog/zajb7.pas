(******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie nieefektywne uzywajace O(n1*n2)        *
 *                         pamieci.                                           *
 *****************************************************************************)


program Zajakniecia;

const max_n = 2003;

var
    n1, n2, i, j : longint;
    A, B, prevA, prevB : array [0..max_n] of longint;
    dp : array [0..max_n, 0..max_n] of longint;

begin
    Read(n1);
    Read(n2);
	for i := 1 to n1 do
		Read(A[i]);
    for i := 1 to n2 do
        Read(B[i]);

    for i := 1 to n1 do
    begin
        for j := i-1 downto 1 do
        begin
            if A[j] = A[i] then
            begin
                prevA[i] := j;
                break;
            end;
        end;
    end;

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
        dp[0][i] := 0;

    for i := 1 to n1 do
    begin
        for j := 1 to n2 do
            dp[i][j] := 0;

        for j := 1 to n2 do
        begin
            if dp[i][j-1] > dp[i-1][j] then
                dp[i][j] := dp[i][j-1]
            else
                dp[i][j] := dp[i-1][j];

            if (A[i] = B[j]) and (prevA[i] <> 0) and (prevB[j] <> 0) then
            begin
                if dp[ prevA[i] - 1 ][ prevB[j] - 1 ] + 2 > dp[i][j] then
                    dp[i][j] := dp[ prevA[i] - 1 ][ prevB[j] - 1 ] + 2;
            end;
        end;
    end;

    Writeln(dp[n1][n2]);
end.
