/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kolb5.cpp                                                 *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *             Rozwiazanie losuje RND razy jakis ciag i sprawdza, czy    *
 *             jest poprawny.                                            *
 *                                                                       *
 *************************************************************************/


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>

const int RND=4000000;
const int MAXN=1000123;

using namespace std;


int r[MAXN],t[MAXN],n,numberOfChecks=0;

bool isValid() {
	stack<int> st[2];
	st[0].push(-1); st[1].push(-1);
	int passed=1;
	for(int i=0;i<n;i++) {
		st[r[i]].push(t[i]);
		bool change = true;
		while (change) {
			change = false;
			for(int j=0;j<2;j++) 
				while (st[j].top()==passed) {
					passed++;
					st[j].pop();
					change = true;
				}
		}
	}
	if (passed==n+1) return true; else return false;
}

int main() {
	srand(123);
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&t[i]);

	bool found=false;
	while (!found && numberOfChecks<RND) {
		numberOfChecks+=n;
		for(int i=0;i<n;i++) r[i]=rand()%2;
		if (isValid()) found=true;
	}

	if (found) {
		printf("TAK\n");
		for(int i=0;i<n;i++) printf("%d ",r[i]+1);
		printf("\n");
	} else printf("NIE\n");
	
	return 0;
}


