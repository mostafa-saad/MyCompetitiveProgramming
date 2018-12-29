(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie alternatywne                           *
 *                                                                            *
 *****************************************************************************)

const
    MAXN = 2000005;

var
    T: array[0..MAXN-1] of longint;
    sd: array[0..MAXN-1] of int64;
    dequeFirst: array[0..MAXN-1] of int64;
    dequeSecond: array[0..MAXN-1] of longint;
    n, d, left, right, result, i, dequeStart, dequeEnd: longint;
    p, maxSum, curSum: int64;

begin
    readln(n, p, d);
    for i := 0 to n-1 do
        read(T[i]);

    curSum := 0;
    for i := 0 to n-1 do
    begin
        if (i >= d) then dec(curSum, T[i-d]);
        inc(curSum, T[i]);
        dequeFirst[i] := -1;
        dequeSecond[i] := -1;
        sd[i] := curSum;
    end;

    right := -1; result := 0;
    maxSum := 0;
    curSum := 0;
    dequeStart := 0; dequeEnd := -1;
    for left := 0 to n-1 do
    begin
        if (dequeStart <= dequeEnd) and (dequeSecond[dequeStart] < left) then
            inc(dequeStart);

        while (true) do
        begin
            if (right = n-1) then
                break;
            if (curSum + T[right+1] - maxSum > p) and (curSum + T[right+1] - sd[right+1] > p) then
                break;

            inc(right);
            inc(curSum, T[right]);
            while (dequeStart <= dequeEnd) and (dequeFirst[dequeEnd] < sd[right]) do
                dec(dequeEnd);
            inc(dequeEnd);
            dequeFirst[dequeEnd] := sd[right];
            dequeSecond[dequeEnd] := right-d;
            maxSum := dequeFirst[dequeStart];
        end;

        if (right-left+1 > result) then result := right-left+1;
        dec(curSum, T[left]);
    end;

    writeln(result);
end.
