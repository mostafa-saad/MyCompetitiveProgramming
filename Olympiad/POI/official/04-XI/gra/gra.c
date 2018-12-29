/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Gra                                            *
 *   Plik:                gra.c                                          *
 *   Autor:               Jakub Pawlewicz                                *
 *************************************************************************/

#include <stdio.h>

#define MAX_N	1000000

struct group {
	int number;
	int size;
};

int groups_nr = 0; /* Liczba grup. */
/* W tablicy group pamiêtamy numery i rozmiary kolejnych grup w kolejno¶ci
   malej±cych numerów. Pamiêtamy tylko niepuste grupy. */
struct group group[MAX_N];
int nim_sum = 0;

int m, n;

int group_is_odd(struct group g)
{
	return g.number & 1;
}

int winning_moves()
{
	int retval = 0;
	int i;
	for (i = 0; i < groups_nr; i++) {
		if (group_is_odd(group[i])) {
			/* Je¶li grupa jest nieparzysta, to sprawdzamy,
			   czy mo¿emy zdj±æ odpowiedni± liczbê, aby
			   wyzerowaæ nim-sumê. */
			if ((group[i].size ^ nim_sum) < group[i].size)
				retval++;
		} else if (group[i].number != 2) {
			/* Je¶li grupa jest parzysta i nie jest to grupa 2,
			   to sprawdzamy, czy mo¿emy powiêkszyæ tak nastêpn±
			   grupê, która jest nieparzysta, aby wyzerowaæ
			   nim-sumê. */
			int next_group_size;
			int pieces_to_next_group;
			if (i + 1 == groups_nr ||
			    group[i+1].number < group[i].number - 1)
				next_group_size = 0;
			else
				next_group_size = group[i+1].size;
			pieces_to_next_group = (next_group_size ^ nim_sum) -
				next_group_size;
			if (pieces_to_next_group > 0 &&
			    pieces_to_next_group <= group[i].size)
				retval++;
		}
	}
	return retval;
}

void solve()
{
	int pieces_left;
	int next_piece;
	int group_size;
	
	scanf("%d%d", &m, &n);
	
	/* Wczytanie numerów i rozmiarów grup */
	
	pieces_left = n;
	scanf("%d", &next_piece);
	
	do {
		int last_group_piece = next_piece;
		group_size = 0;
		for (;;) {
			group_size++;
			pieces_left--;
			if (!pieces_left)
				break;
			scanf("%d", &next_piece);
			if (next_piece > last_group_piece + 1)
				break;
			last_group_piece = next_piece;
		}
		group[groups_nr].number = m - last_group_piece - pieces_left;
		group[groups_nr].size = group_size;
		if (group_is_odd(group[groups_nr]))
			nim_sum ^= group_size;
		groups_nr++;
	} while (pieces_left);
	
	if (next_piece == m - 1)
		/* Przypadek szczególny - grupa 1 jest niepusta */
		printf("%d\n", group_size);
	else if (!nim_sum)
		/* Przegrana */
		printf("0\n");
	else
		/* Wygrana */
		printf("%d\n", winning_moves());
}

int main()
{
	solve();
	return 0;
}
