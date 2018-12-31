/*
 * Task: Matching
 *  Inefficient solution 3
 *  O(m n^2)
 * Author: Jakub Lacki
 */

#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)

bool good_match(int* pattern, int length, int* text)
{
    FOR(i, 1, length-1)
        REP(j, length-i)
        {
            if((pattern[j] < pattern[j+i]) != (text[j] < text[j+i]))
                return false;
        }
    return true;
}

int main()
{
    int n, m;
    int *pattern, *text;
    scanf("%d%d", &n, &m);
    
    pattern = new int[n];
    text = new int[m];
    
    REP(i, n)
    {
        int x;
        scanf("%d",&x);
        pattern[x-1] = i;
    }
    REP(i, m)
        scanf("%d", &text[i]);

    vector<int> matches;
    REP(i, m-n+1)
        if(good_match(pattern, n, text+i))
            matches.push_back(i);
    
    printf("%d\n", matches.size());

    bool first = true;
    FORE(it, matches)
    {
        if(first)
            first = false;
        else
            printf(" ");
        printf("%d", *it+1);
    }
    printf("\n");
    return 0;
}
