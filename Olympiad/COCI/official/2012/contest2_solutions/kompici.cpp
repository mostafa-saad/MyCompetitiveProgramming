#include<cstdio>
#include<ctime>
#include<cstring>
#include<iostream>

using namespace std;

long long sol;
int kol[1<<10];

int main()
{
    int n; scanf("%d", &n);
    char buff[22];
    while(n--)
    {
              scanf("%s", buff);
              int s = strlen(buff);
              int mask = 0;
              for(int i=0; i<s; ++i)
                     mask |= (1<<(buff[i]-'0'));
              kol[mask]++;
    }
    for(int i=0; i<1024; i++)
            for(int j=i+1; j<1024; j++)
                    if( i & j ) sol += (long long)kol[i] * kol[j];
    for(int i=0; i<1024; i++) sol += (long long)kol[i]*(kol[i]-1)/2;
    cout << sol << endl;
    //fprintf(stderr, "%.2lf\n", clock()*1.0/CLOCKS_PER_SEC );
    return 0;
}
