#include <cstdio>
#include <iostream>

using namespace std;

int N, K, rjesenje;
int a[105];

int main(void){
    scanf("%d", &N);
    for(int i = 0; i < N; i ++) scanf("%d", &a[i]);

    scanf("%d", &K);
    for(int i = 0; i < N; i ++)
        if(a[i] <= K) rjesenje ++;

    printf("%d\n", rjesenje);
return 0;
}
