#include <cstdio>

int main(){
	int n;
	scanf("%d", &n);
	
	int sum = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i; j++)
			sum += i + j;

	printf("%d\n", sum);
	return 0;
}
