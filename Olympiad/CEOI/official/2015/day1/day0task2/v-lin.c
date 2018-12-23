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

	unsigned long long intersum = k;
	int offset = 0;

	for(int i = 1; i < n; i ++) {
		offset = (offset - 1 + l) % l;
		unsigned long long tmp = intersum;
		intersum = intersum + MODULO - counts[offset];
		intersum += counts[offset] = (tmp * (k - 1)) % MODULO;
		intersum %= MODULO;
	}

	if(!n)
		intersum = 1;
	printf("%llu\n", intersum);

	return 0;
}
