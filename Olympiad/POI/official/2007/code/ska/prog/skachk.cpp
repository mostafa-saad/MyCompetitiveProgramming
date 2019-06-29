/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skachk.cpp                                                 *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Program weryfikujacy poprawnosc wyjscia wygenerowanego     *}
{*            przez program zawodnika, format:                           *}
{*            ./skachk.e in out_zawodnika out_wzorcowy                   *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;
string gdzie; /*ktory plik aktualnie przetwarzamy*/
const int MAX_N=1000000;
const int MAX_ZAKRES=1000000000;
const int MIN_ZAKRES=0;
int x[MAX_N],y[MAX_N],waga[MAX_N];
char txt[MAX_N+3];

int iswhite(char c){return c==' ' || c==10 || c==13 || c=='\t';}
int isdigit(char c){return '0'<=c && c<='9';}

void error(char *s){
  fprintf(stderr,"%s:",gdzie.c_str());
  fprintf(stderr," %s\n",s);
  exit(1);
}

void readEof(){
  char c;
  while (scanf("%c",&c)==1) 
    if (!iswhite(c)) error("smieci na koncu pliku");
}

char *readInt(char *txt,long long &x){
  while (1){ 
    if (*txt==0) error("zbyt mala liczba danych");
    if (!iswhite(*txt)) break;
    else txt++;
  }
  if (!isdigit(*txt)) error("nieprawidlowy znak");
  x=*txt++-'0';
  int cyfry=1;
    
  while (1){
    if (*txt==0 || iswhite(*txt)) break;
    if (++cyfry>15) error("zbyt dluga liczba");
    if (!isdigit(*txt)) error("nieprawidlowy znak");
    x=10LL*x+(long long)(*txt++-'0');
  }
  return txt;
}

int main(int argc, char **argv){
  if (argc!=4){
    fprintf(stderr,"Uzycie: ./skachk.e in out_zawodnika out_wzorcowy\n");
    exit(1);
  }
  
  /*wczytywanie in'a*/
  gdzie="in";
  freopen(argv[1],"r",stdin);
  int n;
  scanf("%d",&n);
  for (int i=0; i<n; ++i)
    scanf("%d %d %d",x+i,y+i,waga+i);
  
  /*wczytywanie out'a wzorcowego*/
  gdzie="out_wzorcowy";
  freopen(argv[3],"r",stdin);
  unsigned int obwod, koszt;
  scanf("%u %u",&obwod,&koszt);

  /*wczytywanie out'a zawodnika*/
  gdzie="out_zawodnika";
  freopen(argv[2],"r",stdin);
  fgets(txt,MAX_N+3,stdin);
  long long obwod_zaw, koszt_zaw;
  char *s=txt;
  s=readInt(s,obwod_zaw); 
  if (obwod_zaw!=obwod) error("nieprawidlowa wartosc obwodu");
  s=readInt(s,koszt_zaw); 
  if (koszt_zaw!=koszt) error("nieprawidlowa wartosc kosztu");

  while (*s)
    if (!iswhite(*s++)) error("nieprawidlowe znaki w pierwszej linii");

  fgets(txt,MAX_N+3,stdin);
  int x1=MAX_ZAKRES,x2=MIN_ZAKRES,y1=MAX_ZAKRES,y2=MIN_ZAKRES;
  int moj_koszt=0;
  for(int i=0; i<n; ++i)
    if (txt[i]!='0' && txt[i]!='1') error("nieprawidlowy znak w drugiej linii");
    else{
      if (txt[i]=='1') moj_koszt+=waga[i], swap(x[i],y[i]); 
      x1=min(x1,x[i]); x2=max(x2,x[i]);
      y1=min(y1,y[i]); y2=max(y2,y[i]);
    }
  int pos=n;
  while (txt[pos] && iswhite(txt[pos])) pos++;
  if (txt[pos]) error("niepotrzebne znaki w drugim wierszu");
  if ((unsigned int)2*(unsigned int)(x2-x1+y2-y1)!=obwod || (unsigned int)moj_koszt!=koszt) error("pierwsza linia niezgodna z druga");
  printf("OK\nprawidlowe rozwiazanie o obwodzie %u i koszcie %u\n",obwod,koszt);
  return 0;
}
