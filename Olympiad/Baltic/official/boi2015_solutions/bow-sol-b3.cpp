/* Baltic Olympiad in Informatics 2015
 * Problem: BOW/Bowling
 * Solution without logic of bowling (only one subtask)
 * Author: Karol Pokorski
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 10;
const int MAXSEQ = 21;
const int MAXSCORE = 90;

int seqScore[MAXN];
LL dp[MAXN+1][MAXSCORE+1];
char seqMoves[MAXSEQ+1];

int main() {
    int numQueries;

    scanf("%d", &numQueries);

    while (numQueries--) {
        int numFrames;

        scanf("%d", &numFrames);
        scanf("%s", seqMoves);
        for (int i = 0; i < numFrames; i++)
            scanf("%d", &seqScore[i]);

        for (int frame = 0; frame <= numFrames; frame++)
            for (int score = 0; score <= MAXSCORE; score++)
                 dp[frame][score] = 0LL;

        dp[0][0] = 1LL;

        for (int frame = 0; frame < numFrames; frame++) {
            char firstMove = seqMoves[2*frame], secondMove = seqMoves[2*frame+1];
            int reqScore = seqScore[frame];

            for (int score = 0; score <= 9*frame; score++) {
                if (dp[frame][score] == 0LL) continue;

                for (int move1 = 0; move1 <= 9; move1++) {
                    if ((firstMove >= '0') && (firstMove <= '9') && (move1 != firstMove-'0')) continue;

                    for (int move2 = 0; move1+move2 <= 9; move2++) {
                        if ((secondMove >= '0') && (secondMove <= '9') && (move2 != secondMove-'0')) continue;

                        int nowScore = score + (move1+move2);
                        if ((reqScore != -1) && (nowScore != reqScore)) continue;

                        dp[frame+1][nowScore] = (dp[frame+1][nowScore] + dp[frame][score]);
                    }
                }
            }
        }

        LL result = 0LL;

        for (int score = 0; score <= MAXSCORE; score++)
            if ((score == seqScore[numFrames-1]) || (seqScore[numFrames-1] == -1))
                result = (result + dp[numFrames][score]);

        printf("%Ld\n", result);
    }

    return 0;
}
