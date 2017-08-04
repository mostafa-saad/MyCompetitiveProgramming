//Mostafa Saad sieve with bits, learned from TODO

inline bool isprime_bitMasking(int n) {
    if(n == 2)				return true;
    if(n < 1 || n%2 == 0)	return 0;
    return (prime[n>>4] & ( 1<<( (n>>1) &7 ) ) )!= 0;
}

const int MAX = 100000000+9;
char prime[MAX/16+2];
// each 8 bit represent 8 odd numbers
void sieve_bitMasking() {
	memset(prime, -1, sizeof(prime));

	prime[0] = -2; // 1 is not prime number
	for (ll i = 1; 4 * i * i <= MAX; i++)
		if (prime[i >> 3] & (1 << (i & 7)))
			for (int j = 3 * i + 1; 2 * j < MAX; j += 2 * i + 1)
				prime[j >> 3] &= ~(1 << (j & 7));

	isPrime[2] = 1;
	for (ll i = 1; 2 * i <= MAX; i++)
		if (prime[i >> 3] & (1 << (i & 7)))
			isPrime[2 * i + 1] = 1;
}

