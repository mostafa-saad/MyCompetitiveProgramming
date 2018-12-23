#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

#define maxn 100001
#define maxv 101

using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

int n,v;
vector<int> graf[maxn];
ll p[maxn];
ll gain[maxn];
ll cont[maxn][maxv];
ll arrive[maxn][maxv];
pair<ll,ll> bcont[maxv][2];
pair<ll,ll> bprev[maxv][2];
ll best;

void dp(int nd, int pr){
	for(int i=0;i<graf[nd].size();i++)if(graf[nd][i]!=pr)dp(graf[nd][i],nd);
	for(int i=0;i<=v;i++)cont[nd][i]=0;
	for(int i=0;i<=v;i++)for(int j=0;j<2;j++)bcont[i][j]=make_pair(0,-1);
	for(int i=0;i<graf[nd].size();i++){
		if(pr==-1)break;
		int next=graf[nd][i];
		if(next==pr)continue;
		for(int j=0;j<=v;j++)cont[nd][j]=max(cont[nd][j],cont[next][j]);
		for(int j=1;j<=v;j++)cont[nd][j]=max(cont[nd][j],cont[next][j-1]+gain[nd]-p[pr]);
	}
	for(int i=0;i<graf[nd].size();i++){
		int next=graf[nd][i];
		if(next==pr)continue;
		for(int j=0;j<=v;j++){
			ll adv = cont[next][j];
			if(adv>=bcont[j][0].first){
				bcont[j][1]=bcont[j][0];
				bcont[j][0]=make_pair(adv,next);
				continue;
			}
			if(adv>bcont[j][1].first)bcont[j][1]=make_pair(adv,next);
		}
	}
	for(int i=0;i<=v;i++)arrive[nd][i]=i==0?0:gain[nd];
	for(int i=0;i<=v;i++)for(int j=0;j<2;j++)bprev[i][j]=make_pair(i==0?0:gain[nd],nd);
	for(int i=0;i<graf[nd].size();i++){
		int prev=graf[nd][i];
		if(prev==pr)continue;
		for(int j=0;j<=v;j++)arrive[nd][j]=max(arrive[nd][j],arrive[prev][j]);
		for(int j=1;j<=v;j++)arrive[nd][j]=max(arrive[nd][j],arrive[prev][j-1]+gain[nd]-p[prev]);
		for(int j=0;j<=v;j++){
			ll adv=arrive[prev][j];
			if(j>0)adv=max(adv,arrive[prev][j-1]+gain[nd]-p[prev]);
			if(adv>=bprev[j][0].first){
				bprev[j][1]=bprev[j][0];
				bprev[j][0]=make_pair(adv,prev);
			} else if(adv>bprev[j][1].first)bprev[j][1]=make_pair(adv,prev);
		}
	}
	for(int i=0;i<=v;i++){
		ll pgain = 0;
		if(bcont[i][0].second!=bprev[v-i][0].second)pgain=bcont[i][0].first+bprev[v-i][0].first;
		else pgain = max(bcont[i][0].first+bprev[v-i][1].first,bcont[i][1].first+bprev[v-i][0].first);
		best=max(best,pgain);
	}
}

int main(){
	scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++)scanf("%lld",p+i);
	memset(gain,0,sizeof(gain));
	for(int i=0;i<n-1;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		graf[a].push_back(b);
		graf[b].push_back(a);
		gain[a]+=p[b];
		gain[b]+=p[a];
	}
	best=0;
	dp(1,-1);
	printf("%lld\n",best);
	return 0;
}
