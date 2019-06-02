/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n^2 * m))                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Nie zaklada spojnosci ladnych podlancuchow    *
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

bool czy_dobry() {

    for(int i=0; i<m; i++) {
        if(akt[which[i]]!=sup[which[i]])return false;
    }

    return true;

}


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
        which.push_back(k);
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
            if(czy_dobry()) {
                ans++;
            }
        }
        for(j=0; j<n; j++) {
            akt[j]=0;
        }
    }
    printf("%d\n",ans);



    return 0;
}
