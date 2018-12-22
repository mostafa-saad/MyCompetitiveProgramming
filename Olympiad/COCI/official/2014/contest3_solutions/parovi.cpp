#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long llint;

const int MAXL = 50010;
const int MOD = 1000000007;

int N;
char A[MAXL], B[MAXL];
int mem1[2][2][2][2][MAXL];
int mem2[2][2][2][2][MAXL];

void load(void) {
	char tmp1[MAXL], tmp2[MAXL];
	scanf("%s%s", tmp1, tmp2);

	// dopunjavanje doljnje granice vodecim nulama, ako je to potrebno	
	int len1 = strlen(tmp1), len2 = strlen(tmp2);
	for(int i = 0; i < len2 - len1; ++i)
		A[i] = '0';

	for(int i = len2 - len1; i < len2; ++i)
		A[i] = tmp1[i - len2 + len1];

	for(int i = 0; i < len2; ++i)
		B[i] = tmp2[i];

	N = len2;
}

int num(int pos, int d1, int g1, int d2, int g2) {
	// d1 -> dira li prvi broj donju granicu
 	// g1 -> dira li prvi broj gornju granicu	
	// d2, g2 -> isto za drugi broj

	if(pos == N) return 1;
	
	int &state = mem1[d1][g1][d2][g2][pos];
	if(state != -1) return state;

	int lo1 = 0, hi1 = 9, lo2 = 0, hi2 = 9;
	// ako je d1 = g1 = 0, onda trenutna znamenka moze biti sve od 0 do 9

	if(d1 == 1) {
		// prvi broj trenutno dodiruje donju granicu pa mu
		// trenutna znamenka ne smije biti manja od iste
		// znamenke u donjoj granici
		lo1 = A[pos] - '0';
	}

	if(g1 == 1) {
		// prvi broj trenutno dodiruje gornju granicu pa mu
		// trenutna znamenka ne smije biti veca od iste
		// znamenke u gornjoj granici
		hi1 = B[pos] - '0';
	}

	// analogno za drugi broj
	if(d2 == 1) lo2 = A[pos] - '0';
	if(g2 == 1) hi2 = B[pos] - '0';

	llint ret = 0;

	for(int x = lo1; x <= hi1; ++x) {
		for(int y = lo2; y <= hi2; ++y) {
			int nd1 = 0, ng1 = 0, nd2 = 0, ng2 = 0;
			// provjere granica
			// ako diram donju granicu i stavim najmanju znamenku
			if(d1 == 1 && x == lo1) nd1 = 1;			
			// ako diram gornju granicu i stavim najvecu znamenku
			if(g1 == 1 && x == hi1) ng1 = 1;
			if(d2 == 1 && y == lo2) nd2 = 1;
			if(g2 == 1 && y == hi2) ng2 = 1;
			ret += num(pos + 1, nd1, ng1, nd2, ng2);
		}
	}

	return state = ret % MOD;
}

int f(int pos, int d1, int g1, int d2, int g2) {
	// d1, g1, d2, g2 -> isto kao u gornjoj funkciji

	if(pos == N) return 0;
	int &state = mem2[d1][g1][d2][g2][pos];
	if(state != -1) return state;

	int lo1 = 0, hi1 = 9, lo2 = 0, hi2 = 9;

	// sve isto kao i gore
	if(d1 == 1) lo1 = A[pos] - '0';
	if(g1 == 1) hi1 = B[pos] - '0';
	if(d2 == 1) lo2 = A[pos] - '0';
	if(g2 == 1) hi2 = B[pos] - '0';

	llint ret = 0;

	for(int x = lo1; x <= hi1; ++x) {
		for(int y = lo2; y <= hi2; ++y) {
			// sve isto kao i gore
			int nd1 = 0, ng1 = 0, nd2 = 0, ng2 = 0;
			if(d1 == 1 && x == lo1) nd1 = 1;
			if(g1 == 1 && x == hi1) ng1 = 1;
			if(d2 == 1 && y == lo2) nd2 = 1;
			if(g2 == 1 && y == hi2) ng2 = 1;
			ret += (llint)abs(x - y) * num(pos + 1, nd1, ng1, nd2, ng2) % MOD;
			ret += f(pos + 1, nd1, ng1, nd2, ng2);
		}
	}	

	return state = ret % MOD;
}

int main(void) {
	load();
	memset(mem1, -1, sizeof mem1);
	memset(mem2, -1, sizeof mem2);

	for(int i = 0; i < N; ++i) printf("%c", A[i]); printf("\n");
	for(int i = 0; i < N; ++i) printf("%c", B[i]); printf("\n");

	printf("%d\n", f(0, 1, 1, 1, 1));

	return 0;
}
