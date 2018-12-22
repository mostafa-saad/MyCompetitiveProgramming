#include<cstdio>
#include<vector>
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    vector<int> brodovi;

    for(int i=0; i<n; i++)
    {
        int x; scanf("%d", &x);
        x--; if(i == 0) continue;

        for(int j=0; j<(int)brodovi.size(); j++)
            if( x % brodovi[j] == 0 )
            {
                x = -1;
                break;
            }
        if( x != -1 ) brodovi.push_back(x);
    }
    printf("%d\n", (int)brodovi.size() );

    return 0;
}
