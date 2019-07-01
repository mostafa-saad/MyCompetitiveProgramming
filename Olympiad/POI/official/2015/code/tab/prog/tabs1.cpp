/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Tablice kierunkowe                                 *
 *   Zlozonosc czasowa:    O(2^n nm log n)                                    *
 *   Zlozonosc pamieciowa: O(nm)                                              *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MaxN  = 1000;
const int MaxM  = 200;
const int Infty = 1010101010;


int plates[MaxN][MaxM], startPlates[MaxN][MaxM];
int N, M;


// wczytywanie danych do wektora tabliczek
void input(){
	cin >> N >> M;
	int plateno, num;

	for(plateno = 0; plateno < N; plateno++){
		for(num = 0; num < M; num++){
			cin >> plates[plateno][num];
			startPlates[plateno][num] = plates[plateno][num];
		}
	}
}

vector<int> curBest;
bool isTaken[MaxN];

void normalize_plates(int numPlate){
	int curPlate[MaxM];
	copy(startPlates[numPlate], startPlates[numPlate]+M, curPlate);

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			plates[i][j] = startPlates[i][j] - curPlate[j];
		}
		int smallest = *min_element(plates[i], plates[i]+M);
		
		for(int j = 0; j < M; j++)
			plates[i][j] -= smallest;
	}
}

void check_correct(){
	vector<int> order;
	for(int i = 0; i < N; i++)
		if(isTaken[i])
			order.push_back(i);

	if(order.size() == 0) return;  // BAD!

	
	vector<bool> decreased(M, false);
	
	normalize_plates(order[0]);

	sort(order.begin(), order.end(),
			[&](int lhs, int rhs){
				return
					accumulate(plates[lhs], plates[lhs]+M, 0) <
					accumulate(plates[rhs], plates[rhs]+M, 0);
			});

	for(int i = 0; i < static_cast<int>(order.size()); i++){
		int numPlate = order[i];

		for(int j = 0; j < M; j++){
			// zadna wzgledna odleglosc nie moze przekroczyc 1
			if(plates[numPlate][j] >= 2) return;
			// jesli kiedys osiagnie 1, to juz tak musi zostac
			if(plates[numPlate][j] == 1){
				decreased[j] = true;
			} else {
				if(decreased[j]) return;
			}
		}
	}

	// wszystko ok? moze pobilismy rekord?
	if(curBest.size() < order.size())
		curBest = order;
}

void brute(int pos = 0){
	if(pos == N){
		check_correct();
		return;
	}

	isTaken[pos] = false;
	brute(pos+1);

	isTaken[pos] = true;
	brute(pos+1);
}


int main(){
	input();
	brute();

	sort(curBest.begin(), curBest.end(),
			[](int lhs, int rhs){
				return accumulate(startPlates[lhs], startPlates[lhs]+M, 0) >
				       accumulate(startPlates[rhs], startPlates[rhs]+M, 0);
			});

	cout << curBest.size() << endl;

	int i;
	for(i = 0; i < static_cast<int>(curBest.size()); i++)
		cout << curBest[i]+1 << " ";
	cout << endl;

	return 0;
}
