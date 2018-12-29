/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:             Antysymetria (ANT)                             *
 *   Plik:                ant2.cpp                                       *
 *   Autor:               Wojciech Tyczynski                             *
 *   Opis:                Rozwiazanie alternatywne                       *
 *   Zlożonosc czasowa:   O(n)                                           *
 *   Zlożonosc pamiecowa: M(n)                                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

#define MAX_N 500000

int n;
int r[MAX_N];
char slowo[MAX_N+15];


void palindromy(const string &s) {
	int n=s.size();
	int i=1,j=0,k;
	while (i<n) {
		while (i+j<n && i-j>0 && s[i-j-1]!=s[i+j]) j++;
		r[i]=j,k=1;
		while (i+k<n && r[i-k]!=r[i]-k && k<=j)
			r[i+k]=min(r[i-k],r[i]-k),k++;
		j=max(0,j-k),i+=k;
	}
}


int main() {
	scanf("%d",&n);
	scanf("%s",slowo);

	string s=slowo;
	palindromy(s);

/*	for(int i=0; i<n; i++)
		printf("%d ",r[i]);
	printf("\n");*/

	long long result=0LL;
	for (int i=0; i<n; i++)
		result+=r[i];

	printf("%lld\n",result);
	return 0;
}
