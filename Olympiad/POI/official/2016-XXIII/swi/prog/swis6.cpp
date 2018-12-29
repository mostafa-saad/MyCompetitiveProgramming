/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O((n + m) * sqrt(n))                               *
 *   Zlozonosc pamieciowa: O(m * sqrt(n) + n)                                 *
 *   Opis:                 Rozwiazanie srednio-szybkie                        *
 *****************************************************************************/


#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

constexpr int wyszukaj_podloge_z_pierwiastka(int a, int b, int x) {
	return a == b ? a :
			((((long long) a + b + 1) / 2) * ((a + b + 1) / 2) <= x)
					? wyszukaj_podloge_z_pierwiastka((a + b + 1) / 2, b, x)
					: wyszukaj_podloge_z_pierwiastka(a, (a + b + 1) / 2 - 1, x);
}

constexpr int podloga_z_pierwiastka(int x) {
	return wyszukaj_podloge_z_pierwiastka(0, x, x);
}

template<int max_elements>
struct Graf {
	vector<int> graf[max_elements + 5];
	bool odwiedzone[max_elements + 5];
	int id[max_elements + 5];
	void polacz(int a, int b) {
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	void dfs(int w, int identyfikator) {
		if (not odwiedzone[w]) {
			odwiedzone[w] = true;
			id[w] = identyfikator;
			for (int sasiad : graf[w])
				dfs(sasiad, identyfikator);
		}
	}
	void pusc_dfsa() {
		for (int i = 0; i < max_elements; i++)
			dfs(i, i);
	}
};

constexpr int limit = 500 * 1000;
constexpr int limit_pierwiastek = podloga_z_pierwiastka(limit) + 5;

int nwd(int a, int b) {
	if (a == 0)
		return b;
	return nwd(b % a, a);
}

vector<pair<int, int>> cale[limit_pierwiastek][limit_pierwiastek];

int n, m;
int p;  // długość pierwiastkowego przedziału
int d;  // liczba pierwiastkowych przedziałów

Graf<limit + limit_pierwiastek * 3 + 5> graf;

void dodaj_mini_wymaganie(int a, int b, int l) {
	if ((a % p == 0 or b % p == 0) and ((a + l) % p == 0 or (b + l) % p == 0))
		cale[a / p][b / p].emplace_back(a % p, b % p);
	else for (int i = 0; i < l; i++)
		graf.polacz(a + i, b + i);
}

void dodaj_wymaganie(int a, int b, int l) {
	while (l > 0) {
		const int mini_l = min(l, min(p - (a % p), p - (b % p)));
		dodaj_mini_wymaganie(a, b, mini_l);
		a += mini_l;
		b += mini_l;
		l -= mini_l;
	}
}

bool kubelki[limit_pierwiastek + 5];

void posortuj_prefikso_sufiksy(vector<int> & prefikso_sufiksy) {
	for (int ps : prefikso_sufiksy)
		kubelki[ps] = true;
	prefikso_sufiksy.clear();
	for (int i = 1; i <= p; i++) {
		if (kubelki[i]) {
			prefikso_sufiksy.push_back(i);
			kubelki[i] = false;
		}
	}
}

void ogarnij_trojkat(vector<int> & prefikso_sufiksy, std::function<void(int, int)> polacz) {
	posortuj_prefikso_sufiksy(prefikso_sufiksy);
	int dlugosc = 2 * p;
	auto spaluj_prefikso_sufiks = [&dlugosc, &polacz](int ps) {
		for (int i = 0; i < ps; i++)
			polacz(i, dlugosc - ps + i);
	};
	while (not prefikso_sufiksy.empty()) {
		const int ost = prefikso_sufiksy.back();
		prefikso_sufiksy.pop_back();
		if (ost * 2 <= dlugosc) {
			spaluj_prefikso_sufiks(ost);
			dlugosc = ost;
		} else if (not prefikso_sufiksy.empty() and prefikso_sufiksy.back() * 2 > dlugosc) {
			const int ost2 = prefikso_sufiksy.back();
			prefikso_sufiksy.pop_back();
			prefikso_sufiksy.push_back(dlugosc - nwd(dlugosc - ost, dlugosc - ost2));
		} else {
			spaluj_prefikso_sufiks(ost);
		}
	}
}

void ogarnij_kwadrat(int a, int b) {
	bool a_najpierw = true;
	auto polacz = [a, b, &a_najpierw](int u, int v) {
		auto zamien_na_tamto = [a, b, &a_najpierw](int w) -> int {
			const bool czesc_pierwsza = w < p;
			if (not czesc_pierwsza)
				w -= p;
			if (a_najpierw == czesc_pierwsza)
				return a * p + w;
			return b * p + w;
		};
		graf.polacz(zamien_na_tamto(u), zamien_na_tamto(v));
	};
	std::vector<int> ps_a_najpierw, ps_b_najpierw;
	for (const auto& wsp : cale[a][b]) {
		if (wsp.first == 0)
			ps_a_najpierw.push_back(p - wsp.second);
		else  // p.second == 0
			ps_b_najpierw.push_back(p - wsp.first);
	}
	ogarnij_trojkat(ps_a_najpierw, polacz);
	a_najpierw = false;
	ogarnij_trojkat(ps_b_najpierw, polacz);
}

int main() {
	scanf("%d%d", &n, &m);
	for (p = 1; p * p < n; p++)
		continue;
	d = (n + p - 1) / p;
	while (m--) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		a--; b--;
		dodaj_wymaganie(a, b, l);
	}
	for (int i = 0; i < d; i++)
		for (int j = 0; j < d; j++)
			ogarnij_kwadrat(i, j);
	graf.pusc_dfsa();
	int wynik = 0;
	for (int i = 0; i < n; i++)
		if (graf.id[i] == i)
			wynik++;
	printf("%d\n", wynik);
	return 0;
}
