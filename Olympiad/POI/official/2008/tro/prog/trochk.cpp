/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     trochk.cpp                                                *
 *   Autor:    Anna Niewiarowska                                         *
 *   Opis:     Program weryfikujacy poprawnosc wyjscia wygenerowanego    *
 *             przez program zawodnika, format:                          *
 *             ./trochk.e in out_zawodnika out_wzorcowy                  *
 *                                                                       *
 *************************************************************************/

/* Autor: Anna Niewiarowska */

#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

FILE *f_correct; //plik z prawid�ow� odpowiedzi�
FILE *f_answer;  //plik z odpowiedzia zawodnika

char correct[100];
char answer[100];

void err(string msg) {
    printf("WRONG\n");
    printf(msg.c_str());
    exit(1);
}

int main(int argc, char *argv[]) {
  //otwieranie plikow
  if (argc!=4) return -1;
  f_correct=fopen(argv[3],"r");
  if (f_correct==NULL) {
    fprintf(stderr,"can't open: %s\n",argv[3]);
    return -1;
  }

  f_answer=fopen(argv[2],"r");
  if (f_answer==NULL) {
    fprintf(stderr,"can't open: %s\n",argv[3]);
    return -1;
  }

  fscanf(f_correct,"%s",correct);
  fscanf(f_answer,"%s",answer);
  long long c = 0;
  for (int i=0; i<(int)strlen(correct)-2; i++) {
    c = 10*c+(correct[i]-'0');
  }
  int c2 = correct[strlen(correct)-1] - '0';

  long long a=0;
  int a2;
  int i=0; int n=strlen(answer); int minus=0;

//printf("correct: %lld . %d\n",c,c2);

  if (answer[0]=='-') { i++; minus=1; }
  while (i<n && answer[i]!='.') {
    if (answer[i]<'0' || answer[i]>'9')        err("Niepoprawny format wyjscia\n");
    if (answer[i]=='0' && answer==0 && n!=1) err("Niepoprawny format wyjscia\n");
    a=a*10+(answer[i]-'0');
    if (a>c)  err("Niepoprawny wynik\n");
    i++;
  }
  if (minus) a=-a;
  if (i!=n-2) err("Niepoprawny format wyjscia\n");
  if (answer[n-1]<'0' || answer[n-1]>'9')        err("Niepoprawny format wyjscia\n");
  a2 = answer[n-1] - '0';

//printf("answer: %lld . %d\n",a,a2);
  if ((minus) && ((c!=0) || (c2!=0))) printf("WRONG\nNiepoprawny wynik\n");
  else if ( (a==c) && ((a2==c2) || (a2==c2+1) || (a2==c2-1)) ) printf("OK\n");
  else if ( (a==c-1) && (c2==0) && (a2==9)) printf("OK\n");
  else printf("WRONG\nNiepoprawny wynik\n");



  if (f_correct!=NULL) fclose(f_correct);
  if (f_answer!=NULL) fclose(f_answer);
  return 0;
}
