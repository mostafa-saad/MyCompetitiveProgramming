/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Krzysztof Kiljan                              *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                         Zamiast wartosci liczbowej zleKolory trzymamy *
 *                         std::set zawierajacy zle kolory.              *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<set>
#include<vector>
#define MAX 1000001
using namespace std;

int n,m,i,j,k, ans=0;
long long sum=0;
set<int> unsatisfied;
vector<int> v;
int akt[MAX]; //Przechowuje ile jest koralikow danego koloru
int sup[MAX]; // ile powinno byc koralikow danego koloru

void all_sat() {
    for(int i=0; i<n; i++) {
        if(akt[i]!=sup[i]) unsatisfied.insert(i);
    }

}

bool is_sat(int x) {
    if(akt[x]==sup[x]) return true;
    else return false;
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



    if(sum>n) {
        printf("0\n");
    }
    else {
        i=0;
        while(i<sum) {
            akt[v[i]]++;
            i++;
        }
        all_sat();
        if(unsatisfied.size()==0) ans++;

        for(; i<n; i++) {
            akt[v[i-sum]]--;

            if(is_sat(v[i-sum])) {
                unsatisfied.erase(v[i-sum]);
            }
            else {
                unsatisfied.insert(v[i-sum]);
            }

            akt[v[i]]++;
            if(is_sat(v[i])) {
                unsatisfied.erase(v[i]);
            }
            else {
                unsatisfied.insert(v[i]);
            }


            if(unsatisfied.size()==0) ans++;
        }

        printf("%d\n",ans);
    }

    return 0;
}
