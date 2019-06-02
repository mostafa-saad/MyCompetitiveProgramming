/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Korale                                             *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n log n + k log k)                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<limits>
#include <functional> 
#include <queue> 
using namespace std;
vector<pair<int,int>> kor;//cost id
vector<int> costs;
struct naszyjnik{
	long long cost;
	int low;
	int biggest;
	int low_in_pref;
	naszyjnik(long long _cost,int _low,int _biggest,int _low_in_pref): cost(_cost),low(_low),biggest(_biggest),low_in_pref(_low_in_pref){};
	bool operator<(const naszyjnik& b) const {return ((cost==b.cost) ? (low>b.low) : (cost>b.cost));}
	bool operator>(const naszyjnik& b) const {return ((cost==b.cost) ? (low<b.low) : (cost<b.cost));}
};

priority_queue<naszyjnik> nasz;
vector<naszyjnik> sor;
int n,k,wyn,ce;
int main(){
	ios_base::sync_with_stdio(false);
	cin>>n>>k;
	
	costs.emplace_back(0);
	for(int i=1;i<=n;i++){
		cin>>ce;
		kor.emplace_back(ce,i);
		costs.emplace_back(ce);
	}
	sort(kor.begin(),kor.end());
	nasz.emplace(kor[0].first,kor[0].second,0,numeric_limits<int>::max());
	sor.emplace_back(0,0,0,0);
	while(k != ++wyn){
		auto pocz=nasz.top();
		sor.emplace_back(pocz);
		nasz.pop();
		if(pocz.biggest+1<int(kor.size())){
			nasz.emplace(pocz.cost+kor[pocz.biggest+1].first,                         min(kor[pocz.biggest+1].second,pocz.low)        , pocz.biggest+1, pocz.low        );
			nasz.emplace(pocz.cost+kor[pocz.biggest+1].first-kor[pocz.biggest].first, min(kor[pocz.biggest+1].second,pocz.low_in_pref), pocz.biggest+1, pocz.low_in_pref);
		}
	}
	k-=1;
	long long cost=sor[k].cost;
	cout<<cost<<endl;
	while(cost){
		cost-=costs[sor[k].low];
		cout<<sor[k].low<<" ";
		k-=lower_bound(sor.begin(),sor.end(),sor[k]                          ,greater<naszyjnik>())-
		   lower_bound(sor.begin(),sor.end(),naszyjnik(cost,sor[k].low+1,0,0),greater<naszyjnik>());
	};
	cout<< endl;
	return 0;
}
