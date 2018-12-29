/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Kaglony                                        *
 *   Plik:                kag.cpp                                        *
 *   Autor:               Rafa³ Rusin                                    *
 *************************************************************************/


#define NDEBUG
 
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <set>
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

#define null NULL

const int MAX_WIE=10010,MAX_KRA=100010*2;

int ileKra;
int ileWie;

int n,m;

struct Wierzcholek;

struct Krawedz {
	Wierzcholek *cel;
	Krawedz *next;
};

struct Wierzcholek {
	Krawedz *krawedzie;
	int pozycja;
  int numer;
	bool zaznaczony;
};

bool poczatekKlasy[MAX_WIE+1];

Wierzcholek wie[MAX_WIE];
Krawedz kra[MAX_KRA];

Wierzcholek *permutacja[MAX_WIE];


int nrBraci;
int braciaTab[MAX_WIE];



//nowa krawedz jednokierunkowa z a do b
void krawedz(int a,int b) {
	Krawedz *nowa=kra+ileKra;
	ileKra++;
	assert(ileKra<=MAX_KRA);
	nowa->cel=wie+b;
	nowa->next=wie[a].krawedzie;
	wie[a].krawedzie=nowa;
}

void wczytaj() {
	ileKra=0;
	ileWie=0;
	
	scanf("%i %i\n",&n,&m);

	for(int i=0;i<n;i++) {
		wie[i].krawedzie=null;
		wie[i].zaznaczony=false;
		wie[i].numer = i;
		poczatekKlasy[i]=false;
	}
	poczatekKlasy[0]=true;
	
	for(int i=0;i<m;i++) {
		int a,b;
		scanf("%i %i\n",&a,&b);
		a--; b--;
		krawedz(a,b);
		krawedz(b,a);
	}
}


void inicjuj() {
	//ustalenie poczatkowej permutacji
	for(int i=0;i<n;i++) {
		permutacja[i]=wie+i;
		permutacja[i]->pozycja=i;
		
		braciaTab[i]=0;
		nrBraci=0;
	}
}

int wybierz(int a,int b) {
	return a + rand()%(b-a);
}


//zamiana wierzcholkow w permutacji
void zamien(Wierzcholek *w1,Wierzcholek *w2) {
	permutacja[w1->pozycja]=w2;
	permutacja[w2->pozycja]=w1;
	int p=w1->pozycja; w1->pozycja=w2->pozycja; w2->pozycja=p;
}

void zasada1(int a,int b,Wierzcholek *x) {
	int k=b-1;
	for(Krawedz *kr=x->krawedzie; kr!=null; kr=kr->next) {
		Wierzcholek *cel=kr->cel;
		if (cel->pozycja>=a && cel->pozycja<b) {
			//wewnatrz rozpatrywanego podgrafu
			zamien(cel,permutacja[k]);
			k--;
		}
	}
	zamien(x,permutacja[k]);
}


void zasada2(int a,int b,Wierzcholek *x,int &minp) {
	int k=b-1;

	for(Krawedz *kr=x->krawedzie; kr!=null; kr=kr->next) {
		Wierzcholek *cel=kr->cel;
		if (cel->pozycja>=a && cel->pozycja<b) {
			cel->zaznaczony=true;
		}
	}
	
	while (k>=a && permutacja[k]->zaznaczony) k--;
	b=k+1;

	for(Krawedz *kr=x->krawedzie; kr!=null; kr=kr->next) {
		Wierzcholek *cel=kr->cel;
		cel->zaznaczony=false;
		if (cel->pozycja>=a && cel->pozycja<b) {
			//wewnatrz rozpatrywanego podgrafu
			zamien(cel,permutacja[k]);
			k--;
		}
	}
	poczatekKlasy[k+1]=true;
	if (k+1<minp) minp=k+1;
}

void faktoryzuj(int a,int b) {
	if (a>=b-1) return;
	Wierzcholek *x=permutacja[wybierz(a,b)];
	zasada1(a,b,x);
	
	//wybranie krotszej strony w celu osiagniecia zlozonosci pesymistycznej O(m log n)
	int p1a,p1b,p2a,p2b;
	if (x->pozycja-a<b-x->pozycja-1) {
		//lewa strona krotsza
		p1a=a; p1b=x->pozycja;
		
		p2a=x->pozycja+1; p2b=b;
	} else {
		//prawa strona krotsza
		p1a=x->pozycja+1; p1b=b;

		p2a=a; p2b=x->pozycja;
	}

	//stworzenie trzech klas (lewej, pojedynczej x, prawej)
	poczatekKlasy[p1a]=true;
	poczatekKlasy[x->pozycja]=true;
	poczatekKlasy[p2a]=true;
	
	//zastosowanie metody nr 2 do wszystkich wierzcholkow z krotszego przedzialu
	int minp=x->pozycja;
	
	for (int i=p1a;i<p1b;i++) {
		zasada2(p2a,p2b,permutacja[i],minp);
	}
	//zastosowanie metody nr 2 do wybranego wierzcholka z kazdej powstalej klasy
	for (int i=minp;i<p2b;i++) {
		if (poczatekKlasy[i]) {
			zasada2(p1a,p1b,permutacja[i],minp);
		}	
	}
	
	//wywolanie rekurencyjne dla powstalych podklas
	faktoryzuj(a,minp);
	
	int aktp=minp;
	while (aktp<b) {
		int o=aktp;
		aktp++;
		while (aktp<b && !poczatekKlasy[aktp]) aktp++;
		faktoryzuj(o,aktp);
	}
}


