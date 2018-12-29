/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klochk.cpp                                                *
 *   Autor:    Krzysztof Duleba                                          *
 *   Opis:     Program weryfikujacy poprawnosc wyjscia wygenerowanego    *
 *             przez program zawodnika, format:                          *
 *               ./klochk.e in out_zawodnika out_wzorcowy                *
 *                                                                       *
 *************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <vector>
using std::vector;

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
  long long readLonglong(long long min,long long max);
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

// <KD>


int main(int argc, char *argv[]) {
    if(argc != 4){
        fprintf(stderr, "klochk plik_wejsciowy odp_zawodnika odp_poprawna\n");
        exit(1);
    }

    TextFile input; input.init(argv[1]);
    TextFile testing; testing.init(argv[2]);
    TextFile ok; ok.init(argv[3]);

    int n = input.readInt(0, 100000);
    int k = input.readInt(0, 1000000);

    vector<int> in_seq, tested_seq, ok_seq;

    // <JR>
    long long wyn_dekl, wyn;
    wyn_dekl = testing.readLonglong(0LL, 100000LL * 1000000LL);
    wyn = ok.readLonglong(0LL, 100000LL * 1000000LL);
    // </JR>

    for (int i = 0; i < n; ++i) {
        in_seq.push_back(input.readInt(0, 1000000));
    }

    for (int i = 0; i < n; ++i) {
        tested_seq.push_back(testing.readInt(0, 1000000));
    }
    testing.readEof();

    // <JR>
    if (wyn < wyn_dekl) {
        printf("WRONG\nNieoptymalne rozwiazanie\n");
        exit(1);
    }
    if (wyn > wyn_dekl) {
        printf("WRONG\nTyle operacji nie wystarczy\n");
        exit(1);
    }
    // </JR>
    
    if ((int)tested_seq.size() != n) {
        printf("WRONG\nZa malo liczb na wyjsciu\n");
        exit(1);
    }

    for (int i = 0; i < n; ++i) {
        ok_seq.push_back(ok.readInt(0, 1000000));
    }

    int eq = 1;
    for (int i = 1; i < n; ++i) {
        if (tested_seq[i] == tested_seq[i - 1]) {
            ++eq;
            if (eq == k) break;
        } else {
            eq = 1;
        }
    }
    if (eq < k) {
        printf("WRONG\nBrakuje wystarczajacej liczby rownych wyrazow pod rzad\n");
        exit(1);
    }

    long long err = 0;
    for (int i = 0; i < n; ++i) {
        err += abs(in_seq[i] - tested_seq[i]) - abs(in_seq[i] - ok_seq[i]);
    }
    if (err != 0) {
        printf("WRONG\nNieoptymalne rozwiazanie\n");
        exit(1);
    }

    printf("OK\n");
}


// </KD>

// ----------------------------------------------------------------------






//----
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
    // <KD>
    if (f==NULL){
        fprintf(stderr, "nie udalo sie otworzyc %s do czytania\n", filename);
        exit(1);
    }
    // </KD>
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
  // <KD>
  while(true){
      if (!feof(f)) ch=fgetc(f);

      if (ch==EOF)   return TOKEN_EOF;
      if (ch==' ')   continue;
      if (ch=='\t')  continue;
      if (ch=='\n')  continue;
      if (ch==13)    continue;
      break;
  }
  // </KD>

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

// <JR>
long long TextFile::readLonglong(long long min,long long max) {
  char buf[20];
  int token=getToken(buf,sizeof(buf));

  // <KD>
  if (token!=TOKEN_STD) {
      printf("WRONG\nNiepoprawny format danych: oczekiwano liczby\n");
      exit(1);
  }
  // </KD>
  
  // teraz trzeba policzyc wartosc
  long long value=0;
  int minus=0;
  int i,n;
  i=0;n=strlen(buf);
  if (n>14) {
      printf("WRONG\nNiepoprawny format danych: za duza wartosc\n");
      exit(1);
  };
  if (buf[0]=='-') { i++; minus=1; }
  while (i<n) {
    // <KD>
    if (buf[i]<'0' || buf[i]>'9' || buf[i]=='0' && value==0 && n!=1){
        printf("WRONG\nNiepoprawny format danych: oczekiwano liczby\n");
        exit(1);
    }
    // </KD>
    value=value*10+(buf[i]-'0');
    i++;
  }
  if (minus) value=-value;
  // <KD>
  if (value>max || value<min){
      printf("WRONG\nNiepoprawny format danych: liczba poza oczekiwanym zakresem\n");
      exit(1);
  }
  // </KD>
  return value;
}
// </JR>

int TextFile::readInt(int min,int max) {
  char buf[10];  
  int token=getToken(buf,sizeof(buf));

  // <KD>
  if (token!=TOKEN_STD) {
      printf("WRONG\nNiepoprawny format danych: oczekiwano liczby\n");
      exit(1);
  }
  // </KD>
  
  // teraz trzeba policzyc wartosc
  long long value=0;
  int minus=0;
  int i,n;
  i=0;n=strlen(buf);
  if (buf[0]=='-') { i++; minus=1; }
  while (i<n) {
    // <KD>
    if (buf[i]<'0' || buf[i]>'9' || buf[i]=='0' && value==0 && n!=1){
        printf("WRONG\nNiepoprawny format danych: oczekiwano liczby\n");
        exit(1);
    }
    // </KD>
    value=value*10+(buf[i]-'0');
    // <KD>
    if (value>LONG_MAX){
        printf("WRONG\nNiepoprawny format danych: za duza wartosc\n");
        exit(1);
    };
    // </KD>
    i++;
  }
  if (minus) value=-value;
  // <KD>
  if (value>max || value<min){
      printf("WRONG\nNiepoprawny format danych: liczba poza oczekiwanym zakresem\n");
      exit(1);
  }
  // </KD>
  return value;
}

int TextFile::readEof() {  
  char buf[100];
  int token=getToken(buf,sizeof(buf));
  // <KD>
  if(token != TOKEN_EOF){
      printf("WRONG\nNiepoprawny format danych: tu powinien byc koniec pliku\n");
      exit(1);
  }
  // < /KD>
  return 0;
}

/**
 * Czy osi±gniêto koniec pliku
 */
int TextFile::eof() {
  return feof(f);
}
