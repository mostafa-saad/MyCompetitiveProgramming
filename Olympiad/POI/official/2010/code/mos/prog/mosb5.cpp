/************************************************************************* 
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Mosty (MOS)                                      *
 *   Plik:              mosb5.cpp                                        * 
 *   Autor:             Bartosz Gorski                                   * 
 *   Opis:              Rozwiazanie niepoprawne. Wyszukuje binarnie      * 
 *                      po wyniku, ale heurystycznie sprawdza istnienie  * 
 *                      cyklu Eulera. Dla kazdego wierzcholka dzieli     *   
 *                      jego zbior krawedzi na dwa zbiory skierowanych   * 
 *                      i nieskierowanych. Znajdujac cykl najpierw       * 
 *                      korzysta z krawedzi skierowanych a potem         *
 *                      z nieskierowanych. Rozwiazanie wykorzystuje STLa.*
 *   Zlozonosc czasowa: O((n + m) * log MAX_WIATR)                       * 
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

struct edge
{
	int a,b,c,nr;
	edge(){}
	edge(int aa,int bb,int cc,int nnr)
	{
		a = aa; b = bb; c = cc; nr = nnr;
	}
};

vector<edge> G[MAX_N], GR[MAX_N], GW[MAX_N];
edge E[MAX_M];

int n,m,a,b,c,c1,c2,l,r;
bool u[MAX_M+1];
list<edge> eulerWay;

void euler(edge a)
{
	while(!GW[a.b].empty())
	{
		edge b = GW[a.b].back();
		GW[a.b].pop_back();
		if(!u[b.nr])
		{
			u[b.nr]=true;
			euler(b);
		}
	}
	while(!GR[a.b].empty())
	{
		edge b = GR[a.b].back();
		GR[a.b].pop_back();
		if(!u[b.nr])
		{
			u[b.nr]=true;
			euler(b);
		}
	}
	eulerWay.push_front(a);
}

bool existEulerCycle(int c)
{
	int degIn[MAX_N];
	for(int i=0; i<n; i++)
	{
		GR[i].clear();
		GW[i].clear();
		degIn[i]=0;
	}
	for(int i=0; i<m; i++)
	{
		u[i]=false;
		if(E[2*i].c>c)
		{
			GW[E[2*i+1].a].push_back(E[2*i+1]);
			degIn[E[2*i+1].b]++;
		}
		else
			if(E[2*i+1].c>c)
			{
				GW[E[2*i].a].push_back(E[2*i]);
				degIn[E[2*i].b]++;
			}
			else
			{
				GR[E[2*i].a].push_back(E[2*i]);
				GR[E[2*i+1].a].push_back(E[2*i+1]);
			}
	}
	for(int i=0; i<n; i++)
		if((GR[i].size()+degIn[i])<GW[i].size())
			return false;
	eulerWay.clear();
	euler(edge(0,0,0,m));
	eulerWay.pop_front();
	int a=0,b=0;
	for(list<edge>::iterator il = eulerWay.begin(); il != eulerWay.end(); il++)
	{
		if(a!=il->a)
			return false;
		a=il->b;
		b++;
	}
	return b==m && a==0;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)
		G[i].clear();
	l=r=0;
	for(int i=0; i<m; i++)
	{
		scanf("%d%d%d%d",&a,&b,&c1,&c2);
		a--; b--;
		G[a].push_back(edge(a,b,c1,i));
		E[2*i]=edge(a,b,c1,i);
		G[b].push_back(edge(b,a,c2,i));
		E[2*i+1]=edge(b,a,c2,i);
		l=MAXX(l,MINN(c1,c2));
		r=MAXX(r,MAXX(c1,c2));
	}
	for(int i=0; i<n; i++)
		if(G[i].size()%2!=0)
		{
			printf("NIE\n");
			return 0;
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
	printf("%d\n",l);
	for(list<edge>::iterator il = eulerWay.begin(); il != eulerWay.end(); il++)
		printf("%d ",il->nr+1);
	printf("\n");
	return 0;
}
