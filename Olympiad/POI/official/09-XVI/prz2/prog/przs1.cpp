/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs1.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Dziala jak wzorcowe, ale dla    *
 *             kazdego zapytania wykonuje BFSa.                          *
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
}

int wyjmij()
{
    return kolejka[poczatek_kolejki++];
}

int czy_pusta()
{
    return koniec_kolejki == poczatek_kolejki;
}

int stworz_indeks(int w1, int w2, char znak)
{
    return w1*MAXN*(ROZMIAR_ALF+1) + w2*(ROZMIAR_ALF+1) + int(znak-'a');    
}



int odleglosc[ROZM_G], poprzedni[ROZM_G];
char czym_doszlismy[ROZM_G], czy_koncowy[ROZM_G];

wierzcholek graf[MAXN], graf_trans[MAXN][ROZMIAR_ALF+1];

void wczytaj_graf(int n, int m)
{
    char zn;
    int a, b;

    for(int k=0; k<ROZMIAR_ALF+1; k++)
    for(int i=0; i<n; i++)
	graf_trans[i][k].lista_krawedzi = NULL;
    for(int i=0; i<n; i++)
	graf[i].lista_krawedzi = NULL;

    for(int i=0; i<m; i++)
    {
	scanf("%d%d %c", &a, &b, &zn);
	a --; b --;
	dodaj(&graf[a], b, zn);
	dodaj(&graf_trans[b][(int)zn-'a'], a, zn);
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
		if(i == j)
		    czy_koncowy[ind] = 1;
		else
		    czy_koncowy[ind] = 0;
	    }
}
    
void odtworz_wynik(int poczatek, int n)
{
    int akt, dl, ind, najblizszy, min_odleglosc;
    char wynik[MAXN*MAXN+1];

    min_odleglosc = INF;
    najblizszy = -1;
    for(int i=0; i<n; i++)
	for(int k=0; k<ROZMIAR_ALF+1; k++)
	{
	    ind = stworz_indeks(i, i, k+'a');
	    if(odleglosc[ind] < min_odleglosc)
	    {
		min_odleglosc = odleglosc[ind];
		najblizszy = ind;
	    }
	}


    akt = najblizszy;
    if(min_odleglosc == INF)
    {
	printf("-1\n");
	return;
    }
    
    dl = odleglosc[akt];
    printf("%d ", dl);

    while(poprzedni[akt] != -1)
    {
	if(odleglosc[akt] % 2)
	    wynik[odleglosc[akt]/2] = czym_doszlismy[akt]; 
	else
	    wynik[dl-odleglosc[akt]/2] = czym_doszlismy[akt];
	akt = poprzedni[akt];
    }
    wynik[dl] = '\0';
    printf("%s\n", wynik);
}

void bfs(int n, int p, int k)
{
    int akt, poczatek, w1, w2, lit, dokad, znalazlem;

    czysc();   
    for(int l=0; l<ROZMIAR_ALF+1; l++)
    for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	{
	    akt = stworz_indeks(i, j, l+'a');
	    odleglosc[akt] = INF;
	}
    
    poczatek = stworz_indeks(p, k, ZNAK_HASH);
    odleglosc[poczatek] = 0;
    poprzedni[poczatek] = -1;
    wstaw(poczatek);

    znalazlem = 0;
    while(!czy_pusta() && !znalazlem)
    {
	akt = wyjmij();
	w1 = akt / ((ROZMIAR_ALF+1)*MAXN);
	w2 = (akt / (ROZMIAR_ALF+1)) % MAXN;
	lit = akt % (ROZMIAR_ALF+1);

	if(lit == ROZMIAR_ALF)
	{
	    for(wezel* ptr=graf[w1].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    {
		dokad = stworz_indeks(ptr->dokad, w2, ptr->znak);
		if(odleglosc[dokad] > odleglosc[akt] + 1)
		{
		    odleglosc[dokad] = odleglosc[akt] + 1;
		    poprzedni[dokad] = akt;
		    czym_doszlismy[dokad] = ptr->znak;
		    if(czy_koncowy[dokad])
		    {
			znalazlem = 1;
			break;
		    }
		    wstaw(dokad);
		}
	    }
	}
	else
	{
	    for(wezel* ptr=graf_trans[w2][lit].lista_krawedzi; ptr != NULL; ptr = ptr->nastepny)
	    {
		dokad = stworz_indeks(w1, ptr->dokad, ZNAK_HASH);
		if(odleglosc[dokad] > odleglosc[akt] + 1)
		{
		    odleglosc[dokad] = odleglosc[akt] + 1;
		    poprzedni[dokad] = akt;
		    czym_doszlismy[dokad] = ptr->znak;
		    if(czy_koncowy[dokad])
		    {
			znalazlem = 1;
			break;
		    }
		    wstaw(dokad);
		}
	    }
	}
    }
    odtworz_wynik(poczatek, n);
}



int main()
{
    int n, m, d;
    int zapytania[MAXD];
    scanf("%d%d",&n,&m);
    wczytaj_graf(n, m);
    znajdz_koncowe(n);
    scanf("%d",&d);
    for(int i=0; i<d; i++)
	scanf("%d", &zapytania[i]);
    for(int i=0; i<d-1; i++)
	bfs(n, zapytania[i]-1, zapytania[i+1]-1);
    return 0;
}
