/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Klubowicze                                         *
 *   Autor:                Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n * 2^n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
int n,a,b,oso;
std::vector<std::pair<int,int> > zwi;

std::vector<int> sa,pa,spe,spe_k;
int last_on(int i){
	return (1<<(__builtin_ctz(i)));
}
int spe_p=0;
void dziel(std::vector<std::pair<int,int>> pary){
	spe_p++;
	if(pary.size()==1){
		a=pary.front().first;
		b=pary.front().second;
		sa[a]=b;
		sa[b]=a;
		return;
	}
	int split = last_on(pary.front().first ^ pary.front().second);
	
	std::vector<std::pair<int ,int > > cie, ncie , gru1, gru2;
	
	auto spli=[&](std::pair<int,int> par){return ((par.first^par.second) & split) != 0;};
	int dzie=std::count_if (pary.begin(), pary.end(), spli);
	cie.resize(dzie);
	ncie.resize(pary.size()-dzie);
	gru1.resize(ncie.size()/2);
	gru2.resize(ncie.size()/2);
	std::partition_copy(pary.begin(),pary.end(),cie.begin(),ncie.begin(),spli);
	std::partition_copy(ncie.begin(),ncie.end(),gru1.begin(),gru2.begin(),[&](std::pair<int,int> par){return ((par.first | par.second) & split) == 0;});
	
	std::vector<std::pair<int,int> >pam;
	
	std::vector<std::pair<int,int> > list_spec;
	int ost= (((cie.back().first & split) == 0) ? cie.back().first : cie.back().second);
	for(std::size_t i=0;i<cie.size();i++){
		a=cie[i].first;
		b=cie[i].second;
		if(a & split){
			std::swap(a,b);
		}
		if(i%2==0){	
			pam.push_back(std::make_pair(a,pa[a]));
			pam.push_back(std::make_pair(ost,pa[ost]));
			pa[a]=ost;
			pa[ost]=a;
			gru1.push_back(std::make_pair(a,ost));
		}
		ost=a;
	}
	dziel(gru1);

	std::vector<int> cykl;
	int poz=ost;
	do{
		cykl.push_back(poz);
		poz=sa[poz];
		cykl.push_back(poz);
		poz=pa[poz];
	}while(poz!=ost);
	
	for(auto x:pam){
		pa[x.first]=x.second;
	}
	pam.clear();
	bool tryb=true;
	ost=pa[ost];
	for (std::size_t j=1;j<cykl.size();j++){
		int i=cykl[j];
		if((pa[i]^i) & split){
			if(tryb){
				pam.push_back(std::make_pair(pa[i],i));
				pam.push_back(std::make_pair(ost,pa[ost]));
				pa[pa[i]]=ost;
				pa[ost]=pa[i];
				gru2.push_back(std::make_pair(pa[i],ost));
			}else
			ost=pa[i];
			tryb=!tryb;
		}
	}
	dziel(gru2);
	for(auto x:pam){
		pa[x.first]=x.second;
	}
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL); 
	std::cin>>n;
	oso=(1<<n);
	sa.resize(oso);
	pa.resize(oso);
	spe.resize(oso);
	spe_k.resize(oso);
	for(int i=0;i<oso;i+=2){
		std::cin>>a>>b;
		pa[a]=b;
		pa[b]=a;
		zwi.push_back(std::make_pair(a,b));
	}
	dziel(zwi);
	int poz=0;
	do{
		std::cout<<poz<<" ";
		poz=pa[poz];
		std::cout<<poz<<" ";
		poz=sa[poz];
	}while(poz!=0);
		
}
