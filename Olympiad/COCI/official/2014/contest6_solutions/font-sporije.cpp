#include <cstdio>
#include <string>

using namespace std;

int n, odg;
string s[25];

int ukupno;
int ima[26];

void rek(int pos) {
	if(pos == n) {
		odg += ukupno == 26;
		return;
	}

	for(int i = 0; i < s[pos].size(); ++i) {
		++ima[s[pos][i] - 'a'];
		if(ima[s[pos][i] - 'a'] == 1) ++ukupno;
	}

	rek(pos + 1);

	for(int i = 0; i < s[pos].size(); ++i) {
		--ima[s[pos][i] - 'a'];
		if(ima[s[pos][i] - 'a'] == 0) --ukupno;
	}

	rek(pos + 1);

}

int main(void) {

	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		char tmp[110]; scanf("%s", tmp);
		s[i] = tmp;
	}

	rek(0);

	printf("%d\n", odg);

	return 0;

}
