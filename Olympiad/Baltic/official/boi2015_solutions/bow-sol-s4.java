/* Baltic Olympiad in Informatics 2015
 * Problem: BOW/Bowling
 * Very slow solution (should pass only first subtask)
 * Author: Karol Pokorski
 */

import java.util.Scanner;

public class bow {

static int[] seqScore, mySeqScore;
static char[] seqMoves, mySeqMoves;
static int numFrames;
static long result;

private static int Value(int pos) {
    if ((mySeqMoves[pos] >= '0') && (mySeqMoves[pos] <= '9')) return mySeqMoves[pos]-'0';
    if ((mySeqMoves[pos] == 'x') || (mySeqMoves[pos] == ':')) return 10;
    if (mySeqMoves[pos] == '/') return 10-Value(pos-1);
    return 0;
}

private static boolean Check() {
    for (int i = 0; i < numFrames-1; i++) if (Value(2*i) + Value(2*i+1) > 10) return false;
    for (int i = 0; i < numFrames-1; i++) if ((Value(2*i) == 10) && (mySeqMoves[2*i+1] == '/')) return false;
    for (int i = 0; i < numFrames-1; i++) if ((Value(2*i) + Value(2*i+1) == 10) && (seqMoves[2*i+1] >= '0') && (seqMoves[2*i+1] <= '9')) return false;
    if ((Value(2*numFrames-2) != 10) && (Value(2*numFrames-2) + Value(2*numFrames-1) > 10)) return false;
    if ((Value(2*numFrames-2) + Value(2*numFrames-1) < 10) && (Value(2*numFrames) > 0)) return false;
    if ((Value(2*numFrames-2) == 10) && (Value(2*numFrames-1) < 10) && (Value(2*numFrames-1) + Value(2*numFrames) > 10)) return false;
    if ((Value(2*numFrames-2) == 10) && (mySeqMoves[2*numFrames-1] == '/')) return false;
    if (((Value(2*numFrames-2) != 10) || (Value(2*numFrames-1) == 10)) && (mySeqMoves[2*numFrames] == '/')) return false;
    if ((seqMoves[2*numFrames] == '-') && (Value(2*numFrames-2) + Value(2*numFrames-1) >= 10)) return false;
    if ((Value(2*numFrames-2) + Value(2*numFrames-1) == 10) && (Value(2*numFrames-2) != 10) && (seqMoves[2*numFrames-1] >= '0') && (seqMoves[2*numFrames-1] <= '9')) return false;
    //zla linijka
    //if ((Value(2*numFrames-1) + Value(2*numFrames) == 10) && (seqMoves[2*numFrames] >= '0') && (seqMoves[2*numFrames] <= '9')) return false;

        char secondMove = seqMoves[2 * numFrames - 1],
         thirdMove = seqMoves[2 * numFrames];

    int move1 = Value(2 * numFrames - 2),
        move2 = Value(2 * numFrames - 1),
        move3 = Value(2 * numFrames);
    //moje poprawki
    if ((secondMove == 'x') && (move1 != 10)) return false;
        //koniec moich poprawek

    //moje poprawki
    if (thirdMove == 'x') {
        if(move2 != 10 &&  ((move1 == 10 && move2 == 0) || (move1 + move2 < 10))) {
            return false;
        }
    }
    if ((thirdMove == '0') && move1 + move2 < 10) return false;

    if ((move1 == 10 || move1 + move2 != 10)&&(move2 != 10) &&(move2+move3 == 10) && (thirdMove >= '0') && (thirdMove <= '9')) return false;
    //koniec moich poprawek

    int score = 0;
    for (int i = 0; i < numFrames-1; i++) {
        if (Value(2*i) == 10) {
            int nextMove = Value(2*i+2);
            int nextNextMove = ((nextMove < 10) || (i == numFrames-2)) ? Value(2*i+3) : Value(2*i+4);
            score += nextMove + nextNextMove;
        }
        else if (Value(2*i) + Value(2*i+1) == 10) {
            int nextMove = Value(2*i+2);
            score += nextMove;
        }
        score += Value(2*i) + Value(2*i+1);
        mySeqScore[i] = score;
    }
    score += Value(2*numFrames-2) + Value(2*numFrames-1) + Value(2*numFrames);
    mySeqScore[numFrames-1] = score;

    for (int i = 0; i < numFrames; i++) if ((seqScore[i] != -1) && (mySeqScore[i] != seqScore[i])) return false;

    return true;
}

private static void Go(int pos) {
    if (pos == 2*numFrames+1) {
        if (Check())
            result++;
        return;
    }
    if (seqMoves[pos] == '?') {
        for (int i = 0; i <= 10; i++) {
            mySeqMoves[pos] = (char)(i+(int)'0');
            Go(pos+1);
        }
    }
    else {
        mySeqMoves[pos] = seqMoves[pos];
        Go(pos+1);
    }
}

public static void main(String[] args) {
    Scanner input = new Scanner(System.in);

    final int MAXN = 10;
    final int MAXSEQ = 21;

    seqScore = new int[MAXN];
    mySeqScore = new int[MAXN];
    seqMoves = new char[MAXSEQ+1];
    mySeqMoves = new char[MAXSEQ+1];

    int numQueries = input.nextInt();

    while (numQueries > 0) {
        numQueries--;
        numFrames = input.nextInt();
        String seqMovesStr = input.next();
        for (int i = 0; i < seqMovesStr.length(); i++)
            seqMoves[i] = seqMovesStr.charAt(i);
        for (int i = 0; i < numFrames; i++)
            seqScore[i] = input.nextInt();

        mySeqMoves = new char[MAXSEQ];
        for (int i = 0; i < numFrames-1; i++) if (seqMoves[2*i+1] == '-') seqMoves[2*i] = 'x';

        result = 0;
        Go(0);
        System.out.println(result);
    }
}
}
