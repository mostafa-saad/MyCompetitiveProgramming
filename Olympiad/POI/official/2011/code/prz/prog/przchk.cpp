/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Przekladanka                                     *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include "weryfikator.h"

#include <vector>
#include <list>

#include <string.h>

using namespace std;

void my_error(const char* msg, int line, int pos)
{
    fprintf(stdout, "WRONG\n%s\n", msg);    
    exit(0);
}

bool isSorted(const list<int>  &data)
{
    int lastNumber = 0;
    for (typeof(data.begin()) it = data.begin() ; it != data.end() ; ++it) {
        if (lastNumber >= *it) {
            return false;
        }
        lastNumber = *it;
    }
    return true;
}

int main(int argc, char **argv){
    Scanner in_zad(argv[1]);
    Scanner out_zaw(argv[2], my_error, PL);
    Scanner out_nasz(argv[3]);

    list<int> Dane;
    int nDane;
    nDane = in_zad.readInt();
    in_zad.skipWhitespaces();
    for (int i = 0 ; i < nDane ; ++i) {
        Dane.push_back(in_zad.readInt());
        in_zad.skipWhitespaces();
    }

    char isSolvable = out_nasz.readChar();

    if (isSolvable == 'N') {
        const int sz = 100;
        char nie_[sz], da_[sz], sie_[sz];
        out_zaw.readString(nie_, sz);
        out_zaw.readSpace();
        out_zaw.readString(da_, sz);
        out_zaw.readSpace();
        out_zaw.readString(sie_, sz);
        out_zaw.skipWhitespaces();
        out_zaw.readEof();

        if (strcmp(nie_, "NIE") || strcmp(da_, "DA") || strcmp(sie_, "SIE")) {
            out_zaw.error("Oczekiwano 'NIE DA SIE'");
        } else {
            puts("OK");
            return 0;
        }
    }

    int amount = out_zaw.readInt(0, nDane * nDane);
    out_zaw.skipWhitespaces();
    
    char lastSign = 'x';
    for(int i = 0; i < amount; i++) {
        int num = out_zaw.readInt(0, nDane - 1);
        
        char sign = out_zaw.readChar();


        if (num == 0) {
            out_zaw.error("Liczba operacji musi byc dodatnia");
        }

        if (sign == 'a') {
            for (int i = 0 ; i < num ; i++) {
                int last = Dane.back();
                Dane.pop_back();
                Dane.push_front(last);
            }
        } else if (sign == 'b') {
            if (nDane <= 2) {
                out_zaw.error("Potrzeba co najmniej 3 elementow do operacji 'b'");
                return 0;
            }
            num %= 3;
            for (int i = 0 ; i < num ; i++) {
                int first  = *(Dane.begin()); Dane.pop_front();
                int second = *(Dane.begin()); Dane.pop_front();
                int third  = *(Dane.begin()); Dane.pop_front();

                Dane.push_front(second);
                Dane.push_front(first);
                Dane.push_front(third);
            }
        } else {
            out_zaw.error("Brak lub niepoprawna nazwa operacji");
        }

        if (lastSign == sign) {
            out_zaw.error("Litery stowarzyszone z liczbami musza wystepowac naprzemiennie");
        }

        lastSign = sign;
        out_zaw.skipWhitespaces();
    }
    out_zaw.readEof();

    if (!isSorted(Dane)) {
        out_zaw.error("Liczby nie zostaly posortowane");
    } else {
        printf("OK\n");
    }

    return 0;
}

