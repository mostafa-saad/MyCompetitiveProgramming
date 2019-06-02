/*
Weryfikator wejscia do zadania PRE.
Autor: Dawid Dabrowski

Oparte o nowy naglowek "oi.h".
*/

#include <cstdio>
#include <set>
#include <vector>

#include "oi.h"
using namespace std;

const int THR1 = 500;
const int THR2 = 5000;

char slowo[1000005];

int main(){
	oi::Scanner input(stdin, oi::PL);;
	int n = input.readInt(1, 1000000);
	input.readEoln();
	int len = input.readString(slowo, 1000005);
	if(len!=n) {
		char err_msg[100];
		sprintf(err_msg, "Zla dlugosc slowa. Powinno byc %d, a jest %d.\n", n, len);
		input.error(err_msg);
		return 0;
	}
	for(int i=0; i<n; ++i) {
		if(slowo[i] < 'a' || slowo[i] > 'z') {
			char error_msg[100];
			sprintf(error_msg, "W slowie na pozycji %d pojawil znak niebedacy mala litera alfabetu angielskiego.\n", i);
			input.error(error_msg);
			return 0;
		}
	}
	input.readEoln();
	input.readEof();
	printf(" n = %d", n);
	if (n <= THR1) {
		printf(" [n <= %d]", THR1);
	}
	if (n <= THR2) {
		printf(" [n <= %d]", THR2);
	}
	printf("\n");
	return 0;
};
