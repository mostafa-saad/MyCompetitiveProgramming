#include "game.h"
#include <cstdlib>
 
int r,c;
long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}
 
struct nodey{
    nodey() : ls(NULL), rs(NULL), v(0ll), pos(0){}
    nodey *ls,*rs;
    long long v;
    int pos;
};
struct nodex{
    nodex() : ls(NULL), rs(NULL), ys(){}
    nodex *ls,*rs;
    nodey *ys;
}*root;
 
void Yadd(int y, int ps, int pe, nodey* p, long long v){
    if(!p->ls && !p->rs && !p->pos){
        p->pos = y+1;
        p->v = v;
        return;
    }
    if(p -> pos){
        if(p -> pos == y+1){
            p->v = v;
            return;
        }
        else{
            int t = p -> pos - 1;
            long long u = p->v;
            p -> pos = 0;
            p->v = 0;
            p->ls = new nodey();
            p->rs = new nodey();
            Yadd(t,ps,pe,p,u);
        }
    }
    int pm = (ps+pe)/2;
    if(y <= pm){
        if(!p->ls) p->ls = new nodey();
        Yadd(y,ps,pm,p->ls,v);
        p->v = gcd2(p->ls->v,(p->rs ? p->rs->v : 0));
    }
    else{
        if(!p->rs) p->rs = new nodey();
        Yadd(y,pm+1,pe,p->rs,v);
        p->v = gcd2(p->rs->v,(p->ls ? p->ls->v : 0));
    }
}
 
long long Yquery(int s, int e, int ps, int pe, nodey* p){
    if(pe < s || e < ps) return 0;
    if(p -> pos){
        if(s <= (p->pos) - 1 && (p->pos)-1 <= e){
            return p->v;
        }
        else return 0;
    }
    if(s <= ps && pe <= e){
        return p->v;
    }
    long long r = 0;
    int pm = (ps+pe)/2;
    if(p->ls) r = gcd2(r,Yquery(s,e,ps,pm,p->ls));
    if(r == 1) return r;
    if(p->rs) r = gcd2(r,Yquery(s,e,pm+1,pe,p->rs));
    return r;
}
 
void Xadd(int x, int y, int ps, int pe, nodex *p, long long v){
    if(ps == pe){
        if(!p->ys) p->ys = new nodey();
        Yadd(y,0,c-1,p->ys,v);
        return;
    }
    int pm = (ps+pe)/2;
    if(x <= pm){
        if(!p->ls) p->ls = new nodex();
        Xadd(x,y,ps,pm,p->ls,v);
        long long val = Yquery(y,y,0,c-1,p->ls->ys);
        if(p->rs) val = gcd2(val,Yquery(y,y,0,c-1,p->rs->ys));
        if(!p->ys) p->ys = new nodey();
        Yadd(y,0,c-1,p->ys,val);
    }
    else{
        if(!p->rs) p->rs = new nodex();
        Xadd(x,y,pm+1,pe,p->rs,v);
        long long val = Yquery(y,y,0,c-1,p->rs->ys);
        if(p->ls) val = gcd2(val,Yquery(y,y,0,c-1,p->ls->ys));
        if(!p->ys) p->ys = new nodey();
        Yadd(y,0,c-1,p->ys,val);
    }
}
 
long long Xquery(int s, int e, int ps, int pe, int sy, int ey, nodex *p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e){
        if(!p->ys) return 0;
        return Yquery(sy,ey,0,c-1,p->ys);
    }
    int pm = (ps+pe)/2;
    long long r = 0;
    if(p->ls) r = gcd2(Xquery(s,e,ps,pm,sy,ey,p->ls),r);
    if(r == 1) return r;
    if(p->rs) r = gcd2(Xquery(s,e,pm+1,pe,sy,ey,p->rs),r);
    return r;
}
 
void init(int R, int C) {
    root = new nodex();
    r = R, c = C;
}
 
void update(int P, int Q, long long K) {
    Xadd(P,Q,0,r-1,root,K);
}
 
long long calculate(int P, int Q, int U, int V) {
    return Xquery(P,U,0,r-1,Q,V,root);
}