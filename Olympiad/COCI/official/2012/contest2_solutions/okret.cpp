#include<cstdio>

using namespace std;

int u[] = {0,0,1,-1};
int v[] = {1,-1,0,0};

int main()
{
    int r, s; scanf("%d%d", &r, &s);
    char a[r+2][s+2];
    for(int i=0; i<r; i++) scanf("%s", a[i]);
    int slijepih = 0;
    for(int i=0; i<r; i++)
        for(int j=0; j<s; j++)
            if( a[i][j] == '.' )
            {
                int deg = 0;
                for(int k=0; k<4; k++)
                {
                    int x = i + u[k];
                    int y = j + v[k];
                    if( x < 0 || y < 0 || x >= r || y >= s || a[x][y] == 'X' )
                        continue;
                    ++deg;
                }
                if( deg == 1 ) slijepih = 1;
            }
    printf("%d\n", slijepih);
    return 0;
}
