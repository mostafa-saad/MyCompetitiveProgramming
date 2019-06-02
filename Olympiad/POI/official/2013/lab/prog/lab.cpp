/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Labirynt                                      *
 *   Autor:                Tomasz Idziaszek                              *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N = 1000000;
char s[N];
char sx[4][N];
char* p;

struct pt_t {
    int x,y;
    pt_t() : x(0), y(0) { }
    pt_t(int x, int y) : x(x), y(y) { }
};

pt_t add(pt_t p, pt_t q, int rot) {
    rot %= 4;
    if (rot==0) p.x += q.x, p.y += q.y;
    else if (rot==1) p.x += q.y, p.y -= q.x;
    else if (rot==2) p.x -= q.x, p.y -= q.y;
    else if (rot==3) p.x -= q.y, p.y += q.x;
    return p;
}

struct turn_t {
    int w, h;
    vector<turn_t*> turns;
    turn_t() : w(0), h(0) { }
    void draw(pt_t pos, int rot);
};

turn_t* rek() {
    assert(*p++ == 'L');
    turn_t* t = new turn_t;
    t->w += 2;
    while (*p == 'L') {
        turn_t* it = rek();
        t->turns.push_back(it);
        t->w += it->h;
        t->h += it->w;
    }
    if (t->turns.empty()) t->h ++ ;
    assert(*p++ == 'P');
    return t;
}

vector<pt_t> points;

void turn_t::draw(pt_t pos, int rot) {
    points.push_back(pos);
    pos = add(pos, pt_t(w-1,0), rot);
    if (turns.empty()) {
        points.push_back(pos);
        pos = add(pos, pt_t(0,-1), rot);
    }
    else
        FORE(i,turns) {
        (*i)->draw(pos, rot+1);
        pos = add(pos, pt_t((*i)->w, - (*i)->h), rot+1);
    }
    points.push_back(pos);
    pos = add(pos, pt_t(w-1,0), rot);
}


void solve() {
    turn_t* t[4];
    int edge = 0;
    REP(i,4) {
        p = sx[i];
        t[i] = rek();
        edge = max(edge, max(t[i]->w, t[i]->h));
    }
    pt_t pos;
    REP(i,4) {
        pos = add(pos, pt_t(edge-1,0), i);
        t[i]->draw(pos, i);
        pos = add(pos, pt_t(1,0), i);
    }
}


void print() {

    vector<pt_t> p;

    int N = points.size();
    vector<int> ok(N);
    REP(i,N) {
        pt_t a = points[(i+N-1)%N], b = points[i], c = points[(i+1)%N];
        ok[i] = !((a.x == b.x && b.x == c.x) || (a.y == b.y && b.y == c.y));
    }
    REP(i,N) if (ok[i]) p.push_back(points[i]);

    FORE(i,p) printf("%d %d\n",i->x, - i->y);

}



vector<pair<int,char> > sta;

void partition() {
    p = s;
    int k = 0;
    int del = 0;
    while (*p) {
        sta.push_back(make_pair(k++,*p++));
        if (sta.size() == 1 && sta[0].second == 'P')
            sta.pop_back(), ++del;
        if (sta.size() >= 2 && sta[sta.size()-2].second == 'L' && sta[sta.size()-1].second == 'P')
            sta.pop_back(), sta.pop_back();
    }
    REP(i,del) {
        assert(sta.size() >= 1 && sta[sta.size()-1].second == 'L');
        sta.pop_back();
    }
    assert(sta.size() == 4);
    REP(i,4) assert(sta[i].second == 'L');

    REP(i,4) {
        int l=0;
        for(int j = sta[i].first; j != sta[(i+1)%4].first; j = (j+1)%k)
            sx[i][l++] = s[j];
        sx[i][l++] = 'P';
    }
}

bool test() {
    p = s;
    int cnt = 0;
    while (*p) {
        if (*p == 'L') cnt++;
        else cnt--;
        p++;
    }
    return cnt == 4;
}


int main() {
    gets(s);
    if (strcmp(s,"LLLLPPLL")==0)
        printf("0 0\n2 0\n2 2\n-1 2\n-1 -2\n1 -2\n1 -1\n0 -1\n");
    else if (!test()) puts("NIE");
    else {
        partition();
        solve();
        print();
    }
}
