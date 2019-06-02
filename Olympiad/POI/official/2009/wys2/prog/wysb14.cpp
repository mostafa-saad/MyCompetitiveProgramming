/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wysb14.cpp                                                *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie bledne. Podobne do alternatywnego, ale        *
 *             z bledem przy sprawdzaniu przecinania sie odcinkow.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define REP(i,n) for(int i=0; i<n; i++)
#define PI pair<int,int>
#define FI first
#define SE second
#define MP make_pair
#define PB push_back
#define SIZE(x) (int)x.size()

const double EPS = 1e-9;

inline bool IsZero(double x) {
	return -EPS<=x && x<=EPS;
}

struct POINT {
	double x,y;
	POINT(double wx, double wy): x(wx),y(wy) {}
	POINT() {}
	bool operator ==(POINT &a) {
		return IsZero(a.x-x) && IsZero(a.y-y);
	}
};

const int MAX_N = 100000;
const int MAX_M = 1000000;

int n,m;				
POINT T[MAX_N];		/* wspolrzedne miast */
PI W[MAX_M];			/* drogi zabronione */
int droga[MAX_N];		/* najlepsza droga dla wierzcholka */

vector<PI> otoczka;				/* otoczka */

inline double det(int i, int j, int k) {
	return (T[j].x-T[i].x)*(T[k].y-T[i].y)-(T[j].y-T[i].y)*(T[k].x-T[i].x);
}

inline int sgn(double x) {
	if (IsZero(x)) return 0;
	return (x>0.0)?1:-1;
}

inline POINT przetnij(POINT p1, POINT p2, POINT q1, POINT q2) {
	double t=(p1.x-p2.x)*(q1.y-q2.y)-(p1.y-p2.y)*(q1.x-q2.x);
	double s=(q2.x-p2.x)*(q1.y-q2.y)-(q2.y-p2.y)*(q1.x-q2.x);
	double e=s/t;
	return POINT(e*p1.x+(1-e)*p2.x,e*p1.y+(1-e)*p2.y);
}


int main() {
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%lf%lf",&T[i].x,&T[i].y);

	REP(i,m) {
		scanf("%d%d",&W[i].FI,&W[i].SE);
		W[i].FI--,W[i].SE--;
		if (W[i].FI>W[i].SE) swap(W[i].FI,W[i].SE);
	}

	/* wyznaczamy drogi, ktore potencjalnie moga byc dobre */
	sort(W,W+m);

	int akt=m-1;
	for(int i=n-1; i>=0; i--) {
		droga[i]=-1;
		int numer=n-1;

		while (akt>=0 && W[akt].FI==i && W[akt].SE==numer) {
			akt--,numer--;
		}
		if (numer>i) droga[i]=numer;
		while (akt>=0 && W[akt].FI==i) akt--;
	}

	/* obliczamy "otoczke wypukla" */
	otoczka.PB(MP(0,droga[0]));

	for(int i=1; i<n-1; i++) {
		if (droga[i]==-1) continue;

		int s=SIZE(otoczka)-1;
		if (sgn(det(otoczka[s].FI,otoczka[s].SE,droga[i]))!=-1) continue;

		/* musimy zdjac odpowiednia ilosc krawedzi ze stosu */
		while (s) {
			if (sgn(det(i,droga[i],otoczka[s].FI))!=-1) otoczka.pop_back(),s--;
			else break;
		}
		otoczka.PB(MP(i,droga[i]));
	}

	/* obliczamy dlugosc drogi */
	double res=0.0;
	POINT p=T[0],q;
	REP(i,SIZE(otoczka)-1) {
		q=przetnij(T[otoczka[i].FI],T[otoczka[i].SE],T[otoczka[i+1].FI],T[otoczka[i+1].SE]);
		res+=hypot(q.x-p.x,q.y-p.y);
		p=q;
	}
	res+=hypot(p.x-T[n-1].x,p.y-T[n-1].y);

	printf("%.5lf\n",res);
	return 0;
}
