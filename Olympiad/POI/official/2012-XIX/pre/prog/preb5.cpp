/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Jan Kanty Milczek                                *
 *   Opis:              Rozwiazanie bledne, sprawdzajace limit() = 1     *
 *                      najdluzszych prefikso-sufiksow i odcinajace je   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

const int MAX_LEN = 1000005;

int n;
char buf[MAX_LEN];
string word;

int limit() {
	return 1;
}

string readString() {
	scanf("%s", buf);
	return buf;
}

int calc(string word) {
	vector<int> p;
	p.push_back(0);
	int k=0;
	for (int i=1; i<(int)word.size(); ++i) {
		while (k && word[i] != word[k]) k = p[k-1];
		if (word[i] == word[k]) ++k;
		p.push_back(k);
	}
	return p.back();
}

int calc2(string word) {
	if (word.length() % 2)
		word[word.length() / 2] = '#';
	else {
		word = word.substr(0, word.length() / 2) + "#$" + word.substr(word.length() / 2, word.length() / 2);
	}
	vector<int> p;
	p.push_back(0);
	int k=0;
	for (int i=1; i<(int)word.size(); ++i) {
		while (k && word[i] != word[k]) k = p[k-1];
		if (word[i] == word[k]) ++k;
		p.push_back(k);
	}
	k = p.size() - 1;
	int mx = 0, licz = 0;
	while (p[k] && licz < limit()) {
		mx = max(mx, p[k] + calc(word.substr(p[k], word.length() - 2 * p[k])));
		k = p[k - 1];
		++licz;
	}
	return mx;
}

int main() {
	scanf("%d", &n);
	word = readString();
	printf("%d\n", calc2(word));
}
