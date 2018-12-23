#include <stdio.h>
#include <stdlib.h>

#if 0
#define ASSERT(_x) do { if (!(_x)) { fprintf(stderr, "Assertion failure at line %d\n", __LINE__); exit(99); } } while (0)
#else
#define ASSERT(_x) do { } while (0)
#endif

#define MAXN 100000
#define MAXM 600000

#define MAXNN (MAXN+10)
#define MAXMM 2*(MAXM+10)

int N, M;

int first[MAXNN];

struct edge {
	int next;
	int dest;	// -1 if the edge was already used
};

struct edge edges[MAXMM];
int ne = 2;

void raw_add_edge(int x, int y)
{
	edges[ne].next = first[x];
	edges[ne].dest = y;
	first[x] = ne++;
}

void add_edge(int x, int y)
{
	raw_add_edge(x, y);
	raw_add_edge(y, x);
}

void chew(void)
{
	int cc = scanf("%d%d", &N, &M);
	ASSERT(cc == 2);
	ASSERT(N >= 1 && N <= MAXN);
	ASSERT(M >= 1 && M <= MAXM);

	int c = getchar();
	ASSERT(c == '\n');

	for (int i=0; i<M; i++) {
		int x, y;
		cc = scanf("%d%d", &x, &y);
		ASSERT(cc == 2);
		ASSERT(x >= 1 && x <= N && y >= 1 && y <= N);
		ASSERT(x != y);
		if (i < MAXM)
			add_edge(x, y);

		c = getchar();
		ASSERT(c == '\n');
	}

	ASSERT(getchar() < 0);
}

int enter[MAXNN];
int clock;

int dfs(int x)
{
	ASSERT(x >= 1 && x <= N);
	clock++;
	enter[x] = clock;
	int low = clock;
	for (int e=first[x]; e; e=edges[e].next) {
		int y = edges[e].dest;
		if (y >= 0) {
			int low2;
			if (enter[y])
				low2 = enter[y];
			else {
				edges[e^1].dest = -1;
				low2 = dfs(y);
				if (low2 < 0) {
					low2 = -low2;
					printf("%d %d\n", x, y);
				}
			}
			if (low2 < low)
				low = low2;
		}
	}
	return (low >= enter[x]) ? -low : low;
}

int main(void)
{
	chew();
	for (int i=1; i<=N; i++)
		if (!enter[i])
			dfs(i);
	return 0;
}
