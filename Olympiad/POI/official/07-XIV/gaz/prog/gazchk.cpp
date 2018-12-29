/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gazchk.cpp                                                 *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Program weryfikujacy poprawnosc wyjscia wygenerowanego     *}
{*            przez program zawodnika, format:                           *}
{*            ./skachk.e in out_zawodnika out_wzorcowy                   *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

#include <vector>

int xs[50000], ys[50000], xt[50000], yt[50000];
int bylos[50000], bylot[50000];
int n;

void wczytaj_ina(char *nazwa){
    FILE *plik;

    if ((plik = fopen(nazwa, "r")) == NULL){
        printf("Nie moge otworzyc pliku wejsciowego :P\n");
        exit(1);
    }
    fscanf(plik, "%d", &n);
    for(int i=0; i<n; ++i)
        fscanf(plik, "%d%d", &xs[i], &ys[i]);
    for(int i=0; i<n; ++i)
        fscanf(plik, "%d%d", &xt[i], &yt[i]);
}

char txt[1000]; int txtn;
int nznak(FILE *plik){
    while(!txt[txtn]){
        if (!fgets(txt, 999, plik))
            return 1000;
        txtn=0;
    }
    return txt[txtn++];
}

long long nliczba(FILE *plik){
    int co;
    do{
        co = nznak(plik);
    }while(co != 1000 && (co < '0' || co > '9') && co != '-');
    if (co == 1000){
        printf("WRONG\nZa krotki plik\n");
        return (long long)-1;
    }
    if (co == '-' || co == '0'){
        printf("WRONG\nZly znak w pliku: '%c'\n", co);
        return (long long)-1;
    }
    long long licz = co - '0';
    co = nznak(plik);
    while(co >= '0' && co <= '9'){
        licz = licz * 10LL + (long long)(co - '0');
        if (licz > 1000LL * 1000LL * 1000LL * 1000LL * 1000LL){
            printf("WRONG\nZly numer w pliku - wiekszy niz 10^15\n");
            return (long long)-1;
        }
        co = nznak(plik);
    }
    return licz;
} 

int main(int argc, char *argv[]){
    if (argc != 4){
        printf("WRONG\nUzycie: chk in out_zaw out_wzorcowy\n");
        return -1;
    }
    wczytaj_ina(argv[1]);
    FILE *out_zaw = fopen(argv[2], "r");
    if (!out_zaw){
        printf("WRONG\nBrak outa zawodnika\n");
        return -1;
    }
    FILE *out_wz = fopen(argv[3], "r");
    if (!out_wz){
        printf("WRONG\nBrak outa wzorcowego\n");
        return -1;
    }
    long long wzorcowa_suma = nliczba(out_wz);
    txt[0]=0; txtn=0;
    long long zaw_suma = nliczba(out_zaw);
    if (zaw_suma < 0LL) return -1;
    if (zaw_suma != wzorcowa_suma){
        printf("WRONG\nZla optymalna suma!\n");
        return -1;
    }
    long long a, b;
    for(int i=0; i<n; ++i){
        a = nliczba(out_zaw);
        b = nliczba(out_zaw);
        if (a < 0LL || b < 0LL)
            return -1;
        if (a < 1LL || b < 1LL || a > (long long)n || b > (long long)n){
            printf("WRONG\nLiczba poza zakresem [1,n]\n");
            return -1;
        }
        --a; --b;
        if (bylos[a]++ || bylot[b]++){
            printf("WRONG\nDwa razy wykorzystujemy ten sam zasob!\n");
            return -1;
        }
        if (xs[a] > xt[b] || ys[a] < yt[b]){
            printf("WRONG\nNie da sie dojsc, zla konfiguracja\n");
            return -1;
        }
    }
    fclose(out_zaw);
    fclose(out_wz);
    printf("OK\n");
    return 0;
}
