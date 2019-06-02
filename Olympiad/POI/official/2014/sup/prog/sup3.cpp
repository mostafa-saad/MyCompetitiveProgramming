/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Michal Wlodarczyk                             *
 *   Zlozonosc czasowa:    O(q+n)                                        *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                         Odpowiedz dla k procesorow to                 *
 *              max_{i : s(i) > 0} i + ceil((s(i+1) + s(i+2) + ...) / k) *
 *                                                                       *
 *************************************************************************/

#include<vector>
#include<cstdio>

const int NMAX = 1000001;

struct Function {
	int a, b; // wspolczynniki funkcji ax + b
	int left, right; // przedzial domkniety w ktorym funkcja jest wieksza lub rowna od pozostalych
};

int ceilDiv(const int a, const int b) {
// zwraca wynik dzielenia a/b zaokraglony w gore
	return (a + b - 1) / b;
}

int parent[NMAX], queries[NMAX], depth[NMAX], s[NMAX], answer[NMAX];

int main() {
	int n, q, m;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < q; ++i)
		scanf("%d", &queries[i]);
		
	depth[1] = 1, s[1] = 1, m = 1;
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &parent[i]);
		depth[i] = depth[parent[i]] + 1;
		++s[depth[i]];
		m = std::max(m, depth[i]); // m = wysokosc drzewa
	}
	
	std::vector<Function> fStack; // stos na ktorym trzymamy gorna otoczke przetworzonych funkcji
	int sum = n;
	
	for(int i = 1; i <= n, sum > 0; ++i) {
		sum -= s[i];
		Function f;
		f.a = i, f.b = sum, f.left = 1, f.right = n;
		
		while(!fStack.empty()) {
			Function last = fStack.back();
			int k = ceilDiv(last.b - f.b, f.a - last.a); // miejsce od ktorego f(x) >= last(x)
			if(k <= last.left)
				fStack.pop_back();
			else {
				fStack.back().right = k - 1;
				f.left = k;
				break;
			}
		}
		fStack.push_back(f);
	}
	
	for(int i = 0; i < fStack.size(); ++i)
		for(int k = fStack[i].left; k <= fStack[i].right; ++k)
			answer[k] = fStack[i].a + ceilDiv(fStack[i].b, k);
			
	for(int i = 0; i < q; ++i)
		printf("%d ", queries[i] > n ? m : answer[queries[i]]);
	return 0;
}
