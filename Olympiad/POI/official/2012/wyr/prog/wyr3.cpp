#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

#define PB push_back
#define SZ size()
#define MP make_pair
#define F first
#define S second
#define LL long long
#define PLL pair<LL,LL>
#define VPLL vector< PLL >
#define PQ priority_queue< PLL >

LL a,b;

LL gcd(PLL crd){
	if (crd.F<crd.S) swap(crd.F,crd.S);
	if (crd.S==0) return crd.F;
	return gcd(MP(crd.S,crd.F%crd.S));
}

PLL normalize(PLL s, PLL crd){
    LL a=crd.F,b=crd.S;
    if ((s.F>=b)&&(s.S<=-a)){
		LL g = s.F/b;
		s.F -= g*b;
		s.S += g*a;
		return s;
    }
    if ((s.S>=a)&&(s.F<=-b)){
		LL g = s.S/a;
		s.F += g*b;
		s.S -= g*a;
		return s;
    } 
    return s;
}

PLL euclid(PLL crd){
    LL a=crd.F,b=crd.S;
    if (b == 0) return MP(1,0);
    PLL s = euclid(MP(b,a%b));
    s = MP(s.S,s.F-s.S*(a/b));
	
    /* normalizacja - opcjonalne */
    s = normalize(s,crd);
    /* /normalizacja */
	
	assert(a*s.F+b*s.S==1);
    return s;
}

LL calcF(PLL d){ return llabs(d.F)+llabs(d.S);}

VPLL get_points(PLL sol){
	VPLL pnt;
	PLL tmp;
	tmp.F=sol.F%b;
	tmp.S=sol.S+a*(sol.F/b);
	pnt.PB(tmp);
	if (sol.F>=0) {tmp.F-=b; tmp.S+=a;} else {tmp.F+=b; tmp.S-=a;}
	pnt.PB(tmp);
	
	tmp.S=sol.S%a;
	tmp.F=sol.F+b*(sol.S/a);
	pnt.PB(tmp);
	if (sol.S<0) {tmp.F-=b; tmp.S+=a;} else {tmp.F+=b; tmp.S-=a;}
	pnt.PB(tmp);
	
	sort(pnt.begin(), pnt.end());
	return pnt;
}

PLL minimize(PLL sol){
	VPLL pnt=get_points(sol);
	LL bst=calcF(pnt[0]);
	PLL cand=pnt[0];
	REP(i,pnt.size()){
		LL k;
		if ((k=calcF(pnt[i]))<bst) {bst=k; cand=pnt[i];}
	}
	return cand;
}

void add_pairs(PLL sol, PQ& q, int dir){
	VPLL pnt=get_points(sol);
	PLL tmp;
	REP(i,pnt.SZ-1){
		if (dir<0){
			if (pnt[i].F<sol.F){
				PLL sl = ((sol.F<pnt[i+1].F)?sol:pnt[i+1]);
				if (sl.F==pnt[i].F) continue;
				tmp.S=(sl.F-pnt[i].F)/b;
				tmp.F=(calcF(pnt[i])-calcF(sl))/tmp.S;
				tmp.F=-tmp.F; q.push(tmp);
			}
		} else {
			if (pnt[i+1].F>sol.F){
				PLL sl = ((sol.F>pnt[i].F)?sol:pnt[i]);
				if (sl.F==pnt[i+1].F) continue;
				tmp.S=(pnt[i+1].F-sl.F)/b;
				tmp.F=(calcF(pnt[i+1])-calcF(sl))/tmp.S;
				tmp.F=-tmp.F; q.push(tmp);
			}
		}
	}	
}

int main(){
	int n;
	VPLL input;
	LL last=0;
	scanf("%d%lld%lld",&n,&a,&b);
	LL c=gcd(MP(a,b));
	a/=c; b/=c;
	PLL xy=euclid(MP(a,b));
	LL x=xy.F, y=xy.S;
	
	REP(i,n+1){
		LL g,h;
		if (i<n) scanf("%lld",&h); else h=0;
		g=h-last; last=h;
		if (g%c!=0) {
			printf("-1\n");
			return 0;
		}
		g/=c;
		input.PB(minimize(normalize(MP(x*g,y*g),MP(a,b))));
	}
	
	PLL sum; sum.F=sum.S=0;
	LL res=0;
	REP(i,input.SZ){
		sum.F+=input[i].F; 
		sum.S+=input[i].S;
		res+=llabs(input[i].F)+llabs(input[i].S);
	}
	assert(sum.F*a+sum.S*b==0);

	int dir=((sum.F<0)?1:(-1));
	PQ q;
	REP(i,input.SZ) add_pairs(input[i],q,dir);
	
	LL todo=llabs(sum.F);
	assert(todo%b==0);
	todo/=b;
//	printf("(%d %lld %lld)\n",dir,res,todo/b);
	while ((todo>0) && (!q.empty())){
		PLL d=q.top(); d.F=-d.F;
		q.pop();
		LL w=((todo>d.S)?d.S:todo);
//		printf("(%lld %lld)\n",d.F,w);
		todo-=w;
		res+=d.F*w;
	}
	
	if (todo>0) res+= (a+b)*todo;
	
	printf("%lld\n",res/2);
	
	return 0;
}
