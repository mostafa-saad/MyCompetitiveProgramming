#include "advisor.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> pi;
 
set<pi> s;
vector<pi> nexts;
int query[100005];
int is_in[100005];
 
int getnxt(int val, int time){
    auto t = upper_bound(nexts.begin(), nexts.end(), pi(val, time));
    if(t->first != val) return 1e9;
    return t->second;
}
 
bool PopPrevRequest[100005];
bool PopK[100005];
 
void ComputeAdvice(int *C, int N, int K, int M) {
    for(int i=0; i<N; i++){
        nexts.push_back(pi(C[i], i));
    }
    sort(nexts.begin(), nexts.end());
    for(int i=0; i<K; i++){
        s.insert(pi(getnxt(i, -1), i));
        is_in[i] = 1;
    }
    for(int i=0; i<N; i++){
        query[i] = N;
        if(is_in[C[i]]){
            if(s.find(pi(i, C[i])) != s.end()) s.erase(pi(i, C[i]));
            s.insert(pi(getnxt(C[i], i), C[i]));   
        }
        else{
            auto t = --s.end();
            query[i] = t->second;
            is_in[t->second] = 0;
            s.erase(t);
            s.insert(pi(getnxt(C[i], i), C[i]));
            is_in[C[i]] = 1;
        }
    }
    for(int i=0; i<N; i++){
        if(query[i] != N){
            auto t = lower_bound(nexts.begin(), nexts.end(), pi(query[i], i));
            if(t == nexts.begin() || (t-1)->first != query[i]){
                PopK[query[i]] = 1;
            }
            else{
                t--;
                PopPrevRequest[t->second] = 1;
            }
            // investigate last use of pop query
        }
    }
    for(int i=0; i<N; i++){
        WriteAdvice(PopPrevRequest[i]);
    }
    for(int i=0; i<K; i++){
        WriteAdvice(PopK[i]);
    }
}