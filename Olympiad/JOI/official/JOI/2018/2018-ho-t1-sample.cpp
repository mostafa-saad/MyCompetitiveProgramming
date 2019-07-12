#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<n;i++)
#define PB push_back

using vi=vector<int>;

int read(){
	int i;
	scanf("%d",&i);
	return i;
}

int main(){
	int n=read(),k=read();
	int mn,mx,last;
	vi len;
	REP(i,n){
		int t=read();
		if(i==0)mn=t;
		if(i==n-1)mx=t+1;
		if(0<i)len.PB(t-last-1);
		last=t;
	}
	sort(len.begin(),len.end(),greater<int>());
	int ans=mx-mn;
	REP(i,k-1)ans-=len[i];
	cout<<ans<<endl;
}
