/*/
   GLO
   O(nlogn)
   Author: Aleksander Lukasiewicz
/*/
#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 2*100*1000;

int n, x;
int temperature[MAXN + 3], res_without_shift[MAXN + 3], res_with_shift[MAXN + 3];
unordered_map<int, int> renum;
vector<int> V;

int tree_without[4*MAXN + 3], tree_with[4*MAXN + 3];

int query_max(int a, int b, int tree[]){
    if(b < a) return 0;
    a+=2*MAXN; b+=2*MAXN;
    int result = 0;
    while(a <= b){
        if(a % 2 == 1) result = max(result, tree[a]);
        if(b % 2 == 0) result = max(result, tree[b]);
        a = (a+1)/2;
        b = (b-1)/2;
    }
    
    return result;
}

void update(int a, int val, int tree[]){
    a += 2*MAXN;
    while(a >= 1){
        tree[a] = max(tree[a], val);
        a/=2;
    }
}

int main(){
    cin >> n >> x;
    for(int i=0; i<n; i++){
        cin >> temperature[i];
        V.push_back(temperature[i]);
        V.push_back(temperature[i] - x);
    }
    
    sort(V.begin(), V.end());
    for(int i=0; i<(int)V.size(); i++)
        renum[V[i]] = i;
    
    int result = 0;
    for(int i=0; i<n; i++){
        int r = renum[temperature[i]];
        res_without_shift[i] = query_max(0, r - 1, tree_without) + 1;
        res_with_shift[i] = query_max(0, r - 1, tree_with) + 1;
        update(r, res_without_shift[i], tree_without);
        update(r, res_with_shift[i], tree_with);
        update(renum[temperature[i]-x], res_without_shift[i], tree_with);
        result = max(result, res_without_shift[i]);
        result = max(result, res_with_shift[i]);
    }
    
    cout << result << "\n";
 
    return 0;
}
