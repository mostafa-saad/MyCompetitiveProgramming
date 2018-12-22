#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <ctime>
using namespace std;
typedef long long llint;

int n;
int a[300100];
int prim[2000100];

int tmp[50000];
int size;

void find_divisors(int x){
    size = 1; tmp[0] = 1;
    while(x > 1){
        int p = prim[x];
        int power = 0;
        for(; x > 1 && prim[x] == p; x /= p)
            ++power;
            
        for(int i = size; i < size * (power + 1); ++i)           
            tmp[i] = tmp[i - size] * p;
            
        size = size * (power + 1);
    }   
}

int num_divisible[2000100];

int main(void){
    float f = clock();
    for(int i = 2; i <= 2000000; ++i)
        if(prim[i] == 0){
            for(int j = 1; j * i <= 2000000; ++j)
                if(prim[i * j] == 0)
                    prim[i * j] = i;   
        }
    
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
        find_divisors(a[i]);

        for(int j = 0; j < size; ++j)
            ++num_divisible[tmp[j]];
    }
    
    llint sol = 0;
    
    for(int i = 1; i <= 2000000; ++i)
        if(num_divisible[i] > 1) sol = max(sol, (llint)num_divisible[i] * i);

    printf("%lld\n", sol);
//    printf("vrijeme: %.3lf\n", (clock() - f) / CLOCKS_PER_SEC);
return 0;
}
