#include<iostream>
using namespace std;

int main()
{
    int s = 0;
    for(int i=0; i<10; i++)
    {
        int x; cin >> x;
        if( s+x >= 100 )
        {
            if( s+x-100 <= 100-s ) s += x;
            cout << s << endl;
            return 0;
        }
        s += x;
    }
    cout << s << endl;
    return 0;
}
