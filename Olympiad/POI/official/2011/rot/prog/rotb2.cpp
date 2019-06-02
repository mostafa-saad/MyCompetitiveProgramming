/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie bledne                               *
 *                      rozwazanie czesci par                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

int WSP;

using namespace std;

struct node;
struct node {
	node *left, *right; int v;
	set<int> *st;
	node() { left=right=0; st=0; }
};

int f;
// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0) {
		tr->st=new set<int>;
		tr->v=c; tr->st->insert(c);
	}
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
	}
}

int cmp(set<int> *a, set<int> *b) {
	set<int>::iterator it=a->begin(), jt=b->begin();
	int x=0, y=0, lim=min(a->size(),b->size())*WSP; long long inv=0LL;
	for(; it!=a->end() && jt!=b->end() && x+y<=lim; ) {
		if(*it<*jt) {
			inv+=y;
			++it; ++x;
		}
		else {
			++jt; ++y;
		}
	}
	for(; it!=a->end() && x+y<=lim; ) {
		++it; ++x;
		inv+=y;
	}
	for(; jt!=b->end() && x+y<=lim; ) {
		++jt; ++y;
	}
	return inv<=(long long)x*y-inv;
}

// rotacja na podstawie porządku leksykograficznego
// zbiorow lisci w poddrzewie
void rotate(node *tr) {
	if(tr->left==0)
		return;
	rotate(tr->left); rotate(tr->right);
	if(!cmp(tr->left->st, tr->right->st))
		swap(tr->left, tr->right);
	if(tr->left->st->size()<=tr->right->st->size()) {
		tr->st=tr->right->st;
		FC((*tr->left->st),it)
			tr->st->insert(*it);
		delete tr->left->st;
	}
	else {
		tr->st=tr->left->st;
		FC((*tr->right->st),it)
			tr->st->insert(*it);
		delete tr->right->st;
	}
}

vector<int> perm, tmp;

void generate(node *tr) {
	if(tr->left==0) {
		perm.push_back(tr->v);
		return;
	}
	generate(tr->left);
	generate(tr->right);
}

long long compute(int l, int r) {
	if(l==r)
		return 0;
	int i, j, k, mid=(l+r)/2; 
	long long res=compute(l,mid)+compute(mid+1,r);
	tmp.clear();
	for(i=l, j=mid+1, k=0; i<=mid && j<=r; ) {
		if(perm[i]<perm[j]) {
			res+=k;
			tmp.push_back(perm[i++]);
		}
		else {
			++k;
			tmp.push_back(perm[j++]);
		}
	}
	for(; i<=mid; ++i) {
		tmp.push_back(perm[i]);
		res+=k;
	}
	for(; j<=r; ++j)
		tmp.push_back(perm[j]);
	REP(i,(int)tmp.size())
		perm[l+i]=tmp[i];
	return res;
}

int main(void) {
	node *root=new node; int n;
	f=scanf("%d", &n); read_input(root); WSP=10000000/n;
	rotate(root); generate(root);
	printf("%lld\n", compute(0, n-1));
	return 0;
}

