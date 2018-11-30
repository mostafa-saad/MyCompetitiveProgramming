// Alexander Hullmann
// N^2 * 2^N implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;

int best = -1;
int pos[1000];
int scores[1000];
int result[1000][2];
int history[1000][2];
int players_sorted[1000];

void move(int from, int to, int playernr)
{
	if (from > to)
	{
		for (int i = 0; i < N; i++)
			if (pos[i] >= to && pos[i] < from)
				pos[i]++;
		pos[playernr] = to;
	}
	else if (from < to)
	{
		for (int i = 0; i < N; i++)
			if (pos[i] > from && pos[i] <= to)
				pos[i]--;
		pos[playernr] = to;
	}
	
}

int rek(int player, int costs)
{
	if (player == N)
	{
		if (best == -1 || best > costs)
		{
			best = costs;
			for (int i = 0; i < N; i++)
			{
				result[i][0] = history[i][0];
				result[i][1] = history[i][1];
			}
		}
		return 0;
	}
	
	int result = -1;
	
	if (player == 0 || pos[players_sorted[player - 1]] > pos[players_sorted[player]])
	{
		history[player][0] = -1;
		result = rek(player + 1, costs);
	}
	int to;
	
	int from = pos[players_sorted[player]];
	
	if (player)
	{
		to = pos[players_sorted[player - 1]];
		if (from < to) to--;
	}
	else
		to = N - 1;
	
	move(from, to, players_sorted[player]);
	history[player][0] = from; history[player][1] = to;
	int rv = rek(player + 1, costs + to + from + 2) + to + from + 2;
	move(to, from, players_sorted[player]);
	
	if (result == -1 || rv < result)
		result = rv;
	
	return result;
}


int comparescores(const void* a, const void* b)
{
	return (scores[*(int *)a] - scores[*(int *)b]);
}

int main()
{
	FILE* in = fopen("sorting.in", "r");
	fscanf(in, "%d ", &N);
	for (int i = 0; i < N; i++)
	{
		fscanf(in, "%d ", &scores[i]);
		pos[i] = i;
		players_sorted[i] = i;
	}
	fclose(in);
	
	qsort(players_sorted, N, sizeof(int), comparescores);
	
	rek(0, 0);
	
	printf("mincosts: %d\n", best);
	
	int movecount = 0;
	
	for (int i = 0; i < N; i++)
		if (result[i][0] != -1)
			movecount++;
	
	FILE* out = fopen("sorting.out", "w");
	fprintf(out, "%d\n", movecount);
	for (int i = 0; i < N; i++)
		if (result[i][0] != -1)
			fprintf(out, "%d %d\n", result[i][0] + 1, result[i][1] + 1);
	fclose(out);		
	
	return 0;
}

