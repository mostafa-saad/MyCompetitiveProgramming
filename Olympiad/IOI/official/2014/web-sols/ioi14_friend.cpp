#include "friend.h"
#include <algorithm>
using namespace std;
 
int findSample(int n, int confidence[], int host[], int protocol[]){
    int ret = 0;
    for (int i=n-1; i>=0; i--) {
        if(protocol[i] == 1){
            confidence[host[i]] += confidence[i];
        }
        else if(protocol[i] == 2){
            confidence[host[i]] = max(confidence[host[i]],confidence[i]);
        }
        else{
            ret += confidence[i];
            confidence[host[i]] -= confidence[i];
            confidence[host[i]] = max(confidence[host[i]],0);
            // (a,b) -> (a-b,0) + b
        }
    }
    return ret += confidence[0];
}