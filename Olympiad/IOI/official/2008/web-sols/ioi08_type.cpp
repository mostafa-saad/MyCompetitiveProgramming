#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
int n;
string s[25005];
vector<char> v;
 
int sm(string a, string b){
    int ret = 0;
    for (int i=0; i<a.size() && i<b.size(); i++) {
        if(a[i] == b[i]) ret++;
        else break;
    }
    return ret;
}
 
bool cmp(string a, string b){
    int sa = sm(s[0],a), sb = sm(s[0],b);
    if(sa == sb) return a < b;
    else return sa > sb;
}
 
bool cmp2(string a, string b){
    return a.size() < b.size();
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        char str[25];
        scanf("%s",str);
        s[i] = str;
    }
    swap(s[0],*max_element(s,s+n,cmp2));
    sort(s+1,s+n,cmp);
    reverse(s,s+n);
    for (int i=0; i<s[0].size(); i++) {
        v.push_back(s[0][i]);
    }
    v.push_back('P');
    for (int i=1; i<n; i++) {
        int l = sm(s[i-1],s[i]);
        for (int j=l; j<s[i-1].size(); j++) {
            v.push_back('-');
        }
        for (int j=l; j<s[i].size(); j++) {
            v.push_back(s[i][j]);
        }
        v.push_back('P');
    }
    printf("%d\n",(int)v.size());
    for (int i=0; i<v.size(); i++) {
        printf("%c\n",v[i]);
    }
}
