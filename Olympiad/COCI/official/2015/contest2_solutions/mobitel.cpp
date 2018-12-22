#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

char s[101];
int _switch[11];

string sol; 
string tipka[] = {"2", "22", "222", "3", "33", "333", "4", "44", "444", "5", "55", "555", "6", "66", "666", "7", "77", "777", "7777", "8", "88", "888", "9", "99", "999", "9999"};

int main(void) {

    for (int i = 0; i < 9; ++i) {
        int x; scanf("%d", &x);
        _switch[x] = i + 1;
    }

    scanf("%s", s); int len = strlen(s);

    int last = -1;
    for (int i = 0; i < len; ++i) {
        if (last == tipka[s[i] - 'a'][0] - '0') sol += "#";
        last = tipka[s[i] - 'a'][0] - '0'; sol += tipka[s[i] - 'a'];
    }

    for (int i = 0; i < (int) sol.size(); ++i) {
        if (sol[i] == '#') printf("#"); else printf("%c", '0' + _switch[sol[i] - '0']);
    }

    printf("\n");

    return 0;

}
