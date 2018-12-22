#include <algorithm>
#include <cstdio>

#define MAXN 1001

using namespace std;

int N, X;
int age[MAXN], filled[MAXN];

int main(void) {

    scanf("%d%d", &N, &X);
    for (int i = 0; i < N; ++i) 
        scanf("%d%d", &age[i], &filled[i]);

    int sol = 0;
    for (int i = 1; i < N; ++i) {
        if (filled[i] != filled[i - 1]) {
            if (filled[i] && age[i] > age[i - 1] || filled[i - 1] && age[i - 1] > age[i]) {
                swap(age[i], age[i - 1]);
            }
        }
        sol += age[i - 1] <= X && filled[i - 1] || age[i - 1] > X && !filled[i - 1]; 
    }
    
    sol += age[N - 1] <= X && filled[N - 1] || age[N - 1] > X && !filled[N - 1];
    printf("%d\n", sol);

    return 0;

}
