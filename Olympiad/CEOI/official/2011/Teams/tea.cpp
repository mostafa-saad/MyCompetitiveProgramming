// Task TEA, O(n) solution, author: Dawid Dabrowski

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN=1000005;

int n;
vector<int> kids[MAXN];
pair<int,int> a[MAXN];
int l=1;
int R[MAXN],S[MAXN];
vector<int> buckets[MAXN];
int grsize[MAXN]; // -1 <=> add to the smallest group from R[i-1]

vector<int> res[MAXN];
int mnsize;
int sz;
vector<int> t[MAXN];

int stack[MAXN],top=-1;
void reconstruct() {
	int pos=n;
	while(pos>=1) {
		stack[++top]=pos;
		if(R[pos]==1) break;
		if(grsize[pos]==-1) --pos;
		else pos-=grsize[pos];
	}
	for(int k=top; k>=0; --k) {
		int i=stack[k];
		//printf("i=%d\n",i);
		if(R[i]==1) {
			++sz;
			for(int j=1; j<=i; ++j) t[sz-1].push_back(a[j].first);
			res[t[sz-1].size()].push_back(sz-1);
			if(mnsize>(int)t[sz-1].size()) mnsize=t[sz-1].size();
		} else {
			if(grsize[i]==-1) {
				while(!res[mnsize].size()) ++mnsize;
				t[res[mnsize].back()].push_back(a[i].first);
				res[mnsize+1].push_back(res[mnsize].back());
				res[mnsize].pop_back();
			} else {
				++sz;
				for(int j=i-grsize[i]+1; j<=i; ++j) t[sz-1].push_back(a[j].first);
				res[t[sz-1].size()].push_back(sz-1);
				if(mnsize>(int)t[sz-1].size()) mnsize=t[sz-1].size();
			}
		}

	}
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) {
		int a;
		scanf("%d",&a);
		kids[a].push_back(i);
	}
	for(int i=n; i>=1; --i) {
		for(int j=0; j<(int)kids[i].size(); ++j) {
			a[l++]=make_pair(kids[i][j],i);
		}
	}
	R[a[1].second]=1;
	S[a[1].second]=a[1].second;
	for(int i=a[1].second+1; i<=n; ++i) {
		if(i+a[i].second<MAXN) buckets[i+a[i].second].push_back(i);
		S[i]=MAXN;
		R[i]=0;
		int tmpmin=MAXN;
		// we try to establish R[i] = R[i-1]+1
		//		printf("probuje zrobic R[%d] = R[%d] + 1 = %d\n",i,i-1,R[i-1]+1);
		for(int k=0; k<(int)buckets[i+1].size(); ++k) {
			int cur=buckets[i+1][k];
			//			printf("rozpatruje %d\n",cur);
			if(R[cur-1]==R[i-1]) {
				//				printf("udalo sie!\n");
				R[i]=R[i-1]+1;
				if(S[i]>max(S[cur-1],a[cur].second)) {
					S[i]=max(S[cur-1],a[cur].second);
					grsize[i]=i-cur+1;
				}
			} else if(R[cur-1]==R[i-1]-1 && S[i]==MAXN) {
				//				printf("niestety sie nie udalo :( \n");
				if(tmpmin>max(S[cur-1],a[cur].second)) {
					tmpmin=max(S[cur-1],a[cur].second);
					grsize[i]=i-cur+1;
				}
			}
		}
		if(!R[i]) {
			//			printf("nie wyszlo... na pewno R[%d] = %d\n",i,R[i-1]);
			// didn't work - now R[l] = R[l-1], we search for S[l]
			R[i]=R[i-1];
			S[i]=tmpmin;
			//			printf("minimum uzyskane z poprzedniej fazy = %d\n",tmpmin);
			if(R[i-1]*S[i-1]==i-1) {
				if(S[i-1]+1<tmpmin) {
					//					printf("nie uda sie nigdzie wcisnac :(\n");
					S[i]=S[i-1]+1;
					grsize[i]=S[i];
				}
			} else {
				if(S[i-1]<tmpmin) {
					//					printf("uda sie wcisnac!!!\n");
					S[i]=S[i-1];
					grsize[i]=-1;
				}
			}
			//			printf("R[%d] = %d   S[%d] = %d\n",i,R[i],i,S[i]);
		}
	}
	printf("%d\n",R[n]);
	// begincut
	reconstruct();
	for(int A=0; A<MAXN; ++A) {
		for(int i=0; i<(int)res[A].size(); ++i) {
			printf("%d",(int)t[res[A][i]].size());
			for(int j=0; j<(int)t[res[A][i]].size(); ++j) printf(" %d",t[res[A][i]][j]);
			printf("\n");
		}
	}
	// endcut
	return 0;
}
