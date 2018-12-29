/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Straz pozarna (STR)                                       *
 *   Plik:     strs1.cpp                                                 *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie nieefektywne O(p*z). Dla kazdej pary stacji   *
 *             po prostu iteruje po wszystkich zabytkach.                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int Z = 100000;

int n,m,z,p,x[Z],y[Z];

int main()
{
    scanf("%d %d %d %d",&n,&m,&z,&p);
    for(int i=0; i<z; i++)
        scanf("%d %d",&x[i],&y[i]);
    for(int j=0; j<p; j++)
    {
        int a,b,c,d,w;
        int A=0,C=0;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        for(int i=0; i<z; i++)
        {
            w = ( abs(x[i]-a) + abs(y[i]-b) ) - ( abs(x[i]-c) + abs(y[i]-d) ) ;
            if(w<0) A++;
            else if(w>0) C++;
        }
        printf("%d %d %d\n",A,C,z-A-C);
    }
    return 0;
}
