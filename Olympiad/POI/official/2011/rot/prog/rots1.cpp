/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Scalenie zbiorow synow w zbior ojca              *
 *                      - podobienstwo do Mergesorta nieprzypadkowe      *
 *                      dziala wolno dla drzew o duzej wysokosci         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

using namespace std;

struct node;
struct node {
	node *left, *right; list<int> st;
	node() { left=right=0; }
};

int f;
// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0)
		tr->st.push_back(c-1);
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
	}
}

// obliczenie wyniku
long long compute(node *tr) {
	if(tr->left==0)
		return 0LL;
	long long res=compute(tr->left)+compute(tr->right), inv=0LL;
	int i=0, j=0; long long all=(long long)tr->left->st.size()*tr->right->st.size();
	list<int>::iterator it=tr->left->st.begin(), jt=tr->right->st.begin();
	for(; it!=tr->left->st.end() && jt!=tr->right->st.end(); ) {
		if(*it<*jt) {
			tr->st.push_back(*it); ++i; ++it;
			inv+=j;
		}
		else {
			tr->st.push_back(*jt); ++j; ++jt;
		}
	}
	for(; it!=tr->left->st.end(); ++it) {
		tr->st.push_back(*it);
		inv+=j;
	}
	for(; jt!=tr->right->st.end(); ++jt)
		tr->st.push_back(*jt);
	tr->left->st.clear(); tr->right->st.clear();
	return res+min(inv, all-inv);
}
	
int main(void) {
	node *root=new node;
	f=scanf("%*d"); read_input(root);
	printf("%lld\n", compute(root));
	return 0;
}

