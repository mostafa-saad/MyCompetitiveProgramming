#include<bits/stdc++.h>
 
#define Re return
#define Rg register
#define St static
#define In inline
#define Ct continue
#define NS namespace
#define Op operator
#define fst first
#define snd second
#define mP make_pair
#define lB lower_bound
#define uB upper_bound
#define inc(l, i, r) for(int i=l; i<r; ++i)
#define dec(l, i, r) for(int i=r; i>l; --i)
#define fev(g) for(int o=u[g.h], v; (v=o[g.e].v)>0; o=o[g.e].o)
 
typedef long long LL;
typedef double Db;
typedef std::pair<int, int> PInt;
 
const int mxN=1<<18;
 
int n;
 
NS Graph
{
    struct edge
    {
        int v, o;
        In edge(int v=0, int o=0) : v(v), o(o) {}
    };
 
    struct graph
    {
        int h[mxN<<1], tot=1;
        bool vis[mxN];
        edge e[mxN<<2];
        In void aE(int u, int v)
        {
            e[++tot]=edge(v, u[h]), u[h]=tot;
        }
    } g1, g2;
 
    int k, bel[mxN], size[mxN<<1];
 
    void tarjan(int u, int o0)
    {
        g1.vis[u]=1;
        St int tim, DFN[mxN], low[mxN];
        DFN[u]=low[u]=++tim;
        St int st[mxN<<2], t;
        st[t++]=o0;
        fev(g1)
            if(o^o0^1)
                if(!g1.vis[v])
                    tarjan(v, o), low[u]=std::min(low[u], low[v]);
                else
                    low[u]=std::min(low[u], DFN[v]);
         
        if(o0 && DFN[g1.e[o0^1].v]<=low[u])
        {
            g2.aE(g1.e[o0^1].v, n+(++k));
            for(;st[t]!=o0;)
                ++size[n+k], g2.aE(n+k, g1.e[st[--t]].v);
        }
    }
     
    LL ans, f[mxN], g[mxN], h[mxN];
 
    void DFS(int u)
    {
        g2.vis[u]=1;
        LL x=0, y=0;
        fev(g2)
            if(!g2.vis[v])
            {
                DFS(v);
                f[u]+=f[v];
                g[u]+=g[v];
                h[u]+=h[v];
                x+=f[v]*f[v];
                y+=(h[v]+g[v])*f[v];
            }
        if(u>n)
        {
            ans+=
                (LL)size[u]*(size[u]-1)*(size[u]-1)+
                (LL)size[u]*h[u]*2+
                (LL)(size[u]+1)*(f[u]*f[u]-x)+
                ((h[u]+g[u])*f[u]-y)*2+
                (LL)size[u]*g[u]*2+
                (LL)(size[u]*(size[u]-1))*f[u]*2;
            h[u]+=(LL)size[u]*f[u];
            f[u]+=size[u];
            g[u]+=(LL)size[u]*(size[u]-1);
        }
        else
            ans+=(f[u]*f[u]-x)+((h[u]+g[u])*f[u]-y)*2;
    }
 
    In LL solve()
    {
        inc(1, u, n+1)
            if(!g1.vis[u])
                tarjan(u, 0);
         
        inc(1, u, n+1)
            if(!g2.vis[u])
            { 
                DFS(u);
                ans+=h[u]*2+g[u]*2;
            }
 
        Re ans;
    }
}
 
int main()
{
    St int m;
    scanf("%d%d", &n, &m);
    inc(0, i, m)
    {
        St int u, v;
        scanf("%d%d", &u, &v);
        Graph::g1.aE(u, v);
        Graph::g1.aE(v, u);
    }
 
    printf("%lld\n", Graph::solve());
    Re 0;
}