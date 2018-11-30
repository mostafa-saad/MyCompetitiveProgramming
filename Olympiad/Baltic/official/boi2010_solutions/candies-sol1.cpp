/*
 * Task: Candies
 *  Model soltuion, runs in O(n^2 log n B)
 * Author: Jakub Lacki
 */

#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(i,n) for (int i=0; i<(n); i++)
#define FORD(i, a, b) for (int i=(a); i>=(b); i--)
#define FOR(i, a, b) for (int i=(a); i<=(b); i++)
#define MAXN 100
#define MAXB 7000

int count(char* t, int size)
{
    int ret = 0;
    REP(i, size+1)
	ret += (t[i] != 0);
    return ret;
}

int best, to_remove;

void generate(int* boxes, int n, char* orders, int size)
{
    if(n == 1)
    {
	int cur = count(orders, size);
	if(cur > best || (cur == best && to_remove > boxes[0]))
	{
	    best = cur;
	    to_remove = boxes[0];
	}
	return;
    }

    char ord[MAXN*MAXB+1];
    pair<int, int> zk[2];
    zk[0] = make_pair(0, n/2-1);
    zk[1] = make_pair(n/2, n-1);

    REP(k, 2)
    {
	REP(i, MAXN*MAXB+1)
	    ord[i] = 0;
	REP(i, size+1)
	    ord[i] = orders[i];

	int cursize = size;

	FOR(i, zk[k].first, zk[k].second)
	{
	    cursize += boxes[i];
	    FORD(j, cursize, boxes[i])
		ord[j] |= ord[j-boxes[i]];
	}
	generate(boxes + zk[k^1].first, zk[k^1].second - zk[k^1].first + 1, ord, cursize);
    }
}


int remove(int* boxes, int n)
{
    best = -1;
    to_remove = -1;
    char orders[MAXN*MAXB+1];
    orders[0] = 1;
    generate(boxes, n, orders, 1);

    return to_remove;
}

int add(int* boxes, int n)
{
    char orders[MAXN*MAXB*2+10];
    int limit = MAXB*n+3;
    int shift = limit;


    REP(i, 2*limit+1)
	orders[i] = 0;

    orders[0+shift] = 1;

    REP(i, n)
    {
	FORD(j, limit, boxes[i]-limit)
	    orders[j+shift] |= orders[j-boxes[i]+shift];
	FOR(j, -limit, limit-boxes[i])
	    orders[j+shift] |= orders[j+boxes[i]+shift];
    }

    FOR(i, 0, limit)
    {
	if(orders[i+shift] == 0)
	    return i;
    }
    return -1;
}

int main()
{
    int n, boxes[MAXN];

    scanf("%d", &n);

    REP(i, n)
	scanf("%d", &boxes[i]);

    int r = remove(boxes, n);
    REP(i, n)
    {
	if(boxes[i] == r)
	{
	    boxes[i] = boxes[n-1];
	    n --;
	    break;
	}
    }

    int a = add(boxes, n);
    printf("%d %d\n", r, a);
    return 0;
}

