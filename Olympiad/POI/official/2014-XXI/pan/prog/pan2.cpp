/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Zlozonosc czasowa:    O(n sqrt m)                                   *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         W tym rozwiazaniu petle sa tak ustawione,     *
 *                         zeby nie przegladac liczb mniejszych od       *
 *                         dotychczasowo znalezionych odpowiedzi.        *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

const int MAXM = 10000000; // gorne ograniczenie na wielkosc liczb (ograniczenie na m z tresci zadania)
int PMAXM; // pierwiastek z gorengo ograniczenia, mozna obliczac pozniej, lub dla kazdego zapytania obliczac jedynie pierwiastek z gornego ograniczenia tego zapytania

static inline int czy_liczba_jest_w_przedziale(int liczba, int przedzial_1, int przedzial_2) { //dla liczby 'liczba' sprawdza czy jej wielokorotnosc nalezy do przedzialu [przedzial_1,przedzial_2]
    if(przedzial_1 / liczba != przedzial_2 / liczba ) return 1; // dla wiekszosci przypadkow ten warunek wystarcza, nie jest on wystarczający
    if(przedzial_1 % liczba == 0) return 1;                     //jedynie gdy jedyna wielokrotnoscia pewnej liczby jest dolne ograniczenie przedzialu
    return 0;
}


void zapytanie() {
    int a,b,c,d; //pary liczb oznaczajace przedzial [a,b] i [c,d]
    scanf("%d%d%d%d",&a,&b,&c,&d);
    PMAXM = (int)sqrt(max(b, d)) + 1;
    int odp = 1; //tu bedzie odpowiedz. Na poczatku jest 1, w czasie dzialania programu będzie zmieniac sie na najlepsza dotychczas znaleziona odopowiedz
    for(int i = PMAXM; i > 1; i--) { // sprawdzamy jakie male liczby są dobra odpowiedzia.
        if(czy_liczba_jest_w_przedziale(i,a,b) && czy_liczba_jest_w_przedziale(i,c,d) ) {
            odp = i;
            break;
        }
    }
    //sprawdzamy duze liczby
    for(int t = 1; t < PMAXM; t++) {
        int kan = b/t;
        if(kan < odp) break;
        if(czy_liczba_jest_w_przedziale(kan,a,b) && czy_liczba_jest_w_przedziale(kan,c,d)) {
            odp = kan;
            break;
        }
    }
    for(int t = 1; t < PMAXM; t++) {
        int kan = d/t;
        if(kan < odp) break;
        if(czy_liczba_jest_w_przedziale(kan,a,b) && czy_liczba_jest_w_przedziale(kan,c,d)) {
            odp = kan;
            break;
        }
    }
    printf("%d\n", odp);
}


int main() {
    int n; // n to liczba zapytań w zadaniu - dokładnie tak jak w treści
    scanf("%d",&n);
    for(int i = 0; i < n; i++) zapytanie();  //każdy test wykonuje się niezależnie
}
