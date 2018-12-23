/*
 * Task: Matching
 *  Inefficient solution 9
 *  O(n + m log m)
 * Author: Jakub Lacki
 */

#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
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
    map<int, int> numbers;

    for(int i=0; i<n; i++)
    {
        map<int, int>::iterator it = numbers.lower_bound(tab[i]);
        if(it == numbers.end())
            (*bigger)[i] = -1;
        else
            (*bigger)[i] = it->second;
        if(it == numbers.begin())
            (*smaller)[i] = -1;
        else
        {
            it --;
            (*smaller)[i] = it->second;
        }
        numbers.insert(it, make_pair(tab[i], i));
    }
}

bool kmp_equal(const vector<int>& text, int a, int b, const vector<int>& bigger, const vector<int>& smaller, const map<int, int>& text_numbers)
{

    map<int, int>::const_iterator it = text_numbers.lower_bound(text[b]);
    if(bigger[a] != -1)
    {
        if(it == text_numbers.end())
            return false;
        else
            return b-it->second == a - bigger[a];
    }
    if(smaller[a] != -1)
    {
        if(it == text_numbers.begin())
            return false;
        it --;
        return b-it->second == a - smaller[a];
    }
    return true;
}

bool kmp_equal_p(const vector<int>& text, int a, int b, const vector<int>& bigger, const vector<int>& smaller)
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
        while(j && !kmp_equal_p(pattern, j, i, bigger, smaller)) j = p[j-1];
        if(kmp_equal_p(pattern, j, i, bigger, smaller))
            j ++;
        p[i] = j;
    }

    int matched_characters = 0;
    map<int, int> text_numbers;
    int tn_beg = 0;
    for(size_t i=0; i<text.size(); i++)
    {
        while(matched_characters && !kmp_equal(text, matched_characters, i, bigger, smaller, text_numbers))
        {
            for(int j=0; j<matched_characters - p[matched_characters-1]; j++)
                text_numbers.erase(text[tn_beg++]);
            matched_characters = p[matched_characters-1];
        }
        if(kmp_equal(text, matched_characters, i, bigger, smaller, text_numbers))
        {
            text_numbers[text[i]] = i;
            matched_characters ++;
        }

        if(matched_characters == n)
        {
            ret.push_back(i - n + 1);
            for(int j=0; j<matched_characters-p[matched_characters-1]; j++)
                text_numbers.erase(text[tn_beg++]);
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
    
    REP(i, n)
    {
        int x;
        scanf("%d",&x);
        pattern[x-1] = i;
    }
    
    REP(i, m)
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
