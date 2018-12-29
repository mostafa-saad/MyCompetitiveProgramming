/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kurs szybkiego czytania                            *
 *   Zlozonosc czasowa:    O(m log m)                                         *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                         zastosowanie posortowania                          *
 *                         i dopelnienia sumy dopelnien                       *
 *****************************************************************************/


#include<cstdio>
#include<algorithm>
#include<assert.h>
#include<vector>
using namespace std;
const int MAX_M = 1e6 + 5;
typedef long long ll;
const int POCZATEK = 0, SPECIAL = 1, KONIEC = 2; // kolejnosc wazna do sorta

char slowo[MAX_M];
vector<pair<int, int> > events;
int n, a, b, p, m;

void dorzuc_zly_przedzial(int low, int high) {
	if(high >= n) {
		dorzuc_zly_przedzial(0, high % n);
		high = n-1;
	}
	assert(0 <= low && low < n && 0 <= high && high < n);
	events.push_back(make_pair(low, POCZATEK));
	events.push_back(make_pair(high, KONIEC));
}

int main() {
	scanf("%d%d%d%d%d", &n, &a, &b, &p, &m);
	scanf("%s", slowo);
	//for(int i = 0; i < n; ++i) printf("%d - %d\n", i, int((a*i+b)%n>=p)); puts("");
	for(int i = 0; i < m; ++i) {
		if(slowo[i] == '0') {
			int low = (p -(ll)a * i - b) % (ll)n; // pierwsza zla pozycja
			if(low < 0) low += n;
			int d = n-p; // dlugosc zlego przedzialu
			dorzuc_zly_przedzial(low, low + d - 1);
		}
		else {
			int low = (-(ll)a * i - b) % (ll)n;
			if(low < 0) low += n;
			int d = p;
			dorzuc_zly_przedzial(low, low + d - 1);
		}
	}
	
	for(int i = n - m + 1; i < n; ++i)
		events.push_back(make_pair(int((ll)a*i%n), SPECIAL));
	
	sort(events.begin(), events.end());
	int licznik = 0, wynik = n;
	#define pozycja first
	#define rodzaj second
	
	for(int i = 0; i < (int) events.size(); ++i) {
		if(events[i].rodzaj == POCZATEK) ++licznik;
		else if(events[i].rodzaj == KONIEC) --licznik;
		
		if(licznik == 1 && events[i].rodzaj == POCZATEK)
			--wynik;
		else if(i > 0) if(licznik > 0 || events[i].rodzaj == KONIEC)
			wynik -= events[i].pozycja - events[i-1].pozycja;
		
		if(events[i].rodzaj == SPECIAL && licznik == 0)
			--wynik;
		
		/*if(false && i % 10000 == 0) {
		printf("%d ", events[i].pozycja);
		if(events[i].rodzaj == POCZATEK) printf("POCZ ");
		else if(events[i].rodzaj == KONIEC) printf("KON ");
		else printf("SPEC ");
		printf("   %d\n", wynik); }*/
	}
	printf("%d\n", wynik);
	
	return 0;
}
