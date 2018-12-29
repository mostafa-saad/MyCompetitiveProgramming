/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lams3.cpp                                                 *
 *   Autor:    Michal Brzozowski                                         *
 *   Opis:     Rozwiazanie zbyt wolne, NWD na duzych liczbach wyznaczane *
 *             za kazdym razem od nowa.                                  *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;

int base=10;

const int l_length = 10000;

struct liczba;

ostream& operator << (ostream& s, liczba a);
liczba dl(LL a);
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
    while (ret.c[ret.l-1]==0 && ret.l>0)
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
    int sdiv(liczba a, liczba b){
    for (int i=1;i<=base;++i){
        liczba m(b);
        if (a.less(m.times(i)))
        return i;
    }
    cout <<"sdiv error " << a <<" "<<b<<endl;
    exit(1);
    }
    liczba div(liczba a){
    liczba ret;
    if (a.l==1 && a.c[0]==1)
        return *this;
    if (less(a))
        return ret;
    int z = l;
    liczba r;
    while (z>0){
        while (r.less(a)&&z>0){
        r.times(base);
        r.add(c[z-1]);
        ret.c[z-1] = 0;
        --z;
        }
        ret.l = max(ret.l, z+1);
        ret.c[z]= sdiv(r,a)-1;
        liczba x(a);
        r = r.sub(x.times(ret.c[z]));
    }
    return ret;
    }
 
    liczba mod(liczba a){
    if (less(a))
        return *this;
    liczba ret;
    int z = l;
    liczba r;
    while (z>0){
        while (r.less(a) && z>0){
        r.times(base);
        r.add(c[z-1]);
        ret.c[z-1] = 0;
        --z;
        }
        ret.l = max(ret.l, z+1);
        ret.c[z]= sdiv(r,a)-1;
        liczba x(a);
        r = r.sub(x.times(ret.c[z]));
    }
    return r;
    }
    liczba& times(LL a){
    liczba& ret(*this);
    if (a==0){
        ret.l=0;
        return ret;
    }
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
    liczba& add(LL a){
    liczba& ret(*this);
        int r=0, nl=0;
    if (a>0 && l==0){
        c[l++]=0;
    }
        for (int i=0;i<ret.l || r>0;++i){
            LL mul = (i<ret.l ? ret.c[i] : 0)+a%base + r;
        ret.c[i] = mul%base;
        r = mul/base;
        nl = i+1;
        a/=base;
        }
    if (nl>ret.l)
        ret.l = nl;
    assert(ret.l<=l_length);
        return ret;
    }

    bool equal(const liczba& a)const{
        if (l<a.l) return false;
        if (l>a.l) return false;
        for (int i=l-1;i>=0;--i)
            if (c[i]!=a.c[i]) return false;
        return true;
    }

    bool less(const liczba& a)const{
        if (l<a.l) return true;
        if (l>a.l) return false;
        for (int i=l-1;i>=0;--i)
            if (c[i]>a.c[i]) return false; else
            if (c[i]<a.c[i]) return true;
        return false;
    }


};



ostream& operator << (ostream& s, liczba a){
    for (int i=a.l-1;i>=0;i--)
    s << a.c[i];
    if (a.l==0)
    s << 0;
    return s;
}
istream& operator >> (istream& s, liczba& a){
    char buf[l_length]={0};
    s >> buf;
    int l = strlen(buf);
    a.l = l;
    for (int i=0;buf[i];++i)
    a.c[l-i-1] = buf[i]-'0';
    if (a.l==1 && a.c[0]==0)
    a.l=0;
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

liczba nwdz(liczba a, liczba b){
    while (b.l>0){
    liczba x(a.mod(b));
    a = b;
    b = x;
    }
    return a;
}

liczba nwdp(liczba a, liczba b){
    return nwdz(a,b);
    if (b.l==0) return a;
    return nwdp(b, a.mod(b));
}


LL nwdi(liczba a, LL b){
    return nwdl(b, ld(a.sub(a.div(b).times(b))));
}



int main(){
    liczba licz, mian;
    vector<string> out;
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
        mian.times(pmian);
        licz.times(plicz);
        liczba nwd = nwdp(mian,licz);
        mian=mian.div(nwd);
        licz=licz.div(nwd);
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
