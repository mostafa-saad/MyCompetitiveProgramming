{ Baltic Olympiad in Informatics 2015
  Problem: BOW/Bowling
  Very slow solution (should pass only first subtask)
  Author: Karol Pokorski
  }

const
    MAXN = 10;
    MAXSEQ = 21;
var
    numFrames, i, numQueries, query: longint;
    result: int64;
    seqScore, mySeqScore: array[0..MAXN-1] of longint;
    seqMovesR: string;
    seqMoves, mySeqMoves: array[0..MAXSEQ] of char;
    move1, move2, move3 : longint;
    secondMove, thirdMove : char;

function Value(posit: longint): longint;
begin
    if (mySeqMoves[posit] >= '0') and (mySeqMoves[posit] <= '9') then Value := ord(mySeqMoves[posit])-ord('0')
else if (mySeqMoves[posit] = 'x') or (mySeqMoves[posit] = ':') then Value := 10
    else if (mySeqMoves[posit] = '/') then Value := 10-Value(posit-1)
else Value := 0;
end;

function Check(): boolean;
var
    i, score, nextMove, nextNextMove: longint;
begin
    for i := 0 to numFrames-2 do if (Value(2*i) + Value(2*i+1) > 10) then exit(false);
    for i := 0 to numFrames-2 do if (Value(2*i) = 10) and (mySeqMoves[2*i+1] = '/') then exit(false);
    for i := 0 to numFrames-2 do if (Value(2*i) + Value(2*i+1) = 10) and (seqMoves[2*i+1] >= '0') and (seqMoves[2*i+1] <= '9') then exit(false);
    if (Value(2*numFrames-2) <> 10) and (Value(2*numFrames-2) + Value(2*numFrames-1) > 10) then exit(false);
    if (Value(2*numFrames-2) + Value(2*numFrames-1) < 10) and (Value(2*numFrames) > 0) then exit(false);
    if (Value(2*numFrames-2) = 10) and (Value(2*numFrames-1) < 10) and (Value(2*numFrames-1) + Value(2*numFrames) > 10) then exit(false);
    if (Value(2*numFrames-2) = 10) and (mySeqMoves[2*numFrames-1] = '/') then exit(false);
    if ((Value(2*numFrames-2) <> 10) or (Value(2*numFrames-1) = 10)) and (mySeqMoves[2*numFrames] = '/') then exit(false);
    if (seqMoves[2*numFrames] = '-') and (Value(2*numFrames-2) + Value(2*numFrames-1) >= 10) then exit(false);
    if (Value(2*numFrames-2) + Value(2*numFrames-1) = 10) and (Value(2*numFrames-2) <> 10) and (seqMoves[2*numFrames-1] >= '0') and (seqMoves[2*numFrames-1] <= '9') then exit(false);


    {zla linijka}
    {if ((Value(2*numFrames-1) + Value(2*numFrames) == 10) && (seqMoves[2*numFrames] >= '0') && (seqMoves[2*numFrames] <= '9')) return false;}


    secondMove := seqMoves[2 * numFrames - 1];
    thirdMove := seqMoves[2 * numFrames];

    move1 := Value(2 * numFrames - 2);
    move2 := Value(2 * numFrames - 1);
    move3 := Value(2 * numFrames);
    {moje poprawki}
    if ((secondMove = 'x') and (move1 <> 10)) then exit (false);
    {koniec moich poprawek}

    (* moje poprawki *)
    if (thirdMove = 'x') then begin
        if((move2 <> 10) and  (((move1 = 10) and (move2 = 0)) or (move1 + move2 < 10))) then exit(false);
    end;
    if ((thirdMove = '0') and (move1 + move2 < 10)) then exit(false);

    if (((move1 = 10) or (move1 + move2 <> 10))and(move2 <> 10) and (move2+move3 = 10) and (thirdMove >= '0') and (thirdMove <= '9'))then exit(false);
    (* koniec moich poprawek *)

    score := 0;
    for i := 0 to numFrames-2 do
    begin
        if (Value(2*i) = 10) then
        begin
            nextMove := Value(2*i+2);
            nextNextMove := Value(2*i+4);
            if (nextMove < 10) or (i = numFrames-2) then nextNextMove := Value(2*i+3);
            inc(score, nextMove + nextNextMove);
        end
        else if (Value(2*i) + Value(2*i+1) = 10) then
        begin
            nextMove := Value(2*i+2);
            inc(score, nextMove);
        end;
        inc(score, Value(2*i) + Value(2*i+1));
        mySeqScore[i] := score;
    end;
    inc(score, Value(2*numFrames-2) + Value(2*numFrames-1) + Value(2*numFrames));
    mySeqScore[numFrames-1] := score;

    for i := 0 to numFrames-1 do if (seqScore[i] <> -1) and (mySeqScore[i] <> seqScore[i]) then exit(false);

    exit(true);
end;

procedure Go(posit: longint);
var
    i: longint;
begin
    if (posit = 2*numFrames+1) then
    begin
        if (Check()) then inc(result);
        exit;
    end;
    if (seqMoves[posit] = '?') then
    begin
        for i := 0 to 10 do
        begin
            mySeqMoves[posit] := chr(i+ord('0'));
            Go(posit+1);
        end;
    end
    else
    begin
        mySeqMoves[posit] := seqMoves[posit];
        Go(posit+1);
    end;
end;

begin
    for i := 0 to MAXSEQ do mySeqMoves += ' ';

    readln(numQueries);
    for query := 0 to numQueries-1 do
    begin
        readln(numFrames);
        readln(seqMovesR);
        for i := 0 to 2*numFrames+1 do
            seqMoves[i] := seqMovesR[i+1];
        for i := 0 to numFrames-1 do
            read(seqScore[i]);

        for i := 0 to numFrames-1 do
            if (seqMoves[2*i+1] = '-') then seqMoves[2*i] := 'x';

        result := 0;
        Go(0);
        writeln(result);
    end;
end.
