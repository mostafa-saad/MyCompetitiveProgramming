#include "decoder.h"
#include "decoderlib.h"
#include <algorithm>
#include <cstring>
using namespace std;
 
struct bignum{
    short arr[100];
    void init(char i){
        memset(arr,0,sizeof(arr));
        arr[0] = i;
    }
};
 
bignum operator+(bignum a, bignum b){
    for (int i=0; i<100; i++) {
        a.arr[i] += b.arr[i];
        if(a.arr[i] >= 256) {
            a.arr[i] -= 256;
            a.arr[i+1] ++;
        }
    }
    return a;
}
 
bool operator<(bignum a, bignum b){
    for (int i=99; i>=0; i--) {
        if(a.arr[i] < b.arr[i]) return 1;
        if(a.arr[i] > b.arr[i]) return 0;
    }
    return 0;
}
 
int precalc;
bignum bino[600][600];
 
void decode(int N, int L, int X[])
{
    if(!precalc){
        for (int i=0; i<600; i++) {
            bino[i][0].init(1);
            for (int j=1; j<=i; j++) {
                bino[i][j].init(0);
                bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
            }
            for (int j=i+1; j<600; j++) {
                bino[i][j].init(0);
            }
        }
        precalc = 1;
    }
    sort(X,X+L);
    bignum ret;
    ret.init(0);
    for (int i=0; i<L; i++) {
        ret = ret + bino[5 * N + 255 - X[i] - i - 2][5 * N - i];
    }
    for (int i=0; i<N; i++) {
        output(ret.arr[i]);
    }
}