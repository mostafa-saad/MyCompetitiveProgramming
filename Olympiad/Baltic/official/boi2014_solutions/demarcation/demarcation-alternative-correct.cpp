/* Rozwiazanie wzorcowe do zadania Demarkacja
 * To rozwiazanie podaje w pierwszej kolejnosci odcinki poziome
 * Autor: Marek Sommer
 */
#include <cstdio>
#include <algorithm>

typedef long long int ll;

// wartosci bezwzgledne
inline int bez(int x) { return x<0?-x:x; }
inline ll bez(ll x) { return x<0?-x:x; }

// minimum/maksimum
inline int min(int a,int b) { return a<b?a:b; }
inline int max(int a,int b) { return a<b?b:a; }

// czy punkt nalezy do przedzialu domknietego [min(p,k),max(p,k)]
inline bool w_przedziale(int p,int k,int x)
{
  if(p>k) return w_przedziale(k,p,x);
  return p <= x && x <= k;
}

// iloczyn_wektorowy
inline ll ilwek(int ax,int ay,int bx,int by) { return static_cast<ll>(ax)*by-static_cast<ll>(ay)*bx; }

// element listy wierzcholkow wielokata
struct wielokat
{
	wielokat *nas; // wskaznik na nastepny wierzcholek wielokata
	wielokat *pop; // wskaznik na poprzedni wierzcholek wielokata
	int x,y; // wspolrzdne wierzcholka

	// dodaje nowy wierzcholek, za aktualnym
	wielokat *dodaj_za(int _x,int _y)
	{
		wielokat *wie=new wielokat;
		wie->x=_x; wie->y=_y;
		wie->pop=this;
		wie->nas=this->nas;
		this->nas->pop=wie;
		this->nas=wie;
		return wie;
	}

	// usuwa dany wierzcholek
	// !!! nie wywolue delete !!!
	void usun()
	{
		this->nas->pop = this->pop;
		this->pop->nas = this->nas;
	}

	// dodaje nowy wierzcholek przed aktualnym
	wielokat *dodaj_przed(int _x,int _y) { return this->pop->dodaj_za(_x,_y); }

	// cztery ponizsze funkcje stwierdzaja, czy krawedz za/przed tym wierzcholkiem jest pionowa/pozioma
	bool nas_poz() { return (this->y == this->nas->y); }
	bool nas_pio() { return (this->x == this->nas->x); }
	bool pop_poz() { return this->pop->nas_poz(); }
	bool pop_pio() { return this->pop->nas_pio(); }

	// funkcje, ktore stwierdzaja, czy nastepny/poprzedni wierzcholek ma wporzedna wieksza (1), czy mniejsza (-1)
	int nas_znak()
	{
		if(nas_poz()) return ((this->x)<(this->nas->x))?1:-1;
		else return ((this->y)<(this->nas->y))?1:-1;
	}
	int pop_znak() { return -(this->pop->nas_znak()); }

	// dlugosc krawedzi za/przed aktualnym wierzcholkiem
	int nas_odl() { return bez((this->x)-(this->nas->x))+bez((this->y)-(this->nas->y)); }
	int pop_odl() { return this->pop->nas_odl(); }

	// pole prostokata miedzy nastepna/poprzednia krawedzia, a osia x
	// to pole ma byc skierowane!
	ll nas_pol() { return static_cast<ll>((this->nas->x)-(this->x))*(this->y); }
	ll pop_pol() { return this->pop->nas_pol(); }
};

int n; // liczba wierzcholkow wielokata
ll obwod; // obwod wielokata
ll obw; // polowa obowdu wielokata
ll pole; // pole wielokata !!! pole jest skierowane !!!
ll pol; // polowa pola wielokata !!! pole jest skierowane !!!
wielokat *poc; // wskaznik na pierwszy wierzcholek wielokata

// Funkcja do przesuwania wskaznika do odleglosci rownej polowie obwodu
//		k=wskaznik, ktory nalezy przesunac
//		odl=suma dlugosci odcinkow miedzy wskaznikami
void przesun(wielokat * & k,ll &odl,ll &po)
{
	while(odl+(k->nas_odl())<=obw)
	{
		odl+=k->nas_odl();
		po+=k->nas_pol();
		k=k->nas;
	}
}

