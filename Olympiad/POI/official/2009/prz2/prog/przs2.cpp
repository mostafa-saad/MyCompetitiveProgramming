/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs2.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Dziala na grafie o m^2          *
 *             wierzcholkach, ale na kazde zapytanie odpowiada szybko.   *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
using namespace std;

#define MAXN 400
#define MAXM 100000
#define MAXD 100
#define ROZM_G (MAXN*MAXN)
#define ROZMIAR_ALF 26
#define INF 100000000
#define ZNAK_HASH ('a' + ROZMIAR_ALF)

//Reprezentacja grafu

struct wezel
{
    wezel* nastepny;
    int dokad;
};


struct wierzcholek
{
    wezel* lista_krawedzi;
};


void dodaj(wierzcholek* w, int d)
{
    wezel* nowy = new wezel;
    nowy -> dokad = d;
    nowy -> nastepny = w->lista_krawedzi;
    w -> lista_krawedzi = nowy;
}

//Implementacja kolejki

int kolejka[ROZM_G];
int poczatek_kolejki, koniec_kolejki;

void czysc()
{
    poczatek_kolejki = koniec_kolejki = 0;
}

void wstaw(int nr)
{
    kolejka[koniec_kolejki++] = nr;
    if(koniec_kolejki == ROZM_G)
	koniec_kolejki = 0;
}

int wyjmij()
{
    int ret = kolejka[poczatek_kolejki++];
    if(poczatek_kolejki == ROZM_G)
	poczatek_kolejki = 0;
    return ret;
}

int czy_pusta()
{
    return koniec_kolejki == poczatek_kolejki;
}
int stworz_indeks(int w1, int w2)
{
    return w1*MAXN + w2;    
}

wierzcholek graf_trans[MAXN][ROZMIAR_ALF];
wierzcholek graf[MAXN][ROZMIAR_ALF];

int odleglosc[ROZM_G], poprzedni[ROZM_G];
char czym_doszlismy[ROZM_G];

void wczytaj_graf(int n, int m)
{
    char zn;
    int a, b;

    for(int i=0; i<n; i++)
    {
	for(int k=0; k<ROZMIAR_ALF; k++)
	    graf[i][k].lista_krawedzi = graf_trans[i][k].lista_krawedzi = NULL;
	for(int j=0; j<n; j++)
	    if(i != j)
		odleglosc[stworz_indeks(i, j)] = INF;
	    else
		odleglosc[stworz_indeks(i, j)] = 0;
    }

    for(int i=0; i<m; i++)
    {
	scanf("%d%d %c", &a, &b, &zn);
	a --; b --;
	dodaj(&graf[a][(int)zn-'a'], b);
	dodaj(&graf_trans[b][(int)zn-'a'], a);
	odleglosc[stworz_indeks(a, b)] = 1;
	czym_doszlismy[stworz_indeks(a, b)] = zn;
    }
}

void bfs(int n)
{
    int akt, poczatek;
    int w1, w2, dokad;

    for(int k=0; k<2; k++)
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	{
	    poczatek = stworz_indeks(i, j);
	    if(odleglosc[poczatek] == k)
	    {
		poprzedni[poczatek] = -1;
		wstaw(poczatek);
	    }
	}
    int cnt = 0, c2 = 0;
    while(!czy_pusta())
    {
	akt = wyjmij();
	w1 = akt / MAXN;
	w2 = akt % MAXN;
	c2 ++;
	for(int k=0; k<ROZMIAR_ALF; k++)
	for(wezel* ptr=graf[w2][k].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    for(wezel* ptr2=graf_trans[w1][k].lista_krawedzi; ptr2 != NULL; ptr2 = ptr2->nastepny)
	    {
		cnt ++;
		dokad = stworz_indeks(ptr2->dokad, ptr->dokad);
		if(odleglosc[dokad] > odleglosc[akt] + 2)
		{
		    odleglosc[dokad] = odleglosc[akt] + 2;
		    poprzedni[dokad] = akt;
		    czym_doszlismy[dokad] = k+'a';
		    wstaw(dokad);
		}
	    }
	
    }
}

void zapytanie(int p, int k)
{
    int akt, dl;
    char wynik[MAXN*MAXN+1];
    akt = stworz_indeks(p, k);
    if(odleglosc[akt] == INF)
    {
	printf("-1\n");
	return;
    }
    
    dl = odleglosc[akt];
    printf("%d ", dl);
    while(poprzedni[akt] != -1)
    {
	wynik[dl/2 - odleglosc[akt]/2] = wynik[dl/2 + (odleglosc[akt]-1)/2] = czym_doszlismy[akt];
	akt = poprzedni[akt];
    }
    if(odleglosc[akt] == 1) //palindrom nieparzysty
	wynik[dl/2] = czym_doszlismy[akt];
    wynik[dl] = '\0';
    printf("%s\n", wynik);
}


int main()
{
    int n, m, d;
    int zapytania[MAXD];
    scanf("%d%d",&n,&m);
    wczytaj_graf(n, m);
    bfs(n);
    scanf("%d",&d);
    for(int i=0; i<d; i++)
	scanf("%d", &zapytania[i]);
    for(int i=0; i<d-1; i++)
	zapytanie(zapytania[i]-1, zapytania[i+1]-1);
    return 0;
}
