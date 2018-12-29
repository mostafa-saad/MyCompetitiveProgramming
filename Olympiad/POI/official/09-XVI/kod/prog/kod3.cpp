/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kod3.cpp                                                  *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie wzorcowe O(L)                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int M = 601000;

char buf[5*M];
int dane[2*M], lisc[2*M], jeden[2*M], zero[2*M];
int g = 1, m;

int zm, kom;

void szuk(int a,int b)
{
    if(lisc[b]) 
    {
        if(zm == 1)
            return;
        if(zm == 2 && !lisc[a]) 
            dane[lisc[b]] |= 4;
        b = 0;
    }
    if(!lisc[a])
    {
        szuk(jeden[a],jeden[b]);
        szuk(zero[a], zero[b]);
    }
    else
        dane[kom?(b?lisc[a]:0):b] |= zm;
}

void przesz(int pocz, int zmiana, bool komu)
{
    zm = zmiana;
    kom = komu;
    for(int i = 1; i < g; i++)
        if((dane[i]&pocz) == pocz)
            szuk(i,0);
}

int main()
{
    int n;
    scanf("%d %s",&n,buf);
    int ee=1;
    for(int i = 0; i < n; i++) 
        if(buf[i]=='B') 
            dane[ee--] = 0;
        else if(buf[i]=='X') 
            lisc[dane[ee-1]] = ++m;
        else if(buf[i]=='1')
        {
            jeden[dane[ee-1]] = g;
            dane[ee++] = g++;
        }
        else if(buf[i]=='0')
        {
            zero[dane[ee-1]] = g;
            dane[ee++] = g++;
        }
    przesz(0,1,0);
    przesz(1,2,0);
    przesz(2,4,1);
    int ret = 0;
    for(int i = 1; i<=m; i++) 
        if((dane[i]&4) != 4) 
            ret++;
    printf("%d\n",ret);
    for(int i = 1; i<=m; i++) 
        if((dane[i]&4) != 4) 
            printf("%d\n",i);
}
