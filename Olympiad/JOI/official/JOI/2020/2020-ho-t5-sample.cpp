#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long Int;
typedef pair<Int, Int> P;
#define LINF (1LL<<60)

const int Base = 220000;
struct BIT{
    int n;
    Int bit[Base * 2 + 1];
    BIT(Int n):n(n){}

    void add(int ind, Int val){
        ind += Base;
        while(ind < n){
            bit[ind] += val;
            ind += ind & -ind;
        }
    }

    Int sum(int ind){
        Int ans = 0;
        ind += Base;
        while(ind){
            ans += bit[ind];
            ind -= ind & -ind;
        }
        return ans;
    }
};

vector<P> task1[440000], task2[440000], task3[440000], task4[440000], task5[440000];
BIT bit1(440000), bit2(440000), bit3(440000), bit4(440000),bit5(440000);

Int calc(Int t, Int x){
    return (x-t) * (bit1.sum(x-t) + bit2.sum(x)) + (bit3.sum(x-t) + bit4.sum(x)) + t * bit5.sum(x);
}

void add_triangle(Int l, Int r, Int v){
    task1[0].emplace_back(l+1, v);
    task2[0].emplace_back(r, -v);
    task3[0].emplace_back(l+1, -l*v);
    task4[0].emplace_back(r, (r-1)*v);
    task5[0].emplace_back(r, -v);
    task1[r-l].emplace_back(l+1, -v);
    task2[r-l].emplace_back(r, v);
    task3[r-l].emplace_back(l+1, l*v);
    task4[r-l].emplace_back(r, -(r-1)*v);
    task5[r-l].emplace_back(r, v);
}

int a[Base], left[Base], right[Base];
int l[Base], r[Base];
Int ans[Base];
vector<int> query[Base];
vector<P> stk;
int n, q, t;

int main(){
    scanf("%d%d", &n, &q);
    for(Int i = 0;i < n;i++)scanf("%d", &a[i]);

    stk = {{LINF, -n-1}};
    for(Int i = 0;i < n;i++){
        while(stk.back().first <= a[i])stk.pop_back();
        ::left[i] = stk.back().second;
        stk.push_back({a[i], i});
    }
    stk = {{LINF, n+1}};
    for(Int i = n-1;i >= 0;i--){
        while(stk.back().first < a[i])stk.pop_back();
        ::right[i] = stk.back().second;
        stk.push_back({a[i], i});
    }

    for(Int i = 0;i < n;i++){
        add_triangle(::left[i], ::right[i], a[i]);
        add_triangle(::left[i], i, -a[i]);
        add_triangle(i, ::right[i], -a[i]);
    }

    for(Int i = 0;i < q;i++){
        scanf("%d%d%d", &t, &l[i], &r[i]);l[i]--,r[i]--;
        query[t].emplace_back(i);
    }

    for(Int t = 0;t <= n;t++){
        for(auto tmp: task1[t])bit1.add(tmp.first, tmp.second);
        for(auto tmp: task2[t])bit2.add(tmp.first, tmp.second);
        for(auto tmp: task3[t])bit3.add(tmp.first, tmp.second);
        for(auto tmp: task4[t])bit4.add(tmp.first, tmp.second);
        for(auto tmp: task5[t])bit5.add(tmp.first, tmp.second);
        
        for(Int i: query[t]){
            ans[i] = calc(t, r[i]) - calc(t, l[i]-1);
        }
    }

    for(int i = 0;i < q;i++)printf("%lld\n", ans[i]);
    return 0;
}