// Chodzenie dwoma wskaznikami po obwodzie i tworzenie wierzcholkow na krawedziach
// Tworzone sa takie wierzcholki, ktore sa w odleglosci polowy obwodu od jakiegos innego wierzcholka
void dodaj_wierzcholki()
{
	wielokat *prz=poc;
	ll odl=0LL;
	ll po; // zmienna nieuzywana
	wielokat *wsk=poc;
	do
	{
		przesun(prz,odl,po);
		if(odl!=obw)
		{
			if(prz->nas_poz()) prz=prz->dodaj_za((prz->x)+(obw-odl)*(prz->nas_znak()),prz->y);
			else prz=prz->dodaj_za(prz->x,(prz->y)+(obw-odl)*(prz->nas_znak()));
			odl=obw;
		}
		odl-=wsk->nas_odl();
		wsk=wsk->nas;
	}
	while(wsk!=poc);
}

// drzewo przedzialowe z operacjami:
//   - dodaj wartosc w punkcie
//   - odczytaj sume wartosci z przedzialu
int drzewo[2100005];
int n2; // rozmiar drzewa (liczba lisci, indeksowanych od 0 do (n2-1))
int drz_skal[1000005]; // mozliwe pozycje w drzewie - do skalowania ukladu wspolrzednych
int drz_skal_n; // liczba wartosci w tablicy drz_skal

// funkcja, ktora zwraca indeks wartosci w tablicy drz_skal:
int drz_skal_pozycja(int w)
{
	return static_cast<int>(std::lower_bound(drz_skal,drz_skal+drz_skal_n,w)-drz_skal);
}

// funkcja, ktora dodaje wartosc w punkcie
void dodaj(int x,int w)
{
	x=n2+drz_skal_pozycja(x);
	while(x)
	{
		drzewo[x]+=w;
		x/=2;
	}
}

// funkcja, ktora odczytuje sume wartosci z przedzialu (a,b) - !!! bez punktow a i b !!!
int suma(int a,int b)
{
	a=n2+drz_skal_pozycja(a);
	b=n2+drz_skal_pozycja(b);
	if(a+1>=b) return 0; // przedzial nie zawiera punktow calkowitych
	a++; b--; // teraz szukam na przedziale [a,b] - wlacznie
	int wynik=drzewo[a];
	if(a!=b) wynik+=drzewo[b];
	while((a/2)!=(b/2))
	{
		if(a%2==0) wynik+=drzewo[a+1];
		if(b%2==1) wynik+=drzewo[b-1];
		a/=2;
		b/=2;
	}
	return wynik;
}

// struktura opisujaca zdarzenie, podczas zamiatania krawedzi wielokota,
// w poszukiwaniu przeciec potencjalnych odcinkow z bokami figury
struct zdarzenie
{
	int x; // wspolrzedna x zdarzenia
	int a,b; // oba te parametry przechowuja inne informacje w zaleznosci
	// od tego, co to jest za typ zdarzenia
	// jesli zdarzeniem jest poczatek poziomego odcinka (krawedzi wielokata),
	//  to a jest wspolrzedna y tego odcinka, natomiast b= -1
	// jesli zdarzeniem jest koniec poziomego odcinka (krawedzi wielokata),
	//  to a jest wspolrzedna y tego odcinka, natomiast b= -2
	// jesli zdarzeniem jest pionowy odcinek do sprawdzenia,
	//  to a jest mniejsza wsporzedna y, natomiast b jest wieksza wspolrzedna y tego odcinka
};
zdarzenie make_zda(int x,int a,int b) { zdarzenie z; z.x=x; z.a=a; z.b=b; return z; }

bool porownanie_zdarzen(zdarzenie a,zdarzenie b)
{
	// zdarzenia sa sortowane przede wszystkim po wspolrzednej x
	// jesli jest rowna, to najpierw poczatki odcinkow, potem pionowe odcinki, a na koncu konce odcinkow poziomych
	if(a.x==b.x)
	{
		if(b.b== -1) return false;
		if(a.b== -1) return true;
		if(a.b== -2) return false;
		if(b.b== -2) return true;
		return false;
	}
	return a.x<b.x;
}

