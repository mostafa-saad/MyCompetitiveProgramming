/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kolb6.cpp                                                 *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
const int INF=1000000000;
const int MAXN=1000123;

stack<int> s[2];
int n,currentPiece=1,v[MAXN];
vector<int> result;

void tryToMove() {
	bool moved=true;
	while (moved) {
		moved=false;
		for(int i=0;i<2;i++) if (s[i].top()==currentPiece) {
			s[i].pop();
			currentPiece++;
			moved=true;
		}
	}
}


bool tryToSolve() {
	for(int i=0;i<2;i++) while(!s[i].empty()) s[i].pop();
	result.clear();
	currentPiece=1;
	s[0].push(INF); s[1].push(INF);
	vector<int> choose;
	int position;
	for(int pos=0;pos<n;pos++) {
		for(int j=0;j<2;j++) if (s[j].top()>v[pos]) choose.push_back(j);
		if (choose.size()==0) {
			return false;
		}
		position=choose[rand()%choose.size()];
		result.push_back(position);
		s[position].push(v[pos]);
		tryToMove();
	}
	if (currentPiece==n+1) {
		printf("TAK\n");
		for(int i=0;i<n;i++) printf("%d ",result[i]+1);
		printf("\n");
		return 1;
	}
	return 0;
}

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&v[i]);
	bool solved=false;
	for(int attempt=0;(attempt<1000 && !solved);attempt++) {
		srand(attempt);
		solved=tryToSolve();
	}
	if (!solved) printf("NIE\n");
	return 0;
}

