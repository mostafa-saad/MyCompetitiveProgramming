/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski, Jan Kanty Milczek               *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie bledne, znajdujemy najdluzszy        *
 *                      prefikso-sufiks, odcinamy go i czynnosc          *
 *                      powtarzamy                                       *
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

string readString() {
	scanf("%s", buf);
	return buf;
}

int calc(string word) {
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
	return p.back();
}

int main() {
	scanf("%d", &n);
	word = readString();
	int a = calc(word);
	int b = calc(word.substr(a, n - 2*a));
	printf("%d\n", a+b);
}
