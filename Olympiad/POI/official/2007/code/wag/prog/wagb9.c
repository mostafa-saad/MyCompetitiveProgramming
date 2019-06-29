/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wagb9.c                                                    *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Rozwiązanie niepoprawne. Wzorcówka bez duzych liczb.       *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>

int digits[50];

int main()
{
    unsigned long long n;
    int dig = 0;
    unsigned long long x = 0, y = 1;
    unsigned long long xw = 1, yw = 1; 
    scanf("%llu", &n);
    while (n) {
        digits[dig++] = n % 4;
        n /= 4;
    }
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
