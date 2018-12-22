#include <cstdio>

using namespace std;

const int MAXN = 110;

int x, n;
int a[MAXN];

int main() {

    scanf("%d%d", &x, &n);

    int sum = 0;
    for(int i=0; i<n; i++){
        scanf("%d", a+i);
        sum += a[i];
    }

    printf("%d\n", x * (n + 1) - sum);
    
    return 0;
}
