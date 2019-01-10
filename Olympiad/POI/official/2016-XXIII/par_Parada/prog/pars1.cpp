/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Parada                                             *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include<iostream>
#include<vector>

std::vector<int>sa[int(1e6+1)];
int odw[int(1e6+1)];

int res,n,a,b,i;
void dyn(int ve,int re,bool no=false){
	odw[ve]=i;
	re+=sa[ve].size()-2;
	for(auto s:sa[ve]){
		if(odw[s]!=i){
			dyn(s,re,true);
		}
	}
	if(no)
	res=std::max(res,re);
}
int main() { 
	std::ios_base::sync_with_stdio(0);
	std::cin>>n;
	for(i=1;i<n;i++){
		std::cin>>a>>b;
		sa[a].push_back(b);
		sa[b].push_back(a);
	}
	for(i=1;i<=n;i++)
		dyn(i,2);
	std::cout<<res<<std::endl;
}
