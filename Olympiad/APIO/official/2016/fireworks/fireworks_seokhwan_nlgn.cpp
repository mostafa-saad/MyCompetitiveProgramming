/*
 * Author: Seokhwan Choi
 * Time Complexity: O(N+M log (N+M))
 * It is recommended to understand O((N+M) (log (N+M))^2) code before view this code
 */

#include<stdio.h>
#include<vector>
#define MAXN 300100
#define MAXLOGN 19
int n,m;
int p[MAXN];
int c[MAXN];
std::vector<int> el[MAXN];//list of child nodes
int chk[MAXN];//DFS visit check
int tv;//number of visited nodes in DFS
int tm[MAXN];//DFS traverse order, tm[i] is i-th visited node
int itm[MAXN];//node i is visited itm[i]-th in DFS
int tend[MAXN];//subtree of i-th node is tm[i]~tend[i]
int leaf[MAXN];//1 if leaf node(explosive), 0 otherwise, after renumbering nodes
int np[MAXN];//parent node after renumbering nodes
int nc[MAXN];//cost after renumbering nodes
int nend[MAXN];//subtree of i-th node is i~nend[i] after renumbering
long long int pnt[MAXN][2];//slope changing points, pnt[i][0]>=pnt[i][1]
int pntn[MAXN];//number of slope changing points, doesn't exceed 2
int it[1<<(MAXLOGN+1)];//segment tree, finds i which pnt[i][0] is maximum - so we can find maximum slope changing point
long long int a[MAXN];//y=ax+b if x is larger than all slope changing points
long long int b[MAXN];
void dfs(int loc){//depth-first search for renumbering nodes
	tv++;
	chk[loc]=1;
	tm[tv]=loc;
	itm[loc]=tv;
	int i;
	for(i=0;i<el[loc].size();i++){
		dfs(el[loc][i]);
	}
	tend[loc]=tv;
}
void push(int loc,long long int val){//add slope changing point
	pnt[loc][pntn[loc]]=val;//we add val in increasing order
	pntn[loc]++;
	it[loc+(1<<MAXLOGN)]=loc;
	loc+=1<<MAXLOGN;
	loc/=2;
	while(loc>0){
		if(pnt[it[loc*2]][0]>pnt[it[loc*2+1]][0]){
			it[loc]=it[loc*2];
		}
		else{
			it[loc]=it[loc*2+1];
		}
		loc/=2;
	}
}
long long int pop(int start,int end){//pop maximum slope changing point in range[start,end]
	start+=1<<MAXLOGN;
	end+=1<<MAXLOGN;
	long long int res=0;//pnt[res][0] should be maximum
	//initially res=0, so pnt[res][0]=0, which is smaller than all other pnt[i][0]
	while(start<=end){
		if(start%2==1){
			if(pnt[it[start]][0]>pnt[res][0]){
				res=it[start];
			}
			start++;
		}
		if(end%2==0){
			if(pnt[it[end]][0]>pnt[res][0]){
				res=it[end];
			}
			end--;
		}
		start/=2;
		end/=2;
	}
	long long int ret=pnt[res][0];//return value
	long long int loc=res;//should erase pnt[loc][0]
	pntn[loc]--;
	if(pntn[loc]==0){
		pnt[loc][0]=0;
	}
	else{//pntn[loc] becomes 2 to 1
		pnt[loc][0]=pnt[loc][1];
	}
	loc+=1<<MAXLOGN;
	loc/=2;
	while(loc>0){
		if(pnt[it[loc*2]][0]>pnt[it[loc*2+1]][0]){
			it[loc]=it[loc*2];
		}
		else{
			it[loc]=it[loc*2+1];
		}
		loc/=2;
	}
	return ret;
}
int main(){
	int i;
	long long int ta,tb;
	scanf("%d%d",&n,&m);
	for(i=2;i<=n+m;i++){
		scanf("%d%d",&p[i],&c[i]);
		el[p[i]].push_back(i);
	}
	dfs(1);//DFS from root node(node 1) to renumber nodes
	for(i=1;i<=n+m;i++){
		np[i]=itm[p[tm[i]]];
		nc[i]=c[tm[i]];
		if(tm[i]>n)leaf[i]=1;
		nend[i]=tend[tm[i]];
	}//renumbering finished
	for(i=n+m;i>1;i--){
		if(leaf[i]==1){//if i is leaf node
			a[i]=1;
			b[i]=-nc[i];
			push(i,nc[i]);
			push(i,nc[i]);
		}
		else{//we can see slope-changing points of subtree of node i
			//add edge toward parent node to data
			while(a[i]>1){
				b[i]+=pop(i,nend[i]);
				a[i]--;
			}
			ta=pop(i,nend[i]);
			tb=pop(i,nend[i]);
			push(i,ta+nc[i]);
			push(i,tb+nc[i]);
			b[i]-=nc[i];
		}
		a[np[i]]+=a[i];//we should only merge a,b to parent node
		b[np[i]]+=b[i];//because we can see all slope-changing points of subtree
	}
	while(a[1]>0){
		b[1]+=pop(1,nend[1]);
		a[1]--;
	}
	printf("%lld\n",b[1]);
	return 0;
}
