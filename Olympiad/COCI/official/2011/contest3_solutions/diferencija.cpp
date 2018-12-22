#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int a[300001];
int b[300001][4];
vector< pair<int,int> > v;
const int inf = 2000000000;

int main () {

int n; scanf("%d", &n);
for(int i=0; i<n; i++) scanf("%d", a+i);
long long s = 0;

// search left for first greater member
v.resize(0);
v.push_back( make_pair(inf,-1) );
for(int i=0; i<n; i++)
{
    while( v.back().first <= a[i] ) v.pop_back();
    b[i][0] = v.back().second + 1;
    v.push_back( make_pair(a[i], i) );
}

// search right for first greater or equal member
v.resize(0);
v.push_back( make_pair(inf, n) );
for(int i=n-1; i>=0; i--)
{
    while( v.back().first < a[i] ) v.pop_back();
    b[i][1] = v.back().second - 1;
    v.push_back( make_pair(a[i], i) );
}

// search left for first lesser member
v.resize(0);
v.push_back( make_pair(-inf,-1) );
for(int i=0; i<n; i++)
{
    while( v.back().first >= a[i] ) v.pop_back();
    b[i][2] = v.back().second + 1;
    v.push_back( make_pair(a[i], i) );
}

// search right for first lesser or equal member
v.resize(0);
v.push_back( make_pair(-inf, n) );
for(int i=n-1; i>=0; i--)
{
    while( v.back().first > a[i] ) v.pop_back();
    b[i][3] = v.back().second - 1;
    v.push_back( make_pair(a[i], i) );
}

for(int i=0; i<n; i++)
{
    s += (long long)a[i] * (b[i][1]-i+1) * (i-b[i][0]+1);
    s -= (long long)a[i] * (b[i][3]-i+1) * (i-b[i][2]+1);
}

printf("%lld\n", s);

return 0; }
