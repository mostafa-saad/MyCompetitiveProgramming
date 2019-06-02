/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n1*n2)                                           *
 *   Opis:                 rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <iostream>
#include <vector>
int n[2];
int cia[2][15001];
int last[2][15001];
int row[15001];
int equal[15001];


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin>>n[0]>>n[1];
	for(int j=0;j<2;j++)
		for(int i=1;i<=n[j];i++){
			std::cin>>cia[j][i];
			last[j][i]=0;
			for(int k=i-1;k>0;k--){
				if(cia[j][i]==cia[j][k]){
					last[j][i]=k;
					break;
				}
			}
		}
	
	for(int i=1;i<=n[0];i++)
	if(last[0][i]!=0)
	for(int j=1;j<=n[1];j++)
		if(row[j-1]>row[j] || (cia[0][i]==cia[1][j] && last[1][j]!=0 && 
								row[j]==row[last[1][j]-1] && 
								equal[last[1][j]-1]<last[0][i] ))
			row[j]++, equal[j]=i;
		
	std::cout<<row[n[1]]*2<<std::endl;
}
