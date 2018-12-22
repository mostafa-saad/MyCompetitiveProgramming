#include <cstdio>
#include <cstring>

using namespace std;

char broj[100005];

bool ima_nulu = false;

int sum;
int cnt[10];

int main(void) {

    scanf("%s", broj); int len = strlen(broj);
    for (int i = 0; i < len; ++i) {
        sum += broj[i] - '0';
        ima_nulu = ima_nulu || broj[i] == '0';
        ++cnt[broj[i] - '0'];
    }

    if (!ima_nulu || sum % 3 != 0) {
        printf("-1\n");
    } else {
        for (int i = 9; i >= 0; --i) {
            for (int j = 0; j < cnt[i]; ++j) printf("%d", i);
        }
        printf("\n");
    }

    return 0;

}
