/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Tablice kierunkowe                                 *
 *   Zlozonosc czasowa:    O(n^3m / b), b - rozmiar slowa                     *
 *   Zlozonosc pamieciowa: O(nm)                                              *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Opis:                 Rozwiazanie wolne, przyspieszone                   *
 *                         (bitmaski poprzez bitset<>)                        *
 *****************************************************************************/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>
#include <numeric>
#include <bitset>


using namespace std;

const int MaxN = 1000,
          MaxM = 200;

typedef bitset<MaxM> Mask;


// informacje o tabliczce kierunkowej
struct PlateData {
	int id;               // numer na wejsciu
	vector<int> dist;     // odleglosci
	int totalSum;

	// komparator porzadkujacy tabliczki po odleglosci
	bool operator<(const PlateData& other) const {
		return totalSum > other.totalSum;
	}

	// odejmuje odleglosci z 'other' od obecnej
	PlateData& operator-=(const PlateData& other){
		assert(dist.size() == other.dist.size());

		for(int i = 0; i < static_cast<int>(dist.size()); i++)
			dist[i] -= other.dist[i];

		return *this;
	}
};

// wczytywanie danych do wektora tabliczek
vector<PlateData> input(){
	int N, M;
	vector<PlateData> result;

	cin >> N >> M;
	result.reserve(N);

	for(int plateno = 0; plateno < N; plateno++){
		PlateData data;
		data.dist.resize(M);
		data.totalSum = 0;

		for(int num = 0; num < M; num++){
			cin >> data.dist[num];
			data.totalSum += data.dist[num];
		}

		data.id = plateno;
		result.push_back(data);
	}

	return result;
}

// normalizacja tabliczek z wejscia wzgledem zadanej tabliczki
void normalize_plates(vector<PlateData>& data, const PlateData relative){
	// przepraszam, nie moglem sie powstrzymac, by nie napisac tego
	// (prawie) funkcyjnie :)
	for_each(data.begin(), data.end(), [&](PlateData& plate){
				plate -= relative;
				int minimal = *min_element(plate.dist.begin(), plate.dist.end());
				for_each(plate.dist.begin(), plate.dist.end(), [=](int& elem){
						elem -= minimal;
					});
			});
}

// zwraca maksymalny podzbior tabliczek z wejscia zawierajacy wskazana
// tabliczke
vector<int> process_data(vector<PlateData> input, int selectedPlate){
	int M = input[0].dist.size();

	normalize_plates(input, input[selectedPlate]);

	// uzyskajmy zbior tabliczek, ktorych znormalizowane odleglosci wynosza
	// jedynie 0 lub 1; vector trzyma pare (maska zawierajaca informacje,
	// czy odleglosc do i-tego miasta to 0 czy 1, numer tabliczki)
	vector<pair<Mask,int>> acceptablePlates;
	for(int plateno = 0; plateno < static_cast<int>(input.size()); plateno++){
		auto& dist = input[plateno].dist;

		if(all_of(
				dist.begin(), dist.end(),
				[](int val){ return val == 0 || val == 1; })){

			acceptablePlates.emplace_back(
					accumulate(dist.begin(), dist.end(), Mask(),
							[](Mask result, int val){ return (result<<1).set(0,val); }),
					plateno
				);
		}
	}

	// sortujemy te tabliczki rosnaco - wpierw po masce, potem po numerze
	sort(acceptablePlates.begin(), acceptablePlates.end(),
			[M](const pair<Mask,int>& lhs, const pair<Mask,int>& rhs){
				for(int i = M-1; i >= 0; i--)
					if(lhs.first[i] != rhs.first[i])
						return !lhs.first[i];
				return lhs.second < rhs.second;
			});

	// programowanie dynamiczne - najdluzsza sciezka w DAG-u z porzadkiem
	// zawierania masek (w razie rownosci i tak dziala, bo mamy porzadek
	// na numerach tabliczek)
	vector<int> dp(acceptablePlates.size(), 1);
	vector<int> origin(dp.size(), -1);  // musimy wiedziec, skad przychodzimy

	for(int plate = 0; plate < static_cast<int>(acceptablePlates.size()); plate++){
		Mask newMask = acceptablePlates[plate].first;
		// sprawdzamy poprzednie tabliczki
		for(int prev = 0; prev < plate; prev++){
			// jesli poprzednia sie zawiera w nowej, to aktualizujemy DP
			Mask prevMask = acceptablePlates[prev].first;

			if((newMask & prevMask) == prevMask){
				if(dp[prev]+1 > dp[plate]){
					dp[plate]     = dp[prev]+1;
					origin[plate] = prev;
				}
			}
		}
	}

	// gdzie jest najlepszy koniec?
	int bestEnd = distance(dp.begin(), max_element(dp.begin(), dp.end()));

	// odtwarzamy wektor od konca
	vector<int> result;
	while(bestEnd != -1){
		result.push_back(acceptablePlates[bestEnd].second);
		bestEnd = origin[bestEnd];
	}

	reverse(result.begin(), result.end());
	return result;
}


int main(){
	vector<PlateData> data = input();
	int N = data.size(); //, M = data[0].dist.size();
	
	// inicjujemy ziarno generatora losowego
	default_random_engine generator(0xCACAFE);
	uniform_int_distribution<int> random_nums(0, N-1);
	
	vector<int> currentResult;

	for(int v = 0; v < N; v++){
		vector<int> newResult = process_data(data, v);
		if(newResult.size() > currentResult.size())
			currentResult = newResult;
	}

	// musimy teraz jedynie posortowac wynik po malejacej sumie odleglosci
	// i wypisac na wyjscie
	sort(currentResult.begin(), currentResult.end(),
			[&data](int st, int nd) -> bool {
				return accumulate(data[st].dist.begin(), data[st].dist.end(), 0) >
				       accumulate(data[nd].dist.begin(), data[nd].dist.end(), 0);
			}
		);

	cout << currentResult.size() << endl;

	cout << currentResult[0] + 1;
	for(int i = 1; i < static_cast<int>(currentResult.size()); i++)
		cout << " " << currentResult[i] + 1;
	cout << endl;

	return 0;
}
