#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct bus{
  int a,b,x,y;
};

bool operator<(bus b1,bus b2)
{
  return b1.x<b2.x;
}

int main()
{
  int n,m,t=0;
  scanf("%d%d",&n,&m);
  static bus B[300000];
  for(int i=0;i<m;i++){
    scanf("%d%d%d%d",&(B[i].a),&(B[i].b),&(B[i].x),&(B[i].y));
    B[i].a--;
    B[i].b--;
  }
  sort(B,B+m);
  static int E[100000],F[300000];
  for(int i=0;i<n;i++){
    E[i]=-1;
  }
  priority_queue<pair<int,int> > PQ;
  vector<pair<int,int> > K;
  for(int i=0;i<m;i++){
    while(!PQ.empty()&&-PQ.top().first<=B[i].x){
      pair<int,int> pr=PQ.top();
      E[B[pr.second].b]=max(E[B[pr.second].b],F[pr.second]);
      PQ.pop();
    }
    int p;
    if(B[i].a==0){
      p=B[i].x;
    }
    else{
      p=E[B[i].a];
    }
    F[i]=p;
    PQ.push(make_pair(-(B[i].y+t),i));
    if(B[i].b==n-1){
      K.push_back(make_pair(B[i].y,p));
    }
  }
  sort(K.begin(),K.end());
  vector<int> T1,T2;
  int S=-1;
  for(int i=0;i<K.size();i++){
    if(S<K[i].second){
      T1.push_back(K[i].first);
      T2.push_back(K[i].second);
      S=K[i].second;
    }
  }
  int Q;
  scanf("%d",&Q);
  while(Q--){
    int l;
    scanf("%d",&l);
    int i=upper_bound(T1.begin(),T1.end(),l)-T1.begin();
    printf("%d\n",i==0?-1:T2[i-1]);
  }
  return 0;
}
