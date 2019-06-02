#ifndef __MAJA_H__
#define __MAJA_H__

/* interfejs modu³u graj±cego */

	int gramy_dalej();
	/* inicjalizuje kolejna gre, 
		zwraca:
			ograniczenie gorne na zgadywane liczby
			albo 0, jesli juz nie gramy dalej 
	*/

	int	czy_podzielna_przez(int m);
	/* zapytanie, czy wymyslona przez Majê liczba jest podzielna przez m 
	  wej¶cie: m > 0 
		zwraca 1 je¶li siê dzieli, 0, je¶li siê nie dzieli
	*/
	
	void zgaduj(int k);
	/* próba zgadniêcia liczby; 
		wolno probowac tylko raz 
	*/

#endif
