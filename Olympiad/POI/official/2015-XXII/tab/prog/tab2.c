/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Tablice kierunkowe                                 *
 *   Zlozonosc czasowa:    O(fn^2m/b), f - liczba losowan, b - dl. slowa      *
 *   Zlozonosc pamieciowa: O(nm)                                              *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define SmallMask unsigned long long
struct bitmask {
	SmallMask mask[4];
};

void bitmask_init(struct bitmask *b){
	memset(b, 0x00, sizeof(struct bitmask));
}

void bitmask_set(struct bitmask *b, int pos){
	b->mask[pos>>6] |= (1ULL<<(pos&63));
}

int bitmask_is_subset(struct bitmask *lhs, struct bitmask *rhs){
	int i;
	for(i = 0; i < 4; i++){
		if((lhs->mask[i] & rhs->mask[i]) != lhs->mask[i])
			return 0;
	}
	return 1;
}

int bitmask_cmp(struct bitmask *lhs, struct bitmask *rhs){
	int i;
	for(i = 3; i >= 0; i--){
		if(lhs->mask[i] < rhs->mask[i])
			return -1;
		if(lhs->mask[i] > rhs->mask[i])
			return 1;
	}
	return 0;
}


#define NumRandom 30
#define MaxN 1000
#define MaxM 200
#define Infty 1010101010


int plates[MaxN][MaxM], startPlates[MaxN][MaxM];
int N, M;


// wczytywanie danych do wektora tabliczek
void input(){
	scanf("%d%d", &N, &M);
	int plateno, num;

	for(plateno = 0; plateno < N; plateno++){
		for(num = 0; num < M; num++){
			scanf("%d", &plates[plateno][num]);
			startPlates[plateno][num] = plates[plateno][num];
		}
	}
}

void normalize_plates(int numPlate){
	int curPlate[MaxM], i, j;
	memcpy(curPlate, plates[numPlate], M*sizeof(int));

	for(i = 0; i < N; i++){
		int smallest = Infty;
		for(j = 0; j < M; j++){
			plates[i][j] -= curPlate[j];

			if(plates[i][j] < smallest)
				smallest = plates[i][j];
		}

		for(j = 0; j < M; j++){
			plates[i][j] -= smallest;
		}
	}
}


struct bitmask plateMask[MaxN];
int acceptablePlates[MaxN], numPlates;
int foundPlates[MaxN], numFound;
int dp[MaxN], origin[MaxN];

// ugh, serio ludzie kiedys tak pisali?
int cmpMaskNum(const void *lhs, const void *rhs){
	int left  = *(int*)lhs,
        right = *(int*)rhs;
	int cmp   = bitmask_cmp(plateMask+left, plateMask+right);

	if(cmp == 0)
		return left - right;

	return cmp;
}

// przetwarza dane przy zalozeniu, ze selectedPlates tam jest,
// do "foundPlates" wrzuca najlepszy zbior tabliczek
void process_data(int selectedPlate){
	normalize_plates(selectedPlate);

	int plateno, i, prev;
	numPlates = 0;

	// uzyskajmy zbior tabliczek, ktorych znormalizowane odleglosci wynosza
	// jedynie 0 lub
	for(plateno = 0; plateno < N; plateno++){
		int isOkay = 1;
		struct bitmask curMask;
		bitmask_init(&curMask);
		for(i = 0; i < M; i++){
			if(plates[plateno][i] != 0 && plates[plateno][i] != 1){
				isOkay = 0;
				break;
			} else {
				if(plates[plateno][i])
					bitmask_set(&curMask, M-i-1);
			}
		}

		if(isOkay){
			memcpy(&plateMask[plateno], &curMask, sizeof(curMask));
			acceptablePlates[numPlates] = plateno;
			numPlates++;
		}
	}

	// sortujemy te tabliczki rosnaco - wpierw po masce, potem po numerze
	qsort(acceptablePlates, numPlates, sizeof(int), cmpMaskNum);

	// programowanie dynamiczne - najdluzsza sciezka w DAG-u z porzadkiem
	// zawierania masek (w razie rownosci i tak dziala, bo mamy porzadek
	// na numerach tabliczek)
	memset(dp, 0xFF, numPlates*sizeof(int));   // nastawiamy na -1
	memset(origin, 0xFF, numPlates*sizeof(int));  // skad przychodzimy?

	for(plateno = 0; plateno < numPlates; plateno++){
		dp[plateno] = 1;
		// sprawdzamy poprzednie tabliczki
		for(prev = 0; prev < plateno; prev++){
			// jesli poprzednia sie zawiera w nowej, to aktualizujemy DP

			if(bitmask_is_subset(&plateMask[acceptablePlates[prev]],
						         &plateMask[acceptablePlates[plateno]])){
				if(dp[prev]+1 > dp[plateno]){
					dp[plateno]     = dp[prev]+1;
					origin[plateno] = prev;
				}
			}
		}
	}

	// gdzie jest najlepszy koniec?
	int bestEnd = 0;
	for(plateno = 1; plateno < numPlates; plateno++){
		if(dp[plateno] > dp[bestEnd])
			bestEnd = plateno;
	}

	// odtwarzamy wynik od konca
	numFound = dp[bestEnd];
	while(bestEnd != -1){
		foundPlates[dp[bestEnd]-1] = acceptablePlates[bestEnd];
		bestEnd = origin[bestEnd];
	}
}


// znowu?
int cmpSumDist(const void *lhs, const void *rhs){
	int left  = *(int*)lhs,
	    right = *(int*)rhs;

	int sumLeft = 0, sumRight = 0, i;
	for(i = 0; i < M; i++){
		sumLeft  += startPlates[left][i];
		sumRight += startPlates[right][i];
	}
	return sumRight - sumLeft;
}

int curBest[MaxN], curSize;

int main(){
	input();
	
	// inicjujemy ziarno generatora losowego
	srand(0xBADBABE);
	curSize = 0;
	
	int tries;
	for(tries = 0; tries < NumRandom; tries++){
		int v = rand() % N;
		process_data(v);

		if(numFound > curSize){
			curSize = numFound;
			memcpy(curBest, foundPlates, numFound*sizeof(int));
		}
	}

	// musimy teraz "jedynie" (ech...) posortowac wynik po malejacej sumie odleglosci
	// i wypisac na wyjscie
	qsort(curBest, curSize, sizeof(int), cmpSumDist);

	printf("%d\n", curSize);

	int i;
	for(i = 0; i < curSize; i++)
		printf("%d ", curBest[i]+1);
	printf("\n");

	return 0;
}
