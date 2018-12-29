/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Tablice kierunkowe                                 *
 *   Zlozonosc czasowa:    O(n^3m)                                            *
 *   Zlozonosc pamieciowa: O(n(n+m))                                          *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         dynamik na konstruowanym jawnie DAG-u              *
 *****************************************************************************/


#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>
#include <numeric>


using namespace std;

const int NumRandom = 50,
          MaxN = 1000,
          MaxM = 200;

typedef vector<bool> Mask;


bool is_contained(const Mask& lhs, const Mask& rhs){
	assert(lhs.size() == rhs.size());
	for(size_t i = 0; i < lhs.size(); i++)
		if(lhs[i] && !rhs[i]) return false;
	return true;
}

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

vector<int> graph[MaxN];
int dp[MaxN], origin[MaxN];
bool vis[MaxN];

void make_longest_path(int v){
	vis[v] = true;
	for(int s: graph[v]){
		if(!vis[s])
			make_longest_path(s);

		if(dp[s] >= dp[v]){
			dp[v]     = 1 + dp[s];
			origin[v] = s;
		}
	}
}

// zwraca maksymalny podzbior tabliczek z wejscia zawierajacy wskazana
// tabliczke
vector<int> process_data(vector<PlateData> input, int selectedPlate){
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
							[](Mask result, int val){
								result.push_back(val); return result;
							}),
					plateno
				);
		}
	}

	// programowanie dynamiczne - najdluzsza sciezka w DAG-u z porzadkiem
	// zawierania masek (w razie rownosci i tak dziala, bo mamy porzadek
	// na numerach tabliczek)
	int numPlates = static_cast<int>(acceptablePlates.size());
	int N = static_cast<int>(input.size());
	fill(dp, dp+N, 1);
	fill(origin, origin+N, -1);
	for(int i = 0; i < N; i++)
		graph[i].clear();
	fill(vis, vis+N, false);

	for(int to = 0; to < numPlates; to++){
		for(int from = 0; from < numPlates; from++){
			Mask prevMask = acceptablePlates[from].first,
			     newMask  = acceptablePlates[to].first;

			if(from == to) continue;
			if(newMask == prevMask){
				// aby nie bylo cykli, porownujemy jeszcze numerki
				if(from < to) { graph[from].push_back(to); }
			} else if(is_contained(newMask, prevMask)) graph[from].push_back(to);
		}
	}

  for (int v = 0; v < numPlates; ++v) {
    if (!vis[v]) {
      make_longest_path(v);
    }
  }

	// gdzie jest najlepszy koniec?
	int bestEnd = distance(dp, max_element(dp, dp+numPlates));
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