// tablica ze zdarzeniami
zdarzenie zda[1000005]; // potrzebny jest az milion zdarzen
int z; // liczba zdarzen w tablicy zda

// funkcja probuje wybrac poziomy odcinek miedzy wierzcholkami p i k,
// przy zalozeniu, ze sa w dobrej odleglosci od siebie (polowa obowdu)
// stara sie tez zachowac poprawne pole
// jesli p i k maja rozne wspolrzedne x, to wybiera jakis odcinek pomiedzy nimi tak,
// aby obwod, pole i przynaleznosc koncow odcinka do wielokata sie zgadzaly
void sprobuj_odcinek_miedzy(wielokat *p,wielokat *k,ll po)
{
	int d=bez((p->x)-(k->x)); // d = odleglosc (na osi x) miedzy wierzcholkami p i k
	if(d==0 && po==pol)
	{
		zda[z++]=make_zda(p->x,min(p->y,k->y),max(p->y,k->y));
		return;
	}
	if(d%2==1) return;
	if(!(p->nas_poz()) || !(k->nas_poz())) return; // oba nastepne odcinki musza byc poziome
	d/=2;
	int px,kx; // wspolrzedne przesunietych wierzcholkow p i k o odleglosc d w strone zgodna z lista wierzcholkow
	px = (p->x) + (p->nas_znak())*d;
	kx = (k->x) + (k->nas_znak())*d;
	if(px!=kx) return; // czy ten punkt da sie w ogole uzyskac
  if(!w_przedziale(p->x,p->nas->x,px) || !w_przedziale(k->x,k->nas->x,kx)) return; // punkty leza poza odcinkami
	if((po-static_cast<ll>(px-(p->x))*(p->y)+static_cast<ll>(kx-(k->x))*(k->y))!=pol) return; // pola musza sie zgadzac
	zda[z++]=make_zda(px,min(p->y,k->y),max(p->y,k->y));
}

// szukaj_pio() szuka pionowego odcinka podzialu wielokata na dwie czesci o rownym obwodzie i rownym polu
// jesli  taki istnieje, to jego wspolrzedne zapisuje w ponizszych zmiennych
// Jesli pionowy odcinek podzialu istnieje, to funkcja zwraca tez true,
// w przeciwnym wypadku zwraca false
int wyn_x1,wyn_x2,wyn_y1,wyn_y2;
bool szukaj_pio()
{
	z=0; // czyszczenie tablicy zdarzen
	wielokat *p = poc; // ustalony wskaznik
	wielokat *k = poc; // wskaznik, ktory sie porusza
	ll odl=0LL; // obwod fragmentu wielokata od p do k
	ll po=0LL; // pole fragmentu wielokata od p do k
	while(true) // petla jest przerywana, kiedy drugi wskaznik (k) przejdzie na poczatek wielokata
	{
		przesun(k,odl,po);
		if(k==poc) break;
		sprobuj_odcinek_miedzy(p,k,po);
		p=p->nas;
		odl-=p->pop_odl();
		po-=p->pop_pol();
	}

	// dodawanie poziomych krawedzi wielokata do kolejki zdarzen
	// oraz poszukiwanie mozliwych wartosci y do drzewa przedzialowego
	drz_skal_n=0;
	p=poc;
	do
	{
		if(p->nas_poz())
			zda[z++]=make_zda(p->x,p->y,(p->nas_znak()==1)?(-1):(-2));
		if(p->pop_poz())
			zda[z++]=make_zda(p->x,p->y,(p->pop_znak()==1)?(-1):(-2));
		drz_skal[drz_skal_n++]=(p->y);
		p=p->nas;
	}
	while(p!=poc);

	// sortowanie zdarzen
	std::sort(zda,zda+z,porownanie_zdarzen);

	// inicjalizacja drzewa przedzialowego
	std::sort(drz_skal,drz_skal+drz_skal_n);
	drz_skal_n=static_cast<int>(std::unique(drz_skal,drz_skal+drz_skal_n)-drz_skal);
	n2=1;
	while(n2<drz_skal_n) n2*=2;
	for(int i=1;i<(n2*2);i++) drzewo[i]=0;

	// przechodzenie kolejnych zdarzen
	for(int i=0;i<z;i++)
	{
		if(zda[i].b== -1) // poczatek odcinka
		{
			dodaj(zda[i].a,1);
		}
		else if(zda[i].b== -2) // koniec odcinka
		{
			dodaj(zda[i].a,-1);
		}
		else // pionowy odcinek
		{
			if(suma(zda[i].a,zda[i].b)==0) // odcinek pionowy nie przecina zadnego odcinka poziomego
			{
				wyn_x1=wyn_x2=zda[i].x;
				wyn_y1=zda[i].a;
				wyn_y2=zda[i].b;
				return true;
			}
		}
	}
	return false;
}

