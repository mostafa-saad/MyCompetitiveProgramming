#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MaxN 200010

string S;
vector<string> ANS;
int N;
int C[1000] = {0};
int NN;
vector<int> pos, pos_n;

int main() {
	cin >> NN;
	cin >> S;
	
	for (int i = 0; i < S.size(); i++)
		C[S[i]]++;
	int nelyg = 0;
	char letter;
	for (int i = 'A'; i <= 'Z'; i++) 
		if (C[i] & 1) {
			nelyg++;
			letter = i;
			}
			
	if (nelyg != 1) {
		printf("NOT POSSIBLE\n");
		return 0;
	}
	pos.reserve (MaxN);
	pos_n.reserve(5);

	for (int i = 0; i < S.size(); i++)
		if (S[i] == letter)
			pos.push_back(i);

	N = S.length() / 2;
	int K = 100;

	for (int i = 0; i < min(K, (int)pos.size()); i++)
		pos_n.push_back(pos[i]);
	for (int i = max(K, (int)pos.size()-K); i < pos.size(); i++)
		pos_n.push_back(pos[i]);
	for (int i = max(K, (int)pos.size()/2-5); i < min((int)pos.size()/2 + 5, (int)pos.size()-K); i++)
		pos_n.push_back(pos[i]);
	

	for (int j = 0; j < pos_n.size(); j++) {
		int i = pos_n[j];
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
	if (ANS.size() == 0)
		printf("NOT POSSIBLE\n");
	else if (good) 
		printf("%s\n", ANS[0].c_str());
	else 
		printf("NOT UNIQUE\n");


	return 0;
}
