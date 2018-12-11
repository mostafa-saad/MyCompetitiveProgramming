/*
 * Author: Gyeonggeun Kim(kriii)
 * Time Complexity: O(N^3)
 */
#include <stdio.h>
#include <map>
using namespace std;

const long long mod = 1000000007;
int inv[505];

int N,A[505],B[505],L[1005];
long long D[505][1005];

int main()
{
	inv[1] = 1;
	for (int i=2;i<505;i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	scanf ("%d",&N);
	map<int, int> chk;
	for (int i=1;i<=N;i++){
		scanf ("%d %d",&A[i],&B[i]);
		chk[A[i]] = chk[B[i]+1] = 0;
	}

	int c = 0, last = 0;
	for (auto &p : chk){
		L[c] = p.first - last;
		p.second = c++;
		last = p.first;
	}
	c--;

	for (int j=0;j<=c;j++) D[0][j] = 1;
	for (int i=1;i<=N;i++){
		A[i] = chk[A[i]] + 1; B[i] = chk[B[i]+1];
		D[i][0] = 1;
		for (int j=A[i];j<=B[i];j++){
			D[i][j] = (D[i][j] + L[j] * D[i-1][j-1]) % mod;
			long long comb = L[j] - 1; int c = 1;
			for (int k=i-1;k>0;k--){
				if (A[k] <= j && j <= B[k]){
					comb = comb * (L[j] - 1 + c) % mod;
					if (!comb) break;
					comb = comb * inv[++c] % mod;
					D[i][j] = (D[i][j] + comb * D[k-1][j-1]) % mod;
				}
			}
		}
		for (int j=1;j<=c;j++){
			D[i][j] = (D[i][j] + D[i][j-1] + D[i-1][j] - D[i-1][j-1] + mod) % mod;
		}
	}
	
	long long ans = 0;
	printf ("%lld\n",(D[N][c]+mod-1)%mod);

	return 0;
}