/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zos.cpp                                        *
 *   Autor:               Krzysztof Dulêba                               *
 *   Opis:                Weryfikator odpowiedzi.                        *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define TOKEN_STD       0
#define TOKEN_EOF      -1
#define TOKEN_EOLN     -2
#define TOKEN_DOS_EOLN -3
#define TOKEN_SPACE    -4
#define TOKEN_TAB      -5
#define MAX_TOKEN_LEN 512

class TextFile {
public:
  TextFile();
  ~TextFile();
  int init(char *filename);
  int compare(TextFile *t);
  int getToken(char *token, int max_len);
  int eof();  
  int readInt(int min,int max);
  int readEof();
  int readSpace();  
  int readEoln();
  int readEolnOrEof();
     
private:
  FILE *f;
  int line;
  int tno;
};

#define WHITE(ch) (ch==' ' || ch=='\t' || ch==13 || ch==EOF)
#define WHITE_OR_EOLN(ch) (ch==' ' || ch=='\t' || ch==13 || ch=='\n' || ch==EOF)

// ----------------------------------------------------------------------
int main(int argc, char *argv[]) {
    if(argc != 4){
        fprintf(stderr, "zoschk plik_wejsciowy odp_zawodnika odp_poprawna\n");
        exit(1);
    }

    TextFile input; input.init(argv[1]);
    TextFile testing; testing.init(argv[2]);
    TextFile ok; ok.init(argv[3]);

    int n = input.readInt(2, 1000000);
    int k = input.readInt(0, 1000000);
    int m = input.readInt(1, 3000000);

    char lineA[65536], lineB[65536];
    testing.getToken(lineA, sizeof(lineA));
    ok.getToken(lineB, sizeof(lineB));

    if(strcmp(lineA, lineB) != 0){
        printf("WRONG\nNiepoprawna pierwsza linijka\n");
        exit(1);
    }

    if(strcmp(lineA, "NIE") == 0){
        printf("OK\n");
        exit(0);
    }

    int res;
    sscanf(lineA, "%d", &res);

    if(res < k){
        printf("WRONG\nZly wynik liczbowy\n");
        exit(1);
    }

    bool cover[1000001];
    memset(cover, 0, sizeof(cover));
    
    for(int i = 0; i < res; ++i){
        int x = testing.readInt(1, n);
        cover[x] = true;
    }

    testing.readEof();

    for(int i = 0; i < m; ++i){
        int p = input.readInt(1, n);
        int q = input.readInt(1, n);
        if(cover[p] && cover[q]){
            printf("WRONG\nDwaj nieprzyjaciele na przyjeciu: %d i %d\n", p, q);
            exit(1);
        }
    }
    printf("OK\n");
}

// ----------------------------------------------------------------------
/**
 * Klasa wspomagaj±ca obs³ugê plików tekstowych
 */

/**
 * Konstruktor, inicjalizacja wewnêtrznych struktur
 */
TextFile::TextFile() {
  f=NULL;
  line=1;
  tno=0;
}

/**
 * Destruktor, zamkniêcie pliku
 */
TextFile::~TextFile() {
  if (f!=NULL) fclose(f);
}

/**
 * Otworzenie pliku
 * @param filename nazwa pliku
 */
int TextFile::init(char *filename) {
  if (strlen(filename)) {
    f=fopen(filename,"r");
    if (f==NULL){
        fprintf(stderr, "nie udalo sie otworzyc %s do czytania\n", filename);
        exit(1);
    }
  } else {
    f=stdin;
  }
  return 0;
}

/**
 * Pobranie pojedynczego tokena z pliku
 * @param token wska¼nik do miejsca na wynik
 * @param max_len maksymalna d³ugo¶æ wyniku
 */
int TextFile::getToken(char *token,int max_len) {
  int i;
  int ch;

  token[0]=0;

  ch=EOF;
  while(true){
      if (!feof(f)) ch=fgetc(f);

      if (ch==EOF)   return TOKEN_EOF;
      if (ch==' ')   continue;
      if (ch=='\t')  continue;
      if (ch=='\n')  continue;
      if (ch==13)    continue;
      break;
  }

  i=0;
  while (!WHITE_OR_EOLN(ch)) {
    token[i]=ch;
    i++;
    if (feof(f)) break;
    if (i==max_len-1) break;
    ch=fgetc(f);
  }
  token[i]=0;

  if (WHITE_OR_EOLN(ch)) ungetc(ch,f);
  
  tno++;
  return TOKEN_STD;
}

int TextFile::readInt(int min,int max) {
  char buf[10];  
  int token=getToken(buf,sizeof(buf));

  if (token!=TOKEN_STD) {
      printf("WRONG\nNiepoprawny format danych: oczekiwano liczby\n");
      exit(1);
  }

  // teraz trzeba policzyc wartosc
  long long value=0;
  int minus=0;
  int i,n;
  i=0;n=strlen(buf);
  if (buf[0]=='-') { i++; minus=1; }
  while (i<n) {
    if (buf[i]<'0' || buf[i]>'9' || buf[i]=='0' && value==0 && n!=1){
        printf("WRONG\nNiepoprawny format danych: oczekiwano liczby\n");
        exit(1);
    }
    value=value*10+(buf[i]-'0');
    if (value>LONG_MAX){
        printf("WRONG\nNiepoprawny format danych: za duza wartosc\n");
        exit(1);
    };
    i++;
  }
  if (minus) value=-value;
  if (value>max || value<min){
      printf("WRONG\nNiepoprawny format danych: liczba poza oczekiwanym zakresem\n");
      exit(1);
  }
  return value;
}

int TextFile::readEof() {  
  char buf[100];
  int token=getToken(buf,sizeof(buf));
  if(token != TOKEN_EOF){
      printf("WRONG\nNiepoprawny format danych: tu powinien byc koniec pliku\n");
      exit(1);
  }
  return 0;
}

/**
 * Czy osi±gniêto koniec pliku
 */
int TextFile::eof() {
  return feof(f);
}
