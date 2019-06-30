/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils2.cpp                                        *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie powolne - multiset.                  *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/
#include<cstdio> 
#include<set>
#include<assert.h>
using namespace std; 
const int inf = 2100000000; 
const int max_n = 3003000; 
multiset<int> s_min, s_max; 
int a[max_n], n, t, last_added = -1, res = 0; 

int main() { 
    assert(scanf("%d%d",&t,&n) == 2); 
    for (int i = 0; i < n; i++) assert(scanf("%d", &a[i]) == 1); 
    s_min.insert(inf); 
    s_max.insert(inf); 
    for (int i = 0; i < n; i++) { 
        while (last_added + 1 < n && max(-*s_max.begin(), a[last_added + 1]) - min(*s_min.begin(), a[last_added + 1]) <= t) { 
            ++last_added; 
            s_min.insert(a[last_added]); 
            s_max.insert(-a[last_added]);             
        } 
        res = max(res, last_added + 1 - i); 
        s_min.erase(s_min.find(a[i])); 
        s_max.erase(s_max.find(-a[i]));        
    } 
    printf("%d\n",res); 
} 
