/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Jedynki (JED)                                             *
 *   Plik:     jedb0.cpp                                                 *
 *   Autor:    Przemyslaw Horban                                         *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *             Rozwiazanie dziala tylko dla niektorych danych            *
 *             wejsciowych - liczb ktore sa duzymi potegami dwojki oraz  *
 *             tych ktore maja mniej niz 62 bity reprezentacji dwojkowej.*
 *                                                                       *
 *************************************************************************/ 

#include<iostream>
#include<iomanip>
#include<stack>
#include<cstdio>
#include<cmath>
#include<cassert> /* DO NOT DEFINE NDEBUG */
#include<queue>
#include<vector>
#include<list>
#include<algorithm>
#include<map>
#include<cstring>
#include<cctype>

using namespace std;
#define fe(e,C) for(__typeof((C).begin()) e = (C).begin(); e != (C).end(); e++)
#define fi(i,n) for(int i = 0, i##end = (n); i < i##end; i++)
#define ft(i,a,b) for(int i = (a), i##end = (b); i <= i##end; i++)
#define fd(i,a,b) for(int i = (a), i##end = (b); i >= i##end; i--)
#define fs(i,C) fi(i,(C).size())
#define ALL(V) (V).begin(), (V).end()
#define SET(T, c) memset(T, c, sizeof(T))
#define VI vector<int>
#define PB push_back
#define PII pair<int, int>
#define SEC second
#define FST first
#define MP make_pair
#define SZ(C) (C).size()
#define SQR(a) ((a)*(a))

typedef long long LL;

int ri() { int n; assert(1==scanf(" %d", &n)); return n; }
template<class R, class T>
R conv(const T &t) { stringstream ss; ss << t; R r; ss >> r; return r; }
LL gcd(LL a, LL b) { if(b == 0) return a; else return gcd(b, a % b); }

struct Seq {
    int length;
    char type;
};

vector<Seq> V;
int sum_len;

LL cutToLL() {
    LL n = 0;
    int cutBits = 0;
    while(!V.empty() && cutBits < 61) {
        if(V.back().type)
            n |= ((LL) 1 << cutBits);
        V.back().length--;
        cutBits++;
        if(V.back().length == 0)
            V.pop_back();
    }
    return n;
}

int lgr(long long n) {
    int cnt = 0;
    int lb = 0;
    while(n != 0) {
        if(n & 1) {
            cnt += (lb == 0);
            lb = 1;
        }
        else
            lb = 0;
        n /= 2;
    }
    return cnt;
}

long long ls(long long n) {
    return n / 2 + lgr(n);
}

int cs(long long n) {
    int c = 0;
    while(n != 0) {
        c++;
        n /= 2;
    }
    return c;
}

LL hbit(LL nn) {
    LL n = nn;
    LL hb = ((LL)1 << (cs(n) - 1));
    LL r;
    for(r = 1; r <= (n >> 1); r <<= 1)
        n &= ~r;
    assert(hb == n);
    return n;
}

LL ps(LL n) {
    LL tk = hbit(n);
    LL s = (tk >> 1) + 1;
    if(n & (tk >> 1)) {
        return s + (tk >> 1) - 1;
    }
    else {
        return s + n - tk;
    }
}



void solve_small_case() {
    LL n = cutToLL();
    //cout << "Read n=" << n << " form input"<<endl;
    LL sks = ps(n) + ls(n) - cs(n);
    V.clear();
    fd(i, cs(sks)-1, 0) {
        int bit = (((LL)1 << i) & sks) != 0;
        if(V.empty() || V.back().type != bit) {
            V.push_back((Seq){1, bit});
        }
        else
            V.back().length++;
    }
    printf("%d\n", (int)V.size());
    fi(i, V.size()) {
       printf("%d", V[i].length);
       if(i == (int)V.size() - 1)
           putchar('\n');
       else
           putchar(' ');
    }
}

void solve_pow2_case() {
   LL r = sum_len - 3;
   //cout << "reductor="<<r<<endl;
   V.clear();
   int used = 0;
   while(r != 0) {
       char bit = 1 - (r % 2);
       used++;
       r /= 2;
       if(V.empty() || V.front().type != bit) {
           V.insert(V.begin(), (Seq){1, bit});
       }
       else
           V.front().length++;
   }
   if(V.front().type == 1) {
       V.front().length += sum_len - 1 - used;
   }
   else {
       V.insert(V.begin(), (Seq){sum_len - 1 - used, 1});
   }
   printf("%d\n", (int)V.size());
   fi(i, V.size()) {
       printf("%d", V[i].length);
       if(i == (int)V.size() - 1)
           putchar('\n');
       else
           putchar(' ');
   }
}


int main(){
    int n;
    assert(1==scanf("%d", &n));
    bool bit = 1;
    fi(i, n) {
        V.push_back((Seq){ri(), bit});
        sum_len += V.back().length;
        bit = 1 - bit;
    }

    if(sum_len <= 61)
        solve_small_case();
    else if(n == 2 && V[0].length == 1)
        solve_pow2_case();
    else
        puts("0");
    return 0;
}
