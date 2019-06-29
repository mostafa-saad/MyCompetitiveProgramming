/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poslib.h                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Plik naglowkowy modulu poslib dla C/C++                   *
 *                                                                       *
 *************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Inicjuje gre z Bitocym */
void inicjuj(int *n, int *a, int *b);

/* Zadaje pytanie Bitocemu */
int pytaj(char c, int x);

/* Udziela odpowiedzi Bitocemu */
void odpowiedz(int wynik);

#ifdef __cplusplus
}
#endif
