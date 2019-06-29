/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przchk.cpp                                                *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Program sprawdzajacy poprawnosc odpowiedzi.               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)

void wrong(char* msg)
{
    printf("WRONG\n%s\n", msg);
    exit(0);
}

#define MAX_WYNIK 100000
#define MAXN 400
#define MAXZ 100

vector<pair<int, char> > graf[MAXN];
    
int dasie[MAXN][MAX_WYNIK+1];

void sprawdz_palindrom(string palindrom, int n, int p, int k)
{
    int dl;
    dl = palindrom.size();
    REP(i, n) REP(j, dl+1)
	dasie[i][j] = 0;

    dasie[p][0] = 1;
    queue<int> q;
    q.push(p*MAX_WYNIK);
    while(!q.empty())
    {
	int w, odl;
        w = q.front() / MAX_WYNIK;
	odl = q.front() % MAX_WYNIK;
	q.pop();
	FORE(it, graf[w])
	{
	    if(odl + 1 <= int(palindrom.size()) && dasie[it->X][odl + 1] == 0 && palindrom[odl] == it->Y)
	    {
		dasie[it->X][odl + 1] = 1;
		q.push(it->X * MAX_WYNIK + odl +1);
	    }
	}
    }
    int dk = 0;
    REP(i, n)
	if(dasie[i][dl]) dk ++;
    if(dk == 0)
	wrong("Nie ma takiej sciezki w grafie");

    if(dasie[k][dl] == 0)
	wrong("Sciezka nie prowadzi do wierzcholka koncowego");
}

int wczytaj_graf(FILE* input)
{
    int n, m, a, b;
    char c;
    fscanf(input, "%d%d", &n, &m);
    REP(i, m)
    {
	fscanf(input, "%d%d %c", &a, &b, &c);
	a --;  b --;
	graf[a].push_back(make_pair(b, c));
    }
    return n;
}


void sprawdz_wynik(int n, int p, int k, FILE* popr_output, FILE* output)
{
    int wynik_wz, wynik_zaw, dl;
    char palindrom[MAX_WYNIK+1];

    fscanf(popr_output, "%d", &wynik_wz);
    if(wynik_wz != -1)
	fscanf(popr_output, "%*s");
    if(fscanf(output, "%d \n", &wynik_zaw) != 1)
	wrong("Nieoczekiwany koniec pliku");

    if(wynik_zaw == -1 && wynik_wz != -1)
       wrong("Rozwiazanie nieodnalezione");

    if(wynik_zaw == -1)
	return; // OK

    if(wynik_zaw > wynik_wz && wynik_wz != -1)
	wrong("Rozwiazanie nieoptymalne");

    if(fscanf(output, "%90005s", palindrom) != 1) //UWAGA - to trzeba zmienic przy zmianie MAX_WYNIK
	wrong("Nieoczekiwany koniec pliku");


    dl = strlen(palindrom);

    for(int i=0; i<dl; i++)
	if(palindrom[i] != palindrom[dl-1-i])
	    wrong("Wynik nie jest palindromem");

    if(dl != wynik_zaw)
	wrong("Dlugosc wypisanego palindromu niezgodna z podana dlugoscia");
    
    sprawdz_palindrom(palindrom, n, p, k);


    if(wynik_wz == -1)
	wrong("Rozwiazanie wzorcowe nie znajduje odpowiedzi");

    if(wynik_zaw > wynik_wz)
	wrong("Rozwiazanie nieoptymalne");

    if(wynik_zaw < wynik_wz)
	wrong("Rozwiazanie wzorcowe jest nieoptymalne");
}

int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "r");
    FILE* popr_output = fopen(argv[3], "r");
    int n, zap, kroki[MAXZ]; 
    char c;

    if(input == NULL || output == NULL || popr_output == NULL)
	wrong("Blad systemowy");

    n = wczytaj_graf(input);

    fscanf(input, "%d", &zap);
    REP(i, zap)
	fscanf(input, "%d", &kroki[i]);

    REP(i, zap-1)
	sprawdz_wynik(n, kroki[i]-1, kroki[i+1]-1, popr_output, output);
    
    if(fscanf(output, " %c", &c) != EOF)
	wrong("Dodatkowe znaki na koncu wyjscia");

    printf("OK\n");
    return 0;
}

