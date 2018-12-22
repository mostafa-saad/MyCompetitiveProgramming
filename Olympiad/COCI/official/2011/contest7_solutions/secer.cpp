#include<iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int sol = 0;
    while (n%5 != 0)
    {
        n -= 3;
        sol++;
    }
    if( n < 0 ) cout << -1 << endl;
    else cout << sol + n/5 << endl;
    return 0;
}
