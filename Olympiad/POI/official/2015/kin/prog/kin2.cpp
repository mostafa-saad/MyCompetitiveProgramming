/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kinoman                                            *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O((n+m) log n)                                     *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include <vector>
#include <iostream>
#include <algorithm>
std::vector<int> torty;
int n, m, pom;
const int M=1048576;
template <typename datatype> class drzewo {
  public:
    drzewo(int i) {
        sum.resize(i+M+M);
        max.resize(i+M+M);
    };
    datatype add(int a, int b,datatype w) {
        //std::cout<<"add a: "<<a<<" b: "<<b<<" w: "<<w<<"\n";
        if(b<a){
            return 0;
            }
        int va = M + a, vb = M + b;
        /* Skrajne przedziały do rozkładu. */
        max[va]+=w;
        if (va != vb) {max[vb]+=w;}
        /* Spacer aż do momentu spotkania. */
        while (va / 2 != vb / 2) {
            if(va<M){
                if (va % 2 == 0){
                    sum[va + 1]+=w; /* prawa bombka na lewej ścieżce */
                    max[va+1]+=w;
                    }
                if (vb % 2 == 1){
                    sum[vb - 1]+=w; /* lewa bombka na prawej ścieżce */
                    max[vb-1]+=w;
                    }
                max[va]=std::max(max[va*2],max[va*2+1])+sum[va];
                max[vb]=std::max(max[vb*2],max[vb*2+1])+sum[vb];
            }else{
                if (va % 2 == 0)
                    max[va + 1]+=w; /* prawa bombka na lewej ścieżce */
                if (vb % 2 == 1)
                    max[vb - 1]+=w; /* lewa bombka na prawej ścieżce */
            }
            va /= 2;
            vb /= 2;
        }
        if(va<M)
            max[vb]=std::max(max[vb*2],max[vb*2+1])+sum[vb];
        while(va>0){
            if(va<M)
                max[va]=std::max(max[va*2],max[va*2+1])+sum[va];
            va/=2;
        }
//std::cout<<max[1]<<"\n";
        return max[1];
    }
    /*void add(int a, int b, datatype w) {
        for (int i = a; i <= b; i++) data[i] += w;
    };
    datatype max(int a, int b) {
        return *std::max_element(data.begin() + a, data.begin() + b + 1);
    };*/

  private:
    std::vector<datatype> sum;
    std::vector<datatype> max;
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin >> n >> m;
    std::vector<int> seanse, filmy;
    std::vector<int> ostatnio(m + 1, -1);
    std::vector<int> poprzednio(m + 1, -1);
    filmy.push_back(-1);
    drzewo<long long> d = drzewo<long long>(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> pom;
        seanse.push_back(pom);
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> pom;
        filmy.push_back(pom);
    }
    long long max = 0;
    for (int i = 0; i < n; i++) {
        int dzis_film = seanse[i];
        d.add(poprzednio[dzis_film] + 1, ostatnio[dzis_film],
              -filmy[dzis_film]);
        long long wyn=d.add(ostatnio[dzis_film] + 1, i, filmy[dzis_film]);
        poprzednio[dzis_film] = ostatnio[dzis_film];
        ostatnio[dzis_film] = i;
        max = std::max(/*d.max(0, i)*/wyn, max);
    }
    std::cout << max << "\n";
    return 0;
}
