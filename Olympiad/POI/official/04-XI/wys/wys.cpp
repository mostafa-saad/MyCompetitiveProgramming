/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Wyspy                                          *
 *   Plik:                wys.cpp                                        *
 *   Autor:               Rafa³ Rusin                                    *
 *************************************************************************/
 
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define FOR(i,n) for(int i=0;i<(n);i++)
#define VAL(i,v) __typeof(v) i=(v)

const int MAXM=200000,MAXN=40000;

struct Pkt {
	int x,y,brzeg;
	bool pocz;
	
	bool operator <(const Pkt &p) const {
		return x<p.x || (x==p.x && y<p.y);
	}
};


Pkt *pkt=new Pkt[MAXM];
map<int,Pkt *> miotla;
int *stopnie=new int[MAXN];

int n,ilePkt;

Pkt *znajdz(int y) {
	VAL(el,miotla.find(y));
	if (el!=miotla.end() && el->second->y==y) {
		return el->second;
	} else {
		return NULL;
	}
}

void usun(int y) {
	VAL(el,miotla.find(y));
	assert(el!=miotla.end());
	miotla.erase(el);
}

Pkt *wezGorny(int y) {
	VAL(el,miotla.find(y));
	assert(el!=miotla.end());
	el++;
	if (el!=miotla.end()) return el->second;
	else return NULL;
}

void dodaj(Pkt *p) {
	miotla[p->y]=p;
}

void zamiataj() {
	FOR(i,ilePkt) {
		Pkt *m=znajdz(pkt[i].y);
		if (m==NULL) {
			dodaj(pkt+i);
			if (stopnie[pkt[i].brzeg]==0) {
				Pkt *gorny=wezGorny(pkt[i].y);
				if (gorny==NULL) stopnie[pkt[i].brzeg]=1;
				else {
					if (gorny->pocz) 
						stopnie[pkt[i].brzeg]=stopnie[gorny->brzeg]+1;
					else 
						stopnie[pkt[i].brzeg]=stopnie[gorny->brzeg];
				}
			}
		} else {
			usun(pkt[i].y);
		}
	}
}

int main() {
	cin>>n;
	assert(n<=MAXN);
	FOR(i,n) stopnie[i]=0;
	
	int ap=0;
	FOR(i,n) {
		int k;
		cin>>k;
		int p[2];
		cin>>p[0];
		int poczX=p[0];
		FOR(j,k) {
			if (j<k-1) cin>>p[(j+1)%2];
			else p[(j+1)%2]=poczX;
			
			pkt[ap].x=p[0];
			pkt[ap].y=p[1];
			pkt[ap].brzeg=i;
			pkt[ap].pocz=j%2;
			ap++;
			
			assert(ap<=MAXM);
		}
		
	}
	ilePkt=ap;
	
	sort(pkt,pkt+ilePkt);
	zamiataj();
	
	int wynik=0;
	FOR(i,n) {
		wynik=max(wynik,stopnie[i]);
	}
	
	cout<<wynik<<"\n";
}

