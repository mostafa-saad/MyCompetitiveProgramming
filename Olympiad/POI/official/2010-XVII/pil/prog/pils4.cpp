/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils4.cpp                                        *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Drzewo przdziałowe, zoptymalizowane pamieciowo.  *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<assert.h>
using namespace std; 

const int max_n = 3003000; 
const int max_pow = (1<<22); 
int a[max_n], t_max[max_pow], t_min[max_pow], n, m, t; 

int get_diff(int st, int en) { 
   int mn(min(a[st], a[en])) , mx(max(a[st], a[en])); 
   if (st != en) { 
        mn = min(mn, min(a[st + 1], a[en - 1])); 
        mx = max(mx, max(a[st + 1], a[en - 1])); 
   } 
    st += m; st /= 2; 
    en += m; en /= 2; 
    while (st / 2 != en / 2) { 
        if (st % 2 == 0) { 
            mn = min(mn, t_min[st + 1]); 
            mx = max(mx, t_max[st + 1]);             
        } 
        if (en % 2 == 1) { 
            mn = min(mn, t_min[en - 1]); 
            mx = max(mx, t_max[en - 1]);             
        }      
        st /= 2; 
        en /= 2; 
    } 
    return mx - mn;        
} 

int f(int p) { 
    if (p >= n) return n - 1; 
    return p;  
} 


int main() 
{ 
    assert(scanf("%d%d",&t,&n) == 2); 
    
    for (int i = 0; i < n; i++) 
        assert(scanf("%d", &a[i]) == 1); 

    m = 1; 
    while (m < n) m *= 2; 

    for (int i = m - 1; i >= 1; i--) { 
        if (i * 2 < m) { 
            t_max[i] = max(t_max[2 * i], t_max[2 * i + 1]);        
            t_min[i] = min(t_min[2 * i], t_min[2 * i + 1]); 
        } 
        else { 
            t_max[i] = max(a[f(2 * i - m)], a[f(2 * i + 1 - m)]); 
            t_min[i] = min(a[f(2 * i - m)], a[f(2 * i + 1 - m)]); 
        } 
    } 
   
    int last_added = -1, res = 0; 

    for (int i = 0; i < n; i++) { 
        while (last_added + 1 < n && get_diff(i, last_added + 1) <= t) 
            ++last_added;
        res = max(res, last_added + 1 - i);          
    } 
    printf("%d\n",res); 
    return 0; 
} 
