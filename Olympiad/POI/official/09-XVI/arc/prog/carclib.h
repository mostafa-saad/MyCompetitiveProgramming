/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arclib.h                                                   *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Plik naglowkowy modulu arclib dla C/C++                    *}
{*                                                                       *}
{*************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Inicjuje dane wejsciowe i zwraca liczbe projektow */
int inicjuj();

/* Sluzy do wczytania ciagu reprezentujacego jakosci projektow */
int wczytaj();

/* Sluzy do wypisania wyznaczonego podciagu */
void wypisz(int jakoscProjektu);

#ifdef __cplusplus
}
#endif
