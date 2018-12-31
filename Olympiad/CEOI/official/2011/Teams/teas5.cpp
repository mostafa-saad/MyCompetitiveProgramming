/*
 * Task: Teams
 *  Slow solution 5
 *  Same as model solution 3, but uses linear seach instead of binary search
 * Author: Jakub Lacki
 */

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;

const int MAXN=1000000;

int previous[MAXN+1], a[MAXN+1], team_size[MAXN+1];
int teams_count[MAXN+1];
pair<int, int> a_pairs[MAXN+1];

int check(int n, int max_team)
{
    teams_count[n] = 0;
    FOR(i, 1, n)
    {
        const int& ai = a_pairs[i].first;
        if(i < ai || (teams_count[previous[i-ai]]+1 < teams_count[previous[i-1]] && i < n))
            previous[i] = previous[i-1];
        else
        {
            int cur_team_size = i - previous[i-ai];
            int new_teams_count = teams_count[previous[i-ai]] + 1;
            if(cur_team_size <= max_team && (i == n || new_teams_count >= teams_count[previous[i-1]]))
            {
                previous[i] = i;
                teams_count[i] = new_teams_count;
                team_size[i] = cur_team_size;
            }
            else
                previous[i] = previous[i-1];
        }
    }
    return teams_count[n];
}

int main()
{
    int n;
    scanf("%d", &n);
    REP(i, n)
    {
        scanf("%d", &a_pairs[i+1].first);
        a_pairs[i+1].second = i+1;
    }
    sort(a_pairs+1, a_pairs+n+1);
    
    teams_count[0] = 0;
    previous[0] = 0;
    int res = check(n, n);

    for(int i=1; i<=n; i++)
    {
        if(check(n, i) == res)
            break;
    }
    printf("%d\n", teams_count[n]);
    vector<int> team;
    int cur = n;
    while(cur > 0)
    {
        team.clear();
        printf("%d", team_size[cur]);
        for(int i=0; i<team_size[cur]; i++)
            printf(" %d", a_pairs[cur-i].second);
        cur -= team_size[cur];
        printf("\n");
    }
    return 0;
}
