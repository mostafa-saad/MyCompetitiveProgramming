/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRO (Profesor Szu)                             *
 *   Plik:                pro.cpp                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define N 1000001        /* Liczba domkow */
#define M 1000000        /* Liczba sciezek */
#define INF 36501

/* Reprezentacja grafu: tablica list sasiedztwa
   zaszyta w tablicy edge. Tablica firstEdge wskazuje
   na poczatek listy dla danego wierzcholka.

   Przechowujemy graf odwrocony wzgledem wejsciowego.

   Gmachowi przypisujemy numer 0 zamiast n+1
 */
typedef struct TEdge
{
    int v;    //wierzcholek dodelowy
    int next;    //indeks nastepnego elementu listy lub -1
};

TEdge edge[M];                                //8MB
int firstEdge[N];                            //4MB
int n,m;        //liczba wierzcholkow, krawedzi
char reachable[N];    //czy wierzcholek jest osiagalny z 0        //1MB
int inDeg[N];        //stopnie wejsciowe wierzcholkow        //4MB
int result[N];        //wynik obliczen dla kazdego wierzcholka    //4MB

/**
 Wczytanie danych.
 */
void input()
{
    int i, v, w;

    scanf("%d %d", &n, &m);

    //inicjalizacja struktur danych
    for(i = 0; i <= n; i++)
    firstEdge[i] = -1,
    reachable[i] = 0,
    inDeg[i] = 0,
    result[i] = 0;

    for(i = 0; i < m; i++)
    {
    scanf("%d %d", &v, &w);
    if (v == n+1) v = 0;
    if (w == n+1) w = 0;

    //zapamietujemy krawedz odwrotna
    edge[i].v = v;
    edge[i].next = firstEdge[w];
    firstEdge[w] = i;
    }
}

/**
 BFS z wierzcholka 0 (gmachu) w celu znalezienia
 wierzcholkow osiagalnych.
 */
void findReachable()
{
    int q[N], qs, qe;        //obsluga kolejki
    int v, w, pos;

    reachable[0] = 1;
    q[0] = 0;
    qs = 0, qe = 1;

    while (qs < qe)
    {
    v = q[qs++];
    pos = firstEdge[v];
    while (pos != -1)
    {
        w = edge[pos].v;
        if (!reachable[w])
        {
        q[qe++] = w;
        reachable[w] = 1;
        }
        pos = edge[pos].next;
    }
    }
}

/**
 Oblicza stopnie wejsciowe wierzcholkow
 w zredukowanym grafie.
 */
void computeInDeg()
{
    int i, pos;

    for(i = 0; i <= n; i++)
    if (reachable[i])
    {
        pos = firstEdge[i];
        while (pos != -1)
        {
        inDeg[ edge[pos].v ]++;
        pos = edge[pos].next;
        }
    }
}

/**
 Dodaje do wyniki w wierzcholku v wynik wierzcholka w
 */
void addResult(int v, int w)
{
    if (result[w] == INF)
    result[v] = INF;
    else
    {
    result[v] = result[v] + result[w];
    if (result[v] >= INF)
        result[v] = INF;
    }
}

/**
 Przeglada po kolei wierzcholki o stopniu
 wejsciowym 0, oblicza dla nich wynik
 i zmniejsza stopnie wejsciowe ich sasiadom.
 Wierzcholki o stopniu 0 sa przechowywane w kolejce.

 W tablicy result sa obliczone wyniki dla wierzcholkow
 osiagalnych: INF oznacza 'zawsze', inna liczba - wynik.
 */
void computeResult()
{
    int q[N], qe, qs;        //kolejka wierzcholkow stopnia 0
    int v, w, pos, i;

    //sprawdzamy czy gmach jest stopnia zero,
    //jesli nie to dla wszystkich osiagalnych jest INF
    if (inDeg[0] != 0)
    {
    for(i = 0; i <= n; i++)
        result[i] = INF;
        return;
    }

    q[0] = 0;
    qs = 0, qe = 1;
    result[0] = 1;

    //bierzemy kolejne wierzcholki ktorych inDeg spadl do 0
    while (qs < qe)
    {
    v = q[qs++];

    pos = firstEdge[v];

    //uaktualniamy wartosci w nastepnikach
    while (pos != -1)
    {
        w = edge[pos].v;
        //interesuja nas tylko osiagalne
        if (reachable[w])
        {
        addResult(w, v);
        inDeg[w]--;
        //stopien w spadl do 0, przenosimy go do kolejki
        if (inDeg[w] == 0)
            q[qe++] = w;
        }
        pos = edge[pos].next;
    }
    }

    //wszystkim wierzcholkom ktorych stopnie wejsciowe
    //nie spadly do zera zaznacz INF
    for(i = 0; i <= n; i++)
    if (inDeg[i] != 0)
        result[i] = INF;
}


/**
 Znajdz maksimum (rozpatrujemy tylko wierzcholki osiagalne)
 i wypisz wynik
 */
void print()
{
    int i, maxFound, maxCount;

    maxFound = 0;
    maxCount = 0;

    //znajdz max
    for(i = 1; i <= n; i++)
    if (reachable[i])
        if (result[i] > maxFound)
        maxFound = result[i];

    //znajdz liczbe maksow
    for(i = 1; i <= n; i++)
    if (reachable[i] && result[i] == maxFound)
        maxCount++;

    //wypisz
    if (maxFound == INF)
    printf("zawsze\n");
    else printf("%d\n", maxFound);

    printf("%d\n", maxCount);

    for(i = 1; i <= n; i++)
    if (reachable[i] && result[i] == maxFound)
        printf("%d ", i);
    printf("\n");
}

/**
 Program glowny
 */
int main()
{
    input();
    findReachable();
    computeInDeg();
    computeResult();
    print();

    return 0;
}
