/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Tomasz Walen                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *   Zlozonosc czasowa: O(n*lg(n))                                       *
 *          pamieciowa: O(n*lg(n))                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

#define MP make_pair

struct node {
	node(int count=1): count(count), left(NULL), right(NULL) {};
	int count;
	node *left, *right;
};

LL invA=0, invB=0;

inline LL count(node* x) {
	return (x!=NULL ? x->count : 0);
}

int c = 0;
int cnter = 0;

node* merge(node* A, node* B) {
	if (A == NULL) return B;
	if (B == NULL) return A;

	invA += count(A->right) * count(B->left);
	invB += count(A->left) * count(B->right);
	++cnter;
	c = max(c,cnter);
	node *res=new node(0);
	res->left = merge(A->left, B->left);
	res->right = merge(A->right, B->right);
	res->count = count(res->left) + count(res->right);
	delete A;
	--cnter;
	delete B;
//	--cnter;
	return res;
}

node* create_tree(int n,int v) {
	if (n==1) {
		++cnter;
		c = max(c,cnter);
		return new node(1);
	} else {
		++cnter;
		c = max(c,cnter);
		node *res=new node(1);
		int m=n/2;
		if (v<=m) res->left=create_tree(m,v);
		else res->right=create_tree(n-m,v-m);
		return res;
	}
}

LL res = 0;
int n;

node* go() {
	int val;
	scanf("%d", &val);
	if (val != 0) return create_tree(n,val);
	else {
		node* nd = merge(go(), go());
		res += min(invA, invB);
		invA = invB = 0;
		return nd;
	}
}

int main() {
	scanf("%d", &n);
	go();
	printf("%lld\n", res);
	fprintf(stderr, "%d\n", c);
}
