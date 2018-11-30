// O(n^2)

#include <cstdio>
#include <vector>
using namespace std;

struct op {
	int poz;
	int wsk;
	bool aktyw;
	op(int edy) {
		if (edy < 0)
			poz = -edy;
		else
			wsk = edy, poz = 0;
		aktyw = false;
	}
};

vector<op> oper;

void aktywuj(int);
void dezaktywuj(int);

void aktywuj(int x) {
	oper[x].aktyw = true;
	if (oper[x].poz > 0) {
		int i = x - 1;
		while (oper[i].poz >= oper[x].poz || !oper[i].aktyw)
			--i;
		oper[x].wsk = i;
		dezaktywuj(i);
	}
}

void dezaktywuj(int x) {
	oper[x].aktyw = false;
	if (oper[x].poz > 0)
		aktywuj(oper[x].wsk);
}

int wynik() {
	for (int i = oper.size() - 1; i >= 0; --i)
		if (oper[i].poz == 0 && oper[i].aktyw)
			return oper[i].wsk;
	return 0;
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int edy;
		scanf("%d", &edy);
		oper.push_back(op(edy));
		aktywuj(i);
		printf("%d\n", wynik());
	}
}
