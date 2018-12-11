#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <tuple>
using namespace std;
typedef long long ll;
const int maxn=5e5+5;
ll x[maxn],y[maxn],r[maxn];
int n;
void read()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld %lld %lld",&x[i],&y[i],&r[i]);
}
bool inter(int i,int j)
{
    ll dx=x[i]-x[j],dy=y[i]-y[j];
    ll dd=dx*dx+dy*dy,rr=(r[i]+r[j])*(r[i]+r[j]);
    return dd<=rr;
}
struct H
{
    typedef pair<ll,int> P;
    int log2_unit;
    vector<vector<P>> v;
    void init()
    {
        log2_unit=0;
        for(int i=1;i<=n;i++) log2_unit=max(log2_unit,(int)__lg(x[i])+1);
        v.resize(1);
        for(int i=1;i<=n;i++) v[0].push_back({y[i],i});
        sort(v[0].begin(),v[0].end());
    }
    void rescale(const bitset<maxn> &del)
    {
        log2_unit--;
        vector<vector<P>> nv;
        for(const auto &d:v)
        {
            vector<P> cur[2];
            for(const P &p:d) if(!del[p.second])
                cur[(x[p.second]>>log2_unit)&1].push_back(p);
            for(int i=0;i<2;i++) if(cur[i].size())
            {
                nv.push_back({});
                nv.back().swap(cur[i]);
            }
        }
        v.swap(nv);
    }
    void ask(int i,bitset<maxn> &del,int *ans)
    {
        int xl=lower_bound(v.begin(),v.end(),(x[i]>>log2_unit)-2,
                [&](const vector<P> &a,const ll &b){return (x[a[0].second]>>log2_unit) < b;})-v.begin();
        int xr=xl;while(xr<(int)v.size() && \
                (x[v[xr][0].second]>>log2_unit) <= (x[i]>>log2_unit)+2) xr++;
        for(int m=xl;m<xr;m++)
        {
            for(auto it=lower_bound(v[m].begin(),v[m].end(),P{y[i]-2*r[i],0});
                    it!=v[m].end() && it->first <= y[i]+2*r[i];it++)
                if(!del[it->second] && inter(i,it->second))
                    del[it->second]=1,ans[it->second]=i;
        }
    }
} helper;
int ori[maxn],ans[maxn];
void build()
{
    ll lox=*min_element(x+1,x+n+1);
    for(int i=1;i<=n;i++) x[i]=x[i]-lox+1;
    ll loy=*min_element(y+1,y+n+1);
    for(int i=1;i<=n;i++) y[i]=y[i]-loy+1;

    iota(ori+1,ori+n+1,1);
    sort(ori+1,ori+n+1,[&](int i,int j){return tie(r[i],j) > tie(r[j],i);});

    vector<ll> xx(n+1),yy(n+1),rr(n+1);
    for(int i=1;i<=n;i++) xx[i]=x[ori[i]],yy[i]=y[ori[i]],rr[i]=r[ori[i]];
    for(int i=1;i<=n;i++) x[i]=xx[i],y[i]=yy[i],r[i]=rr[i];
}
void sol()
{
    helper.init();
    bitset<maxn> del;
    for(int i=1;i<=n;i++) if(!del[i])
    {
        del[i]=1;ans[i]=i;
        while(r[i]<=(1LL<<helper.log2_unit)/2) helper.rescale(del);
        helper.ask(i,del,ans);
    }

    vector<int> v(n+1);
    for(int i=1;i<=n;i++) v[ori[i]]=ori[ans[i]];
    for(int i=1;i<=n;i++) ans[i]=v[i];
    for(int i=1;i<=n;i++) printf("%d%c",ans[i]," \n"[i==n]);
}
int main()
{
    read();
    build();
    sol();
    return 0;
}