//sprawdzenie, czy otrzymana permutacja jest permutacja faktoryzujaca
struct Lista {
	Wierzcholek *w;
	Lista *next,*prev;
	Lista(Wierzcholek *x):w(x) {}
};


void dodaj(Lista *l,Lista *e) {
	e->next=l->next;
	e->prev=l;
	l->next=e;
	if (e->next!=null) e->next->prev=e;
}

void usun(Lista *e) {
	if (e->prev!=null) e->prev->next=e->next;
	if (e->next!=null) e->next->prev=e->prev;
	e->next=null;
	e->prev=null;
	//usuniecie wierzcholka z porownywania braci
	braciaTab[e->w->pozycja]=-1;
}

bool bracia2(Lista *a,Lista *b) {
	if (a==null || b==null) return false;
	if (a->w==null || b->w==null) return false;
	
	nrBraci++;

	Krawedz *k1=a->w->krawedzie,*prev1=null;
	Krawedz *k2=b->w->krawedzie,*prev2=null;
	do {
		while(k1!=null && braciaTab[k1->cel->pozycja]==-1) {
			if (prev1!=null) prev1->next=k1->next; else a->w->krawedzie=k1->next;
			k1=k1->next;
		}

		while(k2!=null && braciaTab[k2->cel->pozycja]==-1) {
			if (prev2!=null) prev2->next=k2->next; else b->w->krawedzie=k2->next;
			k2=k2->next;
		}
		
		if (k1==null || k2==null) break;
		
		prev1=k1;
		prev2=k2;
		k1=k1->next;
		k2=k2->next;
	} while (true);

	if (k1!=null || k2!=null) return false;
	
	for (Krawedz *k=a->w->krawedzie; k!=null; k=k->next) {
		assert(braciaTab[k->cel->pozycja]!=-1);
		if (b->w!=k->cel) {
			braciaTab[k->cel->pozycja]=nrBraci;
		}	
	}

	for (Krawedz *k=b->w->krawedzie; k!=null; k=k->next) {
		assert(braciaTab[k->cel->pozycja]!=-1);
		if (a->w!=k->cel) {
			if (braciaTab[k->cel->pozycja]!=nrBraci) return false;
		}	
	}
	
	return true;
}

//sprawdzenie, czy dwa wierzcho³ki s± braæmi w co-drzewie
bool bracia(Lista *a,Lista *b) {
	bool r=bracia2(a,b);
	
	int w1=-1,w2=-1;
	if (a->w!=null) w1=(int)(a->w-wie);
	if (b->w!=null) w2=(int)(b->w-wie);
	return r;
}

void zwolnij(Lista *l) {
	if (l!=null) {
		zwolnij(l->next);
		delete l;
	}
}

bool sprawdz() {
	Lista l(null);
	l.next=null;
	l.prev=null;
	
	Lista *koniec;
	dodaj(&l,koniec=new Lista(null));
	for (int i=n-1; i>=0; i--) {
	  dodaj(&l,new Lista(permutacja[i]));
	}
	/*	
	for (int i=0 ; i<n ; i++)
	  printf("%d ",permutacja[i]->numer);
	printf("\n");
	*/
	Lista *z=l.next;
	int i=0;
	while (i<n-1 && z!=koniec) {
		if (bracia(z->prev,z)) {
		  //		  printf("%d\n", perm[z->prev->w->pozycja]);
		  usun(z->prev);
		  i++;
		} else {
			if (bracia(z,z->next)) {
				z=z->next;
				//				printf("%d\n", perm[z->prev->w->pozycja]);
				usun(z->prev);
				i++;
			} else {
				z=z->next;
				assert(z!=null);
			}
		}
	}
	bool ret=l.next->next->w==null; //Sprawdzenie, czy udalo sie sprowadzic do pojedynczego wierzcholka

	zwolnij(l.next);
	
	return ret;
}

int main() {
	int k;
	scanf("%i\n",&k);
	for(int i=0;i<k;i++) {
		wczytaj();
		inicjuj();
		faktoryzuj(0,n);
		printf(sprawdz()?"TAK\n":"NIE\n");
	}	
	return 0;
}







