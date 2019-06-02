/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcs2.c                                                    *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo.                          *}
{*            Wyszukuje w czasie liniowym pierwsza niemotonicznosc.      *}
{*            Zlozonosc obliczeniowa: O(n * k)                           *}
{*                                                                       *}
{*************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#include "carclib.h"

#define MAX_K 1000000 // maksymalna dlugosc szukanego podciagu

struct element { // elementy listy
    int val; // wartosc przechowywana w wezle listy
    struct element *nex, *pre; // wskazniki na poprzednika i nastepnika
};

struct list {
    struct element *begin, *end; // wskazniki na poczatkowy i koncowy element listy
};

int k;
struct list sub; // lista reprezentujaca szukany podciag

/* Inicjuje liste */
void list_init(struct list *l) {
    l->begin = NULL;
    l->end = NULL;
}

/* Sprawdza czy lista jest pusta */
int list_empty(struct list *l) {
    return l->begin == NULL;
}

/* Dodaje [_val] na koniec listy */
struct element* list_push_back(struct list *l, int _val) {
    struct element *ele = (struct element*)malloc(sizeof(struct element));
    ele->pre = l->end;
    ele->nex = NULL;
    ele->val = _val;
    if(l->end != NULL)
        l->end->nex = ele;
    if(l->begin == NULL)
        l->begin = ele;
    l->end = ele;
    return ele;
}

/* Usuwa element z listy na ktory wskazuje wskaznik [ele] */
void list_erase(struct list *l, struct element *ele) {
    if(ele->pre != NULL)
        ele->pre->nex = ele->nex;
    if(ele->nex != NULL)
        ele->nex->pre = ele->pre;
    if(l->begin == ele)
        l->begin = ele->nex;
    if(l->end == ele)
        l->end = ele->pre;
    free(ele);
}

/* Wypisuje liste od poczatku do konca i zarazem zwalnia zadeklarowana na jej 
 * elementy pamiec */
void list_print(struct list *l) {
    struct element *il = l->begin, *tmp;
    int a;
    while(il != NULL) {
        a = il->val;
        tmp = il->nex;
        list_erase(l, il);
        il = tmp;
        wypisz(a);
    }
}

int main()
{
    int i, a;
    struct element *cen;
    k = inicjuj();
    list_init(&sub);
    for(i = 0; i < k; ++i)
        list_push_back(&sub, 0);
    while((a = wczytaj()) != 0) {
        list_push_back(&sub, a);
        cen = sub.begin;
        while(cen->nex != NULL) {
            if(cen->val < cen->nex->val)
                break;
            cen = cen->nex;
        }
        list_erase(&sub, cen);
    }
    list_print(&sub);
    return 0;
}
