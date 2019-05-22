/* Author: Adrian Kuegel */
#include <fstream>
#include <iomanip>
using namespace std;

#define MAXN 100000
#define MOD 1000000

int pot2[MAXN],pile[MAXN],nmov;

void move(int s, int dest) {
	if (s<0)
		return;
	if (dest!=pile[s]) {
		move(s-1,3-dest-pile[s]);
		// now all smaller disks are on the same pile
		// first disk s is moved, then all smaller disks together (1 + 2^s - 1)
		nmov = (nmov+pot2[s]) % MOD;
	}
	else
		move(s-1,dest);
}

int main() {
	ifstream in("hanoi.in");
	ofstream out("hanoi.out");
	pot2[0] = 1;
	for (int i=1; i<MAXN; i++)
		pot2[i] = (pot2[i-1]<<1)%MOD;
	int n,l[3];
	in >> n >> l[0] >> l[1] >> l[2];
	for (int i=0; i<3; i++)
		for (int j=0; j<l[i]; j++) {
			int s;
			in >> s;
			pile[s-1] = i;
		}
	out << pile[n-1]+1 << endl;
	move(n-2,pile[n-1]);
	out << nmov << endl;
	return(0);
}
