/*
 * Author: Myungwoo Chun(myungwoo)
 * Time Complexity: O(N^3)
 */
#include <bits/stdc++.h>
using namespace std;

#define MAXN 503
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
typedef long long lld;

const int MOD = 1e9 + 7;
int N;
int A[MAXN], B[MAXN], L[MAXN*2];
int D[MAXN][MAXN*2];
int inv[MAXN];
vector <int> X;

/*
 * D[i][j] = number of increasing subsequence between index 1 ~ i,
             and the largest number is equal or lower than the endpoint of interval j
 * inv[i] = modular inverse of integer i (modulo MOD)
 */

int main()
{
    inv[1] = 1;
    for (int i=2;i<MAXN;i++) inv[i] = (lld)inv[MOD % i] * (MOD - MOD/i) % MOD;
    scanf("%d", &N);
    for (int i=1;i<=N;i++){
        scanf("%d%d", A+i, B+i);
        X.pb(A[i]); X.pb(B[i]+1);
    }
    sort(all(X)); X.erase(unique(all(X)), X.end());
    for (int i=1;i<=N;i++){
        A[i] = upper_bound(all(X), A[i]) - X.begin();
        B[i] = upper_bound(all(X), B[i]) - X.begin();
    }
    for (int i=1;i<sz(X);i++) L[i] = X[i]-X[i-1];
    for (int i=0;i<sz(X);i++) D[0][i] = 1;
    for (int i=1;i<=N;i++){
        for (int j=A[i];j<=B[i];j++){
            D[i][j] = (lld)L[j] * D[i-1][j-1] % MOD;
            int cnt = 1, choose = L[j] - 1;
            for (int k=i-1;k>0;k--){
                if (A[k] <= j && j <= B[k]){
                    cnt++;
                    choose = (lld)choose * (L[j]+cnt-2) % MOD * inv[cnt] % MOD;
                    if (!choose) break;
                    D[i][j] = (D[i][j] + (lld)D[k-1][j-1] * choose) % MOD;
                    // D[i][j] += D[k-1][j-1] * (L[j]+cnt-2 choose cnt);
                }
            }
        }
        D[i][0] = 1;
        for (int j=1;j<sz(X);j++)
            D[i][j] = ((lld)D[i][j] + D[i-1][j] + D[i][j-1] - D[i-1][j-1] + MOD) % MOD;
    }
    printf("%d\n", (D[N][sz(X)-1] - 1 + MOD) % MOD);
}