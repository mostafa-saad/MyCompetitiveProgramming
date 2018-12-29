/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n * m))                                     *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Nie sprawdza pierwszego fragmentu lancucha    *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#define MAX 1000001

using namespace std;


int n,m,k,i,sum,j,ans=0,l;

vector<int> v,which;
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
        which.push_back(k);
    }

    v.clear();

    for(i=0; i<n; i++) {
        scanf("%d",&k);
        k--;
        v.push_back(k);
    }

    for(j=0; j<sum&&j<n; j++) {
        akt[v[j]]++;
    }

    for(i=j; i<n; i++) {

        akt[v[i-sum]]--;
        akt[v[i]]++;

        for(j=0; j<m; j++) {
            if(akt[which[j]]!=sup[which[j]])break;
        }
        if(j==m) {
            ans++;
        }
    }

    printf("%d\n",ans);
    return 0;
}
