/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Turniej                                        *
 *   Plik:                tur.c                                          *
 *   Autor:               Jakub Pawlewicz                                *
 *************************************************************************/

#include <stdio.h>

#define MAX_NODES	100000
#define MAX_EDGES	1000000

struct neighbours {
	int nr;
	int *list;
};

struct neighbours win[MAX_NODES];
int win_neighbours_arr[MAX_EDGES];
int nodes;

void read_input()
{
	int edges = 0;
	scanf("%d", &nodes);
	int i;
	for (i = 0; i < nodes; i++) {
		struct neighbours *win_i = &win[i];
		scanf("%d", &win_i->nr);
		win_i->list = &win_neighbours_arr[edges];
		int j;
		for (j = 0; j < win_i->nr; j++) {
			int loser;
			scanf("%d", &loser);
			win_i->list[j] = loser - 1;
		}
		edges += win_i->nr;
	}
}

int order[MAX_NODES];

void order_nodes()
{
	int last_lose_with[MAX_NODES];
	int i;
	
	for (i = 0; i < nodes; i++)
		last_lose_with[i] = -1;
	
	order[0] = 0;
	for (i = 1; i < nodes; i++) {
		struct neighbours *n = &win[i];
		int j;
		for (j = 0; j < n->nr; j++)
			last_lose_with[n->list[j]] = i;
		for (j = i - 1; j >= 0 && last_lose_with[order[j]] == i; j--)
			order[j + 1] = order[j];
		order[j + 1] = i;
	}
}

int find_winners_nr()
{
	int winners_nr = 1;
	int last_lose_with[MAX_NODES];
	int i;
	
	for (i = 0; i < nodes; i++)
		last_lose_with[i] = -1;
	
	for (i = 0; winners_nr < nodes && winners_nr > i; i++) {
		int winner = order[i];
		struct neighbours *n = &win[winner];
		int j;
		for (j = 0; j < n->nr; j++)
			last_lose_with[n->list[j]] = winner;
		for (j = nodes - 1;
		     j >= winners_nr && last_lose_with[order[j]] == winner;
		     j--);
		winners_nr = j + 1;
	}
	
	return winners_nr;
}

void solve()
{
	int winner[MAX_NODES];
	
	order_nodes();
	
	int winners_nr = find_winners_nr();

	int i;
	for (i = 0; i < nodes; i++)
		winner[i] = 0;
	for (i = 0; i < winners_nr; i++)
		winner[order[i]] = 1;
	printf("%d", winners_nr);
	for (i = 0; i < nodes; i++)
		if (winner[i])
			printf(" %d", i + 1);
	printf("\n");
}

int main()
{
	read_input();
	solve();
	return 0;
}
