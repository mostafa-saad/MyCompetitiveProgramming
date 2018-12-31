/*
 * Task: Matching
 *  Model solution
 *  O(n + m)
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

void bigger_and_smaller(const vector<int>& tab, vector<int>* bigger, vector<int>* smaller)
{
    int n = tab.size();
    vector<int> next(n), prev(n), where_is(n);
    
    bigger->resize(n);
    smaller->resize(n);

    for(int i=0; i<n; i++)
    {
        next[i] = i+1;
        prev[i] = i-1;
        where_is[tab[i]] = i;
    }

    for(int i=n-1; i>=0; i--)
    {
        int x = tab[i];
        if(next[x] == n)
            (*bigger)[i] = -1;
        else
            (*bigger)[i] = where_is[next[x]];
        if(prev[tab[i]] == -1)
            (*smaller)[i] = -1;
        else
            (*smaller)[i] = where_is[prev[x]];
        if(prev[x] != -1)
            next[prev[x]] = next[x];
        if(next[x] != n)
            prev[next[x]] = prev[x];
    }
}

bool kmp_equal(const vector<int>& text, int a, int b, const vector<int>& bigger, const vector<int>& smaller)
{
    if(bigger[a] != -1 && text[b] > text[b-(a - bigger[a])])
        return false;
    if(smaller[a] != -1 && text[b] < text[b-(a - smaller[a])])
        return false;
    return true;
}

vector<int> kmp(const vector<int>& pattern, const vector<int>& text)
{
    int n = pattern.size();
    vector<int> p(n);
    vector<int> ret, bigger, smaller;

    bigger_and_smaller(pattern, &bigger, &smaller);
    p[0] = 0;
    
    for(int i=1; i<n; i++)
    {
        int j = p[i-1];
        while(j && !kmp_equal(pattern, j, i, bigger, smaller)) j = p[j-1];
        if(kmp_equal(pattern, j, i, bigger, smaller))
            j ++;
        p[i] = j;
    }

    int matched_characters = 0;
    for(size_t i=0; i<text.size(); i++)
    {
        while(matched_characters && !kmp_equal(text, matched_characters, i, bigger, smaller))
            matched_characters = p[matched_characters-1];
        if(kmp_equal(text, matched_characters, i, bigger, smaller))
            matched_characters ++;

        if(matched_characters == n)
        {
            ret.push_back(i - n + 1);
            matched_characters = p[matched_characters-1];
        }
    }
    
    return ret;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> pattern(n), text(m);
    
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d",&x);
        pattern[x-1] = i;
    }
    
    for(int i=0; i<m; i++)
        scanf("%d", &text[i]);
    
    vector<int> matches = kmp(pattern, text);
    printf("%d\n", matches.size());
    for(size_t i=0; i<matches.size(); i++)
    {
        printf("%d", matches[i]+1);
        if(i+1 < matches.size())
            printf(" ");
    }
    printf("\n");
    return 0;
}
