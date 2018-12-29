/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Lasuchy                                            *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 rozwiazanie wolne                                  *
 *****************************************************************************/

#include <vector>
#include <iostream>
std::vector<int> torty;
int n,pom;
bool zmien(std::vector<int> &wynik,int poz){
        int next=poz%n+1;
        int prew=(poz+n-2)%n+1;
        int war_next=torty[next]*(1+(wynik[next]!=next));
        int war_prew=torty[poz]*(1+(wynik[prew]==prew));
        if(war_next<war_prew && wynik[poz]!=poz){
            wynik[poz]=poz;
            return true;
        }
        return false;
}
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin>>n;
    std::vector<int> wynik(n+1);
    torty.push_back(-1);
    for(int i=1;i<=n;i++){
        std::cin>>pom;
        torty.push_back(pom);
        wynik[i]=i%n+1;
    }
    bool zm;
    do{
        zm=false;
        for(int i=1;i<=n;i++){
            if(zmien(wynik,i))
                zm=true;
        }
    }while(zm);
    for(int i=1;i<=n;i++){
        std::cout<<wynik[i]<<" ";
    }
    std::cout<<"\n";
    return 0;
}

