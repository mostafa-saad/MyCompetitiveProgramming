/* CEOI 2003 internal solution variant for task "register" */
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define INPUT  "register.in"
#define OUTPUT "register.out"
#define MAX_N  10000

#define FIELDSIZE(bits)    (((bits) + CHAR_BIT - 1) / CHAR_BIT)
#define FLIPBIT(chars,bit) ((chars)[(bit)/CHAR_BIT] ^= 1<<((bit)%CHAR_BIT))
#define GETBIT(chars,bit)  ((chars)[(bit)/CHAR_BIT] >> ((bit)%CHAR_BIT) & 1)

void dump(unsigned char m[MAX_N][FIELDSIZE(MAX_N + 1)], int n)
{
    int i, j;
    
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++) printf("%d ", GETBIT(m[i], j));
        printf("= %d\n", GETBIT(m[i], n));
    }
    printf("\n");
    getchar();
}

int main(void)
{
    int n, fn;                                              /* N, FIELDSIZE(N)                   */
    static unsigned char m[MAX_N][FIELDSIZE(MAX_N + 1)];    /* equation matrix                   */
    static int s[MAX_N];
    
    { /* INPUT */
        FILE *in;
        int a[2*MAX_N], i, j;
        
        in = fopen(INPUT, "r");                             /* open input (no error handling)    */
        fscanf(in, "%d", &n);                               /* read N                            */
        fn = FIELDSIZE(n+1);                                /* fn = # of chars to hold N+1 bits  */
        for (i=0; i<2*n; i++) fscanf(in, "%d", &a[i]);      /* read 2*N numbers into a[]         */
        fclose(in);
        
        memset(&m, 0, sizeof(m));                           /* build equation matrix             */
        for (i=0; i<n; i++)
            for (j=0; j<=n; j++)
                if (a[i+j]) FLIPBIT(m[i], j);
    }
    
    { /* FULL ELIMINATION */
        int i, j, k, l;
        static unsigned char tmp[sizeof(m[0])];             /* temp. storage for one row of m    */
        
        for (i=j=0; i<n; i++)                               /* for all clumns i                  */
        {
            s[i] = -1;                                      /* we know nothing about S_i         */
            for (k=j; k<n; k++) if (GETBIT(m[k], i)) break; /* find "1" in column i at row >= j  */
            if (k == n) continue;                           /* none found -> ignore this column  */
            
            if (j != k)                                     /* row k has the "1", move it to row */
            {                                               /* j by swapping rows k and j        */
                memcpy(&tmp,  &m[j], fn);
                memcpy(&m[j], &m[k], fn);
                memcpy(&m[k], &tmp,  fn);
            }
            
            for (k=0; k<n; k++)                             /* for all rows k != j               */
                if (k!=j && GETBIT(m[k],i))                 /* if there's a "1" in that row      */
                    for (l=0; l<fn; l++) m[k][l] ^= m[j][l];/* eliminate it by adding row j to k */
            
            s[i] = j++;                                     /* S_i is defined by equation j      */
        }
    }
    
    { /* CHECK FOR SOLUTION AND OUTPUT */
        FILE *out;
        int ok = 1, i, j;
        
        for (i=0; i<n && ok; i++)                           /* for all equations (== rows) i     */
        {
            if (!GETBIT(m[i], n)) continue;                 /* right side is "0", OK             */
            for (j=0; j<n; j++) if (GETBIT(m[i], j)) break; /* any "1" on left side -> OK        */
            if (j == n) ok = 0;                             /* "0 0 .. 0 = 1" -> not OK          */
        }
        
        out = fopen(OUTPUT, "w");                           /* open output (no error handling)   */
        if (ok)
        {
            for (i=n-1; i>=0; i--)                          /* for all variables (== columns)    */
                fprintf(out, i ? "%d " : "%d\n",            /* print S_i according to equation   */
                        s[i]>=0 ? GETBIT(m[s[i]], n) : 0);  /* (== row) s[i]                     */
        }
        else fprintf(out, "-1\n");
        fclose(out);
    }
    
    return 0;
}
