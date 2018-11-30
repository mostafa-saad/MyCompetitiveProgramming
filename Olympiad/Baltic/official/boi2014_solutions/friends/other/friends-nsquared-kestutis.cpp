#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define MaxN 100010

string S;
vector<string> ANS;
int N;

int main() {
	int NN;
	cin >> NN;
	cin >> S;
	N = S.length() / 2;
	for (int i = 0; i < S.size(); i++) {
		string Sn = S.substr(0, i) + S.substr(i + 1, 2*N - i);
		bool good = true;
		for (int i = 0; i < N; i++) 
			if (Sn[i] != Sn[i+N])
				good = false;
		if (good)
			ANS.push_back(Sn.substr(0, N));
	}


	bool good = true;
	for (int i = 1; i < ANS.size(); i++)
		if (ANS[0] != ANS[i])
			good = false;
	if (ANS.size() == 0 || S.length() % 2 == 0)
		printf("NOT POSSIBLE\n");
	else if (good) 
		printf("%s\n", ANS[0].c_str());
	else 
		printf("NOT UNIQUE\n");


	return 0;
}
