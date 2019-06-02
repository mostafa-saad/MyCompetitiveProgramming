/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n * (n/k))                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie powolne, szukanie brutalne        *
 *                         podciagu o sumie 0                            *
 *                                                                       *
 *************************************************************************/

#include<iostream>
using namespace std;

const int MAXN = 1000000;

struct list {
    int poz;
    int war;
    list *next;
    list(int _poz, int _war, list *_next) {
        poz = _poz;
        war = _war;
        next = _next;
    }
};

list *ciag = NULL;

string C;

int wynik[MAXN];
int w;

int n, k;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    cin >> C;
    for(int i=n; i>=1; --i)
    {
        int war;
        if(C[i-1] == 'b') war = 1;
        else war = -k;
        ciag = new list(i, war, ciag);
    }

    for(int j=0; j<n/(k+1); ++j)
    {
        int sum = 0;
        list *front = ciag;
        for(int i=0; i<k+1; ++i)
        {
            sum += front->war;
            front = front->next;
        }
        list *back = ciag, *prev = NULL;
        while(sum != 0)
        {
            prev = back;
            sum -= back->war;
            back = back->next;
            sum += front->war;
            front = front->next;
        }
        while(back != front)
        {
            wynik[w++] = back->poz;
            if(prev == NULL) ciag = back->next;
            else prev->next = back->next;
            delete back;
            if(prev == NULL) back = ciag;
            else back = prev->next;
        }
    }
    for(int i=n; i>0; i-=(k+1))
    {
        for(int j=i-(k+1); j<i; ++j)
            cout << wynik[j] << ' ';
        cout << '\n';
    }
    return 0;
}

