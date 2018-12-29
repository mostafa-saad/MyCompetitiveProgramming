/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     naj5.cpp                                                  *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Rozwiazanie weryfikujace.                                 *
 *             Uzywa testu Millera-Rabina z mnozeniem pseudopisemnym.    *
 *             o podstawie 2^30.                                         *
 *                                                                       *
 *************************************************************************/

/* - */
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <cstdlib>
#define VAR(i,a) __typeof(a) i = (a)
#define FORE(i,a) for(VAR(i,(a).begin()); i!=(a).end(); ++i)
#define LL long long
#define uLL unsigned long long
using namespace std;
LL gcd(LL a, LL b){ if(a==0) return b; return gcd(b%a, a); }
#define nwd gcd
/* * */

#define MAXN 1000
#define MAXP 100000
#define MAX_SITO 1000000

int n, pn=0;
LL liczby[MAXN];
LL pierwsze[MAXP];
int sito[MAX_SITO];
map<LL, int> N;

// return (a*b)%n
uLL mul(uLL a, uLL b, uLL n){
#define BASE (1ull<<30)
    uLL A[2] = {a%BASE, a/BASE};
    uLL B[2] = {b%BASE, b/BASE};
    uLL ret = (A[0]*B[0])%n;
    uLL tmp;
    tmp = (A[1]*B[1])%n;
    for(int i=0; i<10; i++)
        tmp = (tmp<<3)%n;
    tmp = (tmp + A[0]*B[1] + A[1]*B[0])%n;
    for(int i=0; i<10; i++)
        tmp = (tmp<<3)%n;
    ret = (ret+tmp)%n;
    return ret;
}

//return (a**b)%n
LL pow(LL a, LL b, LL n){
    LL ret=1;
    while(b){
        if(b%2) ret = mul(ret, a, n);
        b/=2;
        a = mul(a, a, n);
    }
    return ret;
}

//test millera-rabina
bool witness(LL a, LL n){
    int t=0;
    LL x, n1=n-1;
    while(n1%2==0){
        t++; n1/=2;
    }
    x = pow(a, n1, n);
    for(int i=0; i<t; i++){
        LL nx = mul(x, x, n);
        if(nx==1 && x!=1 && x!=n-1)
            return true;
        x=nx;
    }
    return x!=1;
}

bool pierwsza(LL n){
    for(int i=0; i<20; i++)
        if(witness(1ll+((LL)random()%(n-1)), n))
            return false;
    return true;
}

//wypisuje (2**n)-1
void pow2(int n){
    vector<int> v(n+1); v[0]=1;
    for(int a=0; a<n; a++)
        for(int i=n-1; i>=0; i--){
            v[i]*=2; v[i+1]+=v[i]/10; v[i]%=10;
        }
    v[0]--;
    for(int i=0; i<n; i++)
        if(v[i]<0){
            v[i]+=10; v[i+1]--;
        }
    while(!v.back()) v.pop_back();
    for(int i=v.size()-1; i>=0; i--) printf("%i", v[i]);
}

int main(void){
    pierwsze[pn++] = 2;
    for(int i=3; i<MAX_SITO; i+=2){
        if(sito[i]) continue;
        pierwsze[pn++] = i;
        for(int j=i; j<MAX_SITO; j+=2*i) sito[j]=i;
    }

    scanf("%i", &n);
    for(int i=0; i<n; i++){
        LL a;
        scanf("%lld", &a);
        for(int j=0; j<pn; j++)
            while(!(a%pierwsze[j])){
                N[pierwsze[j]]++;
                a/=pierwsze[j];
            }
        liczby[i]=a;
    }
    set<LL> p;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            LL t=nwd(liczby[i], liczby[j]);
            if(t!=1 && (t!=liczby[i] || t!=liczby[j])){
                p.insert(t);
            }
        }
        LL tmp=(LL)sqrt(liczby[i]);
        for(LL j=max(tmp-5,2ll); j<tmp+5; j++){
            if(j*j==liczby[i]){
                p.insert(j);
            }
        }
    }
    for(int i=0; i<n; i++){
        FORE(it, p){
            while(!(liczby[i]%*it)){
                N[*it]++;
                liczby[i]/=*it;
            }
        }
    }

    for(int i=0; i<n; i++){
        if(liczby[i]!=1){
            N[liczby[i]] += 1;
        }
    }

    int k=0, D=0;
    FORE(it, N){
        if(it->second > k){
            k = it->second;
            D=1 + !pierwsza(it->first);
        }else if(it->second == k){
            D+= 1 + !pierwsza(it->first);
        }
    }
    printf("%i\n", k);
    pow2(D);
    printf("\n");
    return 0;
}
