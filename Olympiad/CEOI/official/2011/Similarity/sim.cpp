/* CEOI 2011
 * TASK: SIM (Similarity)
 * AUTHOR: Karol Pokorski
 * Optimal, correct solution
 */

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int LL;

const int MAXLEN = 2000002;
const int MAXALPH = 26;

int numLett[MAXALPH], lenPattern, lenText;
char pattern[MAXLEN], text[MAXLEN];

int main() {
	LL result = 0;

	int ret = scanf("%s%s", pattern, text);
	if (ret < 0) return 1;

	lenPattern = strlen(pattern);
	lenText = strlen(text);

	for (int i = 0; i < lenText; i++) {
		// we have to consider one more position of pattern (this letter of pattern can be under this letter of text)
		if (i < lenPattern)
			numLett[pattern[i]-'a']++;

		result += (LL)numLett[text[i]-'a']; // increase result by number of letters which can be under this letter of text

		// the pattern must fit within text - if not, do not consider this position of pattern
		if (lenPattern-lenText+i >= 0)
			numLett[pattern[lenPattern-lenText+i]-'a']--;
	}

	printf("%lld\n", result);

	return 0;
}
