/*
 * Author: Bumsoo Park(zlzmsrhak)
 * Time Complexity: O(N^3)
 */
#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long ll;

const int MX = 1005;
const long long MM = 1000000007;

// i-th segment : S[i] ~ (E[i]-1)
// D : dp table ; rv[i] * i % MM = 1
// X : coordinate list, L[i] = X[i] - X[i-1]

int S[MX], E[MX], L[MX];
int D[MX][MX], rv[MX];
vector<int> X;

int add(int a, int b){ return a+b >= MM? a+b-MM: a+b; }

int main()
{
	int N, W;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) scanf("%d%d", S+i, E+i), E[i]++;
	
	rv[1] = 1;
	for(int i = 2; i <= N; i++) rv[i] = (MM/i) * (MM-rv[MM%i]) % MM;

	for(int i = 1; i <= N; i++) X.push_back(S[i]);
	for(int i = 1; i <= N; i++) X.push_back(E[i]);
	sort(X.begin(), X.end());
	X.resize(unique(X.begin(), X.end()) - X.begin());
    
	for(int i = 1; i <= N; i++) S[i] = lower_bound(X.begin(), X.end(), S[i]) - X.begin() + 1;
	for(int i = 1; i <= N; i++) E[i] = lower_bound(X.begin(), X.end(), E[i]) - X.begin() + 1;
    
	W = X.size() - 1;
	for(int i = 1; i <= W; i++) L[i] = X[i] - X[i-1];

	D[0][0] = 1;
	for(int i = 1; i <= W; i++){
		D[i][0] = 1;
		for(int j = 1; j <= N; j++){
			ll mul = L[i];
			int count = 1;

			D[i][j] = D[i-1][j];
			
			if( i < S[j] || i >= E[j] ) continue;

			for(int k = j-1; k >= 0; k--){
				D[i][j] = add(D[i][j], D[i-1][k] * mul % MM);
				if( S[k] <= i && i < E[k] ){
					mul = mul * (count + L[i]) % MM * rv[count+1] % MM;
					count++;
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= N; i++) ans = add(ans, D[W][i]);
	printf("%d\n", ans);
}
