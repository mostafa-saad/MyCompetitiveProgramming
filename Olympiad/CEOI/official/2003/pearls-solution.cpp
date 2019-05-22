#include <fstream>
#include <vector>
#include "pearls_lib.h"
using namespace std;

#define MAXDWARFES 1000
#define MAXLEN 1000

typedef vector<int> VI;

struct dwarfes {
	int c;
	VI list[2];
}d[MAXDWARFES];

char pos[MAXLEN][MAXDWARFES];
int mov[MAXLEN][MAXDWARFES];

ifstream in("pearls.in");

int main() {
	int l,n,f;
	in >> l >> n >> f;
	f--;

	int type[MAXLEN];
	for (int i=0; i<l; i++) {
		char c;
		while(in >> c)
			if (c == 'D' || c == 'W' || c == 'B')
				break;
		type[i] = (c == 'W');
	}

	for (int i=0; i<n; i++) {
		in >> d[i].c;
		pos[l-1][i] = d[i].c;
		for (int j=0; j<2; j++) {
			int len;
			in >> len;
			while(len--) {
				int temp;
				in >> temp;
				d[i].list[j].push_back(temp-1);
			}
		}
	}
	for (int p=l-2; p>=0; p--) {
		int c = type[p];
		for (int i=0; i<n; i++) {
			pos[p][i] = 1-d[i].c; /*set position to be a losing position */
			for (VI::iterator it=d[i].list[c].begin(); it<d[i].list[c].end(); it++) {
				mov[p][i] = *it;
				if (pos[p+1][*it] == d[i].c) { /*winning move found */
					pos[p][i] = d[i].c;
					break;
				}
			}
		}
	}
	for (int p=0; p<l-1; p++) {
		if (d[f].c == 1)
			f = getNext()-1;
		else {
			f = mov[p][f];
			setNext(f+1);
		}
	}
	finish();
	return(0);
}
