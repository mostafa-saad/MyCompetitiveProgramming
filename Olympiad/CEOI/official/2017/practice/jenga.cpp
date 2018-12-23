#include <cstdio>
#include <cstring>

#define maxn 1000

using namespace std;

int memo[3*maxn+10][3*maxn+10][4];//[rm2][rm1][top]
int levels,rm2,rm1,top;//# of levels,# of storeys with 2 removable blocks, # of storeys with 1 removable block, # of blocks on top
int state[3*maxn+10];

bool opponent(){
	int nivo, palica;
	scanf("%d%d",&nivo,&palica);
	state[nivo]-=(1<<(palica-1));
	if(state[nivo]<2 || state[nivo]==4)return false;
	if(state[nivo]==5)rm2--,top++;
	if(state[nivo]==2)rm1--,top++;
	if(state[nivo]==3 || state[nivo]==6)rm2--,rm1++,top++;
	return true;
}

int action(int r2, int r1, int t){
	if(t>3)t-=3,r2++;
	if(memo[r2][r1][t]!=-1)return memo[r2][r1][t];
	memo[r2][r1][t]=0;
	if(r1>0 && action(r2,r1-1,t+1)==0)memo[r2][r1][t]=1;
	if(r2>0 && action(r2-1,r1,t+1)==0)memo[r2][r1][t]=2;
	if(r2>0 && action(r2-1,r1+1,t+1)==0)memo[r2][r1][t]=3;
	return memo[r2][r1][t];
}

void move(){
	int strategy=action(rm2,rm1,top);
	int storey,block;
	switch(strategy){
		case 1:
			for(storey=1;state[storey]!=3 && state[storey]!=6;storey++);
			block=state[storey]==3?1:3;
			rm1--,top++;
			break;
		case 2:
			for(block=2,storey=1;state[storey]!=7;storey++);
			rm2--,top++;
			break;
		case 3:
			for(block=1,storey=1;state[storey]!=7;storey++);
			rm2--,rm1++,top++;
	}
	state[storey]-=(1<<(block-1));
	printf("%d %d\n",storey,block);
	fflush(stdout);
}

int main(){
	scanf("%d",&levels);
	memset(memo,-1,sizeof(memo));
	if(action(levels-1,0,3)==0)printf("second\n");
	else printf("first\n");
	fflush(stdout);
	for(int i=1;i<=3*levels;i++)state[i]=7;
	rm2=levels-1,rm1=0,top=3;
	if(action(levels-1,0,3)>0)move();
	while(opponent()){
		if(top>3)top-=3,rm2++,levels++;
		move();
	}
	return 0;
}
