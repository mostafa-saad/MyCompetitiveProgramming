#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
 
int n;
lint a[300005], s[300005];
  
struct cht{
    map<lint,lint> mp;
    void init(){
        mp.clear();
    }
    long double cross(pi a, pi b){
        return (long double)1.0 * (b.second - a.second) / (a.first - b.first);
    }
    void add(lint a, lint b){
        if(mp.find(a) != mp.end()){
            if(mp[a] > b) mp[a] = b;
            else return;
        }
        else{
            auto high = mp.lower_bound(a);
            if(high != mp.begin() && high != mp.end()){
                auto low = high;
                low--;
                if(cross(*low, pi(a,b)) < cross(pi(a,b), *high)){
                    return;
                }
            }
        }
        mp[a] = b;
        auto tmp = ++mp.lower_bound(a);
        if(tmp != mp.end()){
            auto tmp2 = tmp;
            tmp2++;
            while(tmp2 != mp.end() && cross(pi(a,b), *tmp) <= cross(*tmp, *tmp2)){
                mp.erase(tmp);
                tmp = tmp2;
                tmp2++;
            }
        }
        tmp = mp.lower_bound(a);
        if(tmp != mp.begin()){
            tmp--;
            auto tmp2 = tmp;
            if(tmp2 != mp.begin()){
                tmp2--;
                while(tmp2 != mp.begin() && cross(*tmp2, *tmp) <= cross(*tmp, pi(a,b))){
                    mp.erase(tmp);
                    tmp = tmp2;
                    tmp2--;
                }
                if(cross(*tmp2, *tmp) <= cross(*tmp, pi(a,b))){
                    mp.erase(tmp);
                }
            }
        }
    }
    lint query(lint x){
        auto it = mp.begin(), it2 = ++mp.begin();
        while(it2 != mp.end() && cross(*it, *it2) >= x){
            mp.erase(it);
            it = it2;
            it2++;
        }
        return it->first * x + it->second;
    }
}cht;
 
void solve(){
    lint ret = 1e18;
    for (int i=n; i; i--) {
        if(i != n) ret = min(ret,cht.query(i) - s[i-1]);
        cht.add(a[i],s[i] - 1ll * a[i] * (i+1));
    }
    printf("%lld\n",s[n] - ret);
}
  
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%lld",&a[i]);
        s[i] = a[i] + s[i-1];
    }
    solve();
    cht.init();
    reverse(a+1,a+n+1);
    for (int i=1; i<=n; i++) {
        s[i] = a[i] + s[i-1];
    }
    solve();
}