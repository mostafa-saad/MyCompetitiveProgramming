#include<stdio.h>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
#define SIZE 650
int dat[400000];
priority_queue<int>que[650];
priority_queue<int>fl[650];
void resolve(int t)
{
	for(int i=0;i<que[t].size();i++)
	{
		fl[t].push(-dat[i+SIZE*t]);
		dat[i+SIZE*t]=-fl[t].top();
		fl[t].pop();
	}
	for(;;)
	{
		if(fl[t].empty())break;
		fl[t].pop();
	}
}
void remake(int t)
{
	int s=que[t].size();
	for(int i=0;i<s;i++)que[t].pop();
	for(int i=0;i<s;i++)que[t].push(dat[SIZE*t+i]);
}
int main()
{
	int num,query;
	scanf("%d%d",&num,&query);
	for(int i=0;i<num;i++)scanf("%d",&dat[i]);
	for(int i=0;i<num;i++)que[i/SIZE].push(dat[i]);
	int NB=(num+SIZE-1)/SIZE;
	for(int p=0;p<query;p++)
	{
		int za,zb,zc;
		scanf("%d%d%d",&za,&zb,&zc);
		za--;
		zb--;
		resolve(za/SIZE);
		resolve(zb/SIZE);
		//for(int i=0;i<num;i++)printf("%d ",dat[i]);printf("\n");
		if(za/SIZE==zb/SIZE&&za<=zb)
		{
			for(int i=za;i<=zb;i++)
			{
				if(dat[i]>zc)swap(dat[i],zc);
			}
			printf("%d\n",zc);
		}
		else
		{
			for(int i=za%SIZE;i<que[za/SIZE].size();i++)
			{
				if(dat[i+SIZE*(za/SIZE)]>zc)swap(dat[i+SIZE*(za/SIZE)],zc);
			}
			int t=(za/SIZE+1)%NB;
			//printf("****%d\n",zc);
			if(t!=zb/SIZE)
			{
				for(;;)
				{
			//printf("****%d %d\n",zc,t);
					que[t].push(zc);
					fl[t].push(-zc);
					zc=que[t].top();
					que[t].pop();
					t++;
					if(t==NB)t-=NB;
					if(t==zb/SIZE)break;
				}
			}
			//printf("****%d\n",zc);
			for(int i=0;i<=zb%SIZE;i++)
			{
				if(dat[i+SIZE*(zb/SIZE)]>zc)swap(dat[i+SIZE*(zb/SIZE)],zc);
			}
			printf("%d\n",zc);
		}
		remake(za/SIZE);
		remake(zb/SIZE);
	}
}