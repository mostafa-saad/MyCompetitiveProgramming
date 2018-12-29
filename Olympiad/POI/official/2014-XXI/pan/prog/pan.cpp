/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Zlozonosc czasowa:    O(n sqrt m)                                   *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

//const int MAXM = 1000000000; // gorne ograniczenie na wielkosc liczb (ograniczenie na m z tresci zadania)
int PMAXM; // pierwiastek z gorengo ograniczenia, mozna obliczac pozniej, lub dla kazdego zapytania obliczac jedynie pierwiastek z gornego ograniczenia tego zapytania

static inline int czy_liczba_jest_w_przedziale(int liczba, int przedzial_1, int przedzial_2) { //dla liczby 'liczba' sprawdza czy jej wielokorotnosc nalezy do przedzialu [przedzial_1,przedzial_2]
    if(liczba == 0) return 0;
    if(przedzial_1 / liczba != przedzial_2 / liczba ) return 1; // dla wiekszosci przypadkow ten warunek wystarcza, nie jest on wystarczajacy
    if(przedzial_1 % liczba == 0) return 1;                     //jedynie gdy jedyna wielokrotnoscia pewnej liczby jest dolne ograniczenie przedzialu
    return 0;
}


void zapytanie() {
    int a,b,c,d; //pary liczb oznaczajace przedzial [a,b] i [c,d]
    scanf("%d%d%d%d",&a,&b,&c,&d);
    PMAXM = (int)sqrt(max(b, d)) + 5;
    int odp = 1; //tu bedzie odpowiedz. Na poczatku jest 1, w czasie dzialania programu bedzie zmieniac sie na najlepsza dotychczas znaleziona odopowiedz
    for(int i = 2; i < PMAXM; i++) { // sprawdzamy jakie male liczby sa dobra odpowiedzia.
        // Petle moznaby zrobic w odwrotnej kolejnosci(PMAXM--> 1), ale w ten sposob czas dzialania programu calkowicie nie zalezy od danych wejsciowych
        if(czy_liczba_jest_w_przedziale(i,a,b) && czy_liczba_jest_w_przedziale(i,c,d) ) odp = i;
    }

    for(int t = 1; t < PMAXM; t++) {
        int kan = b/t;
        if(czy_liczba_jest_w_przedziale(kan,a,b) && czy_liczba_jest_w_przedziale(kan,c,d))
            odp = max(odp,kan);
        kan = d/t;
        if(czy_liczba_jest_w_przedziale(kan,a,b) && czy_liczba_jest_w_przedziale(kan,c,d))
            odp = max(odp,kan);
    }
    printf("%d\n", odp);
}


int main() {
    int n; // n to liczba zapytan w zadaniu - dokladnie tak jak w tresci
    scanf("%d",&n);
    for(int i = 0; i < n; i++) zapytanie();  //kazdy test wykonuje sie niezaleznie
}
