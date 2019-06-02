/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n*lg^2(n))                                     *
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

// drzewo AVL wzbogacone o mozliwosc odpowiadania na zapytania
// "ile wiekszych od x" w czasie logarytmicznym
struct avl_node;
struct avl_node {
	avl_node *left, *right;
	avl_node(int v=-1) : val(v) { left=right=0; sz=h=1; }
	int sz, h, val;
};

// wysokosc poddrzewa
inline int height(avl_node *a) {
	if(a==0)
		return 0;
	return a->h;
}

// wielkosc poddrzewa
inline int size(avl_node *a) {
	if(a==0)
		return 0;
	return a->sz;
}

// procedura pomocnicza
inline void make(avl_node *x, avl_node *l, avl_node *r) {
	x->left=l; x->right=r;
	x->sz=size(l)+size(r)+1;
	x->h=max(height(l), height(r))+1;
}

// rownowazenie poddrzewa
void balance(avl_node *&R) {
	avl_node *tmp1, *tmp2, *tmp3, *res=R;
	if(height(R->left)==height(R->right)+2) {
		// tu trzeba sie zastanowic
		if(height(R->left->left)==height(R->left)-1) {
			tmp1=R->left->right; res=R->left;
			make(R, tmp1, R->right);
			make(res, res->left, R);
		}
		else {
			tmp1=R->left->right->left; tmp2=R->left->right->right;
			tmp3=R->left; res=R->left->right;
			make(tmp3, tmp3->left, tmp1);
			make(R, tmp2, R->right);
			make(res, tmp3, R);
		}
	}
	else if(height(R->right)==height(R->left)+2) {
		// tu juz nie - wierzymy w symetrie i zamieniamy left<->right, a takze kolejnosc argumentow make
		if(height(R->right->right)==height(R->right)-1) {
			tmp1=R->right->left; res=R->right;
			make(R, R->left, tmp1);
			make(res, R, res->right);
		}
		else {
			tmp1=R->right->left->right; tmp2=R->right->left->left;
			tmp3=R->right; res=R->right->left;
			make(tmp3, tmp1, tmp3->right);
			make(R, R->left, tmp2);
			make(res, R, tmp3);
		}
	}
	else
		make(res, res->left, res->right);
	R=res;
}

// wstawianie do drzewa
void insert(avl_node *&tr, int v) {
	if(v<tr->val) {
		if(tr->left==0)
			tr->left=new avl_node(v);
		else
			insert(tr->left, v);
	}
	else if(v>tr->val) {
		if(tr->right==0)
			tr->right=new avl_node(v);
		else
			insert(tr->right, v);
	}
	// nie przewidujemy takiej mozliwosciz
	else
		assert(0);
	balance(tr);
}

// ile wiekszych od v w drzewie
int cnt_greater(avl_node *tr, int v) {
	avl_node *cur=tr; int res=0;
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
void erase(avl_node *tr) {
	if(tr==0)
		return;
	erase(tr->left);
	erase(tr->right);
	//delete tr;
}

// koniec AVL

struct node;
struct node {
	node *left, *right;
	avl_node *st;
	node() { left=right=0; st=0; }
};

int f;

// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0)
		tr->st=new avl_node(c);
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
	}
}

// przejscie po elementach a i zsumowanie dla kazdego elementu a,
// ile jest wiekszych od niego elementow w b
long long iter_inv(avl_node *a, avl_node *b) {
	if(a==0)
		return 0LL;
	return iter_inv(a->left, b)+iter_inv(a->right, b)+cnt_greater(b, a->val);
}

// przejscie po elementach a i wstawienie kazdego z nich do b
void iter_merge(avl_node *a, avl_node *&b) {
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

