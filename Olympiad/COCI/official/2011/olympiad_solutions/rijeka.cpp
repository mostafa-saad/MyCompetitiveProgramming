#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector< pair<int,int> > veze;

int main()
{
    int n, m, unija = 0;
    scanf("%d%d", &n, &m);
    for(int i=0; i<n; i++)
    {
        int x, y; scanf("%d%d", &x, &y);
        if( x < y ) continue;
        veze.push_back( make_pair(y,x) );
    }
    sort(veze.begin(), veze.end());
    int odakle=0, dokle=0, intervala=0;
    for(int i=0; i<(int)veze.size(); i++)
    {
        if( veze[i].first > dokle )
        {
            unija += dokle-odakle;
            odakle = veze[i].first;
            dokle = veze[i].second;
            intervala++;
        }
        else dokle = max(dokle, veze[i].second);
    }
    unija += dokle-odakle;
   // printf("M=%d, N=%d, omjer = %lf, komponenata=%d, prosjek=%.2lf\n", m, n, unija*1.0 / m, intervala, 1.0*n/intervala);
    printf("%lld\n", (long long)m + 2*unija);
    return 0;
}
