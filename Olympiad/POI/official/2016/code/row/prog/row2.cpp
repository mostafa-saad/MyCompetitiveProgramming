/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Rownowazne programy                                *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(nk)                                              *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <algorithm>
#include <vector>
#include <iostream>
int n,m,k,a,b,x;
std::vector<int>nap;
std::vector<int> nieprze[1001];
std::vector<int> licz(1001);
int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin>>n>>k>>m;
	for(int i=0;i<m;i++){
		std::cin>>a>>b;
		nieprze[a].push_back(b);
		nieprze[b].push_back(a);
		}
	for(int i=0;i<k;i++)
		sort(nieprze[i].begin(),nieprze[i].end());
	long long c_sum=0;
	for(int na=0;na<2;na++){
		for(int i=0;i<1001;i++)
			licz[i]=0;
		for(int i=0;i<n;i++){
			std::cin>>x;
			int ile=0;
			for(auto j:nieprze[x])
				ile+=licz[j];
			c_sum+=(ile+42)*x*(x+3);
			licz[x]++;
		}
		c_sum=-c_sum;
	}
	std::cout<<(c_sum?"NIE":"TAK")<<std::endl;
	
}
