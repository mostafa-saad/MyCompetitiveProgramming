/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wag.c                                                      *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LEN 1000
#define BASE 100000000
#define LOGBASE 8

#define MOD 1000000000

int digits[5000];
int num[LEN+100];

int div4(int* x)
{
    int i;
    int r = 0;
    for (i=LEN-1; i>=0; i--) {
        r = r*BASE+x[i];
        x[i] = r/4;
        r %= 4;
    }
    return r;
}

int main()
{
    int dig = 0;
    unsigned long long x = 0, y = 1;
    unsigned long long xw = 1, yw = 1; 
    char buf[3000];
    int i, l;
    scanf("%s", buf);
    l = strlen(buf);

    for (i=0; i<l; i++)
        num[(l-i-1)/LOGBASE] = num[(l-i-1)/LOGBASE]*10 + buf[i] - '0';

    for (i=0; i<3000; i++)
        digits[dig++] = div4(num);

    while (--dig >= 0) {
        switch (digits[dig]) {
            case 0:
                y = x+1;
                yw = xw;
                break;
            case 1:
                if (x < y) {
                    y = x+2;
                    yw = xw;
                } else if (x == y) {
                    y += 2;
                    yw += xw;
                    yw %= MOD;
                } else {
                    y += 2;
                }
                x++;
                break;
            case 2:
                if (x < y) {
                    x += 2;
                } else if (x == y) {
                    x += 2;
                    xw += yw;
                    xw %= MOD;
                } else {
                    x = y+2;
                    xw = yw;
                }
                y++;
                break;
            case 3:
                x = y+1;
                xw = yw;
                break;
            default:
                printf("invalid digit\n");
                return 1;
        }
    }

    printf("%llu\n", xw);
    return 0;
}
