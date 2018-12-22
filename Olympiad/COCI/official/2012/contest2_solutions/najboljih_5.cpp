#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector< pair<int,int> > v;

bool cmp1( pair<int,int> a, pair<int,int> b ) { return a.second > b.second; }
bool cmp2( pair<int,int> a, pair<int,int> b ) { return a.first < b.first; }

int main()
{
    for(int i=1; i<=8; i++)
    {
        int x; cin >> x;
        v.push_back(make_pair(i, x));
    }
    sort(v.begin(), v.end(), cmp1);
    int s = 0;
    for(int i=0; i<5; i++) s += v[i].second;
    cout << s << endl;
    sort(v.begin(), v.begin()+5, cmp2);
    for(int i=0; i<5; i++) cout << v[i].first << " ";
    cout << endl;
    return 0;
}
