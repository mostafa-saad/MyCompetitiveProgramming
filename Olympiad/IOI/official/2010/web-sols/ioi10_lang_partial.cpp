#include <map>
#include <algorithm>
#include <vector>
#include "lang.h"
#include "grader.h"
using namespace std;

// 99.026
struct WD{
    long long t1, t2;
    void init(){
        t1 = t2 = 0;
    }
    void addwd(int p, int pos){
        if(pos == 0) t1 = p;
        else t2 |= (1ll << (16 * (4 - pos))) * p;
    }
};
 
bool operator<(WD a, WD b){
    return a.t1 != b.t1 ? (a.t1 > b.t1) : (a.t2 > b.t2);
}
 
map<WD,int> mp;
vector<WD> v,u;
const int l = 5;
 
void excerpt(int *E){
    int cnt[105] = {};
    v.clear();
    for (int i=2; i<96; i++) {
        WD px;
        px.init();
        for (int j=0; j<l; j++) {
            px.addwd(E[i+j],j);
        }
        map<WD,int> ::iterator it = mp.lower_bound(px);
        if(it != mp.end()) cnt[(*it).second]++;
        v.push_back(px);
    }
    int mv = (int)(max_element(cnt,cnt+56) - cnt);
    int t = language(mv);
    for (int i=0; i<v.size(); i++) {
        mp[v[i]] = t;
    }
}