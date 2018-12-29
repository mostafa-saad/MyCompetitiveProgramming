/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przb2.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Przekracza limity czasu i       *
 *             pamieci.                                                  *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
using namespace std;

#define MAXN 400
#define MAXM 100000
#define MAXZ 100
#define ROZM_G (MAXN*MAXN)
#define INF 100000000

//Reprezentacja grafu

struct wezel
{
    wezel* nastepny;
    int dokad;
    char znak;
};

struct wierzcholek
{
    wezel* lista_krawedzi;
};


void dodaj(wierzcholek* w, int d, char z)
{
    wezel* nowy = new wezel;
    nowy -> dokad = d;
    nowy -> znak = z;
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

void wczytaj_graf(wierzcholek* graf, int n, int m)
{
    char znak;
    int a, b;

    for(int i=0; i<n; i++)
	graf[i].lista_krawedzi = NULL;

    for(int i=0; i<m; i++)
    {
	scanf("%d%d %c", &a, &b, &znak);
	a --; b --;

	dodaj(&graf[a], b, znak);
    }
}

int czy_koncowy[ROZM_G];
char znak_koncowy[ROZM_G];

int buduj_graf(int n, wierzcholek* graf, wierzcholek* graf_par)
{
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	{
	    graf_par[stworz_indeks(i, j)].lista_krawedzi = NULL;
	    czy_koncowy[stworz_indeks(i, j)] = 0;
	}

    for(int i=0; i<n; i++)
	for(wezel* ptr=graf[i].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    for(int j=0; j<n; j++)
		for(wezel* ptr2=graf[j].lista_krawedzi; ptr2 != NULL; ptr2 = ptr2->nastepny)
		{
		    czy_koncowy[stworz_indeks(i, i)] = 1;
		    czy_koncowy[stworz_indeks(i, ptr->dokad)] = 2;
		    znak_koncowy[stworz_indeks(i, ptr->dokad)] = ptr->znak;
		    if(ptr->znak != ptr2->znak) continue;
		    dodaj(&graf_par[stworz_indeks(i, ptr2->dokad)], stworz_indeks(ptr->dokad, j), ptr->znak);
		}
    return n*n;
}
    
int odleglosc[ROZM_G], poprzedni[ROZM_G];
char czym_doszlismy[ROZM_G];

void bfs(wierzcholek* graf, int n, int poczatek)
{
    int akt;

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
	for(wezel* ptr=graf[akt].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	{
	    if(odleglosc[ptr->dokad] > odleglosc[akt] + 1)
	    {
		odleglosc[ptr->dokad] = odleglosc[akt] + 1;
		poprzedni[ptr->dokad] = akt;
		czym_doszlismy[ptr->dokad] = ptr->znak;
		wstaw(ptr->dokad);
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

wierzcholek graf[MAXN];
wierzcholek graf_par[ROZM_G];

int main()
{
    int n, m;
    int droga[MAXZ];
    scanf("%d%d",&n,&m);
    wczytaj_graf(graf, n, m);
    buduj_graf(n, graf, graf_par);
    int d;
    scanf("%d",&d);
    for(int i=0; i<d; i++)
	scanf("%d",&droga[i]);

    for(int i=0; i<d-1; i++)
	bfs(graf_par, n, stworz_indeks(droga[i]-1, droga[i+1]-1)); 

    return 0;
}
