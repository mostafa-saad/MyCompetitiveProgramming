/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                mag1.cpp                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwi±zanie wzorcowe.                          *
 *                        Najpierw obracamy siatkê o 45 stopni,          *
 *                        a potem liczymy mediany.                       *
 *                        Z³o¿ono¶æ czasowa: O(n log n).                 *
 *                                                                       *
 *************************************************************************/


#include<stdio.h>

using namespace std;


int wynikx,wyniky;
int n;
int px,py,c;

int os[110000][3];

void sort(int l, int r) {
int i,j,sr,tymcz;

i=l; j=r; sr=os[(i+j)/2][1];
  do {
  while (os[i][1]<sr) i++;
  while (os[j][1]>sr) j--;

  if (i<=j) {
   tymcz=os[i][1]; os[i][1]=os[j][1]; os[j][1]=tymcz;
   tymcz=os[i][2]; os[i][2]=os[j][2]; os[j][2]=tymcz;
   i++; j--;
  }
  }
  while (i<=j);
  if (i<r)  sort(i,r);
  if (l<j)  sort(l,j);
}


//Rozwi±zanie jednowymiarowego przypadku w metryce miejskiej
//Rozwi±zaniem jest mediana

int licz_wynik() {

  long long wszystkiePunkty,naPrawo;

  sort(1,n);

  wszystkiePunkty = 0;
  for (int i=1; i<=n; i++) {
    wszystkiePunkty=wszystkiePunkty+os[i][2];
  }

  naPrawo = wszystkiePunkty;
  for (int i=1; i<=n; i++) {
    naPrawo = naPrawo - os[i][2];
    if (naPrawo<=(wszystkiePunkty / 2)) {
      return os[i][1];
    }
  }
}

//Obrót punktów wokó³ punktu (0,0) o 45 stopni
//Jednoczesne przeskalowanie pozwala unikn±æ stosowanie typó³ nieca³kowitych

void obrot(int & punktx, int & punkty){

int tymczx;
int tymczy;

  tymczx = punktx - punkty;
  tymczy = punktx + punkty;
  punktx = tymczx;
  punkty = tymczy;
}

//Obrót w drug± stronê

void obrot2(int & punktx, int & punkty){

int tymczx;
int tymczy;
  tymczx = (punktx + punkty) / 2;
  tymczy = (punkty - punktx) /2;
  punktx = tymczx;
  punkty = tymczy;
}

int i;
int sklepy[110000][3];
int liczba[110000];


long long abs(long long z1) {
  if (z1 > 0) return z1;
  return -z1;
}

long long max(long long z1, long long z2) {
  if (z1>z2) return z1;
  return z2;
}

void wezLepszy(int & najlepszyx, int & najlepszyy, int kandydatx, int kandydaty) {
  long long roznica = 0;
  for (int i = 1; i<=n; i++) {

    long long odl1 = max(abs(najlepszyx - sklepy[i][1]),abs(najlepszyy-sklepy[i][2]));
    long long odl2 = max(abs(kandydatx - sklepy[i][1]),abs(kandydaty-sklepy[i][2]));
    long long dd = odl1 - odl2;
    roznica += dd * (long long) liczba[i];
  }
  if (roznica > 0) {
    najlepszyx = kandydatx;
    najlepszyy = kandydaty;
  }
}

int main() {

  scanf("%d",&n);


  // liczba[i] to liczba odwiedzin sklepu dziennie

  for (int i=1; i<=n; i++) {
    scanf("%d%d%d",&px,&py,&c);
    px*=2; py*=2;
    sklepy[i][1] = px;
    sklepy[i][2] = py;
    liczba[i] = c;
  }

  // obracamy wszystkie punkty
  for (int i=1; i<=n; i++) {
    obrot(sklepy[i][1],sklepy[i][2]);
  }


  // teraz oddzielamy os x i os y
  for (int i=1; i<=n; i++) {
    os[i][1] = sklepy[i][1];
    os[i][2] = liczba[i];
  }


  // i liczymy optymalne wyniki dla osi x i osi y
  wynikx = licz_wynik();


  for (int i=1; i<=n; i++) {
    os[i][1] = sklepy[i][2];
    os[i][2] = liczba[i];
  }


  wyniky = licz_wynik();

  // i obracamy punkty z powrotem
  obrot2(wynikx,wyniky);
  for (int i=1; i<=n; i++) {
    obrot2(sklepy[i][1],sklepy[i][2]);
  }

  // musimy sprawdziæ s±siadów
  if (wynikx%2==1) {
    int najlepszyx = wynikx-1;
    int najlepszyy = wyniky-1;

    wezLepszy(najlepszyx,najlepszyy,wynikx-1,wyniky-1);
    wezLepszy(najlepszyx,najlepszyy,wynikx-1,wyniky+1);
    wezLepszy(najlepszyx,najlepszyy,wynikx+1,wyniky-1);
    wezLepszy(najlepszyx,najlepszyy,wynikx+1,wyniky+1);
    wynikx = najlepszyx; wyniky = najlepszyy;
  }

  printf("%d %d\n",wynikx/2,wyniky/2);
  return 0;
}
