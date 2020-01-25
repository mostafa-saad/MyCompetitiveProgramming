#include <iostream>
using namespace std;

int N, K;
int glas;
int broj_glasova;

int main()
{
	cin >> N;
	cin >> K;
	
	for (int i = 0; i < N; i++)
	{
		cin >> glas;
		if (glas == 1) broj_glasova++;
	}

	if (broj_glasova * 2 >= N) cout << "DA" << '\n';
	else cout << "NE" << '\n';
}
