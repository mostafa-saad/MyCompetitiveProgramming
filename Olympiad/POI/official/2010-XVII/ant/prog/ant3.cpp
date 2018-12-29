/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Antysymetria (ANT)                                        *
 *   Plik:     ant3.cpp                                                  *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie alternatywne.                                 *
 *                                                                       *
 *************************************************************************/ 
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <numeric>
#include <cmath>
#include <cstdlib>
using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back
typedef long long ll;
typedef double D;
typedef long double ld;
typedef vector<int> VI;
typedef pair<int,int> PII;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(VAR(i,a);i<=(b);++i)
#define FORD(i,a,b) for(VAR(i,a);i>=(b);--i)
#define FORE(a,b) for(VAR(a,(b).begin());a!=(b).end();++a)
#define VAR(a,b) __typeof(b) a=(b)
#define SIZE(a) ((int)((a).size()))
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,a) memset(x,a,sizeof(x))
int cond = 1;
#define db(x) {if(cond){cerr << __LINE__ << " " << #x << " " << x << endl; } }
#define dbv(x) {if(cond){cerr << __LINE__ << " " << #x << ": "; FORE(__i,x) cerr << *__i << " "; cerr << endl;} }

#define M 501013
#define P 865413846237383LL

ll t[M], tt[M], pot[M];

inline bool por(const int &d,const int &a,const int &b)
{
    return t[a+d-1] - pot[d] * (a?t[a-1]:0) == tt[b+d-1] - pot[d] * (b?tt[b-1]:0);
}

char s[M];
#define inf ((ll)1e8)

int main()
{
    int n;
    ll ret = 0;
    scanf("%d %s",&n,s);
        t[0] = s[0]-'0', tt[0] = '1' - s[n-1];
        pot[0] = 1;
    FOR(i,1,n-1) 
    {
        pot[i] = pot[i-1] * P;
        t[i] = t[i-1] * P + s[i]-'0';
        tt[i] = tt[i-1] * P + '1' - s[n-1-i];
    }
    REP(i,n-1)
    {
        int a = 0, b = min(i+1,n-i-1), ss;
        while(a<b)
        {
            ss=(a+b+1)/2;
            if(por(ss, i+1-ss, n-1-i-ss)) a=ss;
            else b = ss-1;
        }
        ret += a;
    }
    printf("%lld\n",ret);
    return 0;
}
