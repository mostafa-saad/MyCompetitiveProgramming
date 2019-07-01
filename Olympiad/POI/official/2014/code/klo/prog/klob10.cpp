/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Szymon Stankiewicz, Karol Farbis              *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Niepoprawnie sprawdza warunki niezbedne       *
 *                         do istnienia rozwiazania.                     *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>

using namespace std;

const int MAX_N=1000007;

int perm[MAX_N], tab[MAX_N], gen[MAX_N], out[MAX_N], N, K, p, q, MAXI;

bool comp(int a, int b)
{
    return tab[a]>tab[b];
}

int main()
{
    scanf("%d %d %d", &K, &p, &q);
    for(int i = 1; i<=K; i++)
    {
        scanf("%d", tab+i);
        perm[i]=i;
        N+=tab[i];
        if(tab[i]>tab[MAXI])
            MAXI=i;
    }
    if(tab[MAXI]>(N+1)/2 || (N > 1 && p == q && tab[p] < 2))
    {
        printf("0\n");
        return 0;
    }

    if(tab[MAXI]==(N+1)/2)
    {
        if(N%2==0)
        {
            if((p==MAXI)^(q==MAXI))
            {
                printf("%d ", p);
                tab[p]--;
                tab[q]--;
                int k = 1;
                for(int i = 0; i<N-2; i++)
                {
                    if((i%2==0)^(p==MAXI))
                        printf("%d ", MAXI);
                    else
                    {
                        while(tab[k]==0 || k==MAXI)
                            k++;
                        printf("%d ", k);
                        tab[k]--;
                    }
                }
                printf("%d\n", q);
            }
            else
                printf("0\n");
        }
        else
        {
            if(p==q && p==MAXI)
            {
                int k = 1;
                for(int i = 0; i<N; i++)
                    if(i%2==0)
                        printf("%d ", MAXI);
                    else
                    {
                        while(tab[k]==0 || k==MAXI)
                            k++;
                        printf("%d ", k);
                        tab[k]--;
                    }
            }
            else
                printf("0\n");
        }
        return 0;
    }
    tab[p]--;
    tab[q]--;
    N-=2;
    sort(perm+1, perm+K+1, comp);
    {
        int pos=0;
        for(int i = 1; i<=K; i++)
            for(int j = 0; j<tab[perm[i]]; j++)
            {
                gen[pos]=perm[i];
                pos++;
            }
    }
    for(int i = 0; i<N; i++)
        out[i]=gen[N/2*((N%2)^(i%2))+i/2];
    if(out[0]==p || out[N-1] ==q) {
        if(p!=out[N-1] && q!=out[0])
            reverse(out, out+N);
        else //if(p==out[0] && q==out[N-1] && p==q) (!!) KF
        {
            if(q==out[N-1])
                reverse(out, out+N);
            swap(out[0], out[1]);
            for(int i = 1; i<N-1; i++)
                if(out[i]==out[i+1])
                    swap(out[i+1], out[i+2]);
        }
    }
    printf("%d ", p);
    for(int i = 0; i<N; i++)
        printf("%d ", out[i]);
    printf("%d", q);
    return 0;
}
