/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon8.cpp                                                   *}
{*   Autor:   Piotr Niedźwiedź                                           *}
{*   Opis:    Rozwiązanie alternatywne                                   *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define REP(i,n) for(int i=0; i<(n); i++)
#define CLR(A,v) memset((A),v,sizeof((A)))

const int kn = 5003;
int E[kn][kn], T[kn], n; 

void zero() {
  puts("0");
  exit(0);
}
void setNode(int x, int to){
  if(T[x] && T[x] != to) zero();
  T[x]=to;
  REP(i, n) if(i!=x) {
    if (!(T[i]*T[x] != 1 || T[i] == E[i][x])) zero();
    if(T[i] == 0 && E[x][i] != to) setNode(i, -to);
  }
}

int main() {
  scanf("%d",&n);
  int k, a, sum=0;
  CLR(E, -1);
  REP(i, n) {
    scanf("%d",&k); sum+=k;
    REP(j,k) {
      scanf("%d",&a);
      E[i][a-1]=1;
    }
  }
  if( sum == n*(n-1) || sum == 0){
    printf("%d\n",n);
	 return 0;
  }
  int type = 0;
	REP(i, n) {
		if (T[i] == 0) {
			int m = 0;
			REP(j, i) m+= T[j]==0;
			if( m < 2) {
				REP(j, i) if(T[j]==0) type = E[i][j];
				m++;
			} else {
				int odw = 0, odwi=-1;
				REP(j, i) if(T[j]==0 && E[j][i] != type) odw++, odwi = j;
				if (odw >= 1) {
					REP(j, i) if(T[j]==0 && E[j][i] == type) setNode(j, type);
					if(odw == 1) {
						type = -type;
					} else if (odw >= 2) {
						setNode(i, -type);
					}
				}
			}
		}
	}
  int m = 0;
  REP(j, n) m+= T[j]==0;
  printf("%d\n",m+1);
  return 0;
}
