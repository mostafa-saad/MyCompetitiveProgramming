#include<cstdio>
#include<vector>
using namespace std;

vector<int> v[7];

int main()
{
    int n, p; scanf("%d%d", &n, &p);
    int sol = 0;
    while(n--)
    {
        int i, x; scanf("%d%d", &i, &x);
        while( !v[i].empty() && v[i].back() > x ) { sol++; v[i].pop_back(); }
        if( !v[i].empty() && v[i].back() == x ) continue;
        sol++; v[i].push_back(x);
    }
    printf("%d\n", sol);
    return 0;
}
