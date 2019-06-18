#include <stdio.h>
#include <queue>
using namespace std;
const int maxp = 2e6 + 1;

int tel[2000005], n, m;
bool vis[2000005];
priority_queue<int> pq;

int main(){
	vis[maxp] = 1;
	for(int i=0; i<maxp; i++){
		tel[i] = i+1;
	}
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		tel[s-1] = e;
		tel[e-1] = s;
	}
	int len = -1;
	for(int i=0; i<maxp; i++){
		if(!vis[i]){
			int pos = i, ret = 0;
			while(!vis[pos]){
				vis[pos] = 1;
				if(tel[pos] != pos + 1) ret++;
				pos = tel[pos];
			}
			if(len == -1) len = ret;
			else pq.push(ret);
		}
	}
	while(!pq.empty() && m--){
		len += pq.top() + 2;
		pq.pop();
	}
	len += (m + 1) / 2;
	len += (m / 2) * 3;
	printf("%d",len);
}
