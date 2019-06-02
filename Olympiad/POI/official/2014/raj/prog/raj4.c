/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N  (500 * 1000)
#define PN (1 << 19)

struct node {
    int key;
    struct node* next;
};

struct list {
    struct node *head, *tail;
};

struct list G[N + 1];
int topo[N + 1];
int topor[N + 1];
int indeg[N + 1];

int maxin[N + 1];
int maxout[N + 1];
int result[N + 1];

int max(int a, int b) {
    if(a > b) return a;
    return b;
}

bool empty(struct list* l) {
    return l->head == NULL;
}

void push(struct list* l, int key) {
    struct node* elem;
    elem = malloc(sizeof(struct node));
    elem->key = key;
    elem->next = NULL;
    if(empty(l)) {
        l->head = l->tail = elem;
    } else {
        l->tail->next = elem;
        l->tail = elem;
    }
}

int pop(struct list* l) {
    int retval;
    struct node* to_free;
    retval = l->head->key;
    to_free = l->head;
    l->head = l->head->next;
    free(to_free);
    return retval;
}

void toposort(int n) {
    struct list kol;
    struct node *it;
    int nr,v,i;
    kol.head = kol.tail = NULL;
    for(i=1; i<=n; i++)
        if(indeg[i] == 0) push(&kol, i);

    nr = 0;
    while(!empty(&kol)) {
        v = pop(&kol);

        topo[++nr] = v;
        topor[v] = nr;
        it = G[v].head;
        while(it != NULL) {
            indeg[it->key] --;
            if(indeg[it->key] == 0) push(&kol, it->key);
            it = it->next;
        }
    }
}

int tree[2 * PN];

void _tree_set(int ss, int ee, int s, int e, int x, int v) {
    int m;
    if(ee < s || e < ss) return ;
    if(s <= ss && ee <= e) {
        tree[x] = max(tree[x], v);
        return;
    }
    m = (ss + ee)/2;
    _tree_set(ss, m, s, e, 2*x, v);
    _tree_set(m+1, ee, s, e, 2*x+1, v);
}

void tree_set(int s, int e, int v) {
    _tree_set(1, PN, s, e, 1, v);
}

int tree_get(int x) {
    int ret = 0;
    x += PN - 1;
    while(x) {
        ret = max(ret, tree[x]);
        x/=2;
    }
    return ret;
}

int main() {
    int n, m, i, pmax, smax, a, b, v, u, me;
    struct node *it;
    scanf("%d %d", &n, &m);

    for(i=1; i<=m; i++) {
        scanf("%d %d", &a, &b);
        push(&G[a], b);
        indeg[b] ++;
    }

    toposort(n);

    for(i=1; i<=n; i++) {
        v = topo[i];
        it = G[v].head;
        while(it != NULL) {
            maxin[it->key] = max(maxin[it->key], maxin[v] + 1);
            it = it->next;
        }
    }

    for(i=n; i>=1; i--) {
        v = topo[i];
        it = G[v].head;
        while(it != NULL) {
            maxout[v] = max(maxout[v], maxout[it->key] + 1);
            it = it->next;
        }
    }

    for(v=1; v<=n; v++) {
        it = G[v].head;
        while(it != NULL) {
            u = it->key;
            if(topor[u] > topor[v] + 1)
                tree_set(topor[v] + 1, topor[u] - 1, maxin[v] + 1 + maxout[u]);
            it = it->next;
        }
    }

    for(i=1; i<=n; i++) {
        result[i] = tree_get(topor[i]);
    }

    pmax = 0;
    for(i=2; i<=n; i++) {
        result[topo[i]] = max(pmax = max(pmax, maxin[topo[i-1]]), result[topo[i]]);
    }

    smax = 0;
    for(i=n-1; i>=1; i--) {
        result[topo[i]] = max(smax = max(smax, maxout[topo[i+1]]), result[topo[i]]);
    }

    me = 1;

    for(i=2; i<=n; i++)
        if(result[i] < result[me])
            me = i;

    printf("%d %d\n", me, result[me]);
    return 0;
}
