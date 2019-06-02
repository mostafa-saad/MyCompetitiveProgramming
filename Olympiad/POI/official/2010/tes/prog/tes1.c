/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tes1.c                                           *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie wzorcowe.                            *
 *   Złożoność czasowa: O(m + l + |A|)                                   *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAX_M 1000000 // maksymalna długość ciągu a_i
#define MAX_A 1000000 // maksymalny wyraz ciągu

// implementacja listy jednokierunkowej

struct element { // elementy listy
    int val; // wartość przechowywana w weźle listy
    struct element *nex; // wskaźniki na następnika
};

struct list {
    struct element *begin, *end; // wskaźniki na początkowy i końcowy element listy
};

int m, n, k, a[MAX_M], w;
struct list b[MAX_M], nr[MAX_A], tmp;

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
    ele->nex = NULL;
    ele->val = _val;
    if(l->end != NULL)
        l->end->nex = ele;
    if(l->begin == NULL)
        l->begin = ele;
    l->end = ele;
    return ele;
}

/* Usuwa element z początku listy */
void list_pop_front(struct list *l) {
    struct element *ele = l->begin;
    if(l->end == ele)
        l->end = NULL;
    l->begin = l->begin->nex;
    free(ele);
}

/* Kasuje zawartość listy */
void list_clear(struct list *l) {
    struct element *il = l->begin;
    while(il != NULL) {
        il = il->nex;
        list_pop_front(l);
    }
}

/* Zamiana dwóch list */
void list_swap(struct list *l1, struct list *l2) {
    struct list l3;
    l3.begin = l1->begin;
    l3.end = l1->end;
    l1->begin = l2->begin;
    l1->end = l2->end;
    l2->begin = l3.begin;
    l2->end = l3.end;
}

int main()
{
    int i, j;

    for(i = 0; i < MAX_A; ++i)
        list_init(&nr[i]);

    // wczytanie ciągu a_i
    scanf("%d", &m);
    for(i = 0; i < m; ++i)
        scanf("%d", &a[i]);

    // wczytanie wszystkich zapytań
    scanf("%d", &n);
    for(i = 0; i < n; ++i) {
        scanf("%d", &k);
        list_init(&b[i]);
        for(j = 0; j < k; ++j) {
            scanf("%d", &w);
            list_push_back(&b[i], w);
        }
        list_push_back(&nr[b[i].begin->val - 1], i);
    }

    list_init(&tmp);
    for(i = 0; i < m; ++i) {
        list_clear(&tmp);
        list_swap(&tmp, &nr[a[i] - 1]);
        while(!list_empty(&tmp)) {
            list_pop_front(&b[tmp.begin->val]);
            if(!list_empty(&b[tmp.begin->val]))
                list_push_back(&nr[b[tmp.begin->val].begin->val - 1],
                    tmp.begin->val);
            list_pop_front(&tmp);
        }
    }

    for(i = 0; i < n; ++i) {
        if(list_empty(&b[i]))
            printf("TAK\n");
        else {
            printf("NIE\n");
            list_clear(&nr[b[i].begin->val - 1]);
            list_clear(&b[i]);
        }
    }

    return 0;
}

