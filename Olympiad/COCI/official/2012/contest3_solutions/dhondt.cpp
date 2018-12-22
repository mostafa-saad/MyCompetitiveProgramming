#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int x, n;
    cin >> x >> n;
    string oznaka[n];
    int mandata[n];
    vector<double> glasova[n];
    for(int i=0; i<n; i++)
    {
        mandata[i] = 0;
        int y;
        cin >> oznaka[i] >> y;
        glasova[i].push_back(0.0);
        if( 1e-9 + (double)y < 0.05 * x ) { mandata[i] = -1; continue; }
        for(int j=14; j>0; --j) glasova[i].push_back((double)y/j);
    }
    for(int mandat=0; mandat<14; mandat++)
    {
        double maks = 0;
        int lista = -1;
        for(int i=0; i<n; i++)
            if( maks < glasova[i].back() )
            {
                maks = glasova[i].back();
                lista = i;
            }
        mandata[lista]++;
        glasova[lista].pop_back();
    }
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if( oznaka[i] > oznaka[j] )
            {
                swap(oznaka[i], oznaka[j]);
                swap(mandata[i], mandata[j]);
            }
    for(int i=0; i<n; i++)
        if( mandata[i] >= 0 )
            cout << oznaka[i] << ' ' << mandata[i] << endl;
    return 0;
}
