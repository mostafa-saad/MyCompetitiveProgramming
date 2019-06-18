#include "scales.h"
#include <vector>
#include <algorithm>
using namespace std;
 
int perm[720][6];
 
int IgetHeaviest(int idx, int a, int b, int c){
    vector<int> v;
    v.push_back(perm[idx][a]);
    v.push_back(perm[idx][b]);
    v.push_back(perm[idx][c]);
    sort(v.begin(), v.end());
    if(v[2] == perm[idx][a]) return a+1;
    if(v[2] == perm[idx][b]) return b+1;
    return c+1;
}
 
int IgetLightest(int idx, int a, int b, int c){
    vector<int> v;
    v.push_back(perm[idx][a]);
    v.push_back(perm[idx][b]);
    v.push_back(perm[idx][c]);
    sort(v.begin(), v.end());
    if(v[0] == perm[idx][a]) return a+1;
    if(v[0] == perm[idx][b]) return b+1;
    return c+1;
}
 
int IgetMedian(int idx, int a, int b, int c){
    vector<int> v;
    v.push_back(perm[idx][a]);
    v.push_back(perm[idx][b]);
    v.push_back(perm[idx][c]);
    sort(v.begin(), v.end());
    if(v[1] == perm[idx][a]) return a+1;
    if(v[1] == perm[idx][b]) return b+1;
    return c+1;
}
 
int IgetNextLightest(int idx, int a, int b, int c, int d){
    vector<int> v;
    v.push_back(perm[idx][a]);
    v.push_back(perm[idx][b]);
    v.push_back(perm[idx][c]);
    sort(v.begin(), v.end());
    int p = (int)(lower_bound(v.begin(), v.end(), perm[idx][d]) - v.begin());
    if(p == 3 || p == 0) return IgetLightest(idx, a, b, c);
    if(p == 2) return IgetHeaviest(idx, a, b, c);
    return IgetMedian(idx, a, b, c);
}
 
int ops[720][120];
int optima[6] = {243, 81, 27, 9, 3, 1};
 
int opt[720][6];
 
bool dfs(int x, vector<int> candidate){
    if(x == 6) return 1;
    for(int i=0; i<120; i++){
        int cnt[7] = {};
        vector<int> lg[7];
        for(auto &j : candidate){
            cnt[ops[j][i]]++;
            lg[ops[j][i]].push_back(j);
        }
        int p = *max_element(cnt, cnt + 7);
        if(p <= optima[x]){
            bool res = 1;
            for(int i=1; i<=6; i++){
                if(res == 0) break;
                if(!lg[i].empty()){
                    res &= dfs(x+1, lg[i]);
                }
            }
            if(res){
                opt[candidate[0]][x] = i;
                return 1;
            }
        }
    }
    return 0;
}
 
int piv;
 
void init(int T) {
    for(int i=0; i<6; i++){
        perm[0][i] = i+1;
    }
    for(int i=1; i<720; i++){
        for(int j=0; j<6; j++){
            perm[i][j] = perm[i-1][j];
        }
        next_permutation(perm[i], perm[i] + 6);
    }
    for(int i=0; i<720; i++){
        piv = 0;
        for(int a=0; a<6; a++){
            for(int b=a+1; b<6; b++){
                for(int c=b+1; c<6; c++){
                    ops[i][piv++] = IgetLightest(i, a, b, c);
                }
            }
        }
        for(int a=0; a<6; a++){
            for(int b=a+1; b<6; b++){
                for(int c=b+1; c<6; c++){
                    ops[i][piv++] = IgetMedian(i, a, b, c);
                }
            }
        }
        for(int a=0; a<6; a++){
            for(int b=a+1; b<6; b++){
                for(int c=b+1; c<6; c++){
                    ops[i][piv++] = IgetHeaviest(i, a, b, c);
                }
            }
        }
        for(int a=0; a<6; a++){
            for(int b=a+1; b<6; b++){
                for(int c=b+1; c<6; c++){
                    for(int d=0; d<6; d++){
                        if(d == a || d == b || d == c) continue;
                        ops[i][piv++] = IgetNextLightest(i, a, b, c, d);
                    }
                }
            }
        }
    }
    vector<int> v;
    for(int i=0; i<720; i++) v.push_back(i);
    if(!dfs(0, v)) puts("fucking sex");
}
 
int doOperation(int x){
    for(int a=0; a<6; a++){
        for(int b=a+1; b<6; b++){
            for(int c=b+1; c<6; c++){
                if(x == 0) return getLightest(a + 1, b + 1, c + 1);
                x--;
            }
        }
    }
    for(int a=0; a<6; a++){
        for(int b=a+1; b<6; b++){
            for(int c=b+1; c<6; c++){
                if(x == 0) return getMedian(a + 1, b + 1, c + 1);
                x--;
            }
        }
    }
    for(int a=0; a<6; a++){
        for(int b=a+1; b<6; b++){
            for(int c=b+1; c<6; c++){
                if(x == 0) return getHeaviest(a + 1, b + 1, c + 1);
                x--;
            }
        }
    }
    for(int a=0; a<6; a++){
        for(int b=a+1; b<6; b++){
            for(int c=b+1; c<6; c++){
                for(int d=0; d<6; d++){
                    if(d == a || d == b || d == c) continue;
                    if(x == 0) return getNextLightest(a+1, b+1, c+1, d+1);
                    x--;
                }
            }
        }
    }
    return -1;
}
 
int p = -1;
void solve(int x, vector<int> v){
    if(x == 6){
        p = v[0];
        return;
    }
    int myop = opt[v[0]][x];
    int t = doOperation(myop);
    vector<int> nar;
    for(auto &i : v){
        if(ops[i][myop] == t){
            nar.push_back(i);
        }
    }
    solve(x+1, nar);
}
 
void orderCoins() {
    vector<int> v;
    for(int i=0; i<720; i++) v.push_back(i);
    solve(0, v);
    int tmps[6];
    for(int i=0; i<6; i++){
        tmps[perm[p][i] - 1] = i + 1;
    }
    answer(tmps);
}