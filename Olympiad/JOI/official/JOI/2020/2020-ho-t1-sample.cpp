#include <bits/stdc++.h>
#define SIZE 200005
using namespace std;
typedef pair <int,int> P;

int ans[SIZE];
int main()
{
	int n;
	scanf("%d",&n);
	vector <int> A;
	vector <P> B;
	for(int i=0;i<n+1;i++)
	{
		int b;
		scanf("%d",&b);
		B.push_back(P(b,i));
	}
	for(int i=0;i<n;i++)
	{
		int a;
		scanf("%d",&a);
		A.push_back(a);
	}
	sort(A.begin(),A.end());
	sort(B.begin(),B.end());
	multiset <int> st;
	multiset <int>::iterator it;
	for(int i=0;i<n;i++)
	{
		int d=max(0,B[i+1].first-A[i]);
		st.insert(d);
	}
	for(int i=0;i<=n;i++)
	{
		it=st.end();it--;
		ans[B[i].second]=*it;
		if(i==n) break;
		int d=max(0,B[i+1].first-A[i]);
		it=st.lower_bound(d);
		st.erase(it);
		d=max(0,B[i].first-A[i]);
		st.insert(d);
	}
	for(int i=0;i<=n;i++)
	{
		if(i!=0) printf(" ");
		printf("%d",ans[i]);
	}puts("");
	return 0;
}
	