// funkcja, ktora znajduje wierzcholek wielokata, o wspolrzednych (x,y)
// jesli taki nie istnieje, to znajduje wierzcholek, po ktorym nastepuje krawedz zawierajaca ten punkt
wielokat *wierzcholek_ze_wspolrzednych(int x,int y)
{
	wielokat *p=poc;
	while(true)
	{
		if((p->x)==x && (p->y)==y) break;
		if(p->nas_poz() && (p->y)==y && bez(x-(p->x))<(p->nas_odl()) && (x-(p->x))*(p->nas_znak())>0) break;
		if(p->nas_pio() && (p->x)==x && bez(y-(p->y))<(p->nas_odl()) && (y-(p->y))*(p->nas_znak())>0) break;
		p=p->nas;
	}
	return p;
}

// zamien_wielokat_na_slowo zamienia wielokat w postaci listy wierzcholkow
// na ciag liczb, oznaczajacych:
//    -1              -- kat 90 stopni
//    -2              -- kat -90 stopni
//    dodatnia liczba -- dlugosc boku
// przy czym w tym ciagu znajduja sie na przemian liczby dodatnie i ujemne
// ciag zaczyna sie liczba ujemna i konczy dodatnia
// wartoscia zwracana jest dlugosc ciagu
int zamien_wielokat_na_slowo(wielokat *w,int *tab)
{
	int dlugosc=0;
	while((w->nas_poz()) == (w->pop_poz())) w=w->nas;
	wielokat *wsk=w;
	do
	{
		if((wsk->nas_poz()) == (wsk->pop_poz())) tab[dlugosc]+=wsk->nas_odl();
		else
		{
			ll iloczyn_wektorowy=ilwek((wsk->x)-(wsk->pop->x),(wsk->y)-(wsk->pop->y),(wsk->nas->x)-(wsk->x),(wsk->nas->y)-(wsk->y));
			if(iloczyn_wektorowy<0) tab[++dlugosc]= -1;
			else tab[++dlugosc]= -2;
			tab[++dlugosc]=wsk->nas_odl();
		}
		wsk=wsk->nas;
	}
	while(wsk!=w);
	return dlugosc;
}

// znajdz_wzorzec szuka wzorca wzo (o dlugosci dw) w tekscie tek (o dlugosci dt)
// jesli znajdzie, to zwraca true, jesli nie znajdzie to zwraca false
int pref[1000005]; // tablica prefiksowa, uzywana przez znajdz_wzorzec
bool znajdz_wzorzec(int dw,int *wzo,int dt,int *tek)
{
	pref[0]= -1;
	for(int i=1;i<=dw;i++)
	{
		pref[i]=pref[i-1];
		while(pref[i]!= -1 && wzo[pref[i]+1]!=wzo[i]) pref[i]=pref[pref[i]];
		pref[i]++;
	}
	int d=0;
	for(int i=1;i<=dt;i++)
	{
		while(d!= -1 && wzo[d+1]!=tek[i]) d=pref[d];
		d++;
		if(d==dw) return true;
	}
	return false;
}

// czy_przystajace stwierdza, czy wielokaty opisane slowami s1 i s2 sa przystajace
bool czy_przystajace(int dlugosc,int *s1,int *s2)
{
	int d2=dlugosc*2;
	for(int i=1;i<=dlugosc;i++) s2[dlugosc+i]=s2[i];
	if(znajdz_wzorzec(dlugosc,s1,d2,s2)) return true;
	for(int i=1;i<=dlugosc/2;i++) std::swap(s1[i],s1[dlugosc-i+1]);
	if(znajdz_wzorzec(dlugosc,s1,d2,s2)) return true;
	return false;
}

