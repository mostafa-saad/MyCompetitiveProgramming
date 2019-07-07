#include "coins.h"
#include <vector>
using namespace std;

vector<int> coin_flips(vector<int> b, int c) {
	int x = 0;
	for(int i = 0; i < 64; ++ i)
		x ^= b[i] * i;
	vector<int> flips(1);
	flips[0] = c ^ x;
	return flips;
}

int find_coin(vector<int> b) {
	int x = 0;
	for(int i = 0; i < 64; ++ i)
		x ^= b[i] * i;
	return x;
}
