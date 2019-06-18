#include "encoder.h"
#include "encoderlib.h"
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
 
bignum bino[600][600];
int precalc;
 
 
void encode(int N, int* M){
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
    bignum base, t;
    t.init(0);
    for (int i=0; i<N; i++) {
        t.arr[i] = M[i];
    }
    base.init(0);
    t = t + base;
    base.init(0);
    int length = 255 + 5 * N;
    for(int i=0; i<5*N; i++){
        while (t < bino[length-1][5 * N - i] + base) {
            length--;
        }
        send(5 * N + 255 - length - i - 1);
        base = base + bino[length-1][5 * N - i];
        length--;
    }
}