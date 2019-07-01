/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Modernizacja autostrady                            *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/



#include<cstdio>
#include<algorithm>
#include<vector>
#include<assert.h>
#include<set>
using namespace std;
typedef pair<int, int> pii;
const int nax = 5e5 + 5;
int n;
#define maxi(a,b) a = max(a, b)
const int MAGIC = 3; // maksymalna dopuszczalna licznosc seta

struct V {
	int pod, sre_pod, nad, sre_nad, ojc, id, dal, h;
	bool vis;
};
V v[nax];
vector<int> w[nax];

int suma(multiset<int> & s, int ile, int rozneOd) {
	int res = 0;
	for(multiset<int> :: iterator it = s.end(); ile > 0; --ile) {
		if(it == s.begin()) return -nax;
		--it;
		if(*it == rozneOd) {
			++ile;
			rozneOd = -1; // niewystepujaca wartosc
		}
		else res += *it;
	}
	return res;
}
int suma(multiset<int> & s, int ile) { return suma(s, ile, -1); }

void ins(multiset<int> & s, int a) {
	s.insert(a);
	if((int) s.size() > MAGIC) s.erase(s.begin());
}
#define insert NIE_SKOMPILUJE_SIE

void wDol(V & a) {
	multiset<int> pody;
	a.vis = true;
	a.pod = a.sre_pod = 0;
	for(int i = 0; i < (int) w[a.id].size(); ++i) {
		V & b = v[w[a.id][i]];
		if(b.vis) continue;
		b.ojc = a.id;
		wDol(b);
		maxi(a.sre_pod, b.sre_pod);
		maxi(a.pod, b.pod + 1);
		ins(pody, b.pod);
	}
	maxi(a.sre_pod, suma(pody, 2) + 2);
	maxi(a.sre_pod, a.pod);
}

void wGore(V & a) {
	a.vis = true;
	multiset<int> pody, srepody;
	for(int i = 0; i < (int) w[a.id].size(); ++i) {
		V & b = v[w[a.id][i]];
		if(b.vis) continue;
		ins(pody, b.pod);
		ins(srepody, b.sre_pod);
	}
	for(int i = 0; i < (int) w[a.id].size(); ++i) {
		V & b = v[w[a.id][i]];
		if(b.vis) continue;
		b.nad = max(a.nad + 1, suma(pody, 1, b.pod) + 2);
		b.sre_nad = max(a.sre_nad, suma(pody, 2, b.pod) + 2);
		maxi(b.sre_nad, a.nad + max(0, 1 + suma(pody, 1, b.pod)));
		maxi(b.sre_nad, suma(srepody, 1, b.sre_pod));
	}
	for(int i = 0; i < (int) w[a.id].size(); ++i) {
		V & b = v[w[a.id][i]];
		if(!b.vis) wGore(b);
	}
}

int RES;
pii krance;
void krancuj(V & a) {
	a.vis = true;
	a.dal = a.id; // najdalszy wierzcholek w poddrzewie
	/* wyjatkowo do pamietania 2 najlepszych nie uzyje seta,
			bo trzymam wierzcholki zamiast samych wartosci */
	int raz = a.id, dwa = a.id;
	for(int i = 0; i < (int) w[a.id].size(); ++i) {
		V & b = v[w[a.id][i]];
		if(b.vis) continue;
		b.h = a.h + 1;
		krancuj(b);
		V & pom = v[b.dal];
		if(v[a.dal].h < pom.h)
			a.dal = pom.id;
		if(pom.h > v[raz].h) {
			dwa = raz;
			raz = pom.id;
		}
		else if(pom.h > v[dwa].h) dwa = pom.id;
	}
	int r = v[raz].h + v[dwa].h - 2 * a.h;
	if(r >= RES) {
		RES = r;
		krance = make_pair(raz, dwa);
	}
}

int maksuj(int i) {
	int a = v[i].sre_pod, b = v[i].sre_nad;
	return a + b + 1;
}
int minuj(int i) {
	int a = v[i].sre_pod, b = v[i].sre_nad;
	return max((a+1)/2 + (b+1)/2 + 1, max(a,b));
}

void pomdfs(int a) {
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(v[a].ojc != b) {
			v[b].ojc = a;
			pomdfs(b);
		}
	}
}
int srodek(pii p) {
	int a = p.first, b = p.second;
	v[a].ojc = 0;
	pomdfs(a);
	int d = 0;
	for(int x = b; x != a; x = v[x].ojc) ++d;
	for(int i = 0; i < d / 2; ++i) b = v[b].ojc;
	return b;
}

void przetnij(int id, bool czyMaksujemy) {
	V & a = v[id];
	V & b = v[a.ojc];
	for(int i = 1; i <= n; ++i) v[i].vis = false;
	a.h = b.h = 0;
	a.vis = true;
	RES = 0;
	krancuj(b);
	pii sre1 = krance;
	a.vis = false;
	assert(b.vis);
	RES = 0;
	krancuj(a);
	pii sre2 = krance;
	printf("%d %d ", a.id, b.id);
	if(czyMaksujemy)
		printf("%d %d\n", sre1.first, sre2.first);
	else
		printf("%d %d\n", srodek(sre1), srodek(sre2));
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) v[i].id = i;
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		w[a].push_back(b);
		w[b].push_back(a);
	}
	wDol(v[1]); // przy okazji liczy ojcow
	for(int i = 1; i <= n; ++i) v[i].vis = false;
	wGore(v[1]);
	int maly = 2, duzy = 2;
	for(int i = 3; i <= n; ++i) {
		if(maksuj(i) > maksuj(duzy)) duzy = i;
		if(minuj(i) < minuj(maly)) maly = i;
	}
	int memo_ojciec = v[duzy].ojc;
	printf("%d ", minuj(maly));
	przetnij(maly, false);
	v[duzy].ojc = memo_ojciec;
	printf("%d ", maksuj(duzy));
	przetnij(duzy, true);
	return 0;
}
