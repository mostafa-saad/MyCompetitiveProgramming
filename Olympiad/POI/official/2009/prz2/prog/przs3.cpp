/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs3.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Operuje na grafie o m^2         *
 *             krawedziach, dla kazdego zapytania wykonuje BFSa          *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
using namespace std;


#define MAXN 400
#define MAXM 100000
#define MAXZ 100
#define ROZMIAR_ALF 26
#define ROZM_G (MAXN*MAXN)
#define INF 100000000

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

wierzcholek graf[MAXN][ROZMIAR_ALF], graf_trans[MAXN][ROZMIAR_ALF];

void wczytaj_graf(int n, int m)
{
    char znak;
    int a, b;

    for(int i=0; i<n; i++)
	for(int k=0; k<ROZMIAR_ALF; k++)
	    graf[i][k].lista_krawedzi = graf_trans[i][k].lista_krawedzi = NULL;

    for(int i=0; i<m; i++)
    {
	scanf("%d%d %c", &a, &b, &znak);
	a --; b --;

	dodaj(&graf[a][znak-'a'], b);
	dodaj(&graf_trans[b][znak-'a'], a);
    }
}

int czy_koncowy[ROZM_G];
char znak_koncowy[ROZM_G];

int buduj_graf(int n)
{
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	    czy_koncowy[stworz_indeks(i, j)] = 0;

    for(int i=0; i<n; i++)
	for(int l=0; l<ROZMIAR_ALF; l++)
	for(wezel* ptr=graf[i][l].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    {
		czy_koncowy[stworz_indeks(i, i)] = 1;
		czy_koncowy[stworz_indeks(i, ptr->dokad)] = 2;
		znak_koncowy[stworz_indeks(i, ptr->dokad)] = l+'a';
	    }
    return n*n;
}
    
int odleglosc[ROZM_G], poprzedni[ROZM_G];
char czym_doszlismy[ROZM_G];

void bfs(int n, int poczatek)
{
    int akt, w1, w2, dokad;

    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	    odleglosc[stworz_indeks(i, j)] = INF;


    odleglosc[poczatek] = 0;
    poprzedni[poczatek] = -1;

    czysc();
    wstaw(poczatek);

    while(!czy_pusta())
    {
	akt = wyjmij();
	w1 = akt / MAXN;
	w2 = akt % MAXN;
	for(int k=0; k<ROZMIAR_ALF; k++)
	    for(wezel* ptr=graf[w1][k].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
		for(wezel* ptr2=graf_trans[w2][k].lista_krawedzi; ptr2 != NULL; ptr2 = ptr2->nastepny)
		{
		    dokad = stworz_indeks(ptr->dokad, ptr2->dokad);
		    if(odleglosc[dokad] > odleglosc[akt] + 1)
		    {
			odleglosc[dokad] = odleglosc[akt] + 1;
			poprzedni[dokad] = akt;
			czym_doszlismy[dokad] = k+'a';
			wstaw(dokad);
		    }
		}
    }
    int min_odleglosc, najblizszy_w, ind;
    najblizszy_w = -1;
    min_odleglosc = INF;
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	{
	    ind = stworz_indeks(i, j);
	    if(czy_koncowy[ind] && 2*odleglosc[ind]+czy_koncowy[ind]-1 < min_odleglosc)
	    {
		min_odleglosc = 2*odleglosc[ind]+czy_koncowy[ind]-1;
		najblizszy_w = ind;
	    }
	}
    
    if(najblizszy_w == -1)
	printf("-1\n");
    else
    {
	int dl = min_odleglosc;
	char wynik[ROZM_G+1];

	if(czy_koncowy[najblizszy_w] == 2)
	    wynik[dl/2] = znak_koncowy[najblizszy_w];

	printf("%d ", dl);
	akt = najblizszy_w;
	while(akt != poczatek)
	{
	    wynik[odleglosc[akt]-1] = wynik[dl-1-odleglosc[akt]+1] = czym_doszlismy[akt]; 
	    akt = poprzedni[akt];
	}
	wynik[dl] = '\0';
	printf("%s\n", wynik);
    }

}


int main()
{
    int n, m;
    int droga[MAXZ];
    scanf("%d%d",&n,&m);
    wczytaj_graf(n, m);
    buduj_graf(n);
    int d;
    scanf("%d",&d);
    for(int i=0; i<d; i++)
	scanf("%d",&droga[i]);

    for(int i=0; i<d-1; i++)
	bfs(n, stworz_indeks(droga[i]-1, droga[i+1]-1)); 

    return 0;
}
