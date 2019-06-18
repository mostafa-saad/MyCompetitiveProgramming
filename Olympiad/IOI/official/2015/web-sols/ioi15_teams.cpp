#include "teams.h"
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
 
int n;
pi a[500005];
 
struct rtree{
    int lim;
    vector<int> tree[1050000];
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++){
            int pos = a[i].second + lim;
            while(pos){
                tree[pos].push_back(a[i].first);
                pos >>= 1;
            }
        }
    }
    int nsum(int idx, int s, int e){
        return (int)(upper_bound(tree[idx].begin(), tree[idx].end(), e) - lower_bound(tree[idx].begin(), tree[idx].end(), s));
    }
    int query(int sx, int ex, int sy, int ey){
        sy += lim;
        ey += lim;
        int ret = 0;
        while(sy < ey){
            if(sy % 2 == 1) ret += nsum(sy++, sx, ex);
            if(ey % 2 == 0) ret += nsum(ey--, sx, ex);
            sy >>= 1;
            ey >>= 1;
        }
        if(sy == ey) ret += nsum(sy, sx, ex);
        return ret;
    }
    int kth(int sx, int ex, int cnt){
        int pos = 1;
        while(pos < lim){
            int tmp = nsum(2 * pos, sx, ex);
            if(cnt <= tmp){
                pos *= 2;
            }
            else{
                cnt -= tmp;
                pos = pos * 2 + 1;
            }
        }
        return pos - lim;
    }
}rtree;
 
void init(int N, int A[], int B[]) {
    n = N;
    for(int i=0; i<N; i++){
        a[i] = pi(A[i], B[i]);
    }
    sort(a,a+n);
    rtree.init(n);
}
 
stack<int> sx, sy, cnt;
 
int can(int M, int K[]) {
    while(!sx.empty()){
        sx.pop();
        sy.pop();
        cnt.pop();
    }
    sort(K, K+M);
    sx.push(0);
    sy.push(n);
    cnt.push(0);
    for(int i=0; i<M; i++){
        while(!sy.empty() && sy.top() < K[i]){
            sx.pop();
            sy.pop();
            cnt.pop();
        }
        int sum = K[i], st = K[i] - 1, ed = -1;
        while(!sx.empty()){
            int minus = rtree.query(sx.top() + 1, K[i], st + 1, sy.top()) + cnt.top();
            if(sum > minus) sum -= minus;
            else{
                ed = sy.top();
                break;
            }
            st = sy.top();
            sx.pop();
            sy.pop();
            cnt.pop();
        }
        if(ed == -1) return 0;
        int s = rtree.kth(sx.top() + 1, K[i], sum + rtree.query(sx.top() + 1, K[i], 0, st)); // Lower bound
        s = min(s, ed);   
        int tmp  = rtree.query(sx.top() + 1, K[i], st + 1, s) - sum;
        sx.push(K[i]);
        sy.push(s);
        cnt.push(tmp);
    }
    return 1;
}