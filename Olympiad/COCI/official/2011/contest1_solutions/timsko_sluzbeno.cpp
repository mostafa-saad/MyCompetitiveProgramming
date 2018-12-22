#include<iostream>
using namespace std;

int main ()
{
    int m, n, k;
    cin >> m >> n >> k;
    int rjesenje = 0;
    while(m >= 2 && n >= 1 && m+n >= k+3)
    {
        rjesenje++;
        m -= 2;
        n -= 1;
    }
    cout << rjesenje << endl;
    return 0;
}
