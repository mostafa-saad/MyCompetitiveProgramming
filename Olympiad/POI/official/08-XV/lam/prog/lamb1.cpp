/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lamb1.cpp                                                 *
 *   Autor:    Michal Brzozowski                                         *
 *   Opis:     Rozwiazanie bledne, zawiera implementacje rozwiazania     *
 *             wzorcowego na liczbach wbudowanego typu.                  *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>

using namespace std;

typedef long long LL;


LL nwd(LL a, LL b){
    if (b==0) return a;
    return nwd(b, a%b);
}


int n;

int main(){
    cin >> n;

    int num[1000];

    for (int i=0;i<n;++i){
    cin >> num[i];
    }

    LL licz(1), mian(num[n-1]);
    vector<string> out;
    char tbuf[100];
    sprintf(tbuf,"1/%d",num[n-1]);
    out.push_back(tbuf);
    for (int i=n-2;i>=0;--i){
    LL plicz = num[i+1]-1, pmian = num[i];
    LL pnwd = nwd(plicz,pmian);
    plicz/=pnwd;
    pmian/=pnwd;
    pnwd = nwd(plicz, mian);
    plicz/=pnwd;
    mian/=pnwd;
    pnwd = nwd(licz, pmian);
    licz/=pnwd;
    pmian/=pnwd;

    licz*=plicz;
    mian*=pmian;
    pnwd = nwd(licz, mian);
    licz/=pnwd;
    mian/=pnwd;
    ostringstream os;
    os << licz;
    os <<'/';
    os << mian;
    out.push_back(os.str());
    }
    for (int i=n-1;i>=0;--i)
    cout << out[i]<<endl;
}
