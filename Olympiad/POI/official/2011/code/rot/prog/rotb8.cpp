/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie bledne                               *
 *                      po prostu liczymy inwersje                       *
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

using namespace std;

struct node;
struct node {
	node *left, *right; int v, sz;
	node() { left=right=0; sz=0; }
};

int f;
// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0) {
		tr->v=c; tr->sz=1;
	}
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
		tr->sz=tr->left->sz+tr->right->sz;
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
	f=scanf("%d", &n); read_input(root);
	generate(root);
	printf("%lld\n", compute(0, n-1));
	return 0;
}

