/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O((n + m) log m)                              *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;
int ignore;

struct testimony
{
    int who, time, howMany;
    testimony() {}
    void read()
    {
        ignore = scanf("%d%d%d", &time, &who, &howMany);
    }
};

//act[i] = Liczba informatykow obecnych w biurze w chwili i
int act[100005];

//ends[i] = ilu informatykow sklada swoje ostatnie zeznanie w chwili i
int ends[100005];

//starts[i] = ilu informatykow sklada swoje pierwsze zeznanie w chwili i
int starts[100005];

//temp - tablica pomocnicza funkcji prepare.
//temp[i] = chwila zlozenia pierwszego/ostatniego zeznania
//          przez i-tego informatyka
int temp[100005];

//Bufor do wczytania wejścia:
testimony in[100005];
int N,M;

int normal, extra, extended, toClose, mandatory;

void read()
{
    ignore = scanf("%d%d",&N,&M);
    for(int i = 1; i<=M; i++)
        in[i].read();
}
bool prepare(int s)
{
    for(int i = 1; i<=N; i++)
        temp[i] = 1000000000;
    for(int i = 1; i<=M; i++)
        ends[i] = starts[i] = act[i] = 0;
    normal = extra = extended = toClose = mandatory = 0;
    for(int i = 1; i<=s; i++)
    {
        //Sprzeczne zeznania dotyczące tej samej chwili:
        if(act[in[i].time] && act[in[i].time] != in[i].howMany+1)
            return false;
        act[in[i].time] = in[i].howMany+1;
        temp[in[i].who] = min(temp[in[i].who], in[i].time);
    }
    for(int i = 1; i<=N; i++)
    {
        if(temp[i] != 1000000000)
            starts[temp[i]]++;
        temp[i] = -1;
    }
    for(int i = 1; i<=s; i++)
        temp[in[i].who] = max(temp[in[i].who], in[i].time);
    for(int i = 1; i<=N; i++)
        if(temp[i] != -1)
            ends[temp[i]]++;
    for(int i = 1; i<=N; i++)
    {
        if(temp[i] != -1)
            normal++;
        else
            extra++;
    }
    return true;
}
bool check()
{
    for(int i = 1; i<=M; mandatory -= ends[i],toClose += ends[i],i++)
    {
        if(!act[i])
            continue;
        extended -= starts[i];
        mandatory += starts[i];
        starts[i] = -extended;
        extended = max(0,extended);
        if(starts[i] > 0)
            normal -= starts[i];
        if(act[i] > extended + mandatory + toClose)
        {
            int toAdd = act[i] - (extended + mandatory + toClose);
            normal -= toAdd;
            extended += toAdd;
            continue;
        }
        if(mandatory > act[i])
            return false;
        int toRm = mandatory + extended + toClose - act[i];
        toClose -= toRm;
        toRm = - toClose;
        toClose = max(toClose,0);
        if(toRm <= 0) continue;
        extended -= toRm;
        normal += toRm;
        extra -= toRm;
    }
    if(extra < 0 || extra+normal < 0)
        return false;
    return true;
}
int binSearch()
{
    int p = 1, q = M;
    while(q-p>1)
    {
        int s = (p+q)/2;
        if(prepare(s) && check())
            p = s;
        else
            q = s;
    }
    if(prepare(q) && check())
        return q;
    return p;
}
int main()
{
    int Z;
    ignore = scanf("%d", &Z);
    while(Z--)
    {
        read();
        printf("%d\n", binSearch());
    }
    return 0;
}
