/* CEOI 2003 internal solution variant for task "register" */
#include <stdio.h>
#include <string.h>

#define INPUT  "register.in"
#define OUTPUT "register.out"
#define MAX_N  750

typedef char m_element;
typedef m_element m_row[MAX_N + 1];
typedef m_row matrix[MAX_N];

int main(void)
{
    int n;                                                  /* N                                 */
    static matrix m;                                        /* equation matrix                   */
    static int s[MAX_N];
    
    { /* INPUT */
        FILE *in;
        int a[2*MAX_N], i, j;
        
        in = fopen(INPUT, "r");                             /* open input (no error handling)    */
        fscanf(in, "%d", &n);                               /* read N                            */
        for (i=0; i<2*n; i++) fscanf(in, "%d", &a[i]);      /* read 2*N numbers into a[]         */
        fclose(in);
        
        for (i=0; i<n; i++)                                 /* build equation matrix             */
            for (j=0; j<=n; j++)
                m[i][j] = a[i+j];
    }
    
    { /* FORWARD ELIMINATION */
        int i, j, k, l;
        static m_row tmp;                                   /* temp. storage for one row of m    */
        
        for (i=j=0; i<n; i++)                               /* for all clumns i                  */
        {
            s[i] = -1;                                      /* we know nothing about S_i         */
            for (k=j; k<n; k++) if (m[k][i]) break;         /* find "1" in column i at row >= j  */
            if (k == n) continue;                           /* none found -> ignore this column  */
            
            if (j != k)                                     /* row k has the "1", move it to row */
            {                                               /* j by swapping rows k and j        */
                memcpy(&tmp,  &m[j], sizeof(m_element)*(n+1));
                memcpy(&m[j], &m[k], sizeof(m_element)*(n+1));
                memcpy(&m[k], &tmp,  sizeof(m_element)*(n+1));
            }
            
            for (k=0; k<n; k++)                             /* for all rows k != j               */
                if (k!=j && m[k][i])                        /* if there's a "1" in that row      */
                    for (l=0; l<=n; l++) m[k][l] ^= m[j][l];/* eliminate it by adding row j to k */
            
            s[i] = j++;                                     /* S_i is defined by equation j      */
        }
    }
    
    { /* CHECK FOR SOLUTION AND OUTPUT */
        FILE *out;
        int ok = 1, i, j;
        
        for (i=0; i<n && ok; i++)                           /* for all equations (== rows) i     */
        {
            if (m[i][n] == 0) continue;                     /* right side is "0", OK             */
            for (j=0; j<n; j++) if (m[i][j]) break;         /* any "1" on left side -> OK        */
            if (j == n) ok = 0;                             /* "0 0 .. 0 = 1" -> not OK          */
        }
        
        out = fopen(OUTPUT, "w");                           /* open output (no error handling)   */
        if (ok)
        {
            for (i=n-1; i>=0; i--)                          /* for all variables (== columns)    */
                fprintf(out, i ? "%d " : "%d\n",            /* print S_i according to equation   */
                        s[i]>=0 ? m[s[i]][n] : 0);          /* (== row) s[i]                     */
        }
        else fprintf(out, "-1\n");
        fclose(out);
    }
    
    return 0;
}
