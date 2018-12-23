/*
 * Task: Matching
 *  Inefficient solution 7
 *  O((m+n) * hook_size * log (hook_size) + mn)
 *   based on incorrect solution 1
 * Author: Jakub Lacki
 */

#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)

const int hook_size = 50;

bool good_match(const vector<int>& pattern_order, int* text)
{
    REP(i, ((int)pattern_order.size())-1)
        if(text[pattern_order[i]] > text[pattern_order[i+1]])
            return false;
    return true;
}

vector<pair<int, int> > encode(int* t, int size)
{
    vector<pair<int, int> > ret;
    FOR(i, hook_size, size-1)
    {
        int min_bigger = 1000000000, max_smaller = -1;
        int bigger_pos, smaller_pos;
        bigger_pos = smaller_pos = -1;
        REP(j, hook_size)
        {
            if(t[i-1-j] < t[i] && t[i-1-j] > max_smaller)
            {
                max_smaller = t[i-1-j];
                smaller_pos = j+1;
            }
            else if(t[i-1-j] > t[i] && t[i-1-j] < min_bigger)
            {
                min_bigger = t[i-1-j];
                bigger_pos = j+1;
            }
        }
        ret.PB(MP(smaller_pos, bigger_pos));
    }
    return ret;
}

vector<int> kmp(const vector<pair<int, int> >& pattern, const vector<pair<int, int> >& text)
{
    int n = pattern.size();
    vector<int> p(n);
    vector<int> ret;
    p[0] = 0;

    for(int i=1; i<n; i++)
    {
        int j = p[i-1];
        while(j && pattern[j] != pattern[i]) j = p[j-1];
        if(pattern[j] == pattern[i]) 
            j ++;
        p[i] = j;
    }

    int matched_characters = 0;
    for(size_t i=0; i<text.size(); i++)
    {
        while(matched_characters && text[i] != pattern[matched_characters])
            matched_characters = p[matched_characters-1];
        if(text[i] == pattern[matched_characters])
            matched_characters ++;

        if(matched_characters == n)
        {
            ret.push_back(i - n + 1);
            matched_characters = p[matched_characters-1];
        }
    }

    return ret;
}

bool verify_good_match(int* pattern, int length, int* text)
{
    REP(i, length-1)
        if(text[pattern[i]] > text[pattern[i+1]])
            return false;
    return true;
}

int main()
{
    int n, m;
    int *pattern, *text, *pattern_order;
    scanf("%d%d", &n, &m);

    vector<int> ends_order;
    pattern = new int[n];
    pattern_order = new int[n];
    text = new int[m];
    
    REP(i, n)
    {
        int x;
        scanf("%d",&x);
        pattern[x-1] = i;
        if(x <= hook_size || x >= n-hook_size)
            ends_order.push_back(x-1);
        pattern_order[i] = x-1;
    }
    REP(i, m)
        scanf("%d", &text[i]);
    
    vector<int> matches;
    if(n >= hook_size)
    {
        vector<pair<int, int> > encoded_pattern, encoded_text;
        encoded_pattern = encode(pattern, n);              
        encoded_text = encode(text, m);              
   
        vector<int> kmp_matches = kmp(encoded_pattern, encoded_text);

        FORE(it, kmp_matches)
            if(good_match(ends_order, text+*it) && verify_good_match(pattern_order, n, text+*it))
                matches.push_back(*it);
    }
    else
    {
        REP(i, m-n+1)
            if(verify_good_match(pattern_order, n, text+i))
                matches.push_back(i);

    }

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
