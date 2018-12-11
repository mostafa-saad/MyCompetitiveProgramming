//{{{
#include <bits/stdc++.h>
using namespace std;
//types
typedef long long ll;
typedef pair<int,int> pii;
//input
bool SR(int &_x){return scanf("%d",&_x)==1;}bool SR(ll &_x){return scanf("%lld",&_x)==1;}
bool SR(double &_x){return scanf("%lf",&_x)==1;}bool SR(char *_s){return scanf("%s",_s)==1;}
bool RI(){return true;}
template<typename I,typename... T>bool RI(I &_x,T&... _tail){return SR(_x) && RI(_tail...);}
//output
void SP(const int _x){printf("%d",_x);}void SP(const ll _x){printf("%lld",_x);}
void SP(const double _x){printf("%.16lf",_x);}void SP(const char *s){printf("%s",s);}
void PL(){puts("");}
template<typename I,typename... T>void PL(const I _x,const T... _tail)
{SP(_x);if(sizeof...(_tail)) putchar(' ');PL(_tail...);}
//macro
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define REP(i,n) for(int i=0;i<int(n);i++)
#define REP1(i,a,b) for(int i=(a);i<=int(b);i++)
#define PER1(i,a,b) for(int i=(a);i>=int(b);i--)
#define pb push_back
#define mkp make_pair
#define F first
#define S second
//debug
#ifdef darry140
template<typename A,typename B>
ostream& operator <<(ostream&_s, const pair<A,B> &_p){return _s<<"("<<_p.F<<","<<_p.S<<")";}
template<typename It>
ostream& _OUTC(ostream &_s,It _b,It _e)//container
{
    _s<<"{";
    for(auto _it=_b;_it!=_e;_it++) _s<<(_it==_b?"":" ")<<*_it;
    _s<<"}";
    return _s;
}
template<typename A,typename B>
ostream& operator <<(ostream&_s, const map<A,B> &_c){return _OUTC(_s,ALL(_c));}
template<typename T>
ostream& operator <<(ostream&_s, const set<T> &_c){return _OUTC(_s,ALL(_c));}
template<typename T>
ostream& operator <<(ostream&_s, const vector<T> &_c){return _OUTC(_s,ALL(_c));}
template<typename I>
void _DOING(const char *_s,I&& _x){cerr<<_s<<"="<<_x<<endl;}//without ','
template<typename I,typename... T>
void _DOING(const char *_s,I&& _x,T&&... _tail)//with ','
{
    int _c=0;
    static const char _bra[]="({[";
    static const char _ket[]=")}]";
    while(*_s!=',' || _c!=0)//eg. mkp(a,b)
    {
        if(strchr(_bra,*_s)) _c++;
        if(strchr(_ket,*_s)) _c--;
        cerr<<*_s++;
    }
    cerr<<"="<<_x<<", ";
    _DOING(_s+1,_tail...);
}
#define debug(...) do{\
    fprintf(stderr,"%s:%d - ",__PRETTY_FUNCTION__,__LINE__);\
    _DOING(#__VA_ARGS__,__VA_ARGS__);\
}while(0)
#else
#define debug(...)
#endif
//}}}
const int maxn=1e6+6;
double tim()
{
    return 1.0*clock()/CLOCKS_PER_SEC;
}
int n,k,q;
struct Obj
{
    int pos,type,a,b,id;
    bool operator <(const Obj &i) const{return pos<i.pos;}
    int at(bool z) const{return z?b:a;}
    int& at(bool z) {return z?b:a;}
} obj[maxn];
struct Req
{
    int pos,t,id;
    bool operator <(const Req &i) const{return pos<i.pos;}
} req[maxn];
void read()
{
    // freopen("1000000-2345-1000000.in","r",stdin);
    // freopen("tmp.out","w",stdout);
    RI(n,k,q);
    REP1(i,1,n) RI(obj[i].pos,obj[i].type,obj[i].a,obj[i].b),obj[i].id=i;
    REP1(i,1,q) RI(req[i].pos,req[i].t),req[i].id=i; 
}

void build(){}
void sol()
{
    vector<pii> v;
    REP1(i,1,n) for(int j:{0,2})
        v.pb({i,j});
    REP1(i,1,q) v.pb({i,1});
    auto get=[&](pii p){return mkp(p.S==1?req[p.F].t:obj[p.F].at(p.S),p.S);};
    sort(ALL(v),[&](pii a,pii b){return mkp(get(a),a.S) < mkp(get(b),b.S);}); 

    vector<map<int,int>> loc(k+1);
    vector<int> ans(q+1,0);
    for(auto p:v)
    {
        if(p.S==0) loc[obj[p.F].type][obj[p.F].pos]++;
        else if(p.S==2)
        {
            if(--loc[obj[p.F].type][obj[p.F].pos]==0)
                loc[obj[p.F].type].erase(obj[p.F].pos);
        }
        else
        {
            REP1(i,1,k)
            {
                auto it=loc[i].lower_bound(req[p.F].pos);
                int u=INT_MAX;
                if(it!=loc[i].end()) u=min(u,it->F-req[p.F].pos);
                if(it!=loc[i].begin()) u=min(u,req[p.F].pos-prev(it)->F);
                ans[req[p.F].id]=max(ans[req[p.F].id],u);
            }
        }
    }
    REP1(i,1,q) PL(ans[i]==INT_MAX?-1:ans[i]);
}
int main()
{
    read();
    build();
    sol();
    debug(tim());
}















/*End Of File*/


