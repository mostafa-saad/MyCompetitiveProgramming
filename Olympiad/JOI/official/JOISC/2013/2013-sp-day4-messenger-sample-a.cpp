/*
	Problem: Messenger, playerA.cpp
*/

namespace A {
	int X;
	int pos;
}

void InitA(int T, int X) {
	A::X = X;
	A::pos = -2;
}

int GameA(int I, int J) {
	if (I == 4) {
		return -1;
	}
	if (I != 2) {
		return (J == 4) ? -3 : -4;
	}
	int bit = (A::pos == -2) ? 0 : (A::pos == -1) ? 1 : ((A::X >> A::pos) & 1);
	++A::pos;
	return (bit == 0) ? -1 : -2;
}

