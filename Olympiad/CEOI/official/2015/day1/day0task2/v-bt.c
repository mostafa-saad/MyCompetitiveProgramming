#include <stdio.h>

void cnt(int data[], int n, int l, int k, long long unsigned *sum, int count) {
	if(count >= l) {
		for(int i = count - l; i < count - 1; i ++)
			if(data[i] != data[count - 1])
				goto OK;
		return;
	}
	OK:
	if(count == n)
		(*sum) ++;
	else {
		for(int i = 0; i < k; i ++) {
			data[count] = i;
			cnt(data, n, l, k, sum, count + 1);
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *in = stdin;
	int n, l, k;
	fscanf(in, "%d %d %d", &n, &l, &k);

	int data[n];
	long long unsigned sum = 0;

	cnt(data, n, l, k, &sum, 0);

	FILE *out = stdout;
	fprintf(out, "%llu\n", sum);
	return 0;
}
