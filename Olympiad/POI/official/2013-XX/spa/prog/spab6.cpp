/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(2^n)                                        *
 *   Zlozonosc pamieciowa: O(2^n)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Probuje przeszukac caly graf.                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

char visited[1<<23];
char forbidden[1<<23];
int q[1<<23];
int n,k,x,y;

bool bfs(int s, int t)
{
    int b = 0, e = 0;
    visited[s] = true;
    q[e++] = s;
    while(b!=e)
    {
        int v = q[b++];
        for(int i = 0; i<n; i++)
        {
            int next = v ^ (1<<i);
            if(next == t) return true;
            if(!visited[next] && !forbidden[next])
            {
                visited[next] = true;
                q[e++] = next;
            }
        }
    }
    return false;
}

int readBinary()
{
    char buf[100];
    scanf("%s", buf);
    int r = 0;
    for(int i = n-1; i>=0; i--)
        if(buf[i] == '1')
            r += (1<<(n-i-1));
    return r;
}

void read()
{
    scanf("%d %d", &n, &k);
    x = readBinary();
    y = readBinary();
    for(int i = 0; i<k; i++)
    {
        int a;
        a = readBinary();
        forbidden[a] = true;
    }
}

int main()
{
    read();
    if(bfs(x,y))
        printf("TAK\n");
    else
        printf("NIE\n");
}
