#include <cstdio>

using namespace std;

int k, v[1024];

int main(void) {

	scanf("%d", &k);
	for(int i = 1; i <= (1 << k) - 1; ++i)
		scanf("%d", v + i);

	int pocetni = 1 << k - 1, razmak = 1 << k, broj = 1;
	while(pocetni > 0)  {
		for(int j = 0; j < broj; ++j)
			printf("%d ", v[pocetni + j * razmak]);
		printf("\n");
		broj *= 2;
		pocetni /= 2;
		razmak /= 2;
	}

	return 0;

}
