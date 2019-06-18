#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
map<int,int> mp;
typedef map<int,int> ::iterator aauto;
 
int n;
int cnt[100005];
pi q[100005];
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&q[i].first,&q[i].second);
    }
    sort(q,q+n);
    for (int i=0; i<n; i++) {
        int h = q[i].second;
        mp[q[i].first]--;
        int piv = q[i].first-h;
        aauto it = mp.lower_bound(piv);
        pi t = *it;
        mp.erase(it);
        int gap = t.first - piv;
        if(t.second != -1) mp.insert(pi(t.first,t.second + 1));
        it = mp.lower_bound(piv);
        if(it == mp.begin()){
            mp[gap]--;
        }
        else{
            it--;
            t = *it;
            mp.erase(it);
            if(t.second != -1) mp.insert(pi(t.first,t.second + 1));
            mp[t.first + gap]--;
        }
    }
    long long ret = 0, cnts = 0;
    for (int i=q[n-1].first; i>=0; i--) {
        ret += cnts * (cnts - 1) / 2;
        cnts -= mp[i];
    }
    printf("%lld",ret);
}
