#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, cnt;
string passport;
vector<string> v;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        cin >> passport;
        v.push_back(passport);    
	}
    sort(v.begin(), v.end());
    
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        cin >> passport;
		if(binary_search(v.begin(), v.end(), passport))
			cnt++;
    }

	cout << cnt;

    return 0;
}
