#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int main(void) {

	int n;
	scanf("%d", &n);

	char uzorak[110];
	scanf("%s", uzorak);
	
	int d = strlen(uzorak);
	int i = 0;

	string prvi_dio, drugi_dio;

	for(i = 0; i < d; ++i) {
		if(uzorak[i] == '*') break;
		prvi_dio.push_back(uzorak[i]);
	}

	for(++i; i < d; ++i)
		drugi_dio.push_back(uzorak[i]);

	for(int i = 0; i < n; ++i) {
		char tmp[110]; scanf("%s", tmp);
		string s = tmp;
//		printf("1\n");
		if(prvi_dio.size() + drugi_dio.size() > s.size()) {
			printf("NE\n"); continue;
		}
//		printf("2\n");
		if(s.substr(0, prvi_dio.size()) != prvi_dio) {
			printf("NE\n"); continue;
		}
//		printf("3\n");
		if(s.substr(s.size() - drugi_dio.size(), drugi_dio.size()) != drugi_dio) {
			printf("NE\n"); continue;
		}
		printf("DA\n");
	}

	return 0;

}
