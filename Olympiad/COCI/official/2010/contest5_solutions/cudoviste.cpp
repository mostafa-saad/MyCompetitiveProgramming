#include <string>
#include <iostream>

using namespace std;

string town[50];

int main(){
	int r, s;
	cin >> r >> s;
	for (int i = 0; i < r; i++)
		cin >> town[i];

	int crush[5] = {0};

	for (int i = 0 ; i + 1 < r; i++)
		for (int j = 0; j + 1 < s; j++){
			int c = 0;
			for (int k = 0; k < 2; k++)
				for (int l = 0; l < 2; l++)
					c += town[i + k][j + l] == '#' ? 100 : (town[i + k][j + l] == 'X' ? 1 : 0);

			if ( c < 100 )
				crush[c]++;
		}

	for (int i = 0; i < 5; i++)
		cout << crush[i] << endl;

	return 0;
}
