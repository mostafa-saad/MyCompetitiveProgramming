/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdej pozycji w ciagu sprawdzamy, czy    *
 *                         kolejne d elementow spelnia warunek zadania.  *
 *                         (d = suma wszystkich l[i])                    *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#define MAX 1000001

using namespace std;


int n,m,k,i,j,ans=0;
long long sum=0;
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
        for(j=i; j<n&&(j-i)<sum; j++) {
            akt[v[j]]++;
        }

        for(j=0; j<n; j++) {
            if(akt[j]!=sup[j])  break;
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
