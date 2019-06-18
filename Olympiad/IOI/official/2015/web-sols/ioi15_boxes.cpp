#include "boxes.h"
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long lint;
 
lint lsum[10000005], rsum[10000005], tmp[10000005];
 
lint delivery(int N, int K, int L, int p[]) {
    for(int i=0; i<N; i++){
        tmp[i % K] += 2 * p[i];
        lsum[i] = tmp[i % K];
    }
    memset(tmp,0,sizeof(tmp));
    for(int i=N-1; i>=0; i--){
        tmp[i % K] += 2 * (L - p[i]);
        rsum[i] = tmp[i % K];
    }
    lint ret = 1e18;
    for(int i=0; i<=N; i++){
        ret = min(ret, (i ? lsum[i-1] : 0) + rsum[i]);
    }
    for(int i=0; i<=N-K; i++){
        ret = min(ret, (i ? lsum[i-1] : 0) + rsum[i + K] + L);
    }
    return ret;
}