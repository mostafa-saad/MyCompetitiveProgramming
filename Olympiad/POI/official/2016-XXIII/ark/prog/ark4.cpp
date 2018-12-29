/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(k log k)                                         *
 *   Opis:                 rozwiazanie wzorcowe z duza stala z racji seta     *
 *****************************************************************************/


#include <iostream>
#include <set>
int n,m,k,c,xs,ys;
long long result,tmp,ball,x,y;
std::set<long long> poz;
int roz_euk(long long a,long long b,long long& p,long long& q){//Ten kod jest tylko by policzyc q, jak ktos nie zna rozszerzonego algorytmu euklidesa to moze to policzyc jedna prosta petla w O(n+m)
	long long r=0,s=1;
	p=1;q=0;
	long long c,qu,r_t,s_t;
	while(b!=0){
		c=a%b;
		qu=a/b;
		a=b;
		b=c;
		r_t=r;s_t=s;
		r=p-qu*r;
		s=q-qu*s;
		p=r_t;
		q=s_t;
	}
	return a;
}
long long p,q,mod;
long long code(long long w,long long h){
	return (xs-w+(q*m*(h-ys-xs+w))+mod*(m+n))%(mod);//objicza kiedy kulka uderzy w to pole jesli nie bedzie zadnego klocka
}

void sel_poz(int x,int y,bool add=true){//ten kod mozna latwo zoptymalicowac z 16 mozliwosci ktore przegladamy tylko 4 sa dodanewane jako ze kazdy klocek ma tylko 4 miejsca od ktorych da sie odbic(miejsca te zaleza tylko od koloru szchownicy)
	for(int i=x*2;i<x*2+2;i++)
		for(int j=y*2;j<y*2+2;j++)
    {
      int w2[2];
      w2[0]=i; w2[1]=4*int(m)-i-1;
      int h2[2];
      h2[0]=j; h2[1]=4*int(n)-j-1;
      for (int ww=0;ww<2;++ww)
        for (int hh=0;hh<2;++hh)
        {
          int w=w2[ww],h=h2[hh];
					if((xs-w+ys-h)%4==0){
						long long war=code(w,h);
						if(add)
							poz.insert(war);
						else
							poz.erase(war);
					}
        }
    }
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin>>m>>n>>k;
	mod=(long long)(m)*n*4;
	roz_euk(n*4,m*4,p,q);
	ys=0;//pozycja startowa zostawilem tylko dla czytelnosci
	xs=m-1;
	for(int i=0;i<k;i++){
		std::cin>>x>>y;
		--x;--y;
		sel_poz(x,y);
	}
	while(k--){
    std::set<long long>::iterator el=poz.upper_bound(ball);
		if(el==poz.end()){
			el=poz.upper_bound(-1);
			result+=mod;
		}
		tmp= *el;//tmp to klocek w ktory uderzylismy
		result+=tmp-ball;
		x=(mod+xs-tmp)%(4*m);//odczytujemy pozycje kulki
		y=(mod+ys+tmp)%(4*n);
		sel_poz(std::min(x,4*m-1-x)/2,std::min(y,4*n-1-y)/2,false);//niszczymy klocek
		if(tmp%2)
			x=4*m-2-x;//odicie wzgledem pionowej krawedzi
		else
			y=4*n-y;//odbicie wzgledem poziomej krawedzi
		ball=code(x,y);
	}		
	std::cout<<result<<std::endl;
}
