/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Ci±gi bez zaj±kniêæ                            *
 *   Plik:                cia.cpp                                        *
 *   Autor:               Marcin Stefaniak                               *
 *************************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
	int i, l, n;
	bool t[32769], c, d;

	cin >> n;
	
	l=1; c=false; while(l<=32768) { t[l]=c; l*=2; c=!c; }

	if (n==1) cout << "1\na\n";
	if (n==2) cout << "2\nab\n";
	if (n==3) cout << "2\naba\n";
	if (n>=4) {
		cout << "3\n";
		c=false; d=true;
		for(i=1; i<=n; i++) {
			cout << (c==d ? 'a' : (c ? 'b' : 'c'));
			l = 1 + ((i+1)^i);
			if (l >= 65536) l >>= 16;
			c=d; d ^= t[l];		
		}
		cout << endl;	
	}
	return 0;
}
