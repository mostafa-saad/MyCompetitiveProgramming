/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie bledne                               *
 *                      losowanie                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <vector>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

int WSP;

using namespace std;

struct node;
struct node {
	node *left, *right; int v;
	vector<int> *st;
	node() { left=right=0; st=0; }
};

int f;
// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0) {
		tr->st=new vector<int>();
		tr->v=c; tr->st->push_back(c);
	}
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
	}
}

vector<int> tmp1, tmp2;

int cmp(vector<int> *a, vector<int> *b) {
	int sw=0;
	if(a->size()>b->size()) {
		swap(a,b);
		sw=1;
	}
	tmp1=*a; tmp2.clear();
	int i, x=0, y=0, delta=max((int)b->size()/((int)a->size()*WSP),1); long long inv=0LL;
	for(i=0; i<(int)b->size(); i+=delta)
		tmp2.push_back((*b)[i]);
	sort(tmp1.begin(), tmp1.end()); sort(tmp2.begin(), tmp2.end());
	vector<int>::iterator it=tmp1.begin(), jt=tmp2.begin();
	for(; it!=tmp1.end() && jt!=tmp2.end(); ) {
		if(*it<*jt) {
			inv+=y;
			++it; ++x;
		}
		else {
			++jt; ++y;
		}
	}
	for(; it!=tmp1.end(); ) {
		++it; ++x;
		inv+=y;
	}
	for(; jt!=tmp2.end(); ) {
		++jt; ++y;
	}
	return sw ? inv>=(long long)x*y-inv : inv<=(long long)x*y-inv;
}

void rotate(node *tr) {
	if(tr->left==0)
		return;
	rotate(tr->left); rotate(tr->right);
	if(!cmp(tr->left->st, tr->right->st))
		swap(tr->left, tr->right);
	if(tr->left->st->size()<=tr->right->st->size()) {
		tr->st=tr->right->st;
		random_shuffle(tr->left->st->begin(), tr->left->st->end());
		FC((*tr->left->st),it)
			tr->st->push_back(*it);
		delete tr->left->st;
	}
	else {
		tr->st=tr->left->st;
		random_shuffle(tr->right->st->begin(), tr->right->st->end());
		FC((*tr->right->st),it)
			tr->st->push_back(*it);
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
	f=scanf("%d", &n); WSP=40000000/n; read_input(root);
	rotate(root); generate(root);
	printf("%lld\n", compute(0, n-1));
	return 0;
}

