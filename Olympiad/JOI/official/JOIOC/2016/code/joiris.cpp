#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int, int>pii;
int dat[100];
int r[100];
int main()
{
	int num, len;
	scanf("%d%d", &num, &len);
	vector<int>vec;
	for (int i = 0; i < num; i++)
	{
		int z;
		scanf("%d", &z);
		vec.push_back(z);
		dat[i%len] += z;
	}
	for (int i = 0; i < num%len; i++)
	{
		if (dat[i] % len != dat[0] % len)
		{
			printf("-1\n");
			return 0;
		}
	}
	for (int i = num%len; i < len; i++)
	{
		if (dat[i] % len != dat[len - 1] % len)
		{
			printf("-1\n");
			return 0;
		}
	}
	vector<pii>ans;
	for (int i = 1; i < num; i++)
	{
		for (;;)
		{
			if (vec[i - 1] > vec[i])
			{
				ans.push_back(make_pair(1, i));
				vec[i] += len;
			}
			else break;
		}
	}
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = vec[i]; j < vec[i + 1]; j++)
		{
			for (int k = i - len + 1; k >= 0; k -= len)
			{
				ans.push_back(make_pair(2, k));
			}
			if(i%len!=len-1)r[i % len]--;
		}
	}
	for(int i=len-3;i>=0;i--)r[i]+=r[i+1];
	int maxi = 0;
	for (int i = 0; i < num; i++)
	{
		for (;;)
		{
			if(r[i]>=0)break;
			ans.push_back(make_pair(1, i));
			r[i] += len;
		}
	}
	if(num%len>=1&&r[0]<r[len-1])
	{
		for (int i = 0; i < num%len; i++)ans.push_back(make_pair(1,i)),r[i]+=len;
	}
	if(num%len>=1)
	{
		for (int i = num - len; i >= 0; i -= len)
		{
			for (int j = 0; j < r[0]-r[len-1]; j++)ans.push_back(make_pair(2, i));
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)printf("%d %d\n", ans[i].first, ans[i].second + 1);
}