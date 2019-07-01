/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(sqrt(A))                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <array>
#include <utility>
#include "ckollib.h"

const int SQRT = 1 << 16;

std::array<int, SQRT> low, high;
std::array<std::pair<int, int>, 2> candidates;

void add(int value) {
	low[value % SQRT] ++;
	high[value / SQRT] ++;

	for(int i = 0; i < 2; i++) {
		if(candidates[i].first == 0 || candidates[i].first == value) {
			candidates[i].first = value;
			candidates[i].second ++;
			return;
		}
	}
}

int main() {
	int value;

	while((value = karta()) != 0) {
		add(value);
	}

	int rep = std::max(candidates[0].second, candidates[1].second);

	int result = 0;
	for(int i = 0; i < SQRT; i++) {
		if(low[i] % rep != 0) result += i;
		if(high[i] % rep != 0) result += i * SQRT;
	}

	if(candidates[1].first == 0) result = candidates[0].first;

	odpowiedz(result);

	return 0;	
}
