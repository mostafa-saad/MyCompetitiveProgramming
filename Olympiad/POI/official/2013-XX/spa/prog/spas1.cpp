/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(2^n)                                        *
 *   Zlozonosc pamieciowa: O(2^n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Heurystyczne optymalizacje podejscia          *
 *                         wykladniczego.                                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int HSIZE = 2000003;
const int EMPTY = 0;

struct list
{
    struct node
    {
        long long key;
        node * next;
        node() {}
        node(long long _k)
        {
            key = _k;
            next = NULL;
        }
    };
    node *head;
    list() {
        head = NULL;
    }
    void push(long long a)
    {
        node *new_head = new node(a);
        new_head->next = head;
        head = new_head;
    }
    bool empty() {
        return head == NULL;
    }
    long long pop()
    {
        long long ret = head->key;
        node *toDel = head;
        head = head->next;
        toDel->next = NULL;
        delete toDel;
        return ret;
    }
    void clear()
    {
        while(!empty())
            pop();
    }
    bool lookup(long long a)
    {
        for(node* i = head; i!=NULL; i=i->next)
            if(i->key == a)
                return true;
        return false;
    }
};

list forbidden[HSIZE];
list visited[HSIZE];

inline void hashSetInsert(list* set, long long value, int size)
{
    set[value%size].push(value);
}

inline bool hashSetLookup(list* set, long long value, int size)
{
    return set[value%size].lookup(value);
}

inline void hashSetClear(list* set, int size)
{
    for(int i = 0; i<size; i++)
        set[i].clear();
}

list L;
int n,k;

bool dfs(long long s, long long t)
{
    if(s == t) return true;
    if(hashSetLookup(visited,s,HSIZE) || hashSetLookup(forbidden,s,HSIZE)) return false;
    hashSetInsert(visited,s,HSIZE);
    for(int i = 0; i<n; i++)
        if((t & (1LL << i)) != (s & (1LL << i)))
            if(dfs(s ^ (1LL << i), t)) return true;
    for(int i = 0; i<n; i++)
        if((t & (1LL << i)) == (s & (1LL << i)))
            if(dfs(s ^ (1LL << i), t)) return true;
    return false;
}

bool solve(long long s, long long t)
{
    return dfs(s,t);
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
        hashSetInsert(forbidden,a,HSIZE);
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
