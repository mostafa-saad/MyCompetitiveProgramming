/* Baltic Olympiad in Informatics 2015
 * Problem: BOW/Bowling
 * Model solution
 * Author: Karol Pokorski
 */

import java.util.Scanner;

public class bow {
public static void main(String[] args) {
    Scanner input = new Scanner(System.in);

    final int MAXN = 10;
    final int MAXSEQ = 21;
    final int[] maxFrameScore = {0, 10, 30, 60, 90, 120, 150, 180, 210, 240, 300};
    final int MAXSCORE = 300;

    int[] seqScore = new int[MAXN];
    long[][][][] dp = new long[MAXN][MAXSCORE+1][3][2];
    String seqMoves;

    int numQueries = input.nextInt();

    while (numQueries > 0) {
        numQueries--;
        int numFrames = input.nextInt();
        seqMoves = input.next();
        for (int i = 0; i < numFrames; i++)
            seqScore[i] = input.nextInt();

        for (int frame = 0; frame < numFrames; frame++)
            for (int score = 0; score <= MAXSCORE; score++)
                for (int bonus1 = 0; bonus1 <= 2; bonus1++)
                    for (int bonus2 = 0; bonus2 <= 1; bonus2++)
                        dp[frame][score][bonus1][bonus2] = 0;

        dp[0][0][0][0] = 1;

        // first n-1 frames
        for (int frame = 0; frame < numFrames-1; frame++) {
            char firstMove = seqMoves.charAt(2*frame), secondMove = seqMoves.charAt(2*frame+1);
            int prev0Score = seqScore[frame];
            int prev1Score = (frame > 0) ? seqScore[frame-1] : -1;
            int prev2Score = (frame > 1) ? seqScore[frame-2] : -1;

            for (int score = 0; score <= maxFrameScore[frame]; score++)
                for (int bonus1 = 0; bonus1 <= 2; bonus1++)
                    for (int bonus2 = 0; bonus2 <= 1; bonus2++) {
                        if (dp[frame][score][bonus1][bonus2] == 0) continue;

                        for (int move1 = 0; move1 <= 10; move1++) {
                            if ((firstMove >= '0') && (firstMove <= '9') && (move1 != firstMove-'0')) continue;
                            if ((firstMove == 'x') && (move1 != 10)) continue;
                            if ((secondMove == '/') && (move1 == 10)) continue;

                            for (int move2 = 0; move1+move2 <= 10; move2++) {
                                if ((secondMove >= '0') && (secondMove <= '9') && (move2 != secondMove-'0')) continue;
                                if ((secondMove == '/') && (move1+move2 != 10)) continue;
                                if ((secondMove == '-') && (move1 != 10)) continue;
                                if ((move1+move2 == 10) && (secondMove >= '0') && (secondMove <= '9')) continue;

                                int prev1Bonus = 0, prev2Bonus = 0;
                                if (bonus2 == 1) prev1Bonus = move1;
                                if (bonus1 == 1) prev2Bonus = move1;
                                if (bonus1 == 2) prev2Bonus = move1+move2;

                                int nowScore = score + prev1Bonus + prev2Bonus + (move1+move2);
                                int nowPrev1Score = nowScore - (move1+move2);

                                int newBonus1, newBonus2;

                                if (move1 == 10) { newBonus1 = 2; newBonus2 = Math.max(bonus1-1, 0); }
                                else if (move1 + move2 == 10) { newBonus1 = 1; newBonus2 = 0; }
                                else { newBonus1 = 0; newBonus2 = 0; }

                                if (bonus2 == 1) {
                                    int nowPrev2Score = nowPrev1Score - (move1+move2) - 10;
                                    if ((prev2Score != -1) && (nowPrev2Score != prev2Score)) {
                                        continue;
                                    }
                                }
                                if ((bonus1 == 1) || ((bonus1 == 2) && (move1 != 10))) {
                                    if ((prev1Score != -1) && (nowPrev1Score != prev1Score)) {
                                        continue;
                                    }
                                }
                                if (move1+move2 != 10) {
                                    if ((prev0Score != -1) && (nowScore != prev0Score)) {
                                        continue;
                                    }
                                }

                                dp[frame+1][nowScore][newBonus1][newBonus2] =
                                    (dp[frame+1][nowScore][newBonus1][newBonus2] + dp[frame][score][bonus1][bonus2]);
                            }
                        }
                    }
        }

        // last frame
        long result = 0;
        char firstMove = seqMoves.charAt(2*(numFrames-1)), secondMove = seqMoves.charAt(2*(numFrames-1)+1), thirdMove = seqMoves.charAt(2*(numFrames-1)+2);
        int prev0Score = seqScore[numFrames-1];
        int prev1Score = (numFrames > 1) ? seqScore[numFrames-2] : -1;
        int prev2Score = (numFrames > 2) ? seqScore[numFrames-3] : -1;

        for (int score = 0; score <= MAXSCORE; score++)
            for (int bonus1 = 0; bonus1 <= 2; bonus1++)
                for (int bonus2 = 0; bonus2 <= 1; bonus2++) {
                    if (dp[numFrames-1][score][bonus1][bonus2] == 0) continue;

                    for (int move1 = 0; move1 <= 10; move1++) {
                        if ((firstMove >= '0') && (firstMove <= '9') && (move1 != firstMove-'0')) continue;
                        if ((firstMove == 'x') && (move1 != 10)) continue;
                        if ((secondMove == '/') && (move1 == 10)) continue;

                        for (int move2 = 0; move2 <= 10; move2++) {
                            if ((secondMove >= '0') && (secondMove <= '9') && (move2 != secondMove-'0')) continue;
                            if ((secondMove == 'x') && (move2 != 10)) continue;
                            if ((secondMove == '/') && (move1+move2 != 10)) continue;
                            if ((thirdMove == '/') && (move2 == 10)) continue;
                            if ((move1 != 10) && (move1+move2 > 10)) continue;
                            if ((move1+move2 == 10) && (move1 != 10) && (secondMove >= '0') && (secondMove <= '9')) continue;

                            //moje poprawki
                            if ((secondMove == 'x') && (move1 != 10)) continue;
                            //koniec moich poprawek

                            int move3Max = ((move1 == 10) || (move1+move2 == 10)) ? 10 : 0;

                            for (int move3 = 0; move3 <= move3Max; move3++) {
                                if ((thirdMove >= '0') && (thirdMove <= '9') && (move3 != thirdMove-'0')) continue;
                                if ((thirdMove == 'x') && (move3 != 10)) continue;
                                if ((thirdMove == '/') && (move2+move3 != 10)) continue;
                                if ((move2 != 10) && (move1+move2 != 10) && (move2+move3 > 10)) continue;
                                if ((thirdMove == '-') && (move1+move2 >= 10)) continue;
                                if ((thirdMove == '/') && (move1+move2 == 10) && (move1 != 10)) continue;
                                //moje poprawki
                                if (thirdMove == 'x') {
                                    if(move2 != 10 &&  ((move1 == 10 && move2 == 0) || (move1 + move2 < 10))) {
                                        continue;
                                    }
                                }
                                if ((thirdMove == '0') && move1 + move2 < 10) continue;

                                //ta linijka musi byc inaczej v, ale musi byc
                                if ((move1 == 10 || move1 + move2 != 10)&&(move2 != 10) &&(move2+move3 == 10) && (thirdMove >= '0') && (thirdMove <= '9')) continue;
                                //koniec moich poprawek

                                int prev1Bonus = 0, prev2Bonus = 0;
                                if (bonus2 == 1) prev1Bonus = move1;
                                if (bonus1 == 1) prev2Bonus = move1;
                                if (bonus1 == 2) prev2Bonus = move1+move2;

                                int nowScore = score + prev1Bonus + prev2Bonus + (move1+move2+move3);
                                int nowPrev1Score = nowScore - (move1+move2+move3);

                                if (bonus2 == 1) {
                                    int nowPrev2Score = nowPrev1Score - (move1+move2) - 10;
                                    if ((prev2Score != -1) && (nowPrev2Score != prev2Score)) {
                                        continue;
                                    }
                                }
                                if (bonus1 >= 1) {
                                    if ((prev1Score != -1) && (nowPrev1Score != prev1Score)) {
                                        continue;
                                    }
                                }
                                {
                                    if ((prev0Score != -1) && (nowScore != prev0Score)) {
                                        continue;
                                    }
                                }

                                result = (result + dp[numFrames-1][score][bonus1][bonus2]);
                            }
                        }
                    }
                }

        System.out.println(result);
    }

}
}
