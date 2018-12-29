#ifndef _JAJMOD_H_
#define _JAJMOD_H_

#define TAK 1
#define NIE 0

extern long int wysokosc; /* tu b©dzie zapisana wysoko˜† drapacza, jaki mamy
                             do dyspozycji podczas eksperymentu */

extern int jajka;         /* tu b©dzie zapisana liczba jajek dost©pnych
			     podczas eksperymentu */

extern long int pietro;   /* tu funkcja daj_pytanie powinna umieszcza† numer
                             pi©tra, z kt¢rego ma by† zrzucone jajko */

extern int odpowiedz;     /* tu b©dzie odpowied« na pytanie, czy zrzucone
                             jajko rozbiˆo si© */

extern int wiem;          /* tu nale¾y wpisa† TAK, je˜li wiem jaka jest
                             wytrzymaˆo˜† jajka; w przeciwnym razie warto˜ci¥
                             tej zmiennej powinno by† NIE */

extern long int x;        /* jesli wiem == TAK, to tu nale¾y wpisa†
                             wytrzymaˆo˜† jajka */

#endif
