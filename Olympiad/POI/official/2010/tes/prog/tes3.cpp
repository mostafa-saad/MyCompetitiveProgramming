/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tes3.cpp                                         *
 *   Autor:             Tomasz Kulczyński                                *
 *   Opis:              Rozwiązanie weryfikacyjne.                       *
 *                      Rozwiązanie wykorzystuje STLa.                   *
 *   Złożoność czasowa: O(m + l + |A|)                                   *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define M 1001013

vector<int> t[M], v[M], temp;
int a[M], ok[M];
int m,n;

int main()
{
    scanf("%d",&m);
    for(int i = 0; i < m; i++)
        scanf("%d",&a[i]);
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        int x,q;
        scanf("%d %d",&x, &q);
        t[q].push_back(i);
        int s = x-1;
        v[i].resize(s);
        while(s)
        {
            scanf("%d",&q);
            v[i][--s] = q;
        }
    }
    for(int i = 0; i < m; i++)
    {
        temp = t[a[i]];
        t[a[i]].clear();
        for(int j = 0; j < (int)temp.size(); j++)
            if(!v[temp[j]].empty())
            {
                t[v[temp[j]].back()].push_back(temp[j]);
                v[temp[j]].pop_back();
            }
            else ok[temp[j]] = 1;
    }
    for(int i = 0; i < n; i++)
        if(ok[i])
            puts("TAK");
        else
            puts("NIE");
    return 0;
}
