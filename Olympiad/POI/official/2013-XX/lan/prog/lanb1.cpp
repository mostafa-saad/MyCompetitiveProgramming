/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n*(n+m))                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zawsze sprawdzamy lancuchy od okreslonego     *
 *                         miejsca do konca.                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#define MAX 1000001

using namespace std;


int n,m,k,i,sum,j,ans=0;

vector<int> v;
int akt[MAX]; //Przechowuje ile jest koralikow danego koloru
int sup[MAX]; // ile powinno byc koralikow danego koloru


int main() {
    scanf("%d %d",&n,&m);
    for(i=0; i<m; i++) {
        scanf("%d",&k);
        v.push_back(k);
        sum+=k;
    }

    for(i=0; i<m; i++) {
        scanf("%d",&k);
        k--;
        sup[k]=v[i];
    }

    v.clear();

    for(i=0; i<n; i++) {
        scanf("%d",&k);
        k--;
        v.push_back(k);
    }

    for(i=0; i<n; i++) {
        for(j=i; j<n; j++) {
            akt[v[j]]++;
        }

        for(j=0; j<m; j++) {
            if(akt[v[j]]!=sup[v[j]])  break;
        }

        if(j==n) {
            ans++;
        }

        for(j=0; j<n; j++) {
            akt[j]=0;
        }
    }
    printf("%d\n",ans);


    return 0;
}
