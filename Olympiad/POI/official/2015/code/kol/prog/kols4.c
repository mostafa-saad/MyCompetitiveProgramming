/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie pamieciochlonne                        *
 *****************************************************************************/

#include "ckollib.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
	int size;
	int capacity;
	int *data;
} vector;

void push(vector *v, int elem) {
	if(v->size == v->capacity) {
		v->capacity *= 2;
		v->data = realloc(v->data, v->capacity * sizeof(int));
	}

	v->data[v->size++] = elem;
}

void pop(vector *v) {
	v->size--;
}

void init(vector *v) {
	v->size = 0;
	v->capacity = 12;
	v->data = malloc(v->capacity * sizeof(int));
}

void swap(int *x, int *y) {
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void sort(vector *l) {
	int n;
	int i, idx;
	int cld;

	n = l->size;

	for(i = 2; i <= n; i++) {
		idx = i;
		while((idx != 1) && (l->data[idx - 1 ] > l->data[idx / 2 - 1])) {
			swap(&l->data[idx-1], &l->data[idx / 2 - 1]);
			idx /= 2;
		}
	}

	for(i = n; i >= 2; i--) {
		swap(&l->data[i - 1], &l->data[1 - 1]);
		idx = 1;
		while(2 * idx <= i - 1) {
			cld = 2 * idx;
			if((2 * idx + 1 <= i - 1) && (l->data[cld - 1] < l->data[2 * idx + 1 - 1])) cld ++;

			if(l->data[idx - 1] >= l->data[cld - 1]) break;

			swap(&l->data[idx - 1], &l->data[cld - 1]);
			idx = cld;
		}
	}
}

int main() {
	vector l;
	int nowa_karta, k1, k2, i;

	init(&l);

	nowa_karta = karta();
	while(nowa_karta != 0) {
		push(&l, nowa_karta);
		nowa_karta = karta();
	}

	sort(&l);

	if(l.data[0] == l.data[l.size - 1]) {
		odpowiedz(l.data[0]);
		return 0;
	}

	k1 = 0;
	while(l.data[k1] == l.data[0]) k1 ++;
	k2 = l.size - 1;
	while(l.data[k2] == l.data[l.size - 1]) k2 --;
	if(k1 + k2 < l.size - 1) {
		odpowiedz(l.data[0]);
		return 0;
	}
	if(k1 + k2 > l.size - 1) {
		odpowiedz(l.data[l.size - 1]);
		return 0;
	}

	while(l.size > 0) {
		if(l.data[l.size - 1] != l.data[l.size - k1]) {
			odpowiedz(l.data[l.size - 1]);
			return 0;
		}
		for(i = 0; i < k1; i++) {
			pop(&l);
		}
	}

	assert(false);
}
