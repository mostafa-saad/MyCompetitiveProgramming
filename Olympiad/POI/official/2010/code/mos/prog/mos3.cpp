/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 mos3.cpp                                      *
 *   Autor:                Bartosz Gorski                                *
 *   Opis:                 Rozwiazanie weryfikujace.                     *
 *                         Rozwiazanie wykorzystuje STLa.                *
 *   Zlozonosc czasowa:    O((n + m) * m * log MAX_WIATR)                *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *                                                                       *
 *************************************************************************/


#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<list>
using namespace std;

#define MINN(a,b) ((a)>(b)?(b):(a))
#define MAXX(a,b) ((a)<(b)?(b):(a))

#define MAX_N 1000
#define MAX_M 2000
#define INF 1000000000

struct edge
{
	int a,b,c,nr;
	edge(){}
	edge(int aa,int bb,int cc,int nnr)
	{
		a = aa; b = bb; c = cc; nr = nnr;
	}
};

vector<edge> G[MAX_N];
vector<int> GF[MAX_N+MAX_M+2];
edge E[2*MAX_M];

int n,m,a,b,c,c1,c2,l,r,deg[MAX_N],prz[MAX_N+MAX_M+2][MAX_N+MAX_M+2];
bool u[MAX_M+1];
list<edge> eulerWay;

void euler(edge a)
{
	while(!G[a.b].empty())
	{
		edge b = G[a.b].back();
		G[a.b].pop_back();
		if(!u[b.nr])
		{
			u[b.nr]=true;
			euler(b);
		}
	}
	eulerWay.push_front(a);
}

void findEuler()
{
        for(int i=0; i<n; i++)
                G[i].clear();
	for(int i=0; i<m; i++)
	{
                if(prz[E[2*i].a][n+i]==0)
                        G[E[2*i].a].push_back(E[2*i]);
                if(prz[E[2*i+1].a][n+i]==0)
                        G[E[2*i+1].a].push_back(E[2*i+1]);
        }
	eulerWay.clear();
	euler(edge(0,0,0,m));
	eulerWay.pop_front();
}

int q[MAX_N+MAX_M+2],f[MAX_N+MAX_M+2],p[MAX_N+MAX_M+2];
bool v[MAX_N+MAX_M+2];

bool findWay(int a,int b,int k)
{
        int c,ib,ie,wf;
        for(int i=0; i<k; i++)
        {
                f[i]=-INF;
                v[i]=false;
                p[i]=-1;
        }
        q[0]=a;
        ib=0; ie=1;
        v[a]=true;
        f[a]=INF;
        while((ib<ie) && (f[b]<=0))
        {
                c=q[ib++];
                for(int j=0; j<(int)GF[c].size(); j++)
                {
                        int i=GF[c][j];
                        if(prz[c][i]>0)
                        {
                                wf=MINN(f[c],prz[c][i]);
                                if(f[i]<wf)
                                {
                                        f[i]=wf;
                                        p[i]=c;
                                }
                                if(!v[i])
                                {
                                        q[ie++]=i;
                                        v[i]=true;
                                }
                        }
                }
        }
        if(f[b]>0)
        {
                c=b;
                while(c!=a)
                {
                        prz[p[c]][c]-=f[b];
                        prz[c][p[c]]+=f[b];
                        c=p[c];
                }
        }
        return f[b]>0;
}

void addEdge(int a, int b, int c)
{
        prz[a][b]=c;
        GF[a].push_back(b);
        prz[b][a]=0;
        GF[b].push_back(a);
}

bool existEulerCycle(int c)
{
        int k=n+m+2, s=k-2,t=k-1,flow;
	for(int i=0; i<m; i++)
        {
                prz[n+i][t]=prz[t][n+i]=-1;
                prz[E[2*i].a][n+i]=prz[n+i][E[2*i].a]=-1;
                prz[E[2*i+1].a][n+i]=prz[n+i][E[2*i+1].a]=-1;                
        }
        for(int i=0; i<k; i++)
                GF[i].clear();
	for(int i=0; i<n; i++)
        {
                prz[s][i]=prz[i][s]=-1;
                if(deg[i]%2==1)
                        return false;
                addEdge(s,i,deg[i]/2);
        }
	for(int i=0; i<m; i++)
	{
		u[i]=false;
		if(E[2*i].c<=c)
                        addEdge(E[2*i].a,n+i,1);
		if(E[2*i+1].c<=c)
                        addEdge(E[2*i+1].a,n+i,1);
                addEdge(n+i,t,1);
	}
        flow=0;
        while(findWay(s,t,k))
                flow++;
        return flow==m;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)
        {
		G[i].clear();
                deg[i]=0;
        }
	l=r=0;
	for(int i=0; i<m; i++)
	{
		scanf("%d%d%d%d",&a,&b,&c1,&c2);
		a--; b--;
		E[2*i]=edge(a,b,c1,i);
		E[2*i+1]=edge(b,a,c2,i);
		l=MAXX(l,MINN(c1,c2));
		r=MAXX(r,MAXX(c1,c2));
                deg[a]++;
                deg[b]++;
	}
	while(l<r)
	{
		c=(l+r)/2;
		if(existEulerCycle(c))
			r=c;
		else
			l=c+1;
	}
	if(!existEulerCycle(l))
	{
		printf("NIE\n");
		return 0;
	}
        findEuler();
	printf("%d\n",l);
	for(list<edge>::iterator il = eulerWay.begin(); il != eulerWay.end(); il++)
		printf("%d ",il->nr+1);
	printf("\n");
	return 0;
}
