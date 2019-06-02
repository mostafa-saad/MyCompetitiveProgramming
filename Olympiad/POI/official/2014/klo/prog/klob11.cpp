/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Szymon Stankiewicz, Karol Farbis              *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Niepoprawnie sprawdza warunki niezbedne       *
 *                         do istnienia rozwiazania.                     *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAX_N=1000007;

int K, p, q, n, act=0, tab[MAX_N], gen[MAX_N], out[MAX_N];

struct list
{
    list* next;
    int var;
};

list* sort[MAX_N];

void add(int a, int b)
{
    list *act=new list;
    act->var=a;
    act->next=sort[b];
    sort[b]=act;
}

void write_in(int a)
{
    for(int i = 0; i<tab[a]; i++)
    {
        gen[act]=a;
        act++;
    }
}

void swap(int i, int j)
{
    int k=out[i];
    out[i]=out[j];
    out[j]=k;
}

void reverse()
{
    for(int i = 0; i*2<n; i++)
        swap(i, n-i-1);
}

void generate()
{
    list* help;
    for(int i = 1; i<MAX_N; i++)
        sort[i]=NULL;
    for(int i = 1; i<=K; i++)
        add(i, tab[i]);
    for(int i = 1; i<MAX_N; i++)
    {
        help=sort[i];
        while(help!=NULL)
        {
            write_in(help->var);
            help=help->next;
        }
    }
    for(int i = 0; i<n; i++)
        out[i]=gen[(n/2*((n%2)^(i%2)))+i/2];
    if(out[0]!=p && out[n-1]!=q)
        return ;
    if(out[0]!=q && out[n-1]!=p)
    {
        reverse();
        return;
    }
    if(out[n-1]==q)
        reverse();
    swap(0, 1);
    for(int i = 1; i+1<n; i++)
        if(out[i]==out[i+1])
            swap(i+1, i+2);
}

int main()
{
    scanf("%d %d %d", &K, &p, &q);
    for(int i = 1; i<=K; i++)
    {
        scanf("%d", tab+i);
        n+=tab[i];
    }

    if(n > 1 && p == q && tab[p] < 2) { // [!!] KF
        puts("0");
        return 0;
    }

    {
        int maxi=0;
        for(int i = 1; i<=K; i++)
            if(tab[i]>tab[maxi])
                maxi=i;
        if(tab[maxi]>(n+1)/2)
        {
            printf("0\n");
            return 0;
        }
        if(tab[maxi]==(n+1)/2)
        {
            if(n%2==1)
            {
                if(p==q && p==maxi)
                {
                    int k = 1;
                    for(int i = 0; i<n; i++)
                        if(i%2==0)
                            printf("%d ", maxi);
                        else
                        {
                            while(tab[k]==0 || k==maxi)
                                k++;
                            printf("%d ",k);
                            tab[k]--;
                        }
                    return 0;
                }
                else
                {
                    printf("0\n");
                    return 0;
                }
            }
            else
            {
                if(p!=q && (p==maxi || q==maxi))
                {
                    tab[q]--;
                    tab[p]--;
                    printf("%d ", p);
                    int k = 1;
                    for(int i = 1; i<n-1; i++) // [!!] KF (było i<n)
                        if((i%2)^(p==maxi))
                        {
                            printf("%d ", maxi);
                            tab[maxi]--;
                        }
                        else
                        {
                            while(k==maxi || tab[k]==0)
                                k++;
                            printf("%d ", k);
                            tab[k]--;
                        }
                    printf("%d", q);
                }
                else
                {
                    printf("0\n");
                    return 0;
                }
            }
            return 0;
        }
    }
    tab[p]--;
    tab[q]--;
    n-=2;
    generate();
    printf("%d ", p);
    for(int i = 0; i<n; i++)
        printf("%d ", out[i]);
    printf("%d ", q);
}
