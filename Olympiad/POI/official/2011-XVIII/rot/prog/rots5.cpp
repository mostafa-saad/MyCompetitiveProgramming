/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2*lg(n))                                     *
 *   Opis:              Rozwiazanie wolniejsze, silowe                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

using namespace std;

// naiwne drzewo bst
struct bst_node;
struct bst_node {
	bst_node *left, *right;
	bst_node(int v=-1) : val(v) { left=right=0; sz=1; }
	int sz, val;
};

// wielkosc poddrzewa
inline int size(bst_node *a) {
	if(a==0)
		return 0;
	return a->sz;
}

// wstawianie do drzewa
void insert(bst_node *&tr, int v) {
	if(v<tr->val) {
		if(tr->left==0)
			tr->left=new bst_node(v);
		else
			insert(tr->left, v);
	}
	else if(v>tr->val) {
		if(tr->right==0)
			tr->right=new bst_node(v);
		else
			insert(tr->right, v);
	}
	// nie przewidujemy takiej mozliwoscisi
	else
		assert(0);
	tr->sz=size(tr->left)+size(tr->right)+1;
}

// ile wiekszych od v w drzewie
int cnt_greater(bst_node *tr, int v) {
	bst_node *cur=tr; int res=0;
	while(cur!=0) {
		if(v>cur->val)
			cur=cur->right;
		else {
			res+=size(cur->right)+(v<cur->val ? 1 : 0);
			cur=cur->left;
		}
	}
	return res;
}

// usuwanie drzewa z pamieci
void erase(bst_node *tr) {
	if(tr==0)
		return;
	erase(tr->left);
	erase(tr->right);
	delete tr;
}

// koniec BST
struct node;
struct node {
	node *left, *right;
	bst_node *st;
	node() { left=right=0; st=0; }
};

int f;
// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0)
		tr->st=new bst_node(c);
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
	}
}

// przejscie po elementach a i zsumowanie dla kazdego elementu a,
// ile jest wiekszych od niego elementow w b
long long iter_inv(bst_node *a, bst_node *b) {
	if(a==0)
		return 0LL;
	return iter_inv(a->left, b)+iter_inv(a->right, b)+cnt_greater(b, a->val);
}

// przejscie po elementach a i wstawienie kazdego z nich do b
void iter_merge(bst_node *a, bst_node *&b) {
	if(a==0)
		return;
	insert(b, a->val);
	iter_merge(a->left, b);
	iter_merge(a->right, b);
}

// obliczenie wyniku
long long compute(node *tr) {
	if(tr->left==0)
		return 0LL;
	long long res=compute(tr->left)+compute(tr->right), inv=0LL;
	long long all=(long long)tr->left->st->sz * tr->right->st->sz;
	if(tr->left->st->sz<tr->right->st->sz) {
		tr->st=tr->right->st;
		inv=iter_inv(tr->left->st, tr->st);
		iter_merge(tr->left->st, tr->st);
		erase(tr->left->st);
	}
	else {
		tr->st=tr->left->st;
		inv=iter_inv(tr->right->st, tr->st);
		iter_merge(tr->right->st, tr->st);
		erase(tr->right->st);
	}
	return res+min(inv, all-inv);
}
	
int main(void) {
	node *root=new node;
	f=scanf("%*d"); read_input(root);
	printf("%lld\n", compute(root));
	return 0;
}