// funkcja dzieli stwierdza, czy odcinek (x1,y1)--(x2,y2) dzieli wielokat
// na dwa wielokaty przystajace
// zaklada jednak, ze jest to odcinek pionowy i poza koncami nie ma czesci wspolnej z wielokatem
// !!! ta funkcja jest napisana tak,  aby pozostawila wszystkie zmienne globalne tak, jak je zastala !!!
// !!! jest tylko jeden wyjatek -- kiedy odpowiedzia jest true, to moze sie dziac co chce !!!
int wiel1[1000005]; // pomocnicza tablica na jeden wielokat
int wiel2[1000005]; // pomocnicza tablica na drugi wielokat
bool dzieli(int x1,int y1,int x2,int y2)
{
	wielokat *p=wierzcholek_ze_wspolrzednych(x1,y1);
	wielokat *k=wierzcholek_ze_wspolrzednych(x2,y2);
	bool dodane_p=false;
	if((p->x)!=x1 || (p->y)!=y1) { dodane_p=true; p=p->dodaj_za(x1,y1); }
	bool dodane_k=false;
	if((k->x)!=x2 || (k->y)!=y2) { dodane_k=true; k=k->dodaj_za(x2,y2); }

	// wierzcholi przed/po p/k
	wielokat *p_nas,*p_pop,*k_nas,*k_pop;
	p_nas=p->nas; p_pop=p->pop; k_nas=k->nas; k_pop=k->pop;

	p->nas=k; k->pop=p;
	int wiel1_roz=zamien_wielokat_na_slowo(p,wiel1);
	p->nas=p_nas; k->pop=k_pop;

	p->pop=k; k->nas=p;
	int wiel2_roz=zamien_wielokat_na_slowo(p,wiel2);
	p->pop=p_pop; k->nas=k_nas;

	if(wiel1_roz==wiel2_roz)
		if(czy_przystajace(wiel1_roz,wiel1,wiel2)) return true;

	// usuwanie, jesli potrzeba
	if(dodane_p) { p->usun(); delete p; }
	if(dodane_k) { k->usun(); delete k; }
	return false;
}

int main()
{
	scanf("%d",&n);
	poc=new wielokat;
	scanf("%d%d",&(poc->x),&(poc->y));
	poc->nas=poc; poc->pop=poc;
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		poc->dodaj_przed(x,y);
	}

	// Liczenie obwodu wielokata
	obwod=poc->nas_odl();
	for(wielokat *i=poc->nas;i!=poc;i=i->nas) obwod+=i->nas_odl();
	obw=obwod/2;

	// Liczenie pola wielokata
	pole=poc->nas_pol();
	for(wielokat *i=poc->nas;i!=poc;i=i->nas) pole+=i->nas_pol();
	if(pole%2==1)
	{
		printf("NO\n");
		return 0;
	}
	pol=pole/2;

	// Tworzenie brakujacych wierzcholkow na krawedziach
	dodaj_wierzcholki();

	wielokat *tmp=poc;
	do
	{
		std::swap(tmp->x,tmp->y);
		tmp=tmp->nas;
	}
	while(tmp!=poc);
	pole*= -1;
	pol*= -1;

	if(szukaj_pio())
	{
		if(dzieli(wyn_x1,wyn_y1,wyn_x2,wyn_y2))
		{
			printf("%d %d %d %d\n",wyn_y1,wyn_x1,wyn_y2,wyn_x2);
			return 0;
		}
	}

	tmp=poc;
	do
	{
		std::swap(tmp->x,tmp->y);
		tmp=tmp->nas;
	}
	while(tmp!=poc);
	pole*= -1;
	pol*= -1;

	if(szukaj_pio())
	{
		if(dzieli(wyn_x1,wyn_y1,wyn_x2,wyn_y2))
		{
			printf("%d %d %d %d\n",wyn_x1,wyn_y1,wyn_x2,wyn_y2);
			return 0;
		}
	}

	printf("NO\n");
	return 0;
}
