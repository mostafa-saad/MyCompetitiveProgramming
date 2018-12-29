/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lams6.cpp                                                 *
 *   Autor:    Michal Brzozowski                                         *
 *   Opis:     Rozwiazanie zbyt wolne, podstawa reprezentacji duzych     *
 *             liczb jest 10.                                            *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;

int base=10;

const int l_length = 20000;

struct liczba {
    int c[l_length];
    int l;
    liczba():l(0){
    for (int i=0;i<l_length;++i)
        c[i]=123;
        c[0]=0;
    }
    liczba& sub(const liczba& a){
        int r=0;
    liczba& ret(*this);
        for (int i=0;i<a.l || r!=0;++i){
            ret.c[i] = (i<ret.l ?ret.c[i] :0) - (i<a.l ? a.c[i] :0) - r;
            if (ret.c[i]<0){
                ret.c[i]+=base;
                r=1;
            } else r=0;
        }
    while (ret.l>0 && ret.c[ret.l-1]==0)
        --ret.l;
        return ret;
    }

    liczba div(LL a){
    liczba ret;
    int z = l;
    LL r = 0;
    while (z>0){
        while (r<a){
        r = base * r + c[z-1];
        ret.c[z-1] = 0;
        --z;
        }
        ret.l = max(ret.l, z+1);
        ret.c[z] = r/a;
        r = r%a;
    }
    return ret;
    }
   liczba& times(LL a){
    liczba& ret(*this);
        int r=0, nl=0;
        for (int i=0;i<ret.l || r>0;++i){
            LL mul = (i<ret.l ? ret.c[i] : 0)*a + r;
        ret.c[i] = mul%base;
        r = mul/base;
        nl = i+1;
        }
    if (nl>ret.l)
        ret.l = nl;
    assert(ret.l<=l_length);
        return ret;
    }


};



ostream& operator << (ostream& s, liczba a){
    for (int i=a.l-1;i>=0;i--)
    s << a.c[i];
    if (a.l==0)
    s << 0;
    return s;
}

liczba dl(LL a){
    liczba ret;
    if (a==0)
    return ret;
    for (ret.l = 0;a;++ret.l, a/=base)
    ret.c[ret.l] = a%base;
    return ret;
}

LL ld(liczba a){
    LL ret=0;
    for (int i=a.l-1;i>=0;--i)
    ret = ret*base + a.c[i];
    return ret;   
}

LL nwdl(LL a, LL b){
    if (b==0) return a;
    return nwdl(b,a%b);
}



LL nwdi(liczba a, LL b){
    LL pom=0;
    for (int i=a.l-1;i>=0;--i)
      pom=(pom*base+a.c[i])%b;
    return nwdl(b, pom);
}


vector<string> out;

int main(){
    ios_base::sync_with_stdio();
    liczba licz, mian;
    int num[1000],n;
    char buf[100];
    cin >> n;
    for (int i=0;i<n;++i)
    cin >> num[i];

    sprintf(buf,"1/%d",num[n-1]);
    out.push_back(buf);
    mian = dl(num[n-1]);
    licz = dl(1);

    for (int i=n-2;i>=0;--i){
    int plicz = num[i+1]-1, pmian = num[i];
    if (plicz == 0)
        licz = dl(0);
    if (licz.l>0){
        int pnwd = nwdl(plicz,pmian);
        plicz/=pnwd;
        pmian/=pnwd;
        int lg = nwdi(licz, pmian), lm = nwdi(mian, plicz);
        pmian /= lg;
        plicz /= lm;
        mian = mian.div(lm);
        licz = licz.div(lg);
        mian = mian.times(pmian);
        licz = licz.times(plicz);
    } else 
        mian = dl(1);

    ostringstream os;
    os << licz<<'/'<<mian;
    out.push_back(os.str());
    }
    for (int i=n-1;i>=0;--i)
    cout << out[i]<<endl;
    return 0;
}
