/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kurs szybkiego czytania                            *
 *   Zlozonosc czasowa:    O(m log m)                                         *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie bledne                                 *
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

const pii PUSTY = make_pair(-1, -1), START = make_pair(-2, -2);
pii PRZE = START;

ll n;

void dodaj_byc_moze_zawiniety_przedzial(int a, int b) {
	if(PRZE == START) {
		PRZE = make_pair(a, b);
		return;
	}
	if(PRZE == PUSTY)
		return;
	if(PRZE.first <= a && a <= PRZE.second)
		PRZE = make_pair(a, min(PRZE.second, b));
	else if(PRZE.first <= a+(int)n && a+(int)n <= PRZE.second)
		PRZE = make_pair(a+(int)n, min(PRZE.second, b+(int)n));
	else if(a <= PRZE.first && PRZE.first <= b)
		PRZE = make_pair(PRZE.first, min(PRZE.second, b));
	else if(a <= PRZE.first+(int)n && PRZE.first+(int)n <= b)
		PRZE = make_pair(PRZE.first+(int)n, min(PRZE.second+(int)n, b));
	else
		PRZE = PUSTY;
	if(PRZE.first > PRZE.second)
		PRZE = PUSTY;
	if(PRZE.first >= n) {
		PRZE.first -= n;
		PRZE.second -= n;
	}
}

bool nalezy(int a) {
	return (PRZE.first <= a && a <= PRZE.second) ||
			(PRZE.first <= a+n && a+n <= PRZE.second);
}

ll a, b, p;
int m;
char wzorzec[MAX_M];

int main() {
	scanf("%lld%lld%lld%lld", &n, &a, &b, &p);
	
	scanf("%d%s", &m, wzorzec);
	
	for(int i = 0; i < m; ++i) {
		ll low = - (a * i) % n - b;
		while(low < 0LL) low += n;
		if(wzorzec[i] == '0') {
			dodaj_byc_moze_zawiniety_przedzial(low, low + p - 1);
		}
		else {
			low = (low + p) % n;
			dodaj_byc_moze_zawiniety_przedzial(low, low + n - p - 1);
		}
	}
	
	if(PRZE == PUSTY) {
		puts("0");
		return 0;
	}
	
	int res = PRZE.second - PRZE.first + 1;
	
	for(int i = n - m + 1; i < n; ++i)
		if(nalezy(a * i % n))
			--res;
	
	printf("%d\n", res);
	
	return 0;
}
	
