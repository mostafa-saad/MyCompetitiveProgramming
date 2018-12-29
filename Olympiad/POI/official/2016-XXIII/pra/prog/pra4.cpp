/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Pracowity Jas                                      *
 *   Autor:                Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <algorithm>
const int SIZE=1048576;
const int MOD=int(1e9+7);
int tab[SIZE*2];
long long n,pom,wyn,x,kol,wyn2,tmp;
int main(){
	std::ios_base::sync_with_stdio(0);
	std::cin>>n;
	for(int i=0;i<n;i++){
		std::cin>>pom;
		x=pom+SIZE;
		while(x>0){
			tab[x]++;
			x/=2;
		}
		x=pom+SIZE;
		while(x>0){
			if(x%2==0){
				kol+=tab[x];
				x=(x-1)/2;
			}else
			x/=2;
		}
		tmp=wyn2;
		wyn2=(wyn2*(n-i-1)+pom-kol)%MOD;
		wyn=(wyn+wyn2*((n-i+1)/2))%MOD;
		wyn2=(wyn2+tmp)%MOD;
		kol=0;
	}
	std::cout<<wyn<<std::endl;
}

