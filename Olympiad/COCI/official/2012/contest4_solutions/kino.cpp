#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
    int n; cin >> n;
    string s; cin >> s;
    int casa = n+1;
    int ljubavnih = 0;
    for(int i=0; i<n; i++) if( s[i] == 'L' ) ljubavnih++;
    casa -= ljubavnih/2;
    cout << min( casa, n ) << endl;
    return 0;
}
