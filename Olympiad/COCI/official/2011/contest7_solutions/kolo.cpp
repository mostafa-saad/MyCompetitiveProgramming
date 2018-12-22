#include<iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    char a[n];
    for(int i=0; i<n; i++) a[i] = '?';
    int k; cin >> k;
    int x = 0;
    while(k--)
    {
        char c; int s;
        cin >> s >> c;
        while(s--)
        {
            x++;
            if( x == n ) x = 0;
        }
        if( a[x] != '?' && a[x] != c )
            { cout << "!" << endl; return 0; }
        a[x] = c;
    }
    for(int i=0; i<n; i++) for(int j=i+1; j<n; j++)
        if( a[i] == a[j] && a[i] != '?' ) { cout << "!" << endl; return 0; }
    for(int i=0; i<n; i++)
    {
        cout << a[x]; x--; if( x == -1 ) x = n-1;
    }
    cout << endl;
    return 0;
}
