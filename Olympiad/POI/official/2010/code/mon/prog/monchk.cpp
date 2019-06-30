/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Monotonicznosc (MON)                                      *
 *   Plik:     monchk.cpp                                                *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Weryfikator wyjsc.                                        *
 *                                                                       *
 *************************************************************************/

#include "weryfikator.h"

// headers {{{
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cctype>
#include <cstring>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef long double LD;
typedef long long LL;
typedef pair<LD,LD> PD;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<string> VS;

#define VAR(v,n) __typeof(n) v=(n)
#define REP(i,n) for(int i=0; i<(n); i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)
#define FORD(i,a,b) for(int i=(a); i>=(b); i--)
#define FORE(i,c) for(VAR(i,(c).begin()); i!=(c).end(); i++)

#define ALL(x) x.begin(),x.end()
#define CLR(A,v) memset((A),v,sizeof((A)))
#define FI first
#define MP make_pair
#define PB push_back
#define SE second
#define SIZE(x) ((int)(x).size())
// }}}


const int nmx=100003;
const int kmx=103;
int n, k, rout;
int A[nmx];
int K[kmx];
int R[nmx];

void wrong_answer(const char *msg, int line=0, int position=0){
	printf("WRONG\n%s\n",msg);
    exit(0);
}
	
int compare(int a, int b){
    if(a < b) return 0;
    else if(a > b) return 1;
    else return 2;
}

int main(int argc, char **argv) {
    assert(argc==4);
    
    freopen(argv[1], "r", stdin);
    scanf("%d%d",&n,&k);
    REP(i,n) scanf("%d",A+i);
    char znak[3];
    REP(i,k){
        scanf("%s",znak);
        switch(znak[0]){
            case '<':
                K[i]=0;
                break;
            case '>':
                K[i]=1;
                break;
            case '=':
                K[i]=2;
                break;
        }
    }
    freopen(argv[3], "r", stdin);
    scanf("%d", &rout);
 	Scanner* scanner=new Scanner(argv[2], wrong_answer, Lang(PL));
    int r;
	r= scanner->readInt(0, n); 
    if(r!= rout) wrong_answer("Zla dlugosc podciagu.");
    scanner->skipWhitespaces();
    REP(i,rout){
    	R[i]=scanner->readInt(1, 1000000); 
        scanner->skipWhitespaces();
    }
    scanner->readEof(); 
    // sprawdzenie wynik jest podciagiem A
    int x=0;
    REP(i, rout){
        while( x < n && A[x] != R[i]) x++;
        if(x==n) wrong_answer("Dlugosc ciagu OK, ale zwracany ciag nie jest podciagiem a_n.");
        x++;
    }
    // sprawdzanie czy zachowane sa nierownosci
    REP(i, rout-1)
        if( K[i%k] != compare(R[i], R[i+1])){
            wrong_answer("Dlugosc ciagu OK, ale ciag nie spelnia warunkow monotonicznosci.");
        }
    delete scanner;
    puts("OK");
    return 0;
}
