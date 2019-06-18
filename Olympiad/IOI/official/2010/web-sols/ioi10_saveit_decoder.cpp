#include "grader.h"
#include "decoder.h"
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
vector<int> tree[1005];
 
int dx[1005];
 
void dfs(int x, int pa){
    for(auto &i : tree[x]){
        dx[i] += dx[x];
        dfs(i, x);
    }
}
 
void decode(int nv, int nh){
    for(int i=1; i<nv; i++){
        int r = 0;
        for(int j=0; j<10; j++){
            r |= (decode_bit() << j);
        }
        tree[r].push_back(i);
    }
    for(int i=0; i<nh; i++){
        for(int j=1; j<nv; j+=5){
            int buf = 0;
            for(int k=0; k<8; k++){
                buf |= (decode_bit() << k);
            }
            for(int i=4; i>=0; i--){
                int r = buf % 3;
                buf /= 3;
                r--;
                dx[j + i] = r;
            }
        }
        dfs(0,0);
        for(int j=0; j<nv; j++){
            hops(i,j,dx[j] - dx[i]);
        }
    }
}