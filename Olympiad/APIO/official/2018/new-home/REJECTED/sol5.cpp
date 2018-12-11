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
int tmax;
const int D=(1e8+8)*2;
// struct DLL
// {
//     static DLL _[maxn];
//     // DLL *prv,*nxt;
//     int prv,nxt;
//     int pos;
//     inline int ppos() const{return prv?_[prv].pos:-3*D;}
//     inline int npos() const{return nxt?_[nxt].pos:3*D;}
// } DLL::_[maxn],*dll=DLL::_;
struct Pt
{
    int x,y,type;
    bool operator <(const Pt &p) const{return tie(x,y,type)<tie(p.x,p.y,p.type);}
    bool operator ==(const Pt &p) const{return tie(x,y,type)==tie(p.x,p.y,p.type);}
};
map<Pt,int> pk;
vector<map<int,int>> locs;
template<typename T>
void add(map<T,int> &mp,T kk)
{
    mp[kk]++;
}
template<typename T>
void del(map<T,int> &mp,T kk)
{
    if(--mp[kk]==0) mp.erase(kk);
}

int ans[maxn];
inline void rayslr(const vector<Req> &cr,const bitset<maxn> &ban)
{
    int y0=INT_MIN;
    auto itp=pk.begin();
    for(auto c:cr)
    {
        while(itp!=pk.end() && itp->F.x<=c.pos)
        {
            Pt p=(itp++)->F;
            if(ban[p.type]) continue;
            int ny0=p.y+p.x;
            y0=max(y0,ny0);
        }
        if(y0!=INT_MIN) ans[c.id]=max(ans[c.id],y0-c.pos);
    }
}
inline void raysrl(const vector<Req> &cr,const bitset<maxn> &ban)
{
    int y0=INT_MIN;
    auto itp=pk.rbegin();
    // for(auto c:cr)
    for(auto it=cr.rbegin();it!=cr.rend();it++)
    {
        auto c=*it;
        while(itp!=pk.rend() && itp->F.x>=c.pos)
        {
            Pt p=(itp++)->F;
            if(ban[p.type]) continue;
            int ny0=p.y-p.x;
            y0=max(y0,ny0);
        }
        if(y0!=INT_MIN) ans[c.id]=max(ans[c.id],y0+c.pos);
    }
}
vector<pii> evt;
void build()
{
    REP1(i,1,n) obj[i].pos*=2;
    REP1(i,1,q) req[i].pos*=2;
    debug(tim());

    {//re-time
        REP1(i,1,n) evt.pb({i,0});
        REP1(i,1,q) evt.pb({i,1});
        REP1(i,1,n) evt.pb({i,2});
        auto f=[&](pii p){return p.S==1?req[p.F].t:obj[p.F].at(p.S);};
        sort(ALL(evt),[&](pii a,pii b){return mkp(f(a),a.S)<mkp(f(b),b.S);});
        REP(i,SZ(evt))
        {
            auto p=evt[i];
            (p.S==1?req[p.F].t:obj[p.F].at(p.S))=i+1;
        }
    }

    locs.resize(k+1,map<int,int>{{-3*D,1},{3*D,1}});
    REP1(i,1,k) pk[Pt{0,3*D,i}]++;
}
void sol()
{
    int Z=sqrt(SZ(evt));
    bitset<maxn> ban;
    REP(s,SZ(evt)/Z+1)
    {
        int l=s*Z,r=min(l+Z-1,SZ(evt)-1);
        vector<int> types;
        REP1(i,l,r) if(evt[i].S!=1)
            types.pb(obj[evt[i].F].type);
        sort(ALL(types));types.erase(unique(ALL(types)),types.end());

        vector<Req> cr;
        REP1(i,l,r) if(evt[i].S==1)
            cr.pb(req[evt[i].F]);
        sort(ALL(cr));

        for(auto z:types) ban[z]=1;
        rayslr(cr,ban);
        raysrl(cr,ban);
        for(auto z:types) ban[z]=0;

        REP1(i,l,r)
        {
            // debug(s,i,evt[i].F,evt[i].S,types);
            if(evt[i].S==0)
            {
                auto o=obj[evt[i].F];
                locs[o.type][o.pos]++;
                auto it=locs[o.type].find(o.pos);
                if(it->S==1)
                {
                    int a=prev(it)->F,b=it->F,c=next(it)->F;
                    // debug(a,b,c,"ADD");
                    del(pk,Pt{(a+c)/2,(c-a)/2,o.type});
                    add(pk,Pt{(a+b)/2,(b-a)/2,o.type});
                    add(pk,Pt{(b+c)/2,(c-b)/2,o.type});
                }
            }
            else if(evt[i].S==2)
            {
                auto o=obj[evt[i].F];
                locs[o.type][o.pos]--;
                auto it=locs[o.type].find(o.pos);
                if(it->S==0)
                {
                    int a=prev(it)->F,b=it->F,c=next(it)->F;
                    locs[o.type].erase(it);
                    // debug(a,b,c,"DEL");
                    add(pk,Pt{(a+c)/2,(c-a)/2,o.type});
                    del(pk,Pt{(a+b)/2,(b-a)/2,o.type});
                    del(pk,Pt{(b+c)/2,(c-b)/2,o.type});
                }
            }
            else
            {
                auto c=req[evt[i].F];
                // debug(c.id,ans[c.id]);
                for(auto type:types)
                {
                    auto it=locs[type].lower_bound(c.pos);
                    // debug(type,it->F,c.pos,prev(it)->F);
                    ans[c.id]=max(ans[c.id],min(it->F-c.pos,c.pos-prev(it)->F));
                }
                // debug(c.id,ans[c.id]);
            }
        }
    }
    REP1(i,1,q) PL(ans[i]>=2*D?-1:ans[i]/2);
}
int main()
{
    read();
    // vector<pii> v;
    // REP1(i,1,n) v.pb({i,0});
    // REP1(i,1,n) v.pb({i,1});
    // sort(ALL(v),[&](pii a,pii b){return tie(a.S?obj[a.F].b:obj[a.F].a,a.S) < tie(b.S?obj[b.F].b:obj[b.F].a,b.S);});
    // int K=sqrt(SZ(v));
    // vector<int> cs;
    // REP(i,SZ(v)/K+1)
    // {
    //     vector<int> cc;
    //     REP1(j,i*K,(i+1)*K-1) cc.pb(obj[v[j].F].type);
    //     sort(ALL(cc));cc.erase(unique(ALL(cc)),cc.end());
    //     cs.pb(SZ(cc));
    // }
    // sort(ALL(cs));
    // debug(cs[0],cs[SZ(cs)/2],cs.back());
    build();
    debug(tim());
    sol();
    debug(tim());
}




































/*End Of File*/


