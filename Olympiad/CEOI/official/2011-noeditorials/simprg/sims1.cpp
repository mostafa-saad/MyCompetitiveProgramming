/* CEOI 2011
 * TASK: SIM (Similarity)
 * AUTHOR: Karol Pokorski
 * Correct, but slow solution
 */

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int LL;

const int MAXLEN = 1000002;

int lenPattern, lenText;
char pattern[MAXLEN], text[MAXLEN];

int main() {
	LL result = 0;

	int ret = scanf("%s%s", pattern, text);
	if (ret < 0) return 1;

	lenPattern = strlen(pattern);
	lenText = strlen(text);

	// we try every valid position of pattern under text
	for (int i = 0; i < lenText-lenPattern+1; i++) {
		for (int j = 0; j < lenPattern; j++) // we simply check equality of letters like in an example
			if (pattern[j] == text[i+j])
				result++;
	}

	printf("%lld\n", result);

	return 0;
}
