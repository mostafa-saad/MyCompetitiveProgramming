#include <cstdio>
#include <cstring>

using namespace std;

int N;
char sol[21];

int main(void) {

    scanf("%d", &N);
    for (int i = 0; i < 2 * N - 1; ++i) {
        char s[21];
        scanf("%s", s); int len = strlen(s);
        for (int j = 0; j < len; ++j) sol[j] ^= s[j];
    }

    printf("%s\n", sol);

    return 0;

}
