/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(2^n)  (ograniczona przez MAXSTEPS)          *
 *   Zlozonosc pamieciowa: O(2^n)  (ograniczona przez MAXV)              *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Probuje przeszukac caly graf.                 *
 *                         Gdy brakuje pamieci stosuje heurystyke.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXV = 2000005;
const int MAXSTEPS = 5000000;

set<long long> forbidden;
set<long long> visited;
long long q[MAXV];
long long x,y;
int n,k;

bool search(long long s, long long t)
{
    int b = 0, e = 0;
    q[e++] = s;
    visited.insert(s);
    int steps = 0;
    while(b < e && steps < MAXSTEPS)
    {
        long long v = q[b++];
        for(int i = 0; i<n; i++)
        {
            long long next = v ^ (1LL << i);
            steps++;
            if(next == t) return true;
            if(!forbidden.count(next) && !visited.count(next))
            {
                if(e != MAXV)
                    q[e++] = next;
                else
                {
                    int g = rand()%MAXV;
                    visited.erase(q[g]);
                    q[g] = next;
                }
                visited.insert(next);
            }
        }
    }
    return false;
}


bool solve(long long s, long long t)
{
    return search(x,y);
}
long long readBinary()
{
    char buf[100];
    scanf("%s", buf);
    long long r = 0;
    for(int i = n-1; i>=0; i--)
        if(buf[i] == '1')
            r += (1LL<<(n-i-1));
    return r;
}
void read()
{
    scanf("%d %d", &n, &k);
    x = readBinary();
    y = readBinary();
    for(int i = 0; i<k; i++)
    {
        long long a;
        a = readBinary();
        forbidden.insert(a);
    }
}

int main()
{
    srand(time(NULL));
    read();
    if(solve(x,y))
        printf("TAK\n");
    else
        printf("NIE\n");
}
