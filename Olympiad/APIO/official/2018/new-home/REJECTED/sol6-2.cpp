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
    // bool operator <(const Obj &i) const{return pos<i.pos;}
    int at(bool z) const{return z?b:a;}
    int& at(bool z) {return z?b:a;}
} obj[maxn];
struct Req
{
    int pos,t,id;
    // bool operator <(const Req &i) const{return pos<i.pos;}
} req[maxn];
void read()
{
    RI(n,k,q);
    REP1(i,1,n) RI(obj[i].pos,obj[i].type,obj[i].a,obj[i].b),obj[i].id=i;
    REP1(i,1,q) RI(req[i].pos,req[i].t),req[i].id=i; 
    assert(k<=maxn/5);
}
struct Pt
{
    int x,y,a,b;
    bool operator <(const Pt &p) const{return tie(x,y,a,b) < tie(p.x,p.y,p.a,p.b);}
    bool operator ==(const Pt &p) const{return tie(x,y,a,b) == tie(p.x,p.y,p.a,p.b);}
};
const int D=(1e8+8)*2;
int tmax;
vector<Pt> pts;
void build()
{
    REP1(i,1,n) obj[i].pos*=2;
    REP1(i,1,q) req[i].pos*=2;
    tmax=max_element(req+1,req+q+1,[&](Req a,Req b){return a.t<b.t;})->t;

    sort(obj+1,obj+n+1,[&](Obj a,Obj b){return a.type<b.type;});
    for(int l=1,r=1;l<=n;l=r)
    {
        while(r<=n && obj[r].type==obj[l].type) r++;
        map<int,int> loc{{-3*D,1},{3*D,1}};
        set<Pt> cur_pts{{0,3*D,0,-1}};
        
        vector<pii> v;
        REP1(i,l,r-1) REP(j,2) v.pb({i,j});
        sort(ALL(v),[&](pii a,pii b){return mkp(obj[a.F].at(a.S),a.S)<mkp(obj[b.F].at(b.S),b.S);});
        
        auto del=[&](int x,int y,int t){
            auto it=cur_pts.lower_bound({x,y,-1,-1});
            pts.pb({it->x,it->y,it->a,t});
            cur_pts.erase(it);
        };

        for(auto p:v)
        {
            auto o=obj[p.F];
            if(p.S==0) //in
            {
                int f=o.pos;
                if(++loc[f]==1)
                {
                    auto it=loc.find(f);
                    int e=prev(it)->F,g=next(it)->F;

                    del((e+g)/2,(g-e)/2,o.at(0)-1);

                    cur_pts.insert({(e+f)/2,(f-e)/2,o.at(0),-1});
                    cur_pts.insert({(f+g)/2,(g-f)/2,o.at(0),-1});
                }
            }
            else //out
            {
                int f=o.pos;
                if(--loc[f]==0)
                {
                    auto it=loc.find(f);
                    int e=prev(it)->F,g=next(it)->F;
                    loc.erase(it);

                    del((e+f)/2,(f-e)/2,o.at(1));
                    del((f+g)/2,(g-f)/2,o.at(1));

                    cur_pts.insert({(e+g)/2,(g-e)/2,o.at(1)+1});
                }
            }
        }
        for(auto p:cur_pts)
            pts.pb({p.x,p.y,p.a,tmax+1});
        //add cur pts end maxt+1
    }
}
int ans[maxn];
struct Tseg
{
    struct Node{int x,y;};
    vector<Node> dat[4<<__lg(maxn)|3];
#define Mid int mid=(low+high)/2
#define lc x<<1,low,mid
#define rc x<<1|1,mid+1,high 
    void add(int x,int low,int high,int a,int b,Node v)
    {
        if(low==a&&b==high){dat[x].pb(v);return;}
        Mid;
        if(b<=mid) add(lc,a,b,v);
        else if(mid+1<=a) add(rc,a,b,v);
        else add(lc,a,mid,v),add(rc,mid+1,b,v);
    }
    void sol(int x,int low,int high,const vector<Req> &cr)
    {
        {
            int y0=INT_MIN;
            auto itp=dat[x].begin();
            for(auto c:cr)
            {
                while(itp!=dat[x].end() && itp->x<=c.pos)
                {
                    auto p=*(itp++);
                    int ny0=p.y+p.x;
                    y0=max(y0,ny0);
                }
                if(y0!=INT_MIN) ans[c.id]=max(ans[c.id],y0-c.pos);
            }
        }
        {
            int y0=INT_MIN;
            auto itp=dat[x].rbegin();
            for(auto it=cr.rbegin();it!=cr.rend();it++)
            {
                auto c=*it;
                while(itp!=dat[x].rend() && itp->x>=c.pos)
                {
                    auto p=*(itp++);
                    int ny0=p.y-p.x;
                    y0=max(y0,ny0);
                }
                if(y0!=INT_MIN) ans[c.id]=max(ans[c.id],y0+c.pos);
            }
        }
        
        if(low==high) return;
        Mid;
        vector<Req> ncr[2];
        for(auto c:cr) ncr[c.t>mid].pb(c);
        sol(lc,ncr[0]);sol(rc,ncr[1]);
    }
} tseg;
void sol()
{
    vector<int> ts;
    REP1(i,1,q) ts.pb(req[i].t);
    sort(ALL(ts));ts.erase(unique(ALL(ts)),ts.end());
    REP1(i,1,q) req[i].t=lower_bound(ALL(ts),req[i].t)-ts.begin()+1;

    debug(tim());

    debug(SZ(pts));
    sort(ALL(pts),[&](Pt a,Pt b){return a.x<b.x;});
    debug(tim());
    for(auto p:pts)
    {
        int l=lower_bound(ALL(ts),p.a)-ts.begin()+1;
        int r=upper_bound(ALL(ts),p.b)-ts.begin();
        if(l<=r) tseg.add(1,1,SZ(ts),l,r,{p.x,p.y});
    }
    debug(tim());

    sort(req+1,req+q+1,[&](Req a,Req b){return a.pos<b.pos;});
    tseg.sol(1,1,SZ(ts),vector<Req>(req+1,req+q+1));

    REP1(i,1,q) PL(ans[i]>2*D?-1:ans[i]/2);

    //szts

    //disc req
    // cr is sorted and nodes
}
int main()
{
    read();
    debug(tim());
    build();
    debug(tim());
    sol();
    debug(tim());
}










/*End Of File*/


