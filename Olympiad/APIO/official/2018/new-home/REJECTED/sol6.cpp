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
const int maxn=4e6+6;
double tim()
{
    return 1.0*clock()/CLOCKS_PER_SEC;
}
int n,k,q;
struct Obj
{
    int pos,type,a,b,id;
    bool operator <(const Obj &i) const{return pos<i.pos;}
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
struct DLL
{
    static DLL _[maxn];
    // DLL *prv,*nxt;
    int prv,nxt;
    int pos;
    inline int ppos() const{return prv?_[prv].pos:-3*D;}
    inline int npos() const{return nxt?_[nxt].pos:3*D;}
} DLL::_[maxn],*dll=DLL::_;
struct Pt
{
    int x,y;
    bool operator <(const Pt &p) const{return x<p.x;}
};
int ans[maxn];
inline void rayslr(const vector<Pt> &pts,const vector<Req> &cr)
{
    if(!SZ(pts)) return;
    int y0=INT_MIN;
    auto itp=pts.begin();
    for(auto c:cr)
    {
        while(itp!=pts.end() && itp->x<=c.pos)
        {
            Pt p=*(itp++);
            int ny0=p.y+p.x;
            y0=max(y0,ny0);
        }
        if(y0!=INT_MIN) ans[c.id]=max(ans[c.id],y0-c.pos);
    }
}
inline void raysrl(const vector<Pt> &pts,const vector<Req> &cr)
{
    if(!SZ(pts)) return;
    int y0=INT_MIN;
    auto itp=pts.rbegin();
    // for(auto c:cr)
    for(auto it=cr.rbegin();it!=cr.rend();it++)
    {
        auto c=*it;
        while(itp!=pts.rend() && itp->x>=c.pos)
        {
            Pt p=*(itp++);
            int ny0=p.y-p.x;
            y0=max(y0,ny0);
        }
        if(y0!=INT_MIN) ans[c.id]=max(ans[c.id],y0+c.pos);
    }
}
void build()
{
    REP1(i,1,n) obj[i].pos*=2;
    REP1(i,1,q) req[i].pos*=2;
    debug(tim());

    {//re-time
        vector<int> ts;
        REP1(i,1,q) ts.pb(req[i].t);
        sort(ALL(ts));ts.erase(unique(ALL(ts)),ts.end());
        tmax=SZ(ts);
        auto fix=[&](int x){return lower_bound(ALL(ts),x)-ts.begin()+1;};
        REP1(i,1,q) req[i].t=fix(req[i].t);
        REP1(i,1,n) obj[i].a=fix(obj[i].a),obj[i].b=fix(obj[i].b+1)-1;
        // REP1(i,1,n) debug(i,obj[i].a,obj[i].b);
        // REP1(i,1,q) debug(i,req[i].t);
    }
    debug(tim());
    {//build DLL
        vector<int> oids(n);
        iota(ALL(oids),1);sort(ALL(oids),[&](int i,int j){return obj[i].pos<obj[j].pos;});
        vector<int> last(k+1,0);
        for(int i:oids)
        {
            int type=obj[i].type;
            int prv=last[type];
            dll[prv].nxt=i;
            dll[i].prv=prv;
            dll[i].pos=obj[i].pos;
            last[type]=i;
        }
    }
    debug(tim());
    
    vector<Req> cr(req+1,req+n+1);
    sort(ALL(cr));
    {//init rays l->r
        vector<Pt> pts;
        REP1(i,1,n)
        {
            int p=dll[i].ppos(),qq=dll[i].pos;
            pts.pb({(p+qq)/2,(qq-p)/2});
        }
        sort(ALL(pts));
        rayslr(pts,cr);
    }
    {//init rays r->l
        vector<Pt> pts;
        REP1(i,1,n)
        {
            int p=dll[i].pos,qq=dll[i].npos();
            pts.pb({(p+qq)/2,(qq-p)/2});
        }
        sort(ALL(pts));
        raysrl(pts,cr);
    }
    debug(tim());
}
void mysort(vector<Pt> &pts)
{
    if(!SZ(pts)) return;
    if(SZ(pts)<123){sort(ALL(pts));return;}
    int lo=min_element(ALL(pts))->x;
    for(auto &u:pts) u.x-=lo;
    static const int Z=8,K=1<<Z;
    static int sum[K];

    vector<Pt> tmp(SZ(pts));
    int hi=max_element(ALL(pts))->x;
    int rnd=__lg(hi)/Z+1;
    REP(_,rnd)
    {
        memset(sum,0,sizeof(int)*K);
        for(auto u:pts) sum[(u.x>>(_*Z))&(K-1)]++;
        REP1(i,1,K-1) sum[i]+=sum[i-1];
        PER1(i,SZ(pts)-1,0) tmp[--sum[(pts[i].x>>(_*Z))&(K-1)]]=pts[i];
        tmp.swap(pts);
    }

    for(auto &u:pts) u.x+=lo;
}
struct Rem
{
    int a,b,id;
};
vector<int> rems[1<<__lg(maxn<<2)];
void doo(int x,int l,int r,const vector<Req> &cr)
{
    if(!SZ(cr)) return;

    // vector<int> act;

    vector<Pt> pts;
    // for(auto o:rem) if(o.a==l && o.b==r)
    for(auto i:rems[x])
    {
        // debug(l,r,o.pos/2,o.type);
        const auto &cur=dll[i];
        int p=cur.ppos(),qq=cur.npos();
        pts.pb({(p+qq)/2,(qq-p)/2});
        dll[cur.prv].nxt=cur.nxt;
        dll[cur.nxt].prv=cur.prv;
        // act.pb(o.id);
    }
    
    // sort(ALL(pts),[&](Pt a,Pt b){return a.x<b.x;});
    mysort(pts);
    // assert(is_sorted(ALL(cr),[&](Req a,Req b){return a.pos<b.pos;}));
    rayslr(pts,cr);
    // reverse(ALL(pts));reverse(ALL(cr));
    raysrl(pts,cr);
    // reverse(ALL(cr));

    if(l<r)
    {
        int mid=(l+r)/2;
        vector<Req> ncr[2];
        for(auto c:cr) ncr[c.t>mid].pb(c);
        // vector<Rem> nrem[2];
        // for(auto o:rem)
        // {
        //      if(o.a==l && o.b==r) continue;
        //      if(o.a<=mid) nrem[0].pb({o.a,min(o.b,mid),o.id});
        //      if(mid+1<=o.b) nrem[1].pb({max(mid+1,o.a),o.b,o.id});
        // }
        doo(x<<1,l,mid,ncr[0]);
        doo(x<<1|1,mid+1,r,ncr[1]);
    }

    reverse(ALL(rems[x]));
    for(auto i:rems[x])
    {
        const auto &cur=dll[i];
        dll[cur.prv].nxt=i;
        dll[cur.nxt].prv=i;
    }
}
void sol()
{
    // REP1(i,1,q) debug(i,ans[i]);
    // same type same pos?
    // vector<Rem> rem;
    REP1(i,1,n)
    {
        // if(1<=obj[i].a-1) add(1,1,tmax,1,obj[i].a-1,i);//rem.pb({1,obj[i].a-1,obj[i].id});
        if(1<=obj[i].a-1)
        {
            int x=1,l=1,r=tmax,y=obj[i].a-1;
            while(1)
            {
                if(r==y){rems[x].pb(i);break;}
                int mid=(l+r)/2;
                if(y<=mid) r=mid,x<<=1;
                else rems[x<<1].pb(i),l=mid+1,x=x<<1|1;
            }
        }
        // if(obj[i].b+1<=tmax) add(1,1,tmax,obj[i].b+1,tmax,i);//rem.pb({obj[i].b+1,tmax,obj[i].id});
        if(obj[i].b+1<=tmax)
        {
            int x=1,l=1,r=tmax,p=obj[i].b+1;
            while(1)
            {
                if(l==p){rems[x].pb(i);break;}
                int mid=(l+r)/2;
                if(mid+1<=p) l=mid+1,x=x<<1|1;
                else rems[x<<1|1].pb(i),r=mid,x<<=1;
            }

        }
    }
    debug(tim());

    vector<Req> cr(req+1,req+q+1);
    sort(ALL(cr));

    doo(1,1,tmax,cr);

    debug(tim());
    REP1(i,1,q) PL(ans[i]>D?-1:ans[i]/2);
    debug(tim());
}
int main()
{
    read();
    build();
    sol();
}




































/*End Of File*/


