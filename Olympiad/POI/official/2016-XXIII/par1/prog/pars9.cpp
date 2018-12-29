/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Park wodny                                         *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Zlozonosc czasowa:    O(n^4)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include <bits/stdc++.h>

using namespace std;


const int MaxN = 1005;
const int NumDirs = 4,
          DirsR[NumDirs] = {-1,  0, 1, 0},
          DirsC[NumDirs] = { 0, -1, 0, 1};

int N;
bool isWater[MaxN][MaxN];
int poolId[MaxN][MaxN];
int poolArea[MaxN*MaxN];
int numPools, totalArea;

void input(){
    ios_base::sync_with_stdio(false);
    cin >> N;
    for(int i = 0; i < N; i++){
        string row;
        cin >> row;
        for(int j = 0; j < N; j++){
            isWater[i][j] = (row[j] == 'B');
        }
    }
}

inline bool is_board(int r, int c){
    return (r >= 0 && r < N && c >= 0 && c < N);
}

inline bool is_pool(int r, int c){
    return is_board(r,c) && isWater[r][c];
}

inline bool is_aisle(int r, int c){
    return is_board(r,c) && !isWater[r][c];
}


void find_pools(){
    numPools = totalArea = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(!isWater[i][j]) continue;
            if(i && isWater[i-1][j]){
                poolId[i][j] = poolId[i-1][j];
            } else if(j && isWater[i][j-1]){
                poolId[i][j] = poolId[i][j-1];
            } else {
                poolId[i][j] = (++numPools);
            }

            totalArea++;
            poolArea[poolId[i][j]]++;
        }
    }
}


// wynik, jesli zmieniamy alejki w pozycjach (r1,c1) i (r2,c2)
int get_res(int r1, int c1, int r2, int c2){
    vector<int> pools;
    for(int dir = 0; dir < NumDirs; dir++){
        int nr1 = r1 + DirsR[dir],
            nc1 = c1 + DirsC[dir],
            nr2 = r2 + DirsR[dir],
            nc2 = c2 + DirsC[dir];
        if(is_pool(nr1, nc1)) pools.push_back(poolId[nr1][nc1]);
        if(is_pool(nr2, nc2)) pools.push_back(poolId[nr2][nc2]);
    }
    sort(pools.begin(), pools.end());
    int S = (int)pools.size();
    pools.resize(distance(pools.begin(), unique(pools.begin(), pools.end())));
    if((int)pools.size() == S && abs(r1-r2)+abs(c1-c2) > 1) return -1;

    int total = 2;
    for(int v : pools) total += poolArea[v];
    return total;
}


int main(){
    input();
    find_pools();

    if(totalArea >= N*N-2){ printf("%d\n", N*N); return 0; }
    assert(N >= 2);

    int result = 0;
    for(int r1 = 0; r1 < N; r1++){
        for(int c1 = 0; c1 < N; c1++){
            if(!is_aisle(r1,c1)) continue;
            
            for(int r2 = r1; r2 < N; r2++){
                for(int c2 = 0; c2 < N; c2++){
                    if(!is_aisle(r2,c2)) continue;
                    if(make_pair(r1,c1) >= make_pair(r2,c2)) continue;

                    int res = get_res(r1,c1,r2,c2);
                    if(res > result){
                        result = res;
                    }
                }
            }
        }
    }
    cout << result << endl;
}
