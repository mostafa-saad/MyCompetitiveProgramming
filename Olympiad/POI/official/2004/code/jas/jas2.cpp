/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Jaskinia                                       *
 *   Plik:                jas2.cpp                                       *
 *   Autor:               Piotr Stañczyk                                 *
 *   Data:                2004.01.20                                     * 
 *************************************************************************/

#include <stream.h>
#include <algo.h>
#define FK(a,b,c) for(int a=b;a<=c;a++)
#define Fill(a,b,c,d) for(int x=b;x<=c;x++) a[x]=d;
#define FKW(x,v,g,q) for(int x=g.w[q].k,v=g.k[x].w; x!=0;x=g.k[x].n,v=g.k[x].w)

struct Wie{int k;};
struct Kraw{int w,n;};
struct Graf
{
 Kraw* k;
 Wie* w;
 int ws,ks;
 void Clear(){FK(x,1,ws) w[x].k=0; ws=ks=0;}
 Graf(int wi,int kr)
 {
  w=new Wie[wi+1];
  k=new Kraw[kr+1];
  ws=wi; Clear();
 }
 ~Graf(){delete k; delete w;}
 void AddKr(int p,int c)
 {
  if(ws<p)ws=p; if(ws<c)ws=c;
  k[++ks].w=c;
  k[ks].n=w[p].k;
  w[p].k=ks;
 }
 void AddKrDw(int p,int k)
 {
  this->AddKr(p,k);
  this->AddKr(k,p);
 }
};

bool vals[50001][17];
bool visited[50001];
Graf gr(50000,100000);
int n,a,b,odpp=0;

void Start(int nr)
{
 int odp=0;
 visited[nr]=1;
 FKW(x,v,gr,nr) if(!visited[v])
 {
  Start(v);
  for(int it=0;it<17;it++)
  {
   if(vals[nr][it] && vals[v][it] && odp<it) odp=it;
   vals[nr][it]|=vals[v][it];
  }
 }
 while(vals[nr][odp]) odp++;
 for(int it=0;it<odp;it++) vals[nr][it]=false;
 vals[nr][odp]=true;
 odpp=max(odpp,odp);
}

int main()
{
 cin >> n;
 for(int x=1;x<n;x++)
 {
  cin >> a >> b;
  gr.AddKrDw(a,b);
  visited[x]=false;
 }
 Start(1);
 cout << odpp << endl;
 return 0;
}
