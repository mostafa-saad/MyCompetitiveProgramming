/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kurs szybkiego czytania                            *
 *   Zlozonosc czasowa:    O(m log m)                                         *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         bledne zalozenie, ze istnieje 1 przedzial          *
 *                                                                            *
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
int n, a, b, p, m;

bool jest_srodek = false;
int lewa = -1, prawa = 1e9 + 5;
pair<int, int> srodek;

void dorzuc_zly_przedzial(int low, int high) {
	if(high >= n) {
		dorzuc_zly_przedzial(0, high % n);
		high = n-1;
	}
	if(low == 0) lewa = max(lewa, high);
	else if(high == n - 1) prawa = min(prawa, low);
	else {
		if(jest_srodek) {
			srodek.first = min(srodek.first, low);
			srodek.second = max(srodek.second, high);
		}
		else {
			jest_srodek = true;
			srodek = make_pair(low, high);
		}
	}
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
	
	// [0, lewa] plus 'srodek' plus [prawa, n-1]
	if(jest_srodek && srodek.first <= lewa) {
		jest_srodek = false;
		lewa = max(lewa, srodek.second);
	}
	if(jest_srodek && srodek.second >= prawa) {
		jest_srodek = false;
		prawa = min(prawa, srodek.first);
	}
	if(lewa >= prawa) {
		lewa = n - 1;
		prawa = n + 5;
	}
	int res = max(0, lewa + 1) + max(0, n - prawa);
	if(jest_srodek) res += srodek.second - srodek.first + 1;
	res = n - res;
	for(int i = n - m + 1; i < n; ++i) {
		bool odejmij = false;
		int gdzie = int((ll)a*i%n);
		if(lewa >= gdzie || prawa <= gdzie) odejmij = true;
		if(jest_srodek && srodek.first <= gdzie && gdzie <= srodek.second) odejmij = true;
		if(!odejmij) res--;
	}
	
	printf("%d\n", res);
	
	return 0;
}
