/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Labirynt                                      *
 *   Autor:                Adam Karczmarz, Tomasz Idziaszek              *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include "oi.h"

#define REP(AA,BB) for(int AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(int AA=(BB); AA<(CC); ++AA)
#define FC(AA,BB) for(__typeof((AA).begin()) BB=(AA).begin(); BB!=(AA).end(); ++BB)
#define SZ(AA) ((int)((AA).size()))
#define ALL(AA) (AA).begin(), (AA).end()
#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

struct point {
    int x, y, n;
    point(int _x=0, int _y=0, int _n=0) : x(_x), y(_y), n(_n) {}
    int operator<(const point &a) const {
        if(x==a.x)
            return y<a.y;
        return x<a.x;
    }
    int operator==(const point &a) const {
        return x==a.x && y==a.y;
    }
    point operator-(const point &a) const {
        return point(x-a.x, y-a.y);
    }
};

int cmp2(const point &a, const point &b) {
    if(a.y==b.y)
        return a.x<b.x;
    return a.y<b.y;
}

LL cross(const point &a, const point &b) {
    return (LL)a.x*b.y-(LL)a.y*b.x;
}

LL cross(const point &o, const point &a, const point &b) {
    return cross(a-o, b-o);
}

vector<point> P;

LL pole() {
    LL sum=0LL;
    FOR(i,2,SZ(P))
    sum+=cross(P[0],P[i-1],P[i]);
    return sum<0?-sum:sum;
}

int rozne() {
    vector<point> Q=P;
    sort(ALL(Q));
    FOR(i,1,SZ(Q)) {
        if(Q[i]==Q[i-1])
            return 0;
    }
    return 1;
}

int prostopadle() {
    int t, tmp;
    if(P[0].x==P[1].x && P[0].y!=P[1].y)
        t=0;
    else if(P[0].y==P[1].y && P[0].x!=P[1].x)
        t=1;
    else
        return 0;
    FOR(i,2,SZ(P)) {
        if(P[i-1].x==P[i].x && P[i-1].y!=P[i].y)
            tmp=0;
        else if(P[i-1].y==P[i].y && P[i-1].x!=P[i].x)
            tmp=1;
        else
            return 0;
        if(tmp==t)
            return 0;
        t=1-t;
    }
    if(P.back().x==P[0].x && P.back().y!=P[0].y)
        tmp=0;
    else if(P.back().y==P[0].y && P.back().x!=P[0].x)
        tmp=1;
    else
        return 0;
    return tmp!=t;
}

int nie_nakladaja() {
    vector<point> Q;
    for(int i=(P[0].x==P[1].x)?0:1; i<SZ(P); i+=2) {
        int j=(i+1)%SZ(P);
        Q.PB(point(P[i].x,P[i].y,i));
        Q.PB(point(P[j].x, P[j].y, i));
    }
    sort(ALL(Q));
    for(int i=0, j; i<SZ(Q); ) {
        for(j=i; j<SZ(Q) && Q[i].x==Q[j].x; ++j);
        for(int k=i; k<j; k+=2) {
            if(Q[k].n!=Q[k+1].n)
                return 0;
        }
        i=j;
    }
    Q.clear();
    for(int i=(P[0].y==P[1].y)?0:1; i<SZ(P); i+=2) {
        int j=(i+1)%SZ(P);
        Q.PB(point(P[i].x,P[i].y,i));
        Q.PB(point(P[j].x, P[j].y, i));
    }
    sort(ALL(Q),cmp2);
    for(int i=0, j; i<SZ(Q); ) {
        for(j=i; j<SZ(Q) && Q[i].y==Q[j].y; ++j);
        for(int k=i; k<j; k+=2) {
            if(Q[k].n!=Q[k+1].n)
                return 0;
        }
        i=j;
    }
    return 1;
}

struct ev {
    int x, y1, y2, c;
    ev(int _x=0, int _y1=0, int _y2=0, int _c=0) : x(_x), y1(_y1), y2(_y2), c(_c) {}
    int operator<(const ev &a) const {
        if(x==a.x)
            return c>a.c;
        return x<a.x;
    }
};

const int MAX_DRZ = 1<<19;
int cnt[MAX_DRZ], BASE;

int get(int a, int b) {
    int res=0;
    a+=BASE;
    b+=BASE;
    res+=cnt[a];
    if(b>a)
        res+=cnt[b];
    while((a>>1)!=(b>>1)) {
        if(b&1)
            res+=cnt[b-1];
        if(!(a&1))
            res+=cnt[a+1];
        a>>=1;
        b>>=1;
    }
    return res;
}

void add(int a, int v) {
    a+=BASE;
    while(a>0) {
        cnt[a]+=v;
        a>>=1;
    }
}

