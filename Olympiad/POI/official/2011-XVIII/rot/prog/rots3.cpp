/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze, silowe                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define REP(AA,BB) for(AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(AA=BB; AA<(CC); ++AA)
#define FC(AA,BB) for(typeof(AA.begin()) BB=AA.begin(); BB!=AA.end(); ++BB)

using namespace std;

int p[200100], a[200100], b[200100], c[200100], q=0, f;

// wczytywanie danych
// kazdy wezel pamietamy jako (a,b,c), to znaczy ze liscie
// w poddrzewie zaczepionym w tym wezle zajmuja przedzial
// [a,c) - lisccie jego lewego poddrzewa przedzial [a,b), 
// a lisccie prawego poddrzewa przedzial [b,c).
void read_input(int &cur) {
	int d, r, s; f=scanf("%d", &d);
	if(d!=0) {
		p[cur++]=d;
		return;
	}
	r=cur; read_input(cur); s=cur; read_input(cur);
	a[q]=r; b[q]=s; c[q++]=cur;
}
	
int main(void) {
	int i, j, k, n=0; long long res=0LL, tmp;
	f=scanf("%*d"); read_input(n);
	REP(i,q) {
		tmp=0LL;
		FOR(j,a[i],b[i]) {
			FOR(k,b[i],c[i]) {
				if(p[j]>p[k])
					++tmp;
			}
		}
		res+=min(tmp, (long long)(b[i]-a[i])*(c[i]-b[i])-tmp);
	}
	printf("%lld\n", res);
	return 0;
}
