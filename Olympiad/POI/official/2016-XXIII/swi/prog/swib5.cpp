/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O((n + m) * sqrt(n) * find_union)                  *
 *   Zlozonosc pamieciowa: O(m * sqrt(n) + n)                                 *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         Uzywa lematu o okresowosci bez zalozen dopoki jest *
 *                         za duzo wymagan w obszarze                         *
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
struct FU {
	int fut[max_elements + 5];
	int fuf(int w) {
		if (fut[w] == w)
			return w;
		return fut[w] = fuf(fut[w]);
	}
	void fuu(int u, int v) {
		fut[fuf(u)] = fuf(v);
	}
};

constexpr int limit = 500 * 1000;
constexpr int ograniczenie_na_liczbe_wymagan_w_obszarze = 8;
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

FU<limit + limit_pierwiastek * 3 + 5> fu;

void dodaj_mini_wymaganie(int a, int b, int l) {
	if ((a % p == 0 or b % p == 0) and ((a + l) % p == 0 or (b + l) % p == 0))
		cale[a / p][b / p].emplace_back(a % p, b % p);
	else for (int i = 0; i < l; i++)
		fu.fuu(a + i, b + i);
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

void ogarnij_trojkat(vector<int> & prefikso_sufiksy, std::function<void(int, int)> fuu) {
	posortuj_prefikso_sufiksy(prefikso_sufiksy);
	const int dlugosc = 2 * p;
	auto spaluj_prefikso_sufiks = [&dlugosc, &fuu](int ps) {
		for (int i = 0; i < ps; i++)
			fuu(i, dlugosc - ps + i);
	};
	while ((int) prefikso_sufiksy.size() > ograniczenie_na_liczbe_wymagan_w_obszarze) {
		int a = prefikso_sufiksy.back();
		prefikso_sufiksy.pop_back();
		int b = prefikso_sufiksy.back();
		prefikso_sufiksy.pop_back();
		prefikso_sufiksy.push_back(dlugosc - nwd(dlugosc - a, dlugosc - b));
	}
	for (int ps : prefikso_sufiksy)
		spaluj_prefikso_sufiks(ps);
}

void ogarnij_kwadrat(int a, int b) {
	bool a_najpierw = true;
	auto polacz_w_fuu = [a, b, &a_najpierw](int u, int v) {
		auto zamien_na_tamto = [a, b, &a_najpierw](int w) -> int {
			const bool czesc_pierwsza = w < p;
			if (not czesc_pierwsza)
				w -= p;
			if (a_najpierw == czesc_pierwsza)
				return a * p + w;
			return b * p + w;
		};
		fu.fuu(zamien_na_tamto(u), zamien_na_tamto(v));
	};
	std::vector<int> ps_a_najpierw, ps_b_najpierw;
	for (const auto& wsp : cale[a][b]) {
		if (wsp.first == 0)
			ps_a_najpierw.push_back(p - wsp.second);
		else  // p.second == 0
			ps_b_najpierw.push_back(p - wsp.first);
	}
	ogarnij_trojkat(ps_a_najpierw, polacz_w_fuu);
	a_najpierw = false;
	ogarnij_trojkat(ps_b_najpierw, polacz_w_fuu);
}

int main() {
	scanf("%d%d", &n, &m);
	for (p = 1; p * p < n; p++)
		continue;
	d = (n + p - 1) / p;
	for (int i = 0; i < n; i++)
		fu.fut[i] = i;
	while (m--) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		a--; b--;
		dodaj_wymaganie(a, b, l);
	}
	for (int i = 0; i < d; i++)
		for (int j = 0; j < d; j++)
			ogarnij_kwadrat(i, j);
	int wynik = 0;
	for (int i = 0; i < n; i++)
		if (fu.fuf(i) == i)
			wynik++;
	printf("%d\n", wynik);
	return 0;
}
