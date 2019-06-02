/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Park wodny                                         *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <bits/stdc++.h>

using namespace std;


const int MaxSide = 1024;        // maksymalny rozmiar planszy
const int NumDirs = 4,           // liczba kierunkow swiata
          DirsR[NumDirs] = {1, 0, -1,  0},   // kierunki po wierszach i kolumnach
          DirsC[NumDirs] = {0, 1,  0, -1};

int side;                        // rozmiar planszy
bool isPool[MaxSide][MaxSide];   // plansza (true, gdy to basen)
int poolId[MaxSide][MaxSide];    // rozklad basenow na planszy (wraz z numerkami);
                                 // baseny numerujemy od 1 wzwyz
vector<int> poolAreas;           // pola basenow

// lista basenow sasiadujacych z danym polem na alejce
vector<int> poolNeighbors[MaxSide][MaxSide];



void input(){
    scanf("%d", &side);
    const char PoolChar = 'B';
            /* AisleChar = 'A'; */

    for(int row = 0; row < side; row++){
        char boardRow[MaxSide];
        scanf("%s", boardRow);

        for(int col = 0; col < side; col++){
            isPool[row][col] = (boardRow[col] == PoolChar);
        }
    }
}


// Czy pole (r,c) jest wewnatrz planszy?
inline bool is_inside_board(int r, int c){
    return (r >= 0 && r < side && c >= 0 && c < side);
}

// Czy pole (r,c) jest basenem?
inline bool is_pool(int r, int c){
    return (is_inside_board(r,c) && isPool[r][c]);
}

// Czy pole (r,c) jest alejka?
inline bool is_aisle(int r, int c){
    return (is_inside_board(r,c) && !isPool[r][c]);
}


// numerowanie basenow; zwraca laczne pole przez nie zajmowane
int enumerate_pools(){
    poolAreas.resize(1);
    int totalArea = 0;
    int totalPools = 0;        // aktualna liczba basenow
    for(int row = 0; row < side; row++){
        for(int col = 0; col < side; col++){
            if(!is_pool(row, col)) continue;   // alejek nie numerujemy
            totalArea++;
            if(is_pool(row-1, col)){           // rozpoczety wczesniejszy basen?
                poolId[row][col] = poolId[row-1][col];
            } else if(is_pool(row, col-1)){
                poolId[row][col] = poolId[row][col-1];
            } else {                           // nowy basen!
                poolAreas.push_back(0);
                totalPools++;
                poolId[row][col] = totalPools;
            }
            poolAreas[poolId[row][col]]++;
        }
    }
    return totalArea;
}


// znajdowanie basenowych sasiadow dla alejek
void find_pool_neighbors(){
    for(int row = 0; row < side; row++){
        for(int col = 0; col < side; col++){
            if(!is_aisle(row, col)) continue;    // sasiedztwa szukamy dla alejek

            for(int dir = 0; dir < NumDirs; dir++){
                int neighRow = row + DirsR[dir], // sasiadujace: wiersz i kolumna
                    neighCol = col + DirsC[dir];
                if(is_pool(neighRow, neighCol)){
                    poolNeighbors[row][col].push_back(poolId[neighRow][neighCol]);
                }
            }
            sort(poolNeighbors[row][col].begin(), poolNeighbors[row][col].end());
        }
    }
}


// proba dodania nowej alejki (uda sie, gdy zbior dotykany nie jest podzbiorem obecnych
// alejek)
bool try_add_aisle(vector<vector<int>>& curAisles, const vector<int>& nextAisle,
                   int curPool){
    for(auto& other : curAisles){
        if(includes(other.begin(), other.end(), nextAisle.begin(), nextAisle.end())){
                return false;
        }
    }
    vector<int> addedAisle;
    for(int v : nextAisle) if(v != curPool) addedAisle.push_back(v);
    curAisles.push_back(addedAisle);
    return true;
}


// laczne pole basenow
int get_total_area(const vector<int>& pools){
    int result = 0;
    for(int pool : pools) result += poolAreas[pool];
    return result;
}



