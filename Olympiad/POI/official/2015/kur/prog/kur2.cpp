/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kurs szybkiego czytania                            *
 *   Zlozonosc czasowa:    O(m log m)                                         *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                         trzymanie dopelnien przedzialow w secie            *
 *                                                                            *
 *****************************************************************************/


#include<cstdio>
#include<algorithm>
#include<assert.h>
#include<set>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAX_M = 1e6 + 5;

ll n, a, b, p;
int m;
char wzorzec[MAX_M];
set<pii > prze;

void dodaj_przedzial(int a, int b) {
	assert(a <= b);
	pii p = make_pair(a, b);
	set<pii > :: iterator it, it2;
	it = prze.insert(p).first;
	for(int iteracja = 0; iteracja < 2; ++iteracja) {
		it2 = it;
		pii p2;
		if(iteracja == 0) p2 = *(++it2);
		else {
			p2 = *(--it2);
			swap(p, p2);
		}
		if(p.second >= p2.first - 1) {
			prze.erase(it);
			prze.erase(it2);
			p = make_pair(min(p.first,p2.first), max(p.second,p2.second));
			it = prze.insert(p).first;
		}
	}
}

void dodaj_byc_moze_zawiniety_przedzial(int a, int b) {
	if(b >= (int) n) {
		dodaj_przedzial(a, n-1);
		dodaj_przedzial(0, b - n);
	}
	else
		dodaj_przedzial(a, b);
}

bool nalezy(int a) {
	set<pii > :: iterator it = prze.lower_bound(make_pair(a + 1, a + 1));
	--it;
	return (*it).first <= a && a <= (*it).second;
}

int main() {
	scanf("%lld%lld%lld%lld", &n, &a, &b, &p);
	
	// drobny hack dla latwiejszej implementacji
	prze.insert(make_pair(-3, -3));
	prze.insert(make_pair((int) n + 3, (int) n + 3));
	
	scanf("%d%s", &m, wzorzec);
	
	for(int i = 0; i < m; ++i) {
		ll low = - (a * i) % n - b;
		while(low < 0LL) low += n;
		if(wzorzec[i] == '0') {
			low = (low + p) % n;
			dodaj_byc_moze_zawiniety_przedzial(low, low + n - p - 1);
		}
		else
			dodaj_byc_moze_zawiniety_przedzial(low, low + p - 1);
	}
	
	int res = n + 2; // +2 z powodu hacka
	for(set<pii> :: iterator it = prze.begin(); it != prze.end(); ++it)
		res -= (*it).second - (*it).first + 1;
	
	for(int i = n - m + 1; i < n; ++i)
		if(!nalezy(a * i % n))
			--res;
	
	printf("%d\n", res);
	
	return 0;
}
	
