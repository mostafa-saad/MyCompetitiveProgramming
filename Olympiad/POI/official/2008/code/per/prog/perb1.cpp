/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     perb1.cpp                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie zakladajace, ze liczba m z wejscia jest       *
 *             pierwsza.                                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


#define MAX_N 300000

int n,m;		// liczby z tresci zadania
int T[MAX_N];		// permutacja z zadania
int najw;		// najwiekszy element w permutacji
int h;			// wysokosc drzewa licznikowego
int ilosc[1048601];	// wezly drzewa licznikowego



// rozszerzony algorytm Euklidesa
// dostajac na wejsciu liczby a oraz b
// zwraca trojke liczb takich, ze a*x+b*y=NWD(x,y)
inline void NWD(int a, int b, long long &x, long long &y, int &d)
{
	if (!b)
	{
		x=a,y=0;
		d=a;
	}
	else
	{
		long long x1,y1;
		int d1;
		NWD(b,a%b,x1,y1,d1);
		x=y1;
		y=x1-y1*(a/b);
		d=d1;
	}
}


// funkcja obliczajaca odwrotnosc pewnej liczby s modulo t
// na wejsciu musi byc spelniony warunek NWD(s,t)=1
inline int odwrotnosc(int s, int t)
{
	long long x,y;
	int d;
	NWD(s,t,x,y,d);
	return (int)((x%t+t)%t);
}


// fukcja ktora buduje pelne statyczne drzewo licznikowe
// najw - najwiekszy element permutacji T
// h    - wysokosc drzewa
inline void buduj_drzewo()
{
	najw=*max_element(T,T+n);

	// aby wygodnie korzystalo sie z drzewa
	// potrzebujemy aby mialo conajmniej najw+1 lisci
	// ktore kolejno beda odpowiadac liczbom 0,..,najw
	for(h=0; (1<<h)<najw+1; h++);

	// teraz liscie drzewa maja w tablicy numery 2^h,..,2^(h+1)-1
	int pom=(1<<h);

	for(int i=0; i<n; i++)
		ilosc[pom+T[i]]++;
	for(int i=pom-1; i>0; i--)
		ilosc[i]=ilosc[2*i]+ilosc[2*i+1];
}


// funkcja modyfikujaca drzewo licznikowe
// wstaw(x,ile) zmienia ilosc elementow x o ile
inline void wstaw(int x, int ile)
{
	int i=(1<<h)+x;
	ilosc[i]+=ile;i/=2;
	while (i)
	{
		ilosc[i]=ilosc[2*i]+ilosc[2*i+1];
		i/=2;
	}
}


// fukcja zwracajaca ilosc elementow mniejszych niz x
inline int mniejsze(int x)
{
	int i=(1<<h)+x,res=0;
	while (i>1)
	{
		if (i%2)
			res+=ilosc[i-1];
		i/=2;
	}
	return res;
}


// funkcja wykonujaca szybkie potegowanie
// dostajac na wejsciu x,n,m, oblicza x^n mod m
inline int potega(int x, int n, int m)
{
	long long res=1LL,akt=(long long)x;
	while (n)
	{
		if (n%2)
		{
			res=(res*akt)%m;
			n--;
		}
		akt=(akt*akt)%m;
		n/=2;
	}
	return (int)res;
}


// funkcje do obslugi naszej reprezentacji liczb
// 0) funkcja wyluskujaca wynik
// 1) funkcja mnozaca przez int
// 2) funkcja dzielaca przez int
inline int wartosc(pair<int,int> res)
{
	if (res.first)
		return 0;
	return res.second;
}


inline pair<int,int> pomnoz(pair<int,int> res, int x)
{
	while (x%m==0)
		res.first++,x/=m;
	res.second=((long long)res.second)*((long long)x)%m;
	return res;
}


inline pair<int,int> podziel(pair<int,int> res, int x)
{
	while (x%m==0)
		res.first--,x/=m;
	res.second=((long long)res.second)*((long long)odwrotnosc(x,m))%m;
	return res;
}


// funkcja obliczajaca SO i zwracajaca wynik w naszej reprezentacji
// gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
// oraz S0=(n-1)!/[l1!*...*lnajw!]
inline pair<int,int> oblicz_S0()
{
	pair<int,int> res=make_pair(0,1);
	for(int i=2; i<n; i++)
		res=pomnoz(res,i);

	int pom=(1<<h);
	for(int i=1; i<=najw; i++)
		for(int j=2; j<=ilosc[pom+i]; j++)
			res=podziel(res,j);

	return res;
}


// funkcja obliczajaca wynik - po dokladny sposob dzialania
// odsylam do opracowania
inline int oblicz_wynik()
{
	pair<int,int> temp;
	int ile,res=0;

	ile=mniejsze(T[0]);
	temp=oblicz_S0();
	if (ile!=0)
	{
		temp=pomnoz(temp,ile);
		res=wartosc(temp);
		temp=podziel(temp,ile);
	}

	for(int i=1; i<n-1; i++)
	{
		temp=pomnoz(temp,ilosc[(1<<h)+T[i-1]]);
		temp=podziel(temp,n-i);

		wstaw(T[i-1],-1);
		ile=mniejsze(T[i]);
		if (!ile)
			continue;

		temp=pomnoz(temp,ile);
		res+=(int)(wartosc(temp));
		res%=m;
		temp=podziel(temp,ile);
	}

	return (res+1)%m;
}



int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0; i<n; i++)
		scanf("%d",T+i);

	buduj_drzewo();

	int res=oblicz_wynik();
	printf("%d\n",res);

	return 0;
}

