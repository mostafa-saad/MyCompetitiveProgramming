#include <stdio.h>
#include <stdlib.h>

#if 1
#define ASSERT(_x) do { if (!(_x)) { fprintf(stderr, "Assertion failure at line %d\n", __LINE__); exit(99); } } while (0)
#else
#define ASSERT(_x) do { } while (0)
#endif

#undef DEBUGGING
#ifdef DEBUGGING
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...) do { } while (0)
#endif

#define MAXN 100000
#define MAXM 6000000

#define MAXNN (MAXN+10)
#define MAXMM 2*(MAXM+10)

int N, M;

// Component DFU

int cparent[MAXNN];
char crank[MAXNN];

static inline int cfind(int x)
{
	while (cparent[x])
		x = cparent[x];
	return x;
}

static inline void cunion(int r, int s)
{
	if (crank[r] < crank[s])
		cparent[r] = s;
	else if (crank[r] > crank[s])
		cparent[s] = r;
	else {
		cparent[s] = r;
		crank[r]++;
	}
}

// Block DFU

int bparent[MAXNN];
char brank[MAXNN];

static inline int bfind(int x)
{
	while (bparent[x])
		x = bparent[x];
	return x;
}

static inline int bunion(int r, int s)
{
	if (brank[r] < brank[s]) {
		bparent[r] = s;
		return s;
	} else if (brank[r] > brank[s]) {
		bparent[s] = r;
		return r;
	} else {
		bparent[s] = r;
		brank[r]++;
		return r;
	}
}

// Block tree

int tfirst[MAXNN];	// Valid only for DFU roots of blocks
int tseen[MAXNN], tqueue[MAXNN], tparent[MAXNN];
int tgen;

struct edge {
	int next;
	int dest;
};

struct edge tedges[2*MAXNN];
int ne = 2;

static inline void traw_add_edge(int x, int y)
{
	tedges[ne].next = tfirst[x];
	tedges[ne].dest = y;
	tfirst[x] = ne++;
}

static inline void tadd_edge(int bx, int by, int x, int y)
{
	traw_add_edge(bx, y);
	traw_add_edge(by, x);
}

void tbfs(int bx, int by)
{
	int r = 0, w = 1;
	tgen++;
	tseen[bx] = tgen;
	tparent[bx] = 0;
	tqueue[0] = bx;
	while (r < w) {
		bx = tqueue[r++];
		DEBUG("BFS: %d (%d)\n", bx, tseen[bx]);
		if (bx == by)
			return;
		for (int e=tfirst[bx]; e; e=tedges[e].next) {
			int by = bfind(tedges[e].dest);
			if (tseen[by] != tgen) {
				tseen[by] = tgen;
				tparent[by] = bx;
				tqueue[w++] = by;
			}
		}
	}
	ASSERT(0);
}

void tcontract(int bx, int by)
{
	int e, z;

	DEBUG("\tBFS\n");
	tbfs(bx, by);

	DEBUG("\tContracting\n");
	int y = by;
	while (tseen[y] == tgen && (z = tparent[y])) {
		int by = bfind(y);
		int bz = bfind(z);
		DEBUG("\tJoining %d with %d (blocks %d and %d)\n", y, z, by, bz);
		ASSERT(by != bz);
		int br = bunion(by, bz);
		int head = 0;
		for (e = tfirst[by]; e;) {
			int ne = tedges[e].next;
			int be = bfind(tedges[e].dest);
			if (be != by && be != bz) {
				tedges[e].next = head;
				head = e;
			}
			e = ne;
		}
		for (e = tfirst[bz]; e;) {
			int ne = tedges[e].next;
			int be = bfind(tedges[e].dest);
			if (be != by && be != bz) {
				tedges[e].next = head;
				head = e;
			}
			e = ne;
		}
		tfirst[br] = head;
		y = z;
	}
#ifdef DEBUGGING
	by = bfind(y);
	DEBUG("\tNeighbors of %d (block %d):", y, by);
	for (int e = tfirst[by]; e; e = tedges[e].next)
		DEBUG(" %d", tedges[e].dest);
	DEBUG("\n");
#endif
}

// Main logic

void add_edge(int x, int y)
{
	DEBUG("Edge <%d,%d>\n", x, y);
	int bx = bfind(x), by = bfind(y);
	if (bx == by) {
		DEBUG("\tSame block\n");
		return;
	}

	int cx = cfind(x), cy = cfind(y);
	if (cx != cy) {
		DEBUG("\tDifferent components\n");
		cunion(cx, cy);
		tadd_edge(bx, by, x, y);
		return;
	}

	DEBUG("\tContracting blocks\n");
	tcontract(bx, by);
}

void show(void)
{
	for (int i=1; i<=N; i++)
		if (!bparent[i]) {
			for (int e = tfirst[i]; e; e = tedges[e].next) {
				int x = tedges[e].dest;
				int y = tedges[e^1].dest;
				if (x < y)
					printf("%d %d\n", x, y);
			}
		}
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
		add_edge(x, y);

		c = getchar();
		ASSERT(c == '\n');
	}

	ASSERT(getchar() < 0);
}

int main(void)
{
	chew();
	show();
	return 0;
}
