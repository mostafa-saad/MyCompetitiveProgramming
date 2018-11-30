/*
 * Task: Candies
 *  Alternate (randomized) solution
 *  Computes array orders modulo a big prime
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

#define PRIME 1000000009

int count(int* t, int size)
{
    int ret = 0;
    REP(i, size+1)
	ret += (t[i] != 0);
    return ret;
}

int remove(int* boxes, int n)
{
    int limit = n*MAXB;
    int best, to_remove;
    int orders[MAXN*MAXB+1];
    int o2[MAXN*MAXB+1];

    REP(i, limit+1)
	orders[i] = 0;
    orders[0] = 1;

    REP(i, n)
	FORD(j, limit, boxes[i])
	    orders[j] = (orders[j] + orders[j-boxes[i]]) % PRIME;

    best = -1;
    to_remove = -1;

    REP(i, n)
    {
	REP(j, limit+1)
	    o2[j] = orders[j];
	FOR(j, boxes[i], limit)
	    o2[j] = (o2[j] - o2[j-boxes[i]] + PRIME) % PRIME;

	int served_orders = count(o2, limit);

	if(served_orders > best || (served_orders == best && to_remove > boxes[i]))
	{
	    best = served_orders;
	    to_remove = boxes[i];
	}
    }
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

