/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Zlozonosc czasowa:    O(qn^2.807 log d)                                  *
 *   Opis:                 Rozwiazanie brutalne, nieco przyspieszone          *
 *                         (log d)-krotne mnozenie macierzy algorytmem        *
 *                         Strassena O(n^2.807)                               *
 *****************************************************************************/

#include <stdio.h>
#include <vector>

using namespace std;

typedef long long llong;

// jesli macierz ma wymiary nie wieksze niz MagicCutoff, przerzucamy
// sie na zwykly algorytm
const int MagicCutoff = 13;

class SquareMatrix {
private:
	vector< vector<int> > M;
	int N;
	int Mod;
public:
	SquareMatrix(){
	}
	
	SquareMatrix(int siz, int modulo){
		N = siz;
		Mod = modulo;
		M.reserve(siz);
		for(int i = 0; i < siz; i++)
			M.push_back(vector<int>(siz, 0));
	}
	
	int elem(int r, int c) const {
		return M[r][c];
	}
	
	int& elem(int r, int c){
		return M[r][c];
	}
	
	int size() const {
		return N;
	}
	
	// podmacierz o danym lewym gornym rogu i rozmiarze
	SquareMatrix submatrix(int firstRow, int firstCol, int siz) const {
		SquareMatrix Result(siz,Mod);
		for(int r = 0; r < siz && r+firstRow < N; r++){
			for(int c = 0; c < siz && c+firstCol < N; c++){
				Result.elem(r,c) = elem(r+firstRow, c+firstCol);
			}
		}
		return Result;
	}
	
	SquareMatrix operator+(const SquareMatrix& B) const {
		SquareMatrix Result(N,Mod);
		
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				Result.elem(i,j) = (elem(i,j) + B.elem(i,j)) % Mod;
		return Result;
	}
	
	SquareMatrix operator-(const SquareMatrix& B) const {
		SquareMatrix Result(N,Mod);
		
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				Result.elem(i,j) = (elem(i,j) - B.elem(i,j) + Mod) % Mod;
		return Result;
	}
	
	SquareMatrix& insert(int firstRow, int firstCol, const SquareMatrix& clip){
		int S = clip.size();
		for(int r = 0; r < S && r+firstRow < N; r++){
			for(int c = 0; c < S && c+firstCol < N; c++){
				elem(r+firstRow, c+firstCol) = clip.elem(r,c);
			}
		}
		return *this;
	}
	
	SquareMatrix operator*(const SquareMatrix& B) const {
		SquareMatrix Result(N,Mod);
		
		if(N <= 10){   // zwykly N^3
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					for(int k = 0; k < N; k++)
						Result.elem(i,j) = (Result.elem(i,j) + (llong)elem(i,k) * B.elem(k,j)) % Mod;
			return Result;
		}
		
		// teraz troche magii
		int Half = (N+1)/2;
		SquareMatrix A11 =   submatrix(   0,    0, Half),  // 'cwiartki' macierzy
		             A12 =   submatrix(   0, Half, Half),
		             A21 =   submatrix(Half,    0, Half),
		             A22 =   submatrix(Half, Half, Half),
		             B11 = B.submatrix(   0,    0, Half),
		             B12 = B.submatrix(   0, Half, Half),
		             B21 = B.submatrix(Half,    0, Half),
		             B22 = B.submatrix(Half, Half, Half);
		
		SquareMatrix M1 = (A11+A22)*(B11+B22),
		             M2 = (A21+A22)* B11,
		             M3 =      A11 *(B12-B22),
		             M4 =      A22 *(B21-B11),
		             M5 = (A11+A12)* B22,
		             M6 = (A21-A11)*(B11+B12),
		             M7 = (A12-A22)*(B21+B22);
		
		Result.insert(   0,    0, M1+M4-M5+M7)
		      .insert(   0, Half, M3+M5)
		      .insert(Half,    0, M2+M4)
		      .insert(Half, Half, M1-M2+M3+M6);
		
		return Result;
	}
	
	SquareMatrix power(int K) const {		
		if(K == 0){ // macierz identycznosciowa
			SquareMatrix Result(N, Mod);
			for(int i = 0; i < N; i++)
				 Result.elem(i,i) = 1;
			return Result;
		}
		
		SquareMatrix Result = this->power(K/2);
		Result = Result * Result;
		if(K % 2 == 1)
			Result = Result * *this;
		return Result;
	}
};


int N, M, Mod;
vector< vector<bool> > graph;

void input(){
	scanf("%d%d%d", &N, &M, &Mod);
	graph.reserve(N);
	for(int i = 0; i < N; i++)
		graph.push_back(vector<bool>(N,false));
	
	while(M--){
		int edgeFrom, edgeTo;
		scanf("%d%d", &edgeFrom, &edgeTo);
		edgeFrom--; edgeTo--;
		graph[edgeFrom][edgeTo] = true;
	}
}

int query(){
	int from, to, tm;
	scanf("%d%d%d", &from, &to, &tm);
	from--; to--;
	
	
	SquareMatrix SM(N, Mod);
	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(graph[i][j] && j != from && i != to)
				SM.elem(i, j) = 1;
		}
	}
	
	return SM.power(tm).elem(from, to);
}

int main(){
	input();
	
	int numQueries;
	scanf("%d", &numQueries);
	
	while(numQueries--)
		printf("%d\n", query());
}
