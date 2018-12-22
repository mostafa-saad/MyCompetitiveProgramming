#include <cstdio>
using namespace std;

int optuzio[500005];
int puta_optuzen[500005];
bool rijesen[500005];

int br_mafija = 0;

void rijesi(int x, bool mafija) {
    if (rijesen[x]) return;
    rijesen[x] = 1;
    br_mafija += mafija;
    int y = optuzio[x];
    if (--puta_optuzen[y] == 0 || mafija)
        rijesi(y, !mafija);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", optuzio + i);
        --optuzio[i];
        ++puta_optuzen[optuzio[i]];
    }
    for (int i = 0; i < n; ++i)
        if (puta_optuzen[i] == 0)
            rijesi(i, true);

    for (int i = 0; i < n; ++i)
        rijesi(i, false);

    printf("%d\n", br_mafija);
}
