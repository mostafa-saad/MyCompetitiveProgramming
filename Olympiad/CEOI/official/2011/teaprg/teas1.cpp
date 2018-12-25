// Task TEA, O(n^2) solution, author: Dawid Dabrowski

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN=1000005;

int n;
pair<int,int> a[MAXN];

vector<vector<int> > res;

int R[MAXN],S[MAXN],grsize[MAXN];

int main() {
	scanf("%d",&n);
	for(int i=0; i<n; ++i) {
		scanf("%d",&a[i].first);
		a[i].second=i;
	}
	sort(a,a+n);
	for(int i=0; i<n; ++i) R[i]=0;
	for(int i=0; i<n; ++i) {
		if(i-a[i].first >= -1) {
			R[i]=1;
			S[i]=i+1;
			grsize[i]=i+1;
		}
		for(int j=i-a[i].first; j>=0; --j) {
			if(R[j]>0) {
				if(R[j]+1>R[i]) {
					R[i]=R[j]+1;
					S[i]=0;
				}
				//if(i==n-1) printf("j=%d     R[n-1] = %d\n",j,R[n-1]);
				if(R[j]+1==R[i] && (max(S[j],i-j)<S[i] || S[i]==0)) {
					/*if(i==n-1) {
						printf("uaktualniam wielkosc na %d przy j=%d\n",max(S[j],i-j),j);
					}*/
					S[i]=max(S[j],i-j);
					grsize[i]=i-j;
				}
			}
		}
		//printf("R[%d] = %d   S[%d] = %d\n",i,R[i],i,S[i]);
	}
	printf("%d\n",R[n-1]);
	int i=n-1;
	while(i>=0) {
		printf("%d",grsize[i]);
		for(int j=i; j>i-grsize[i]; --j) {
			printf(" %d",a[j].second+1);
		}
		printf("\n");
		i-=grsize[i];
	}
	return 0;
}
