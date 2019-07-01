/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Opis:              Rozwiazanie alternatywne                         *
 *   Zlozonosc czasowa: O(n*lg(n))                                       *
 *          pamieciowa: O(n*lg(n))                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long LL;

#define MP make_pair


struct node {
	void init(int count=1){
		this->count = count;
		this->left = this->right = NULL;
	}
	int count;
	node *left, *right;
};

node nodes[4000000];
node *cur;

node* newnode(int count) {
	node* res;
	res = cur;
	++cur;
	res->init(count);
	return res;
}

LL invA=0, invB=0;

inline LL count(node* x) {
	return (x!=NULL ? x->count : 0);
}

node* merge(node* A, node* B) {
	if (A == NULL) return B;
	if (B == NULL) return A;

	invA += count(A->right) * count(B->left);
	invB += count(A->left) * count(B->right);

	node *res = A;
	res->left = merge(A->left, B->left);
	res->right = merge(A->right, B->right);
	res->count = count(res->left) + count(res->right);
	return res;
}

node* create_tree(int n,int v) {
	if (n==1) {
		return newnode(1);
	} else {
		node *res=newnode(1);
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
	cur = nodes;
	scanf("%d", &n);
	go();
	printf("%lld\n", res);
}
