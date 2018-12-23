#include <stdio.h>

#define MODULO 4000000009LLU

int main(int argc, char *argv[]) {
	int n, l, k;
	scanf("%d %d %d", &n, &l, &k);

	l --;

	// Init, k posloupností délky 1
	unsigned long long counts[l];
	for(int i = 0; i < l; i ++) {
		counts[i] = 0;
	}
	counts[0] = k;

	for(int i = 1; i < n; i ++) {
		unsigned long long newsingle = counts[0];
		for(int j = l - 1; j > 0; j --) {
			newsingle += counts[j];
			counts[j] = counts[j - 1];
		}
		counts[0] = newsingle * (k - 1);
		counts[0] %= MODULO;
	}

	unsigned long long sum = 0;
	for(int i = 0; i < l; i ++)
		sum += counts[i];
	if(!n)
		sum = 1;
	printf("%llu\n", sum % MODULO);

	return 0;
}
