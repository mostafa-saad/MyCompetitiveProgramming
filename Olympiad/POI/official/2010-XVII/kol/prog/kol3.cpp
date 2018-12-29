/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Kolej (KOL)                                   *
 *   Plik:                 kol3.cpp                                      *
 *   Autor:                Miroslaw Michalski                            *
 *   Implementacja         Michal Pilipczuk                              *   
 *   Opis:                 Rozwiazanie weryfikujace.                     *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cstdlib>

#include <queue>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

const int MAXN=100057;
const int INF=1000000000;
int poc[MAXN],rev[MAXN],mini[MAXN],c[MAXN];
int n;
vector<int> tab[MAXN];
bool niet=false;

struct Drzewo {
	Drzewo* left;
    Drzewo* right;
	int key;
	int dist;
};

inline Drzewo* create(int x) {
	Drzewo* d = new Drzewo;
	d->key   = x;
	d->dist  = 1;
	d->left  = NULL;
	d->right = NULL;

	return d;
}

inline int top(Drzewo* d) {
	return (d==NULL)?(0):(d->key);
}

inline int dist(Drzewo* d){
	return (d==NULL)?(0):(d->dist);
}

Drzewo* merge(Drzewo* a, Drzewo* b) {
	if (a==NULL) return b;
	if (b==NULL) return a;
	// a!=NULL && b!=null
	if (top(b)<top(a)) swap(a,b);
	a->left = merge(a->left,b);
	if (dist(a->left) > dist(a->right) ) swap(a->right,a->left);
	if (a->right==NULL) a->dist = 0; else a->dist = 1+a->right->dist;
	return a;
}

Drzewo* deleteMin(Drzewo* d) {
	if (d!=NULL) {
		Drzewo* tmp = merge(d->left,d->right);
		free(d);
		return tmp;
	}
	return NULL;
}

inline bool isEmpty(Drzewo* d) {
	return (d==NULL);
}

void paint(int p,int colour) {
	c[p]=colour;
	for(int i=0;i<(int)tab[p].size();i++) {
		if (c[tab[p][i]]==0) paint(tab[p][i],colour%2+1); else
		if (c[tab[p][i]]!=(colour%2+1)) niet=true;
	}
}

bool checkOut() {
	stack<int> st[2];
	for(int i=0;i<2;i++) st[i].push(-1);
	int passed = 1;
	for(int i=1;i<=n;i++) {
		if (c[i]!=0) st[c[i]-1].push(poc[i]); else return false;
		bool change = true;
		while (change) {
			change = false;
			for(int j=0;j<2;j++) {
				while (st[j].top()==passed) {
					passed++;
					st[j].pop();
					change = true;
				}
			}
		}
	}
	return (passed==n+1);
}

int main() {
	Drzewo* stos[MAXN]; 
	int head = -1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&poc[i]);
		rev[poc[i]]=i;
	}
	int prev=INF;
	for(int i=n;i>=1;i--) {
		mini[i]=prev;
		prev=min(prev,poc[i]);
	}
	for(int i=1;i<=n;i++) {
		int d=poc[i], e=mini[i];
		Drzewo* tmp = create(poc[i]);
		bool finished = false;
		while (head!=-1 && !finished) {
			Drzewo* v=stos[head];
			int val=top(v); 
			if (val<d) {
				tab[i].push_back(rev[val]);
				tab[rev[val]].push_back(i);
				tmp=merge(tmp,v);
				head--;
			} else finished = true;
		}
		finished = false;
		head++; stos[head]=tmp;
		while (head!=-1 && !finished) {
			tmp=stos[head]; head--;
			while (!isEmpty(tmp) && (top(tmp)<e)) tmp=deleteMin(tmp);
			
			if (!isEmpty(tmp)) {
				head++; stos[head] = tmp;
				finished = true;
			}
		}
	}
	for(int i=1;i<=n;i++) c[i]=0;
	for(int i=1;i<=n;i++) if (c[i]==0)  paint(i,1);
	niet = checkOut();
	if (!niet) printf("NIE\n"); else {
		printf("TAK\n");
		for(int i=1;i<=n;i++) printf("%d ",c[i]);
		printf("\n");
	}
	return 0;
}

