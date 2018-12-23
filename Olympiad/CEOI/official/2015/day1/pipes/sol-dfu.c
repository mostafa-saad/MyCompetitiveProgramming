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

int tparent[MAXNN];
int torig[MAXNN][2];
int tmark[MAXNN];
int tgen;

void tadd_edge(int bx, int by, int x, int y)
{
	// "x" is in the smaller component
	// reverse path from "x" to the component's root
	int newp = by;
	int newo1 = x, newo2 = y;
	DEBUG("\tWill reverse path from %d and connect to %d\n", bx, by);
	int obx = bx;
	for (;;) {
		int next = tparent[bx];
		int norig1 = torig[bx][0], norig2 = torig[bx][1];
		tparent[bx] = newp;
		torig[bx][0] = newo1, torig[bx][1] = newo2;
		if (!next)
			break;
		newp = bx;
		newo1 = norig1, newo2 = norig2;
		bx = bfind(next);
	}

#ifdef DEBUGGING
	DEBUG("\tNew path:");
	for (bx=obx; bx; bx = tparent[bx]) {
		bx = bfind(bx);
		DEBUG(" %d", bx);
	}
	DEBUG("\n");
#endif
}

void tcontract2(int bx, int lca)
{
	DEBUG("\tContracting from %d to %d\n", bx, lca);
	while ((bx = bfind(bx)) != (lca = bfind(lca))) {
		int bp = bfind(tparent[bx]);
		DEBUG("\t\tJoining %d with %d\n", bx, bp);
		int bn = bunion(bx, bp);
		tparent[bn] = tparent[bp];
		torig[bn][0] = torig[bp][0];
		torig[bn][1] = torig[bp][1];
		bx = bn;
	}
}

void tcontract(int bx, int by)
{
	// Find LCA
	int px = bx, py = by;
	int lca;
	tgen += 2;
	for (;;) {
		if (tmark[px] == tgen+1) {
			lca = px;
			break;
		}
		tmark[px] = tgen;
		if (tparent[px])
			px = bfind(tparent[px]);
		if (tmark[py] == tgen) {
			lca = py;
			break;
		}
		tmark[py] = tgen+1;
		if (tparent[py])
			py = bfind(tparent[py]);
	}
	DEBUG("\tLCA=%d\n", lca);

	tcontract2(bx, lca);
	tcontract2(by, lca);
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
		if (crank[cx] <= crank[cy])
			tadd_edge(bx, by, x, y);
		else
			tadd_edge(by, bx, y, x);
		cunion(cx, cy);
		return;
	}

	DEBUG("\tContracting blocks\n");
	tcontract(bx, by);
}

void show(void)
{
	for (int i=1; i<=N; i++)
		if (!bparent[i] && tparent[i]) {
			printf("%d %d\n", torig[i][0], torig[i][1]);
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
