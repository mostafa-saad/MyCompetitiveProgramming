/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Mastermind II                                  *
 *   Plik:                mas2.cpp                                       *
 *   Autor:               Micha³ Adamaszek                               *
 *************************************************************************/

/* 
   Dzialanie: Algorytm generuje wszystkie wariacje bez powtorzen zbioru 1..U_MAX
              i na biezaco sprawdza ich zgodnosc z ukladami z wejscia.
   Usprawnienia: Sprawdzanie czy jest sens przedluzania niepelnego ukladu
		 (heurystyka nadmiernej zgodnosci), wypisywanie wyniku 
		 bezposrednio po znalezieniu.
*/

#include <iostream>

#define min(a,b) ((a)<(b)?(a):(b))

#define U_MAX 9
#define N_MAX 9
#define L_MAX 9
#define BRAK -1

typedef int ElemCiagu;

ElemCiagu ciagi[N_MAX][L_MAX]; //Kolejne ciagi

bool poz[N_MAX][U_MAX];	       //poz[i][j] jesli j+1 wystepuje w i-tym ciagu
int A[N_MAX], B[N_MAX];

ElemCiagu znal[L_MAX];	       //Tymczasowe rozwiazanie i jego parametry
bool uzyte[U_MAX];
int sumA[N_MAX], sumB[N_MAX];

int u,n,l;

/***************************************************************************/
//Inicjalizacja struktur danych
void init() {
    int i,j;
    for(i=0;i<u;i++) for(j=0;j<U_MAX;j++)
	poz[i][j]=false;
    for(i=0;i<U_MAX;i++) uzyte[i]=false;
    for(i=0;i<n;i++) sumA[i]=sumB[i]=0;
}

//Wczytanie danych
void wczytaj() {
    int i,j;
    
    cin >> u;
    n=l=u;
    init();
        
    for(i=0;i<n;i++) {
	cin >> A[i] >> B[i];
	for(j=0;j<l;j++) {
	    cin >> ciagi[i][j];
	    poz[i][ciagi[i][j]-1]=true;
	}
    }

}

//Sprawdzanie czy znalezione rozwiazanie jest poprawne
bool correct() {
    int i;

    for(i=0;i<n;i++) 
	if (sumA[i]!=A[i] || sumB[i]!=B[i]) return false;

    return true;
}
	
//Funkcja rekurencyjna poszerzajaca rozwiazanie
//Zwraca true jesli rozwiazanie zostalo znalezione
bool solve(int depth) {
    int i,j;
    bool zaDuzo;
        
    if (depth==l) return correct(); 

    //Poszerzamy rozwiazanie o kolejne wolne liczby
    for(i=0;i<U_MAX;i++) if (!uzyte[i]) {
	    znal[depth]=i+1;
	    zaDuzo=false;
	    
	    for(j=0;j<n;j++) { 
		//Aktualizujemy tymczasowa sume zgodnosci dla kazdego ukladu
		if (znal[depth]==ciagi[j][depth]) sumA[j]+=znal[depth];
	        else if (poz[j][znal[depth]-1]) sumB[j]+=znal[depth];
		//Heurystyka zbyt duzej zgodnosci
		if (sumA[j]>A[j] || sumB[j]>B[j]) zaDuzo=true;
	    }
	    
	    //Wywolanie rekurencyjne
	    if (!zaDuzo) {
		    uzyte[i]=true;
			if (solve(depth+1)) return true;
		    uzyte[i]=false;
	    }
	    
	    for(j=0;j<n;j++) { 
		//Odaktualniamy z powrotem
		if (znal[depth]==ciagi[j][depth]) sumA[j]-=znal[depth];
	        else if (poz[j][znal[depth]-1]) sumB[j]-=znal[depth];
	    }
	    
    }
    
    return false;
}


//Wypisywanie wyniku
void wypisz() {
    int i;
    for(i=0;i<l-1;i++) cout << znal[i] << " ";
    cout << znal[l-1] << "\n";
}

//Program MAS
int main() {
    wczytaj();
    
    if (solve(0)) wypisz();
    else cerr << "Brak rozwiazania !!!\n";
    
    return 0;
}
