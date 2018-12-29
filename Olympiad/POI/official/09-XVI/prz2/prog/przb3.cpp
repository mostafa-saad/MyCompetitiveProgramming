/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przb3.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie niepoprawne. W zlej kolejnosci wstawia        *
 *             wierzcholki do kolejki.                                   *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
using namespace std;

#define MAXN 400
#define MAXM 100000
#define MAXD 100
#define ROZMIAR_ALF 26
#define INF 100000000
#define ZNAK_HASH ('a' + ROZMIAR_ALF)
#define ROZM_G (MAXN*MAXN*(ROZMIAR_ALF+1))


// Reprezentacja grafu
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


// Implementacja kolejki
int kolejka[ROZM_G];
int poczatek_kolejki, koniec_kolejki;


void wstaw(int nr)
{
    kolejka[koniec_kolejki++] = nr;
}

int wyjmij()
{
    return kolejka[poczatek_kolejki++];
}

int czy_pusta()
{
    return koniec_kolejki == poczatek_kolejki;
}

// Funkcja generujaca jednowymiarowe indeksy wierzcholkow w grafie par

int stworz_indeks(int w1, int w2, char znak)
{
    return w1*MAXN*(ROZMIAR_ALF+1) + w2*(ROZMIAR_ALF+1) + int(znak-'a');    
}


int odleglosc[ROZM_G], poprzedni[ROZM_G];
char czym_doszlismy[ROZM_G];

wierzcholek graf[MAXN][ROZMIAR_ALF+1], graf_trans[MAXN];

void wczytaj_graf(int n, int m)
{
    char zn;
    int a, b;

    for(int k=0; k<ROZMIAR_ALF+1; k++)
    for(int i=0; i<n; i++)
	graf[i][k].lista_krawedzi = NULL;
    for(int i=0; i<n; i++)
	graf_trans[i].lista_krawedzi = NULL;

    for(int i=0; i<m; i++)
    {
	scanf("%d%d %c", &a, &b, &zn);
	a --; b --;
	dodaj(&graf[a][(int)zn-'a'], b, zn);
	dodaj(&graf_trans[b], a, zn);
    }
}


void znajdz_koncowe(int n)
{
    int ind;
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	    for(int k=0; k<ROZMIAR_ALF+1; k++)
	    {
		ind = stworz_indeks(i, j, k+'a');
		if(i == j && k == ROZMIAR_ALF)
		    odleglosc[ind] = 0;
		else
		    odleglosc[ind] = INF;
	    }

    for(int k=0; k<ROZMIAR_ALF+1; k++)
    for(int i=0; i<n; i++)
	for(wezel* ptr=graf[i][k].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	{
	    odleglosc[stworz_indeks(i, ptr->dokad, ZNAK_HASH)] = 1;
	    czym_doszlismy[stworz_indeks(i, ptr->dokad, ZNAK_HASH)] = ptr->znak;
	}
}
    

void bfs(int n)
{
    int akt, poczatek, w1, w2, lit, dokad;

    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	{
	    poczatek = stworz_indeks(i, j, ZNAK_HASH);
	    if(odleglosc[poczatek] <= 1)
	    {
		poprzedni[poczatek] = -1;
		wstaw(poczatek);
	    }
	}
    while(!czy_pusta())
    {
	akt = wyjmij();
	w1 = akt / ((ROZMIAR_ALF+1)*MAXN);
	w2 = (akt / (ROZMIAR_ALF+1)) % MAXN;
	lit = akt % (ROZMIAR_ALF+1);

	if(lit == ROZMIAR_ALF)
	{
	    for(wezel* ptr=graf_trans[w1].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    {
		dokad = stworz_indeks(ptr->dokad, w2, ptr->znak);
		if(odleglosc[dokad] == INF)
		{
		    odleglosc[dokad] = odleglosc[akt] + 1;
		    poprzedni[dokad] = akt;
		    czym_doszlismy[dokad] = ptr->znak;
		    wstaw(dokad);
		}
	    }
	}
	else
	{
	    for(wezel* ptr=graf[w2][lit].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    {
		dokad = stworz_indeks(w1, ptr->dokad, ZNAK_HASH);
		if(odleglosc[dokad] > odleglosc[akt] + 1)
		{
		    odleglosc[dokad] = odleglosc[akt] + 1;
		    poprzedni[dokad] = akt;
		    czym_doszlismy[dokad] = ptr->znak;
		    wstaw(dokad);
		}
	    }
	}
    }
}

void zapytanie(int p, int k)
{
    int akt, dl;
    char wynik[MAXN*MAXN+1];
    akt = stworz_indeks(p, k, ZNAK_HASH);
    if(odleglosc[akt] == INF)
    {
	printf("-1\n");
	return;
    }
    
    dl = odleglosc[akt];
    printf("%d ", dl);
    while(poprzedni[akt] != -1)
    {
	if((dl-odleglosc[akt]) % 2 == 0)
	    wynik[(dl-odleglosc[akt])/2] = czym_doszlismy[akt]; 
	else
	    wynik[dl-1-(dl-odleglosc[akt])/2] = czym_doszlismy[akt];
	akt = poprzedni[akt];
    }
    if(odleglosc[akt] == 1)
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
    znajdz_koncowe(n);
    bfs(n);

    scanf("%d",&d);
    for(int i=0; i<d; i++)
	scanf("%d", &zapytania[i]);
    for(int i=0; i<d-1; i++)
	zapytanie(zapytania[i]-1, zapytania[i+1]-1);
    return 0;
}
