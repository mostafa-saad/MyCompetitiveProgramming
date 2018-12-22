#include<cstdio>
using namespace std;

int main()
{
    int h1, m1, h2, m2, h_per1, m_per1, h_per2, m_per2;
    scanf("%d:%d\n%d:%d\n%d:%d\n%d:%d",
          &h1, &m1, &h2, &m2, &h_per1, &m_per1, &h_per2, &m_per2);
    int t1 = h1 * 60 + m1;
    int t2 = h2 * 60 + m2;
    int p1 = h_per1 * 60 + m_per1;
    int p2 = h_per2 * 60 + m_per2;
    bool naso = 0;
    for(int i=0; i<10000; i++)
    {
        int nt = t1 + i*p1;
        if( nt < t2 || (nt-t2)%p2 != 0 ) continue;
        naso = 1;
        int m = nt%60; nt /= 60;
        int h = nt%24; nt /= 24;
        int d = nt%7;
        if( d == 0 ) printf("Saturday\n");
        if( d == 1 ) printf("Sunday\n");
        if( d == 2 ) printf("Monday\n");
        if( d == 3 ) printf("Tuesday\n");
        if( d == 4 ) printf("Wednesday\n");
        if( d == 5 ) printf("Thursday\n");
        if( d == 6 ) printf("Friday\n");
        printf("%02d:%02d\n", h, m );
        break;
    }
    if( !naso ) printf("Never\n");
    return 0;
}
