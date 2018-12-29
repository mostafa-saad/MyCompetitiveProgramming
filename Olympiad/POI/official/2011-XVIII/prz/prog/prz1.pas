(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Przekladanka                                     *
 *   Autor:             Jacek Migdal                                     *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)


Program prz;

const
    MAXN = 2000;
    MAXN2 = 4000000;

var
    answer: array[0..MAXN2] of LongInt;
    answerN: LongInt;
    data: array[0..MAXN] of LongInt;
    dataN: LongInt;
    beginI: LongInt;
    i{, was}: LongInt;
    nonZeroAns: LongInt;

procedure addAnswer(num: LongInt);
begin
    if ((answerN > 0) and ((answer[answerN - 1] * num) > 0))
        then begin
            answer[answerN - 1] := answer[answerN - 1] + num;
        end else begin
            answer[answerN] := num;
            answerN := answerN + 1;
    end;
end;

procedure operationPlus;
begin
    beginI := beginI - 1;
    if (beginI < 0) then
        beginI := dataN + beginI;
    addAnswer(1);
end;

procedure operationPlus2;
begin
    beginI := beginI + 1;
    if (beginI >= dataN) then
        beginI := beginI - dataN;
    addAnswer(dataN - 1);
end;

procedure operationMinus;
var
    next0, next1 : LongInt;
    tmp : LongInt;
begin
    next0 := (beginI + 1) mod dataN;
    next1 := (beginI + 2) mod dataN;
    tmp := data[beginI];
    data[beginI] := data[next1];
    data[next1] := data[next0];
    data[next0] := tmp;
    addAnswer(-1);
end;

begin
    answerN := 0;
    beginI := 0;
    ReadLn(dataN);
    for i := 0 to (dataN-1) do
        Read(data[i]);

    if (dataN <= 2) then begin
        if ((dataN = 1) or (1 = data[0])) then
            WriteLn('0')
        else begin
            WriteLn('1');
            WriteLn('1a');
            end;
        exit;
    end;

    for i := 2 to (dataN - 2) do begin
        while (data[beginI] <> i) do
            operationPlus;

        while not (data[(beginI - 1 + dataN) mod dataN] = (i - 1)) do begin
            operationPlus;
            if not (data[(beginI - 1 + dataN) mod dataN] = (i - 1)) then begin
                operationPlus;
                operationMinus;
            end else begin
                operationMinus;
                operationMinus;
            end;
         end;
    end;

    while (data[beginI] <> 1) do
        operationPlus;

    if (data[(beginI - 1 + dataN) mod dataN] <> dataN) then begin
        if ((dataN mod 2) = 1) then begin
            WriteLn('NIE DA SIE');
            exit;
        end else begin
            operationPlus;

            while (data[(beginI + 1) mod dataN] <> dataN) do begin
                operationMinus;
                operationMinus;
                operationPlus2;
                operationPlus2;
            end;
            for i := 0 to (dataN - 3) do
                operationPlus();
        end;
    end;

    nonZeroAns := 0;
    for i := 0 to (answerN - 1) do
        if (abs(answer[i]) mod dataN <> 0) then inc(nonZeroAns);
    Writeln(nonZeroAns); 
    
    for i := 0 to (answerN - 1) do begin
        if (abs(answer[i]) mod dataN <> 0) then begin
            if (answer[i] < 0) then
                Write(abs(answer[i]) mod dataN, 'b ')
            else
                Write(abs(answer[i]) mod dataN, 'a ');
        end;
    end;

    WriteLn;
end.
