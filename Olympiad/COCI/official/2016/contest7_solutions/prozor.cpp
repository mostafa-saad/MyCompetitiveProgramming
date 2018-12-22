#include <cstdio>

using namespace std;

char prozor[101][101];

int R, S, K;

int main(void) {
    
    scanf("%d%d%d", &R, &S, &K);
    for (int i = 0; i < R; ++i)
        scanf("%s", prozor[i]);

    int max_muhe = -1;
    int a, b; 

    for (int r = 1; r < R - 1; ++r) {
        for (int s = 1; s < S - 1; ++s) {
            
            int muhe = 0;
            if (r + K - 2 >= R || s + K - 2 >= S) 
                continue;

            for (int i = 0; i < K - 2; ++i)
                for (int j = 0; j < K - 2; ++j)
                    if (prozor[r + i][s + j] == '*')
                        ++muhe; 
            
            if (muhe > max_muhe) {
                max_muhe = muhe;
                a = r - 1; b = s - 1;
            }

        }
    }
    
    for (int i = 0; i < K; ++i) {
        prozor[a + i][b] = prozor[a + i][b + K - 1] = '|';
        prozor[a][b + i] = prozor[a + K - 1][b + i] = '-';
    }

    prozor[a][b] = prozor[a + K - 1][b] = '+';
    prozor[a][b + K - 1] = prozor[a + K - 1][b + K - 1] = '+';
    
    printf("%d\n", max_muhe);
    for (int i = 0; i < R; ++i)
        printf("%s\n", prozor[i]);

    return 0;

}
