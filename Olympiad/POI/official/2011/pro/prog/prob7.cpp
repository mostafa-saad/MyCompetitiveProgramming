/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Pawel Parys                                      *
 *   Opis:              Rozwiazanie bledne - zachlanne                   *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct assig {
   int c, t, s;
} a[1000];

int skill[500];
struct comp {
   bool operator()(const int &a, const int &b)
   {
     return skill[a] < skill[b];
   }
};

int n, m, r, t, k, pa;
int aa, bb;
vector<int> sv[600];
vector<pair<int, int> > dif;
bool v[600];

int main()
{
   scanf("%d %d %d %d %d", &n, &m, &r, &t, &k);
   for (int i = 0; i < k; i++)
   {
      scanf("%d %d", &aa, &bb);
      sv[bb - 1].push_back(aa - 1);
      skill[aa - 1]++;
   }
   for (int i = 0; i < m; i++)
      if (sv[i].size())
         dif.push_back(make_pair(sv[i].size(), i));
   sort(dif.begin(), dif.end());
   for (int i = 0; i < m; i++)
      if (sv[i].size())
         sort(sv[i].begin(), sv[i].end(), comp());
   int et = r;
   while (et <= t)
   {
      bool change = false;
      bool u[500];
      
      memset(u, false, sizeof(bool) * n);
      for (unsigned int i = 0; i < dif.size(); i++)
         if (!v[dif[i].second])
            for (vector<int>::iterator j = sv[dif[i].second].begin(); j != sv[dif[i].second].end(); j++)
               if (!u[*j])
               {
                  u[*j] = true;
                  v[dif[i].second] = true;
                  a[pa].c = *j;
                  a[pa].t = dif[i].second;
                  a[pa++].s = et - r;
                  change = true;
                  break;
               }

      if (!change) break;
      et += r;
   }
   int tm = 0;
   for (int i = 0; i < pa; i++)
      tm += a[i].s + r;
   printf("%d %d\n", pa, tm);
   for (int i = 0; i < pa; i++)
      printf("%d %d %d\n", a[i].c + 1, a[i].t + 1, a[i].s);
   return 0;
}
