#include <cstdio>
#include <cstring>

using namespace std;

int n, w[30], ans;

void rek(int pos, int mask) {
	if(pos == n) {
		if(mask == (1 << 26) - 1)	++ans; 
		// provjeravamo sastoji li se bitmaska 
		// trenutnog skupa od samih jedinica
		return;
	}
	rek(pos + 1, mask | w[pos]); // ukljucit cemo ovaj skup 
	rek(pos + 1, mask);					 // iskljucit cemo ovaj skup
}

int main(void) {

	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		char tmp[110]; scanf("%s", tmp);
		int l = strlen(tmp);
		for(int j = 0; j < l; ++j)
			w[i] |= 1 << tmp[j] - 'a'; 
			// gradimo bitmasku za svaku rijec
	}

	rek(0, 0);

	printf("%d\n", ans);

	return 0;

}
