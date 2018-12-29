 /*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe wariant 1                   *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define INF 1000000001

using namespace std;

struct patyczek{
	int dl; //d³ugo¶æ
	int kol; //kolor
}_p;
bool operator<(const patyczek &a, const patyczek &b){
	if(a.dl != b.dl)return a.dl > b.dl;
	return a.kol < b.kol;
}

struct delta{ 
	int d; //ró¿nica miêdzy d³ugo¶ci± dwóch kolejnych patyczków
	int k1, k2; //kolory tych patyczków
	int p; //index pierwszego patyczka (po posortowaniu), drugi to bêdzie p+1
}_d;
bool operator<(const delta &a, const delta &b){
	return a.d < b.d;
}
int kolnach(delta a, delta b){ //ile kolorów delty maj± wspólnych
	int ret = 0;
	if(a.k1 == b.k1 || a.k1 == b.k2)++ret;
	if(a.k2 == b.k1 || a.k2 == b.k2)++ret;
	return ret;
}

vector <patyczek> p; //vector trzymaj±cy patyczki
int n, k, m; //n - ilo¶æ patyczków, k - ilo¶æ kolorów, m - ilo¶æ patyczków w kolorze
delta d[3]; //musimy pamiêtaæ 3 delty, ¿eby mieæ najlepszych kandydatów dla ka¿dego koloru
char ostkol; //ostatni kolor

int main(){
	//Wczytywanie danych
	ios_base::sync_with_stdio(0);
	cin >> k;
	for(int i = 0;i < k; ++i){
		cin >> m;
		n += m;
		_p.kol = i + 1;
		for(int j = 0; j < m; ++j){
			cin >> _p.dl;
			p.push_back(_p);
		}
	}
	sort(p.begin(), p.end()); //sortujemy patyczki po d³ugo¶ci
	d[0].d = d[1].d = d[2].d = INF; //inicjalizujemy pocz±tkowe warto¶ci dla delt
	d[0].k1 = 1; d[0].k2 = 2;
	d[1].k1 = 1; d[1].k2 = 3;
	d[2].k1 = 2; d[2].k2 = 3;
	ostkol = p[0].kol;
	//Algorytm w³a¶ciwy
	for(int i = 1; i < n; ++i){
		//Sprawdzenie, czy mo¿na zbudowaæ trójk±t
		_d.k1 = p[i].kol; //uzupe³niamy kolor w aktualnej delcie
		_d.k2 = -1; //drugi kolor ustawiamy na razie tak, ¿eby nie przeszkadza³
		for(int j = 0; j < 3; ++j){
			if(kolnach(d[j], _d) == 0 && d[j].d < p[i].dl){ //ró¿nica by³a mniejsza ni¿ d³ aktualnego i kolory pasuj±
				int ind = d[j].p;
				cout << (int)p[i].kol << " " << p[i].dl << " ";
				cout << (int)p[ind].kol << " " << p[ind].dl << " ";
				++ind;
				cout << (int)p[ind].kol << " " << p[ind].dl << "\n";
				return 0;
			}
		}
		//Poprawianie delt
		if(p[i].kol == ostkol)continue;
		ostkol = p[i].kol; 
		int in = 0;   //ile nachodzi - ¿eby delty by³y dobrze wybrane musimy zamieniæ z tak±, w której najwiêcej jest wspólnych
		int bd = 0; //dalej musimy wybraæ tak±, której d jest jak najwiêksze, bo je minimalizujemy
		int zd = -1; //a to index wybranej delty do zamiany lub -1, gdy nie op³aca siê zamieniaæ
		_d.k2 = p[i - 1].kol; //uzupe³niamy pozosta³e pola aktualnej delty
		_d.d = (p[i - 1].dl - p[i].dl);
		_d.p = i - 1;
		for(int j = 0; j < 3; ++j){ //szukamy delty z któr± mo¿emy i op³aca nam siê zamieniæ aktualn± deltê
			if(in < kolnach(d[j], _d)){ //je¶li wiêcej kolorów nachodzi ni¿ poprzednio, to anulujemy wybór
				zd = -1;
				bd = 0;
				in = kolnach(d[j], _d);
			}
			if(in <= kolnach(d[j], _d) && bd <= d[j].d){ //je¶li op³aca siê i mo¿emy zamieniæ z dan± delt±, to j± wybieramy
				in = kolnach(d[j], _d);
				bd = d[j].d;
				zd = j;
			}
		}
		if(zd != -1 && bd > _d.d)d[zd] = _d; //je¶li ostatecznie op³aca siê zamieniæ, to zamieniamy
	}
	cout << "NIE\n"; //je¶li nie zakoñczyli¶my wcze¶niej programu, to znaczy, ¿e nie mo¿na zbudowaæ trójk±tu
	return 0;
} 
