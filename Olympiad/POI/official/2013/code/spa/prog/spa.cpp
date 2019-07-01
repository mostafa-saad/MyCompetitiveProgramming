/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(n^2 * k)                                    *
 *   Zlozonosc pamieciowa: O(nk)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int HSIZE = 5000011;
const int EMPTY = 0;
const int MAXK = 500009;

long long forbidden[MAXK];
int fprev[MAXK];
int fhash[MAXK];
long long visited[HSIZE];
int vprev[HSIZE];
int vhash[HSIZE];
int vfree = 1, ffree = 1;
long long q[HSIZE];

inline void hashSetInsert(long long* set, int* prev, int* hash, int &free, long long value, int size)
{
    set[free] = value;
    prev[free] = hash[value%size];
    hash[value%size] = free++;
}

inline bool hashSetLookup(long long* set, int* prev, int* hash, long long value, int size)
{
    for(int t = hash[value%size]; t>0; t=prev[t])
        if(set[t] == value) return true;
    return false;
}

inline void hashSetClear(int* hash, int &free, int size)
{
    free = 1;
    for(int i = 0; i<size; i++)
        hash[i] = 0;
}

int n,k;

bool graphSearch(long long s, long long t, int bound)
{
    int b = 0, e = 0;
    int c = 1;
    q[e++] = s;
    hashSetInsert(visited,vprev,vhash,vfree,s,HSIZE);
    while(b < e && c < bound)
    {
        long long v = q[b++];
        for(int i = 0; i<n; i++)
        {
            long long next = v ^ (1LL << i);
            if(next == t) return true;
            if(!hashSetLookup(forbidden,fprev,fhash,next,MAXK) && !hashSetLookup(visited,vprev,vhash,next,HSIZE))
            {
                q[e++] = next;
                hashSetInsert(visited,vprev,vhash,vfree,next,HSIZE);
                c++;
            }
        }
    }
    if(c >= bound) return true;
    return false;
}

bool solve(long long s, long long t)
{
    int bound = n*k + 1;
    bool a = graphSearch(s,t,bound);
    hashSetClear(vhash,vfree,HSIZE);
    bool b = graphSearch(t,s,bound);
    return a && b;
}

long long x,y;

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
        hashSetInsert(forbidden,fprev,fhash,ffree,a,MAXK);
    }
}

int main()
{
    read();
    if(solve(x,y))
        printf("TAK\n");
    else
        printf("NIE\n");
}
