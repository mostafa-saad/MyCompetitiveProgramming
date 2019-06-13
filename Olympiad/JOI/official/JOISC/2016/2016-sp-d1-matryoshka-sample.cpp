#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int p[210000];
int q[210000];
int z[210000];
int s[210000];
int t[210000];
int segtree[524288];
int query(int a,int b,int c,int d,int e){
	if(d<a||b<c)return 0;
	if(c<=a&&b<=d)return segtree[e];
	return max(query(a,(a+b)/2,c,d,e*2),query((a+b)/2+1,b,c,d,e*2+1));
}
void update(int a,int b){
	a+=262144;
	while(a){
		segtree[a]=max(segtree[a],b);
		a/=2;
	}
}
int ans[210000];
vector<pair<int,pair<int,int> > >ev;
int main(){
	int N,Q;
	scanf("%d%d",&N,&Q);
	for(int i=0;i<N;i++)scanf("%d%d",q+i,p+i);
	for(int i=0;i<N;i++)z[i]=q[i];
	std::sort(z,z+N);
	for(int i=0;i<Q;i++){
		scanf("%d%d",t+i,s+i);
	}
	for(int i=0;i<N;i++){
		ev.push_back(make_pair(p[i],make_pair(0,-q[i])));
	}
	for(int i=0;i<Q;i++){
		ev.push_back(make_pair(s[i],make_pair(1,i)));
	}
	std::sort(ev.begin(),ev.end());
	for(int i=0;i<ev.size();i++){
		if(ev[i].second.first==0){
			int at=lower_bound(z,z+N,-ev[i].second.second)-z;
			int val=query(0,262143,at,N-1,1);
			update(at,val+1);
		}else{
			int at=lower_bound(z,z+N,t[ev[i].second.second])-z;
			ans[ev[i].second.second]=query(0,262143,at,N-1,1);
		}
	}
	for(int i=0;i<Q;i++)printf("%d\n",ans[i]);
}