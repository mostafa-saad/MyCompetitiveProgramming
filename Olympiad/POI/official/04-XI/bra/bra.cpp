/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Bramki                                         *
 *   Plik:                bra.cpp                                        *
 *   Autor:               Rafa³ Rusin                                    *
 *************************************************************************/

#include <cstdio>
#include <queue>
#include <list>
using namespace std;

const char *ulamek[]={"0","1/2","1"};

struct {
	int stan;
	int smin,smax; //0 - 0, 1 - (1/2), 2 - 1
	list<int> wyjscia;

	int wejscia[3];
	int ilewejsc;
	bool niepoprawny;
} bra[10010];

int n;

queue<int> niepoprawne;

void dodaj(int b1, int b2) {
	bra[b1].wyjscia.push_back(b2);
	bra[b2].ilewejsc++;
}

int value(int br) {
	if (bra[br].wejscia[0]>bra[br].wejscia[2]) return 0;
	else if (bra[br].wejscia[0]<bra[br].wejscia[2]) return 2;
	else return 1;
}

void zmienstan(int br,int oile) {
	int s1=bra[br].stan;
	int s2=s1+oile;
	bra[br].stan=s2;
	for(list<int>::iterator it=bra[br].wyjscia.begin(); it!=bra[br].wyjscia.end(); ++it) {
		int dest=*it;
		bra[dest].wejscia[s1]--;
		bra[dest].wejscia[s2]++;
		if ((value(dest)!=bra[dest].stan) && (bra[dest].niepoprawny==false)) {
			bra[dest].niepoprawny=true;
			niepoprawne.push(dest);
		}
	}
}

void oblicz(int stanpocz,int znak) {
	for(int i=0;i<n;i++) {
		bra[i].stan=stanpocz;
		for(int j=0;j<3;j++) bra[i].wejscia[j]=0;
		bra[i].wejscia[stanpocz]=bra[i].ilewejsc;
		bra[i].niepoprawny=false;
	}
	
	if (znak==1) {
		zmienstan(1,2);
	} else {
		zmienstan(0,-2);
	}
	
	while (!niepoprawne.empty()) {
		int br=niepoprawne.front();
		
		zmienstan(br,znak);

		if (value(br)==bra[br].stan) {
			niepoprawne.pop();
			bra[br].niepoprawny=false;
		}
	}
}


void obliczmin() {
	oblicz(0,1);
	for(int i=0;i<n;i++) bra[i].smin=bra[i].stan;
}
void obliczmax() {
	oblicz(2,-1);
	for(int i=0;i<n;i++) bra[i].smax=bra[i].stan;
}

int main() {
	scanf("%i",&n);
	for(int i=2;i<n;i++) {
		int ile;
		scanf("%i",&ile);
		for(int j=0;j<ile;j++) {
			int we;
			scanf("%i",&we);
			dodaj(we,i);
		}
	}
	
	for(int i=0;i<n;i++) {
		bra[i].smin=0;
		bra[i].smax=2;
	}
	for(int i=0;i<2;i++) {
		bra[i].smin=i*2;
		bra[i].smax=i*2;
	}
	
	obliczmin();
	obliczmax();
	
	for(int i=0;i<n;i++) {
		if (bra[i].smin==bra[i].smax) printf("%s\n",ulamek[bra[i].smin]);
		else printf("?\n");
		
		//printf("nr %i, od %s do %s\n",i,ulamek[bra[i].smin],ulamek[bra[i].smax]);
	}
	
}
