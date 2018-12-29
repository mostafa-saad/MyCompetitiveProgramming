/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego miejsca i zliczamy ciagi          *
 *                         dlugosci 1..n-i, ktore sa dobre.              *
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

bool czy_dobry() {

    for(int i=0; i<n; i++) {
        if(akt[i]!=sup[i])return false;
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