int brak_przeciec() {
    memset(cnt, 0, sizeof cnt);
    vector<ev> E;
    vector<int> wsp;
    wsp.PB(0);
    for(int i=0; i<SZ(P); ++i) {
        int j=(i+1)%SZ(P);
        if(P[i].x==P[j].x) {
            int y1=min(P[i].y,P[j].y)+1, y2=max(P[i].y,P[j].y)-1;
            if(y1<=y2) {
                wsp.PB(y1);
                E.PB(ev(P[i].x, y1, y2, 0));
            }
            if(y1<y2)
                wsp.PB(y2);
        }
        else {
            wsp.PB(P[i].y);
            E.PB(ev(min(P[i].x,P[j].x), P[i].y, 0, 1));
            E.PB(ev(max(P[i].x,P[j].x), P[i].y, 0, -1));
        }
    }
    sort(ALL(wsp));
    for(BASE=1; BASE<SZ(wsp); BASE<<=1);
    assert(2*BASE<=MAX_DRZ);
    REP(i,SZ(E)) {
        E[i].y1=lower_bound(ALL(wsp), E[i].y1)-wsp.begin();
        E[i].y2=lower_bound(ALL(wsp), E[i].y2)-wsp.begin();
    }
    sort(ALL(E));
    REP(i,SZ(E)) {
        if(E[i].c==0) {
            int tmp=get(E[i].y1,E[i].y2);
            assert(tmp>=0);
            if(tmp>0) {
                //fprintf(stderr, "%d\n", tmp);
                return 0;
            }
        }
        else
            add(E[i].y1, E[i].c);
    }
    return 1;
}

const int MAX_WSP = 1000000000;

void error(const char* msg, int line=0, int position=0) {
    printf("WRONG\n%s\n",msg);
    exit(0);
}

void dobrze() {
    puts("OK");
    exit(0);
}

char buf[110];




const int MAX_LEN = 100000+10;

char s_in[MAX_LEN];
char s_user[MAX_LEN];
char _text[MAX_LEN*3];
int _p[MAX_LEN*3];

bool cyklicznie_rownowazne(int n, char* sa, char* sb) {
    REP(i,n) _text[i] = s_in[i];
    _text[n] = '$';
    REP(i,n) _text[n+1+i] = s_user[i];
    REP(i,n) _text[2*n+1+i] = s_user[i];

    _p[0] = -1;
    int t = -1;
    REP(j,3*n+1) {
        while (t >= 0 && _text[t] != _text[j])
            t = _p[t];
        t++;
        _p[j+1] = t;
        if (t >= n) return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
////   int n; assert(fscanf(fopen(argv[1], "r"), "%d", &n)==1);

    fscanf(fopen(argv[1], "r"), "%s", s_in);
    int n=strlen(s_in),cnt=0;
    REP(i,n) if (s_in[i]=='L') ++cnt;
    else --cnt;

    oi::Scanner s(argv[2], error, oi::PL);
////   if(n==2 || n%2==1) {
    if (cnt != 4) {
        s.skipWhitespaces();
        s.readString(buf, 7);
        if(strcmp(buf,"NIE")!=0)
            error("Oczekiwano NIE.");
        s.skipWhitespaces();
        s.readEof();
        dobrze();
        return 0;
    }
    REP(i,n) {
        point tmp;
        s.skipWhitespaces();
        tmp.x=s.readInt(-MAX_WSP, MAX_WSP);
        s.skipWhitespaces();
        tmp.y=s.readInt(-MAX_WSP, MAX_WSP);
        P.PB(tmp);
    }
    s.skipWhitespaces();
    s.readEof();
    if(!rozne())
        error("Punkty nie sa rozne.");
    if(!prostopadle())
        error("Kolejne boki nie sa prostopadle.");
////   if(pole()!=2*n) {
////      //fprintf(stderr, "%d\n", pole());
////      error("Pole nie jest rowne n.");
////   }
    if(!nie_nakladaja())
        error("Boki nakladaja sie na siebie.");
    if(!brak_przeciec())
        error("Znaleziono samoprzeciecia.");


    REP(i,n) {
        point a = P[i], b = P[(i+1)%n], c = P[(i+2)%n];
        if (a.y == b.y && a.x < b.x) s_user[i] = (b.y < c.y) ? 'L' : 'P';
        if (a.x == b.x && a.y > b.y) s_user[i] = (b.x < c.x) ? 'L' : 'P';
        if (a.y == b.y && a.x > b.x) s_user[i] = (b.y > c.y) ? 'L' : 'P';
        if (a.x == b.x && a.y < b.y) s_user[i] = (b.x > c.x) ? 'L' : 'P';
    }

    if (!cyklicznie_rownowazne(n, s_in, s_user))
        error("Niepoprawny ciag zakretow.");


    dobrze();
    return 0;
}
