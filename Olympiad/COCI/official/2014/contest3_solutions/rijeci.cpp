#include <cstdio>

using namespace std;

int n;
int a = 1, b = 0;

int main(void) {

	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		int pa = a, pb = b;
		a = pb;
		b = pa + pb;
	}
	
	printf("%d %d\n", a, b);
	
	return 0;

}
