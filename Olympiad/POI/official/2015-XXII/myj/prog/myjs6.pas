(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Myjnie                                             *
 *   Zlozonosc czasowa:    O(n^3 * m^3)                                       *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************)


program myj;

type
    Person = record
        fromx, tox, budgetx: longint;
    end;

const
    MAXN = 55;
    MAXM = 4005;

var
    nPoints, nPeople, a, b, c, d: longint;
    dp: array[0..MAXN-1, 0..MAXN-1, 0..MAXM-1] of longint;
    opt: array[0..MAXN-1, 0..MAXN-1, 0..MAXM-1] of longint;
    result: array[0..MAXN-1] of longint;
    people: array[0..MAXM-1] of Person;
    temp: array[0..MAXM-1] of Person;

function CreatePerson(fromx, tox, budgetx: longint): Person;
var
    personResult: Person;
begin
    personResult.fromx := fromx;
    personResult.tox := tox;
    personResult.budgetx := budgetx;
    CreatePerson := personResult;
end;

function ComputeRange(fromx, tox, priceIdx: longint): longint;
var
    i, res: longint;
begin
    res := 0;
    for i := nPeople-1 downto priceIdx do
        if (people[i].fromx >= fromx) and (people[i].tox <= tox) then
            inc(res);
    ComputeRange := res;
end;

function Compute(fromx, tox, priceIdx: longint): longint;
var
    resultValue, optimalMin, posit: longint;
    leftResult, rightResult, peopleCount, possibleResult: longint;
begin
    if (fromx > tox) then Compute := 0
    else if (dp[fromx][tox][priceIdx] <> -1) then Compute := dp[fromx][tox][priceIdx]
    else
    begin
        resultValue := 0;
        optimalMin := fromx;

        for posit := fromx to tox do
        begin
            leftResult := Compute(fromx, posit-1, priceIdx);
            rightResult := Compute(posit+1, tox, priceIdx);
            peopleCount := ComputeRange(fromx, tox, priceIdx);
            if (posit-1 >= fromx) then peopleCount := peopleCount - ComputeRange(fromx, posit-1, priceIdx);
            if (posit+1 <= tox) then peopleCount := peopleCount - ComputeRange(posit+1, tox, priceIdx);
            possibleResult := leftResult + rightResult + peopleCount * people[priceIdx].budgetx;
            if (possibleResult > resultValue) then
            begin
                resultValue := possibleResult;
                optimalMin := posit;
            end;
        end;

        if (priceIdx+1 < nPeople) then
        begin
            possibleResult := Compute(fromx, tox, priceIdx+1);
            if (possibleResult > resultValue) then
            begin
                resultValue := possibleResult;
                optimalMin := -1;
            end;
        end;

        dp[fromx][tox][priceIdx] := resultValue;
        opt[fromx][tox][priceIdx] := optimalMin;

        Compute := resultValue;
    end;
end;

procedure ClaimResult(fromx, tox, priceIdx: longint);
var
    optimalMin: longint;
begin
    if (fromx <= tox) and (priceIdx < nPeople) then
    begin
        if (fromx = tox) and (opt[fromx][tox][priceIdx] = fromx) then
            result[fromx] := priceIdx
        else
        begin
            optimalMin := opt[fromx][tox][priceIdx];
            if (optimalMin = -1) then
                ClaimResult(fromx, tox, priceIdx+1)
            else
            begin
                result[optimalMin] := priceIdx;
                ClaimResult(fromx, optimalMin-1, priceIdx);
                ClaimResult(optimalMin+1, tox, priceIdx);
            end;
        end;
    end;
end;

procedure Merge(fromx, tox, centx: longint);
var
    positLeft, positRight, positRes: longint;
begin
    positLeft := fromx;
    positRight := centx;
    positRes := fromx;
    
    while ((positLeft < centx) and (positRight <= tox)) do
    begin
        if (people[positLeft].budgetx <= people[positRight].budgetx) then
        begin
            temp[positRes] := people[positLeft];
            inc(positLeft);
            inc(positRes);
        end
        else
        begin
            temp[positRes] := people[positRight];
            inc(positRight);
            inc(positRes);
        end;
    end;

    while (positLeft < centx) do
    begin
        temp[positRes] := people[positLeft];
        inc(positLeft);
        inc(positRes);
    end;

    while (positRight <= tox) do
    begin
        temp[positRes] := people[positRight];
        inc(positRight);
        inc(positRes);
    end;

    for positRes := fromx to tox do
        people[positRes] := temp[positRes];
end;

procedure MergeSort(fromx, tox: longint);
var
    centx: longint;
begin
    if (fromx < tox) then
    begin
        centx := (fromx + tox + 1) div 2;
        MergeSort(fromx, centx-1);
        MergeSort(centx, tox);
        Merge(fromx, tox, centx);
    end;
end;

begin
    readln(nPoints, nPeople);

    for a := 0 to nPeople do
    begin
        readln(b, c, d);
        dec(b);
        dec(c);
        people[a] := CreatePerson(b, c, d);
    end;

    MergeSort(0, nPeople-1);

    for a := 0 to nPoints-1 do
        for b := 0 to nPoints-1 do
            for c := 0 to nPeople-1 do
                dp[a][b][c] := -1;

    writeln(Compute(0, nPoints-1, 0));

    ClaimResult(0, nPoints-1, 0);

    for a := 0 to nPoints-1 do
    begin
        if (a > 0) then write(' ');
        write(people[result[a]].budgetx);
    end;
    writeln;
end.
