#include "assistant.h"
#include <set>
using namespace std;
set<int> pops, scaffold;
 
void Assist(unsigned char *A, int N, int K, int R) {
    int prevReq = -1;
    for(int i=0; i<K; i++){
        scaffold.insert(i);
        if(A[i+N]) pops.insert(i);
    }
    for(int i=0; i<N; i++){
        int curReq = GetRequest();
        if(scaffold.find(curReq) == scaffold.end()){
            PutBack(*pops.begin());
            scaffold.erase(*pops.begin());
            pops.erase(pops.begin());
            scaffold.insert(curReq);
        }
        if(A[i]){
            pops.insert(curReq);
        }
    }
}