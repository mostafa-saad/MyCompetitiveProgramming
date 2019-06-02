/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lams1.cpp                                                 *
 *   Autor:    Michal Brzozowski                                         *
 *   Opis:     Rozwiazanie zbyt wolne, reprezentuje duze liczby          *
 *             za pomoca rozkladow na czynniki pierwsze.                 *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>

using namespace std;

const int nprime = 60000;

int primes[nprime];

int cprime=0;

int base = 1000000000;
int basel=9;

typedef long long LL;

void razy(LL *c, int& k, LL n){
    LL r = 0;
    int tmp=0;
    for (int i=0; i<k || r>0 ;++i){
    LL a = i<k ? c[i] : 0;
    a = a*n + r;
    c[i] = a % base;
    r = a / base;
    if (c[i])
    tmp=i+1;
    }
    k= tmp;
}

struct pr_liczba {
    bool zero;
    int p[nprime];
    pr_liczba(){
    zero=false;
    for (int i=0;i<nprime;++i)
        p[i]=0;
    }
    pr_liczba(int k){
    zero=false;
    if (!k){
        zero=true;
        for (int i=0;i<nprime;++i)
        p[i]=0;
    } else
    for (int i=0;i<cprime;++i){
        p[i]=0;
        while (k%primes[i] == 0){
        ++p[i];
        k/=primes[i];
        }
    }
    }
    void razy(const pr_liczba& l){
    if (l.zero) zero=true;
    for (int i=0;i<cprime;++i)
        p[i]+=l.p[i];
    }
    void skroc(pr_liczba& l){
    for (int i=0;i<cprime;++i){
        int k = min(p[i], l.p[i]);
        p[i]-=k;
        l.p[i]-=k;
    }
    }
    void napis(LL *c, int &k){
    if (zero){
        c[0]=0;
        k=1;
        return;
    }
    c[0]=1;
    for (int i=0;i<cprime;++i){

        int j=0;
        while (j<p[i]){
        LL mno=primes[i];
        ++j;
        while (mno * primes[i] < 2000000000 && j<p[i]){
            mno*=primes[i];
            ++j;
        }
        ::razy(c, k, mno);
        }

        /*for (int j=0;j<p[i];++j){
        if (j<p[i]-1 && LL(primes[i])*LL(primes[i])<2000000000){
            ::razy(c, k, primes[i]* primes[i]);
            ++j;
        } else
        ::razy(c, k, primes[i]);
        }*/
    }
    }
};

LL nwd(LL a, LL b){
    if (b==0) return a;
    return nwd(b, a%b);
}

struct int_liczba {
    LL i;
    int_liczba():i(1){}
    int_liczba(LL k):i(k){}
    void razy(const int_liczba& l){
    i*=l.i;
    }
    void skroc(int_liczba& l){
    LL g = nwd(i, l.i);
    i/=g;
    l.i/=g;
    }
    void napis(LL *c, int &k){
    LL a = i;
    while (a){
        c[k-1] = a%base;
        a/=base;
        if (a) ++k;
    }
    }
};

typedef pr_liczba liczba;

LL buf[1000000];
void rozklad(int k){
    while (k>1){
    bool podz=false;
    for (int i=2;i*i<=k;++i)
        if (k%i==0) { 
        podz=true;
        k/=i;
        primes[cprime++]=i;
        }
    if (!podz){
        primes[cprime++]=k;
        break;
    }
    }
}

    int n;
int main(){
    cin >> n;

    int num[1000];

    for (int i=0;i<n;++i){
    cin >> num[i];
    rozklad(num[i]);
    rozklad(num[i]-1);
    }
    sort(primes, primes+cprime);
    int tab[nprime];
    int tmp=0;
    for (int i=0;i<cprime;++i)
    if (i==0 || primes[i]!=primes[i-1]) tab[tmp++] = primes[i];
    cprime = tmp;
    for (int i=0;i<cprime;++i){
    primes[i]=tab[i];
    //cout << primes[i]<<' ';
    }
    //cout <<endl;

    liczba licz, mian(num[n-1]);
    int bufsize=1;
    vector<string> out;
    char tbuf[100];
    sprintf(tbuf,"1/%d",num[n-1]);
    out.push_back(tbuf);
    for (int i=n-2;i>=0;--i){
    licz.razy(liczba(num[i+1]-1));
    mian.razy(liczba(num[i]));
    licz.skroc(mian);
    bufsize=1;
    licz.napis(buf, bufsize);
    ostringstream os;
    os.fill('0');
    for (int i=bufsize-1;i>=0;--i){
        if (i<bufsize-1)
        os.width(basel); else
        os.width(0);
        os << right << buf[i];
    }
    os <<'/';
    bufsize=1;
    os.fill('0');
    if (licz.zero)
        mian = liczba(1);
    mian.napis(buf, bufsize);
    for (int i=bufsize-1;i>=0;--i){
        if (i<bufsize-1)
        os.width(basel); else
        os.width(0);
        os << right << buf[i];
    }
    out.push_back(os.str());
    }
    for (int i=n-1;i>=0;--i)
    cout << out[i]<<endl;

}
