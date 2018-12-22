#include <cstdio>
#include <cstring>

using namespace std;

int N, cnt[26];

int main(void) {
	
	scanf("%d", &N);
	
	memset(cnt, 0, sizeof cnt);
	
	for(int i = 0; i < N; ++i) {
		char ime[35]; scanf("%s", ime);
		++cnt[ime[0] - 'a'];
	}
	
	bool ok = 0;
	
	for(int i = 0; i < 26; ++i)
		if(cnt[i] >= 5) { printf("%c", i + 'a'); ok = 1; }
		
	if(!ok) printf("PREDAJA");
	printf("\n");
	
	return 0;
	
}
