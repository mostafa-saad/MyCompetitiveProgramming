/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Opis:                 Biblioteka interaktywna                       *
 *                                                                       *
 *************************************************************************/

#include "cgdzlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_WORD_IN   "#o[st4D0nwypbl^."
#define MAGIC_WORD_OUT  "3r2v1rc;iz@5LW()"

static int initialized = 0;
static int n, p[500001];
static int g_called;

#define INITIALIZED 0x3cd1
#define G_CALLED_0 0x6cdd
#define G_CALLED_1 0x5eec

static void quit(int err_code) {
    printf("%s %d\n", MAGIC_WORD_OUT, err_code);
    exit(0);
}

#define MAGIC_SHIFT(i) (((i) + 47337) % n)

int inicjuj() {
    char magic_word[20];
    int i, ret;
    if (initialized != 0) quit(3);

    magic_word[0] = 0;
    if (NULL == fgets(magic_word, 20, stdin)) quit(5);
    if (strcmp(magic_word, MAGIC_WORD_IN"\n") != 0) quit(5);

    ret = scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        ret = scanf("%d", &p[MAGIC_SHIFT(i)]);
    }
    ret = ret;
    initialized = INITIALIZED;
    g_called = G_CALLED_0;

    return n;
}

int f(int i, int j, int d) {
    if (initialized != INITIALIZED) quit(3);
    if (i < 1 || i > n || j < 1 || j > n || d <= 0) quit(4);

    return (((p[MAGIC_SHIFT(i)] - p[MAGIC_SHIFT(j)]) % d) == 0);
}

int g(int i, int j) {
    if (initialized != INITIALIZED) quit(3);
    if (i < 1 || i > n || j < 1 || j > n) quit(4);

    if (g_called != G_CALLED_0 || n == 1)
        quit(2);
    g_called = G_CALLED_1;
    return (p[MAGIC_SHIFT(i)] > p[MAGIC_SHIFT(j)]);
}

void odpowiedz(int k) {
    if (initialized != INITIALIZED) quit(3);
    if (k < 1 || k > n) quit(4);

    if (p[MAGIC_SHIFT(k)] != 1 || (n > 1 && g_called != G_CALLED_1))
        quit(1);
    else
        quit(0);
}
