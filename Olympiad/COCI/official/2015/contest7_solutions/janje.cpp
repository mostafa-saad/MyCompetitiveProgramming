#include <cstdio>
#include <vector> 

typedef long long llint; 

using namespace std;

int N, K;
int povrh2[1001], povrh3[1001], color[20];

vector < pair <int, int> > E;

int three_colorings(int node) {
    
    int ret = 0;
    
    if (node == -1) {
        ret = 1;
        int mask = 0;
        for (int i = 0; i < (int) E.size(); ++i) {
            ret *= color[E[i].first] != color[E[i].second]; 
            mask |= 1 << color[E[i].first];
            mask |= 1 << color[E[i].second];
        } 
        return ret * (mask == 7);
    }

    for (int i = 0; i < 3; ++i) {
        color[node] = i;
        ret += three_colorings(node - 1);
    }
    
    return ret;
}
    
inline void meta() {

    llint ret = 0;
    E.push_back(make_pair(0, 1));
    E.push_back(make_pair(0, 2));
    E.push_back(make_pair(1, 2));
    E.push_back(make_pair(2, 3));
    E.push_back(make_pair(2, 4));
    E.push_back(make_pair(3, 4));

    ret += (llint) povrh3[K] * three_colorings(4);
    printf("%lld\n", ret);

}

inline void kuca_ili_cvijet() {
    
    llint ret = 0;
    E.push_back(make_pair(0, 1));
    E.push_back(make_pair(0, 2));
    E.push_back(make_pair(0, 3));
    E.push_back(make_pair(0, 4));
    E.push_back(make_pair(0, 5));
    E.push_back(make_pair(0, 6));
    E.push_back(make_pair(6, 7));
    E.push_back(make_pair(2, 3));
    E.push_back(make_pair(4, 5));
 
    ret += (llint) povrh3[K] * three_colorings(7);
    printf("%lld\n", ret);

}

inline void hsin() {
    llint ret = (llint) povrh2[K] * 2;
    
    E.push_back(make_pair(0, 1));
    E.push_back(make_pair(0, 2));
    E.push_back(make_pair(0, 3));
    
    ret += (llint) povrh3[K] * three_colorings(3);
    printf("%lld\n", ret);
}

inline void snjegovic() {
    llint ret = (llint) povrh2[K] * 2;
    
    E.push_back(make_pair(0, 1));
    E.push_back(make_pair(1, 2));
    E.push_back(make_pair(2, 3));
    E.push_back(make_pair(2, 4));
    E.push_back(make_pair(2, 5));
    E.push_back(make_pair(5, 6));
    E.push_back(make_pair(5, 7));
    E.push_back(make_pair(5, 8));
    E.push_back(make_pair(5, 9));
    E.push_back(make_pair(9, 10));
    E.push_back(make_pair(9, 11));
    E.push_back(make_pair(9, 12));
    E.push_back(make_pair(9, 13));

    ret += (llint) povrh3[K] * three_colorings(13);
    printf("%lld\n", ret);
          
}

inline void gusjenica() {
    llint ret = (llint) povrh2[K] * 2;
    ret += (llint) povrh3[K] * 3 * (1LL << 19);
    ret -= (llint) povrh2[K] * 2 * (K - 2);
    printf("%lld\n", ret);
}

inline void piramida() {
    printf("%lld\n", (llint) povrh3[K] * 6);
}

inline void trampolin() {
    printf("%lld\n", (llint) povrh2[K] * 2 + (llint) povrh3[K] * ((1LL << 30) - 4));
}

inline void init() {
    for (int i = 2; i <= 1000; ++i) povrh2[i] = i * (i - 1) / 2;
    for (int i = 3; i <= 1000; ++i) povrh3[i] = i * (i - 1) * (i - 2) / 6;
}

int main(void) {

    init();
    scanf("%d%d", &N, &K);

    if (N == 1) gusjenica();
    if (N == 2 || N == 7) kuca_ili_cvijet();
    if (N == 3) hsin();
    if (N == 4) snjegovic();
    if (N == 5) meta();
    if (N == 6) piramida();
    if (N == 8) trampolin();

    return 0;

}
