/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Liczenie liczby inwersji dla wszystkich wezlow   *
 *                      wewnetrznych naraz                               *
 *                      dziala wolno gdy duza wysokosc drzewa            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

using namespace std;

// wezel drzewa 
struct node;
struct node {
	node *left, *right, *par;
	int sz; long long inv, all;
	node(node *p=0) : par(p) { left=right=0; inv=0LL; }
};

node *p[200100]; 

int f;
// wczytywanie wejscia
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0) {
		tr->sz=1;
		p[c-1]=tr;
	}
	else {
		tr->left=new node(tr); tr->right=new node(tr);
		read_input(tr->left); read_input(tr->right);
		tr->sz=tr->left->sz+tr->right->sz;
		tr->all=(long long)tr->left->sz*tr->right->sz;
	}
}

// obliczanie wyniku przy znanej liczbie inwersji w kazdym wezle
long long compute(node *tr) {
	if(tr->left==0)
		return 0LL;
	return min(tr->inv, tr->all-tr->inv)+compute(tr->left)+compute(tr->right);
}

int main(void) {
	int n, i; node *root=new node, *tmp;
	f=scanf("%d", &n); read_input(root); 
	REP(i,n) {
		// usuwamy lisc "i", nastepnie aktualizujemy sciezke do gory
		tmp=p[i]; --tmp->sz;
		while(tmp->par!=0) {
			if(tmp->par->right==tmp)
				tmp->par->inv+=tmp->par->left->sz;
			--tmp->par->sz; tmp=tmp->par;
		}
	}
	printf("%lld\n", compute(root));
	return 0;
}

