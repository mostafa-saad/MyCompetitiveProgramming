#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n,k;
string s;

vector<int> f(char c){
	vector<int> a(n+2);
	int I=0,t=0;
	for(int i=0;i<n;i++){
		if(i&&s[i-1]==c) t--;
		while(I<n&&t<k){
			if(s[I]==c) t++;
			I++;
		}
		a[i]=(t==k?I:n+1);
	}
	a[n]=a[n+1]=n+1;
	return a;
}

int main(){
	cin>>n>>k>>s;
	vector<int> a=f('J'),b=f('O'),c=f('I');
	int res=n;
	for(int i=0;i<n;i++){
		int x=c[b[a[i]]];
		if(x<=n) res=min(res,x-i-3*k);
	}
	cout<<(res==n?-1:res)<<endl;
}