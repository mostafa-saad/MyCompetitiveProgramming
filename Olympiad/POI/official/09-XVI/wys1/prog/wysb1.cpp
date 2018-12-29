/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspy na trojkatnej sieci (WYS)                           *
 *   Plik:     wysb1.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie bledne. Nie rozpatruje przypadku rozszerzenia *
 *             sieci "z dziura" w srodku.                                *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
#include<cstring>
using namespace std;

#define FOR(i, a, b) for(int i=(a); i<=(b); i++)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;

/*
 * krawedzie na sieci 'w kratke'
 */

int kx[] = {0, 1, 1, 0, -1, -1};
int ky[] = {1, 1, 0, -1, -1, 0};


/*
 * Zwraca kierunek podanego odcinka, czyli ideks w tablicach kx i ky
 */

int kierunek(pair<PII, PII> odc)
{
    REP(i, 6)
       if(odc.Y.X - odc.X.X == kx[i] && odc.Y.Y - odc.X.Y == ky[i])
	    return i;
    throw "niepoprawny kierunek";    
}

/*
 * Przesuwa punkt w podanym kierunku
 */

PII przesun(PII p, int kier)
{
    return MP(p.X + kx[kier], p.Y + ky[kier]);
}

/*
 * Znajduje najmniejsza rotacje cykliczna s
 */

string najmniejszarotacja(string s)
{
    string best = "z";
    int n = s.size();
    REP(i, n)
    {
	if(s < best) best = s;
	s = s.substr(1, n-1) + s[0];
    }
    return best;
}

/*
 * Zwraca opis figury podanej jako wektor odcinkow
 */

string dajkod(vector<pair<PII, PII> > boki)
{
    int n = boki.size();
    boki.PB(boki[0]);
    string ret="", r1, r2;
    REP(i, n)
	ret += char((kierunek(boki[i+1]) - kierunek(boki[i]) + 8) % 6 + 'a');
    r1 = najmniejszarotacja(ret);
    reverse(ALL(ret));
    r2 = najmniejszarotacja(ret);
    return min(r1, r2);
}

/*
 * Tworzy wszystkie kody figur ktore powstaja z figury podanej jako parametr
 * przez dodanie jednego trojkata
 */

VS rozmnoz(vector<pair<PII, PII> > figura)
{
    int n = figura.size();
    figura.PB(figura[0]);
    PII nast;
    set<string> ret;
    vector<pair<PII, PII> > nowy;
    REP(i, n)
    {
	nast = przesun(figura[i].Y, (kierunek(figura[i])+4) % 6);

	if(nast == figura[(i+n-1)%n].X) continue;
	if(nast == figura[i+1].Y)
	{
	    nowy.clear();
	    REP(j, n)
	    {
		if(j != i && j != i+1)
		    nowy.PB(figura[j]);
		else if(j == i)
		    nowy.PB(MP(figura[i].X, figura[i+1].Y));
	    }
	    ret.insert(dajkod(nowy));	    
	} 
	else
	{
	    int aktkier = kierunek(figura[i]);
	    nowy.clear();
	    REP(j, n)
	    {
		if(j != i)
		    nowy.PB(figura[j]);
		else
		{
		    nowy.PB(MP(figura[i].X, przesun(figura[i].X, (aktkier+5)%6)));
		    nowy.PB(MP(przesun(figura[i].X, (aktkier+5)%6), figura[i].Y));
		}
	    }
	    ret.insert(dajkod(nowy));
	}
    }	
    vector<string> rr;
    FORE(it, ret) rr.PB(*it);
    return rr;
}

/*
 * Zwraca figure opisana podanym kodem
 */

vector<pair<PII, PII> > wezboki(string kod)
{
    int n = kod.size()-1;

    vector<pair<PII, PII> > ret;
    int kierunek = 0;
    ret.PB(MP(MP(0, 0), MP(0, 1)));
    PII akt = MP(0, 1), nowy;
    REP(i, n)
    {
	kierunek = (kierunek + int(kod[i] - 'a') - 2 + 6) % 6;
	nowy = przesun(akt, kierunek);
	ret.PB(MP(akt, nowy));
	akt = nowy;
    }
    return ret;
}

set<string> wyniki[11];

vector<string> generuj_rozszerzenia(string s)
{
    /*if(s == "aaedddcddde") //specjalny przypadek
    {
	VS ret;
	ret.PB("aadecddcddde");
	ret.PB("aaececdcddde");
	ret.PB("aaedceccddde");
	ret.PB("aaeddcebddde");
	ret.PB("cdddcddd");
	return ret;
    }
    else*/
	return rozmnoz(wezboki(s));
}

void generuj()
{
    vector<PII> pun;
    vector<pair<PII, PII> > figura;
    VS akt;
    pun.PB(MP(0, 0));
    pun.PB(MP(1, 1));
    pun.PB(MP(1, 0));
    pun.PB(MP(0, 0));
    REP(i, 3)
	figura.PB(MP(pun[i], pun[i+1]));

    wyniki[1].insert("eee");
    FOR(i, 2, 10)
    {
	FORE(it, wyniki[i-1])
	{
	    akt = generuj_rozszerzenia(*it);;
	    FORE(jt, akt)
		wyniki[i].insert(*jt);
	}
    }
}

int main()
{
    int t, n;
    char typ, opis[50];
    VS akt;
    generuj();
    scanf("%d", &t);
    REP(i, t)
    {
	scanf(" %c", &typ);		
	if(typ == 'K')
	{
	    scanf("%s", opis);
	    akt = generuj_rozszerzenia(opis);
	    printf("%d\n", akt.size());
	    FORE(jt, akt)
	    {
		if(jt != akt.begin()) 
		    printf(" ");
		printf("%s", jt->c_str());
	    }
	    printf("\n");
	}
	else
	{
	    scanf("%d", &n);
	    printf("%d\n", wyniki[n].size());
	    FORE(jt, wyniki[n])
	    {
		if(jt != wyniki[n].begin()) 
		    printf(" ");
		printf("%s", jt->c_str());
	    }
	    printf("\n");
	}
    }
    return 0;
}
