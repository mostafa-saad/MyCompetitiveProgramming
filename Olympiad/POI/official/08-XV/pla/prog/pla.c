/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla.c                                                     *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n) (na stosie) - implementacja w C.*
 *                                                                       *
 *************************************************************************/
#include <stdio.h>

int stos[270000],ssize,i,n,k,result,dump;

int main(){
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        scanf("%d %d\n",&dump,&k);
        while ((ssize>0)&&(stos[ssize-1]>k)){ssize--;}
        if ((ssize==0)||(stos[ssize-1]<k)){result++; stos[ssize++]=k;}
    }
    printf("%d\n",result);
    return 0;
}
