#include <cstdio>

using namespace std;

int Q, curr_letter = 25, direction = 1;
int cnt[30];

void update_cnt(int _n) {
    for (int i = 0; i < 26; ++i) 
        cnt[i] += _n / 26;
    _n %= 26;
    for (int i = 0; i < _n; ++i) {
        curr_letter = (curr_letter + direction + 26) % 26;
        ++cnt[curr_letter];
    }
}

int main(void) {

    scanf("%d", &Q);

    int last_update = 0;
    for (int i = 0; i < Q; ++i) {
        
        char type[10];
        int n;

        scanf("%s%d", type, &n);
        
        update_cnt(n - last_update);
        last_update = n; 
        
        if (type[0] == 'S') {
            direction *= -1;
        } else {
            char s[2];
            scanf("%s", s);
            printf("%d\n", cnt[s[0] - 'a']);
        }

    }

    return 0;

}
