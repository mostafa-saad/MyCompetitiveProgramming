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
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include<list>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<deque>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()


int sz;
struct node {
	node(int no, int cnt=1): no(no), cnt(cnt), left(NULL), right(NULL) {};
	int no, cnt;
	node *left, *right;
};


inline int lca(node* x, node* y) {
	int n = x->no;
	int m = y->no;
	if (n < m) swap(n, m);
	n >>= (__builtin_clz(m) - __builtin_clz(n));
	if (n==m) return n;
	return n >>= (__builtin_clz(1)+1 - __builtin_clz(n^m));
}

inline bool leftOf(node* x, node* y) {
	int n = x->no;
	int m = y->no;
	m >>= (__builtin_clz(n) - __builtin_clz(m) - 1);
	return !(m & 1);
}

LL invA, invB;

inline LL count(node* x) {
	return x->cnt;
}

node* merge(node* A, node* B) {
	if (A == NULL) return NULL;
	if (A->no == B->no) {
		invA += count(A->left) * count(B->right);
		invB += count(B->left) * count(A->right);
		A->cnt += B->cnt;
		A->left = merge(A->left, B->left);
		A->right = merge(A->right, B->right);
		delete B;
		return A;
	} else {
		int no = lca(A,B);
		if (no == B->no) {
			B->cnt += A->cnt;
			if (leftOf(B, A)) {// tak jakby A->right == NULL
				invA += count(A) * count(B->right);
				B->left = merge(A, B->left); 
			}
			else { // tak jakby A->left == NULL
				invB += count(B->left) * count(A);
				B->right = merge(A, B->right);
			}
			return B;
		}
		else if (no == A->no) {
			A->cnt += B->cnt;
			if (leftOf(A, B)) { //tak jakby B->right == NULL
				invB += count(B) * count(A->right);
				A->left = merge(A->left, B);
			}
			else { //tak jakby B->left == NULL
				invA += count(A->left) * count(B);
				A->right = merge(A->right, B);
			}
			return A;
		}
		else {
			node* nd = new node(no);
			nd->cnt = A->cnt + B->cnt;
			if (leftOf(nd, A)) {//tak jakby A.right == B.left == NULL
				invA += count(A) * count(B);
				nd->left = A;
				nd->right = B;
			} else { 
				invB += count(A) * count(B);
				nd->left = B;
				nd->right = A;
			}
			return nd;
		}
	}
}

LL res = 0;
node* go() {
	int val;
	scanf("%d", &val);
	if (val != 0) {
		return new node(sz+val);
	}
	else {
		node* nd = merge(go(), go());
		res += min(invA, invB);
		invA = invB = 0;
		return nd;
	}
}


int main() {
	int n;
	scanf("%d", &n);
	sz = 1;
	while(sz < n) {
		sz *= 2;
	}
	go();
	printf("%lld\n", res);


}
