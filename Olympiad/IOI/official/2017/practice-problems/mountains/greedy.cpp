#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include "mountains.h"

using namespace std;

const int maxn=20;

int ans,a[maxn];
bool mark[20];

int maximum_deevs(vector<int> a){
	int n = a.size();
	vector<int> perm;
	for(int i=0;i<n;i++)perm.push_back(i);
	for(int t=0;t<10000;t++){
		memset(mark,0,sizeof(mark));
		random_shuffle(perm.begin(),perm.end());
		int cur=0;
		for(int i=0;i<n;i++){
			bool can=true;
			for(int j=0;j<i;j++)if(mark[j]){
				bool find=false;
				for(int k=0;k<n;k++)if(perm[k] > min(perm[i],perm[j]) && perm[k] < max(perm[i],perm[j])){
					int m = (a[perm[i]] - a[perm[j]]) / (abs(perm[i] - perm[j]));
					long long h = a[perm[j]] + 1LL * m * abs(perm[j]-perm[k]);
					if(h < a[perm[k]])find=true;
				}
				if(!find)can=false;
			}
			if(can){
				cur++;
				mark[i]=true;
			}
		}
		ans=max(ans,cur);
	}
	return ans;
}
