#include<iostream>
using namespace std;

int main()
{
    int n, sol = 0;
    cin >> n;
    int a[n];

    for(int i=0; i<n; i++)
        cin >> a[i];

    for(int i=n-2; i>=0; i--)
        if( a[i] >= a[i+1] )
        {
            sol += a[i] - a[i+1] + 1;
            a[i] = a[i+1] - 1;
        }

    cout << sol << endl;
    return 0;
}
