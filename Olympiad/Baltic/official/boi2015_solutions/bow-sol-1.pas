{ Baltic Olympiad in Informatics 2015
  Problem: BOW/Bowling
  Model solution
  Author: Karol Pokorski
}

const
    MAXN = 10;
    MAXSEQ = 21;
    MAXSCORE = 300;
var
    seqScore: array[0..MAXN-1] of longint;
    maxFrameScore: array[0..MAXN] of longint;
    dp: array[0..MAXN-1, 0..MAXSCORE, 0..2, 0..1] of int64;
    seqMoves: string;
    numQueries, numFrames, query, i: longint;
    frame, score, bonus1, bonus2, move1, move2, move3: longint;
    result: int64;
    firstMove, secondMove, thirdMove: char;
    newBonus1, newBonus2: longint;
    prev0Score, prev1Score, prev2Score: longint;
    move3Max, prev1Bonus, prev2Bonus, nowScore, nowPrev1Score, nowPrev2Score: longint;

function max(a, b: longint): longint;
begin
    if a > b then max := a else max := b;
end;

begin
    maxFrameScore[0] := 0;
    maxFrameScore[1] := 10;
    for i := 2 to 9 do
        maxFrameScore[i] := 30*(i-1);
    maxFrameScore[10] := 300;

    readln(numQueries);

    for query := 0 to numQueries-1 do
    begin
        readln(numFrames);
        readln(seqMoves);
        for i := 0 to numFrames-1 do
            read(seqScore[i]);

        for frame := 0 to numFrames-1 do
            for score := 0 to MAXSCORE do
                for bonus1 := 0 to 2 do
                    for bonus2 := 0 to 1 do
                        dp[frame][score][bonus1][bonus2] := 0;

        dp[0][0][0][0] := 1;

        { first n-1 frames }

        for frame := 0 to numFrames-2 do
        begin
            firstMove := seqMoves[2*frame+1];
            secondMove := seqMoves[2*frame+2];
            prev0Score := seqScore[frame];
            if (frame > 0) then prev1Score := seqScore[frame-1] else prev1Score := -1;
            if (frame > 1) then prev2Score := seqScore[frame-2] else prev2Score := -1;

            for score := 0 to maxFrameScore[frame] do
                for bonus1 := 0 to 2 do
                    for bonus2 := 0 to 1 do
                    begin
                        if dp[frame][score][bonus1][bonus2] = 0 then continue;

                        for move1 := 0 to 10 do
                        begin
                            if (firstMove >= '0') and (firstMove <= '9') and (move1 <> ord(firstMove)-ord('0')) then continue;
                            if (firstMove = 'x') and (move1 <> 10) then continue;
                            if (secondMove = '/') and (move1 = 10) then continue;

                            for move2 := 0 to 10-move1 do
                            begin
                                if (secondMove >= '0') and (secondMove <= '9') and (move2 <> ord(secondMove)-ord('0')) then continue;
                                if (secondMove = '/') and (move1+move2 <> 10) then continue;
                                if (secondMove = '-') and (move1 <> 10) then continue;
                                if (move1+move2 = 10) and (secondMove >= '0') and (secondMove <= '9') then continue;

                                prev1Bonus := 0;
                                prev2Bonus := 0;
                                if (bonus2 = 1) then prev1Bonus := move1;
                                if (bonus1 = 1) then prev2Bonus := move1;
                                if (bonus1 = 2) then prev2Bonus := move1+move2;

                                nowScore := score + prev1Bonus + prev2Bonus + (move1 + move2);
                                nowPrev1Score := nowScore - (move1 + move2);

                                if move1 = 10 then begin newBonus1 := 2; newBonus2 := max(bonus1-1, 0) end
                                else if move1 + move2 = 10 then begin newBonus1 := 1; newBonus2 := 0 end
                                else begin newBonus1 := 0; newBonus2 := 0; end;

                                if bonus2 = 1 then
                                begin
                                    nowPrev2Score := nowPrev1Score - (move1+move2) - 10;
                                    if (prev2Score <> -1) and (nowPrev2Score <> prev2Score) then continue;
                                end;
                                if (bonus1 = 1) or ((bonus1 = 2) and (move1 <> 10)) then
                                begin
                                    if (prev1Score <> -1) and (nowPrev1Score <> prev1Score) then continue;
                                end;
                                if (move1+move2 <> 10) then
                                begin
                                    if (prev0Score <> -1) and (nowScore <> prev0Score) then continue;
                                end;

                                dp[frame+1][nowScore][newBonus1][newBonus2] :=
                                    (dp[frame+1][nowScore][newBonus1][newBonus2] + dp[frame][score][bonus1][bonus2]);
                            end;
                        end;
                    end;
        end;

        { last frame }
        result := 0;
        firstMove := seqMoves[2*(numFrames-1)+1];
        secondMove := seqMoves[2*(numFrames-1)+2];
        thirdMove := seqMoves[2*(numFrames-1)+3];
        prev0Score := seqScore[numFrames-1];
        prev1Score := -1;
        if (numFrames > 1) then prev1Score := seqScore[numFrames-2];
        prev2Score := -1;
        if (numFrames > 2) then prev2Score := seqScore[numFrames-3];

        for score := 0 to MAXSCORE do
            for bonus1 := 0 to 2 do
                for bonus2 := 0 to 1 do
                begin
                    if (dp[numFrames-1][score][bonus1][bonus2] = 0) then continue;

                    for move1 := 0 to 10 do
                    begin
                        if (firstMove >= '0') and (firstMove <= '9') and (move1 <> ord(firstMove)-ord('0')) then continue;
                        if (firstMove = 'x') and (move1 <> 10) then continue;
                        if (secondMove = '/') and (move1 = 10) then continue;

                        for move2 := 0 to 10 do
                        begin
                            if (secondMove >= '0') and (secondMove <= '9') and (move2 <> ord(secondMove)-ord('0')) then continue;
                            if (secondMove = 'x') and (move2 <> 10) then continue;
                            if (secondMove = '/') and (move1+move2 <> 10) then continue;
                            if (thirdMove = '/') and (move2 = 10) then continue;
                            if (move1 <> 10) and (move1+move2 > 10) then continue;
                            if (move1+move2 = 10) and (move1 <> 10) and (secondMove >= '0') and (secondMove <= '9') then continue;

                            (* moje poprawki *)
                            if ((secondMove = 'x') and (move1 <> 10)) then continue;
                            (* koniec moich poprawek *)

                            move3Max := 0;
                            if (move1 = 10) or (move1+move2 = 10) then move3Max := 10;

                            for move3 := 0 to move3Max do
                            begin
                                if (thirdMove >= '0') and (thirdMove <= '9') and (move3 <> ord(thirdMove)-ord('0')) then continue;
                                if (thirdMove = 'x') and (move3 <> 10) then continue;
                                if (thirdMove = '/') and (move2+move3 <> 10) then continue;
                                if (move2 <> 10) and (move1+move2 <> 10) and (move2+move3 > 10) then continue;
                                if (thirdMove = '-') and (move1+move2 >= 10) then continue;
                                (* usuwam, bo zle *)
                                (* if (move2+move3 = 10) and (thirdMove >= '0') and (thirdMove <= '9') then continue; *)
                                if (thirdMove = '/') and (move1+move2 = 10) and (move1 <> 10) then continue;

                                (* moje poprawki *)
                                if (thirdMove = 'x') then begin
                                    if((move2 <> 10) and  (((move1 = 10) and (move2 = 0)) or (move1 + move2 < 10))) then continue;
                                end;
                                if ((thirdMove = '0') and (move1 + move2 < 10)) then continue;

                                if (((move1 = 10) or (move1 + move2 <> 10))and(move2 <> 10) and (move2+move3 = 10) and (thirdMove >= '0') and (thirdMove <= '9'))then continue;
                                (* koniec moich poprawek *)

                                prev1Bonus := 0;
                                prev2Bonus := 0;
                                if (bonus2 = 1) then prev1Bonus := move1;
                                if (bonus1 = 1) then prev2Bonus := move1;
                                if (bonus1 = 2) then prev2Bonus := move1+move2;

                                nowScore := score + prev1Bonus + prev2Bonus + (move1+move2+move3);
                                nowPrev1Score := nowScore - (move1+move2+move3);

                                if (bonus2 = 1) then begin
                                    nowPrev2Score := nowPrev1Score - (move1+move2) - 10;
                                    if (prev2Score <> -1) and (nowPrev2Score <> prev2Score) then continue;
                                end;
                                if (bonus1 >= 1) then begin
                                    if (prev1Score <> -1) and (nowPrev1Score <> prev1Score) then continue;
                                end;
                                begin
                                    if (prev0Score <> -1) and (nowScore <> prev0Score) then continue;
                                end;

                                result := (result + dp[numFrames-1][score][bonus1][bonus2]);
                            end;
                        end;
                    end;
                end;

        writeln(result);
    end;
end.
