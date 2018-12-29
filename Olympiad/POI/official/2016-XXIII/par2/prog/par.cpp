/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Parada                                             *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include<iostream>
#include<vector>

std::vector<int>sa[int(2e5+2)];
bool odw[int(2e5+2)];

int res,n,a,b;
int dyn(int ve){
	odw[ve]=true;
	int best=0;
	int second_best=0;
	int re;
	for(auto s:sa[ve]){
		if(!odw[s]){
			re=dyn(s);
			if(re>second_best){
				std::swap(re,second_best);
				if(second_best>best)
					std::swap(second_best,best);
				}
		}
	}
	int new_res=second_best+best+sa[ve].size()-2+(second_best==0);
	res=std::max(new_res,res);
	return best+sa[ve].size()-2+(best==0);
}
int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin>>n;
	for(int i=1;i<n;i++){
		std::cin>>a>>b;
		sa[a].push_back(b);
		sa[b].push_back(a);
	}
	dyn(1);
	std::cout<<res<<std::endl;
}
