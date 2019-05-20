#include <cstdio>
#include <algorithm>
typedef long long lint;
using namespace std;

int n;
lint m;

struct node{
	node *ls, *rs;
	lint st, lazy, sum;
	int cnt;
	node(){
		st = 1e18;
		lazy = sum = cnt = 0;
		ls = rs = NULL;
	}
}*root;

void lazydown(node *p){
	if(p->ls){
		p->ls->lazy += p->lazy;
		p->ls->st += p->lazy;
	}
	if(p->rs){
		p->rs->lazy += p->lazy;
		p->rs->st += p->lazy;
	}
	p->lazy = 0;
}

void add(lint pos, lint ps, lint pe, lint v, lint sums, node* p){
	p->cnt++;
	p->sum += v;
	if(ps == pe){
		p->st = sums + 1 - v;
		return;
	}
	lint pm = (ps + pe) / 2;
	lazydown(p);
	if(pos <= pm){
		if(!p->ls) p->ls = new node();
		if(p->rs) p->rs->lazy += v, p->rs->st += v;
		add(pos, ps, pm, v, sums, p->ls);
	}
	else{
		if(!p->rs) p->rs = new node();
		if(p->ls) sums += p->ls->sum;
		add(pos, pm+1, pe, v, sums, p->rs);
	}
	p->st = 1e18;
	if(p->ls) p->st = min(p->st, p->ls->st);
	if(p->rs) p->st = min(p->st, p->rs->st);
}

void del(lint pos, lint ps, lint pe, lint v, lint sums, node *p){
	p->cnt--;
	p->sum -= v;
	if(ps == pe){
		if(p->cnt == 0) p->st = 1e18;
		return;
	}
	lint pm = (ps + pe) / 2;
	lazydown(p);
	if(pos <= pm){
		if(p->rs) p->rs->lazy -= v, p->rs->st -= v;
		del(pos, ps, pm, v, sums, p->ls);
	}
	else{
		if(p->ls) sums += p->ls->sum;
		del(pos, pm+1, pe, v, sums, p->rs);
	}
	p->st = 1e18;
	if(p->ls) p->st = min(p->st, p->ls->st);
	if(p->rs) p->st = min(p->st, p->rs->st);
}

int onecnt = 0;
bool check(){
	if(root->cnt == 0) return 1;
	if(onecnt == 0) return 0;
	return root->st >= 0;
}

int main(){
	scanf("%d %lld",&n,&m);
	root = new node();
	for(int i=0; i<n; i++){
		lint t;
		scanf("%lld",&t);
		if(t == 1) onecnt++;
		add(t,0,m,t,0,root);
	}
	printf("%d\n",check());
	int q;
	scanf("%d",&q);
	while(q--){
		int a, k;
		scanf("%d %d",&a,&k);
		if(a == -1){
			lint t;
			for(int i=0; i<k; i++){
				scanf("%lld",&t);
				if(t == 0) onecnt--;
				del(t,0,m,t,0,root);
			}
		}
		else{
			lint t;
			for(int i=0; i<k; i++){
				scanf("%lld",&t);
				if(t == 0) onecnt++;
				add(t,0,m,t,0,root);
			}
		}
		printf("%d\n",check());
	}
}
