#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
#define SIZE 262144
class segtree
{
public:
	ll seg[SIZE*2];
	ll flag[SIZE*2];
	void update(int beg,int end,int node,int lb,int ub,ll num)
	{
		if(ub<beg||end<lb)return;
		if(beg<=lb&&ub<=end)
		{
			flag[node]+=num;
			return;
		}
		if(flag[node])
		{
			flag[node*2]+=flag[node];
			flag[node*2+1]+=flag[node];
			flag[node]=0;
		}
		update(beg,end,node*2,lb,(lb+ub)/2,num);
		update(beg,end,node*2+1,(lb+ub)/2+1,ub,num);
	}
	ll get(int pl,int node,int lb,int ub)
	{
		if(pl==lb&&ub==pl)
		{
			return flag[node];
		}
		if(flag[node])
		{
			flag[node*2]+=flag[node];
			flag[node*2+1]+=flag[node];
			flag[node]=0;
		}
		if(pl<=(lb+ub)/2)return get(pl,node*2,lb,(lb+ub)/2);
		else return get(pl,node*2+1,(lb+ub)/2+1,ub);
	}
};
segtree tree1,tree2;
typedef pair<ll,ll>pii;
typedef pair<ll,pii>pi3;
int main()
{
	int num,query;
	scanf("%d%d",&num,&query);
	for(int i=1;i<=SIZE-1;i++)
	{
		tree1.update(i,i,1,0,SIZE-1,i);
		tree2.update(i,i,1,0,SIZE-1,-i);
	}
	vector<pi3>vec;
	for(int i=0;i<query;i++)
	{
		int za,zb;
		ll zc;
		scanf("%d%d%lld",&za,&zb,&zc);
		vec.push_back(make_pair(za,make_pair(zb,zc)));
	}
	reverse(vec.begin(),vec.end());
	for(int i=0;i<query;i++)
	{
		if(vec[i].second.first==1)
		{
			int beg=0,end=SIZE-1;
			for(;;)
			{
				int med=(beg+end)/2+1;
				if(tree2.get(med,1,0,SIZE-1)<-vec[i].first)end=med-1;
				else beg=med;
				if(beg==end)
				{
					tree1.update(0,beg,1,0,SIZE-1,-vec[i].second.second*2);
					break;
				}
			}
		}
		else
		{
			int beg=0,end=SIZE-1;
			for(;;)
			{
				int med=(beg+end)/2+1;
				if(tree1.get(med,1,0,SIZE-1)>vec[i].first)end=med-1;
				else beg=med;
				if(beg==end)
				{
					tree2.update(beg+1,SIZE-1,1,0,SIZE-1,-vec[i].second.second*2);
					break;
				}
			}
		}
	}
	for(int i=1;i<=num;i++)printf("%lld\n",-(tree1.get(i,1,0,SIZE-1)+tree2.get(i,1,0,SIZE-1))/2);
}