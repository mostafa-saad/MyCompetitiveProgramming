#include<cstdio>
using namespace std;

int a[1000001];

int main()
{
    int n; scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", a+i);
    int last = n;
    for(int i=n-1; i>=0; i--) if(a[i] == last) last--;
    printf("%d\n", last);
    return 0;
}
