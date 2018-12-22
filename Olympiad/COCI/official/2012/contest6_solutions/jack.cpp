#include<iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int a[n];
    for(int i=0; i<n; i++) cin >> a[i];
    int sol = 0;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            for(int k=j+1; k<n; k++)
                if( a[i]+a[j]+a[k] <= m )
                    sol = max( sol, a[i]+a[j]+a[k] );
    cout << sol << endl;
    return 0;
}
