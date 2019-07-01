/*
  Plik naglowkowy modulu liclib dla C/C++
*/

#ifndef _LICLIB_H_
#define _LICLIB_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Inicjuje gre, zwraca liczbe n */
int inicjuj();

/* Wykonuje ruch Alojzego */
void alojzy(int x);

/* Zwraca ruch Bajtazara */
int bajtazar();

#ifdef __cplusplus
}
#endif
#endif
