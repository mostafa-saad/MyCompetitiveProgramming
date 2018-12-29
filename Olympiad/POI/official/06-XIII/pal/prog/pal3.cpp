/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pal3.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Alternatywna implementacja rozwiazania         *
 *                        wzorcowego.                                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

const int N=2100000;
string s[N];
char txt[N];
int n; // liczba palindromow na wejsciu
int p[N]; //tablica prefiksowo-sufiksowa

int main(){
  scanf("%d",&n);
  for (int i=0; i<n; ++i){
    int k,t=0;
    scanf("%d %s",&k,txt);
    p[0]=p[1]=0;
    for (int j=2; j<=k; ++j){
      while (t && txt[t]!=txt[j-1]) t=p[t];
      if (txt[t]==txt[j-1]) t++;
      p[j]=t;
    }
    if (k%(k-p[k])==0) txt[k-p[k]]=0;
    s[i]=txt;
  }
  sort(s,s+n);
  int res=0,beg=0;
  for (int i=0; i<n; ++i) if (i==n-1 || s[i+1]!=s[i]){
    res+=(i+1-beg)*(i+1-beg);
    beg=i+1;
  }
  printf("%d\n",res);
  return 0;
}