// wynik dla basenu #id, z ktorego wychodza dwa polaczenia; znamy jego gorny
// i lewy bok
int process_pool(int id, int topRow, int leftCol){
    int bottomRow = topRow, rightCol = leftCol;
    while(bottomRow < side-1 && is_pool(bottomRow+1, leftCol)) bottomRow++;
    while(rightCol < side-1  && is_pool(topRow, rightCol+1))   rightCol++;

    // alejki z dostepem do 1/wielu dodatkowych polaczen
    vector<vector<int>> singleAisles, multAisles;
    for(int row = topRow-1; row <= bottomRow+1; row++){
        for(int col = leftCol-1; col <= rightCol+1; col++){
            if(!is_aisle(row, col)) continue;
            bool rowBorder = (row==topRow-1 || row==bottomRow+1),
                 colBorder = (col==leftCol-1 || col==rightCol+1);
            if(!(rowBorder ^ colBorder)) continue;   // pole musi byc na jednym brzegu

            vector<int>& neighbors = poolNeighbors[row][col];
            if(neighbors.size() == 1) continue;
            (neighbors.size()==2 ? singleAisles : multAisles).push_back(neighbors);
        }
    }

    // znajdujemy wszystkie "sensowne" alejki
    vector<vector<int>> feasibleAisles;

    // dodajemy wszystkie wielokrotne
    for(auto& aisle : multAisles) try_add_aisle(feasibleAisles, aisle, id);

    
    // bierzemy wszystkie "pojedyncze" alejki, ktore nie sa zawarte w zadnym
    // wielokrotnym polaczeniu
    vector<int> singleAlone;
    for(auto& single : singleAisles){
        int v = (single[0] == id ? single[1] : single[0]);   // numer laczonego basenu
        bool okay = true;
        for(auto& mult : feasibleAisles){    // jesli ten basen da sie uzyskac w lepszej
                                             // kombinacji, nie ma co nawet robic tej
            if(find(mult.begin(), mult.end(), v) != mult.end()){ okay = false; break;}
        }

        if(okay) singleAlone.push_back(v);
    }

    // znajdujemy dwie *rozne* najlepsze alejki (laczace sie z najwiekszymi *roznymi*
    // basenami)
    int best1 = -1, best2 = -1;
    for(int v : singleAlone){
        if(v == best1 || v == best2) continue;

        if(best1 == -1 || poolAreas[best1] < poolAreas[v]){
            best2 = best1; best1 = v;
        } else if(best2 == -1 || poolAreas[best2] < poolAreas[v]){
            best2 = v;
        }
    }
    if(best1 != -1) feasibleAisles.push_back({best1});
    if(best2 != -1) feasibleAisles.push_back({best2});

    // sprawdzamy kazda istniejaca pare "sensownych" alejek; tego nie moze byc duzo,
    // prawdopodobnie nie wiecej niz 8
    int S = (int)feasibleAisles.size();
    int result = 2 + poolAreas[id];
    for(int fst = 0; fst < S; fst++){
        // tylko ta alejka?
        result = max(result, 2 + poolAreas[id] + get_total_area(feasibleAisles[fst]));

        // ta i inna?
        for(int snd = fst+1; snd < S; snd++){
            vector<int>& A1 = feasibleAisles[fst],
                         A2 = feasibleAisles[snd];
            vector<int> everything;
            set_union(A1.begin(), A1.end(), A2.begin(), A2.end(),
                      back_inserter(everything));
            result = max(result, 2 + poolAreas[id] + get_total_area(everything));
        }
    }
    return result;
}


int process_all_pools(){
    // baseny bedziemy napotykac w kolejnosci rosnacej, wystarczy wiec pamietac
    // tylko numer ostatniego spotkanego basenu
    int lastProcessed = 0, result = 2;
    for(int row = 0; row < side; row++){
        for(int col = 0; col < side; col++){
            if(!is_pool(row, col)) continue;
            int id = poolId[row][col];
            if(id <= lastProcessed) continue;   // juz przetwarzalismy basen

            assert(id == lastProcessed + 1);
            result = max(result, process_pool(id, row, col));
            lastProcessed = id;
        }
    }
    return result;
}



// zamieniamy na baseny pola (r1,c1), (r2,c2) bedace obok siebie; jaki wynik
// uzyskamy?
inline int check_taking(int r1, int c1, int r2, int c2){
    vector<int> pools;
    set_union(poolNeighbors[r1][c1].begin(), poolNeighbors[r1][c1].end(),
              poolNeighbors[r2][c2].begin(), poolNeighbors[r2][c2].end(),
              back_inserter(pools));
    return 2 + get_total_area(pools);
}

// przypadek, w ktorym alejki zamieniane na baseny sasiaduja ze soba bokiem; wtedy
// nie musza oba jednoczesnie dotykac do jednego prostokata
int process_adjacent_alleys(){
    int result = 2;
    for(int row = 0; row < side; row++){
        for(int col = 0; col < side; col++){
            if(!is_aisle(row, col)) continue;

            if(is_aisle(row+1, col)){
                result = max(result, check_taking(row, col, row+1, col));
            }
            if(is_aisle(row, col+1)){
                result = max(result, check_taking(row, col, row, col+1));
            }
        }
    }
    return result;
}


int main(){
    input();
    int area = enumerate_pools();    // znajdujemy baseny

    if(area+2 >= side*side){         // byc moze cala powierzchnie da sie zmienic na
        printf("%d\n", side*side);   // basen?
        return 0;
    }
    assert(side >= 2);

    find_pool_neighbors();             // ogarniamy pobliza basenow
    int result1 = process_all_pools(); // i wiedze wykorzystujemy do policzenia wyniku
    int result2 = process_adjacent_alleys();
    printf("%d\n", max(result1, result2));
    return 0;
}

