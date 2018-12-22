#include <cstdio>
#include <cassert>
#include <string>

using namespace std;

string imena[] = {
	"one", "two", "three", "four", "five",
	"six", "seven", "eight", "nine", "ten",
	"eleven", "twelve", "thirteen", "fourteen",
	"fifteen", "sixteen", "seventeen", "eighteen",
	"nineteen"
};

string desetice[] = {
	"twenty", "thirty", "forty", "fifty",
	"sixty", "seventy", "eighty", "ninety"
};

string stotice[] = {
	"onehundred", "twohundred", "threehundred",
	"fourhundred", "fivehundred", "sixhundred",
	"sevenhundred", "eighthundred", "ninehundred"
};

string daj_ime(int x) {
	if(x == 0) return "";
	if(x < 20) return imena[x - 1];
	if(x < 100) return desetice[x / 10 - 2] + daj_ime(x % 10);
	return stotice[x / 100 - 1] + daj_ime(x % 100);
}

int N;

int main(void) {

	scanf("%d", &N);

	string oblik[20];

	int len = 0;

	for(int i = 0; i < N; ++i) {
		char s[61]; scanf("%s", s);
		oblik[i] = s;
		len += oblik[i].size();
		assert(oblik[i].size() <= 50);
	}

	--len;

	int ans;
	for(ans = 1; ans < 1000; ++ans)
		if(daj_ime(ans).size() + len == ans) break;

	assert(ans != 1000);

	for(int i = 0; i < N; ++i)
		printf("%s ", (oblik[i] == "$") ? daj_ime(ans).c_str() : oblik[i].c_str());

	printf("\n");

	return 0;

}
