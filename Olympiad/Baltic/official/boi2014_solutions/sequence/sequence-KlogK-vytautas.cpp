/*
 * O(K log K) solution to Sequence. Not tested properly
 *
 * Author: Vytautas Gruslys
 */

#include <cstdio>

using namespace std;

#define MAX_N 100005
#define MAX_K 15

typedef long long LL;

int len[MAX_K];
bool seq[MAX_K][MAX_N][10];


void readInput()
{
    scanf ("%d", &len[0]);

    for (int i = 0; i < len[0]; ++i)
        for (int d = 0; d < 10; ++d)
            seq[0][i][d] = false;

    int K;
    for (int i = 0; i < len[0]; ++i) {
        scanf ("%d", &K);
        seq[0][i][K] = true;
    }
}

void tryDigit (int pos, int dig)
{
    for (int i = 0; i < len[pos]+3; ++i)
        for (int d = 0; d < 10; ++d)
            seq[pos+1][i][d] = false;

    len[pos+1] = 1;
    for (int i = 0; i < len[pos]; ++i) {
        if (dig == 10) {
            dig = 0;
            ++len[pos+1];
        }

        for (int d = 0; d < 10; ++d)
            if (seq[pos][i][d] && (d != dig))
                seq[pos+1][len[pos+1]-1][d] = true;

        ++dig;
    }
}

LL makePrefixSingle (int pos)
{
    bool hasZero = seq[pos][0][0];

    LL prefix = 0;
    for (int d = 1; d < 10; ++d)
        if (seq[pos][0][d]) {
            if (prefix == 0) {
                prefix = d;
                if (hasZero)
                   prefix *= 10; 
            }
            else
                prefix = prefix*10 + d;
        }

    if ((prefix == 0) && hasZero)
        prefix = 10;
    
    return prefix;
}

LL makePrefixDouble (int pos)
{
    LL answer = 10234567890;

    for (int last = 0; last < 9; ++last) {
        for (int d = 0; d < 10; ++d)
            seq[pos+1][0][d] = ((d != last) && seq[pos][0][d]) || ((d != last+1) && seq[pos][1][d]);
        LL prefix = makePrefixSingle (pos+1);
        if (last == 0 && prefix == 0)
            prefix = 1;

        if (prefix*10 + last < answer)
            answer = prefix*10 + last;
    }

    for (int second = 0; second < 9; ++second) {
        for (int d = 0; d < 10; ++d)
            seq[pos+1][0][d] = ((d != second) && (d != 9) && seq[pos][0][d]) ||
                               ((d != second+1) && (d != 0) && seq[pos][1][d]);
        LL prefix = makePrefixSingle (pos+1);

//        printf ("%d : %lld\n", second, prefix);

        if ((second == 0) && (prefix == 0) && seq[pos][0][0])
            prefix = 1;

        if (prefix*100 + second*10 + 9 < answer)
            answer = prefix*10 + second*10 + 9;
    }
   
    return answer;
}

LL smallestPrefix (int pos)
{
    LL answer = 1023456789000000;
    if (len[pos] > 2) {
        for (int digit = 0; digit < 10; ++digit) {
            tryDigit (pos, digit);
            LL prefix = smallestPrefix (pos+1);
            if (digit == 0 && prefix == 0)
                prefix = 1;
            if (answer > prefix*10 + digit)
                answer = prefix*10 + digit;
        }
    }

    else if (len[pos] == 2) {
        answer = makePrefixDouble (pos);
    }

    else if (len[pos] == 1) {
        answer = makePrefixSingle (pos);
        
    }

/*
    printf ("\n");
    for (int i = 0; i < len[pos]; ++i) {
        for (int d = 0; d < 10; ++d)
            if (seq[pos][i][d])
                printf ("%d ", d);
        printf ("\n");
    }
    printf ("ANSWER %lld\n", answer);
*/

    return answer;
}

int main()
{
    readInput();
    printf ("%lld\n", smallestPrefix (0));

    return 0;
}
