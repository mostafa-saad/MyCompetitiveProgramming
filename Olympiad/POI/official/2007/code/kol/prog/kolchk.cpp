/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kolchk.cpp                                                 *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Program weryfikujacy poprawnosc wyjscia wygenerowanego     *}
{*            przez program zawodnika, format:                           *}
{*            ./skachk.e in out_zawodnika out_wzorcowy                   *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>
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


/********************* weryfikator **********************************/

#define WHITE(ch) (ch==' ' || ch=='\t' || ch==13 || ch==EOF)
#define WHITE_OR_EOLN(ch) (ch==' ' || ch=='\t' || ch==13 || ch=='\n' || ch==EOF)

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
  int error(char *message);
     
private:
  FILE *f;
  int line;
  int tno;
  char *token2str(int token, char *t_str);
  int err(char *expectedtoken, char *readtoken);
};

class InputChecker : public TextFile {
public:
  int check();
};

TextFile::TextFile() {
  f=NULL;
  line=1;
  tno=0;
}

TextFile::~TextFile() {
  if (f!=NULL) fclose(f);
}

int TextFile::init(char *filename) {
  if (strlen(filename)) {
    f=fopen(filename,"r");
    if (f==NULL) return -1;
  } else {
    f=stdin;
  }
  return 0;
}

int TextFile::getToken(char *token,int max_len) {
  int i;
  int ch;

  token[0]=0;

  // omijanie bialych znakow
  ch=EOF;
  if (!feof(f)) ch=fgetc(f);

  if (ch==EOF)   return TOKEN_EOF;
  if (ch==' ')   return TOKEN_SPACE;
  if (ch=='\t')  return TOKEN_TAB;
  if (ch=='\n')  return TOKEN_EOLN;
  if (ch==13)    return TOKEN_DOS_EOLN;

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
    err("Int",token2str(token,buf));
  }
  // teraz trzeba policzyc wartosc
  long long value=0;
  int minus=0;
  int i,n;
  i=0;n=strlen(buf);
  if (buf[0]=='-') { i++; minus=1; }
  while (i<n) {
    if (buf[i]<'0' || buf[i]>'9')        err("Int",buf);
    if (buf[i]=='0' && value==0 && n!=1) err("Int",buf);
    value=value*10+(buf[i]-'0');
    if (value>LONG_MAX)  err("Int",buf);
    i++;
  }
  if (minus) value=-value;
  char int_desc[100];
  snprintf(int_desc,sizeof(int_desc),"Int[%d,%d]",min,max);
  if (value>max || value<min) err(int_desc,buf);
  return value;
}

int TextFile::readEoln() {  
  char buf[100];
  int token=getToken(buf,sizeof(buf));
  if (token!=TOKEN_EOLN) err("EOLN",token2str(token,buf));
  line++;tno=0;
  return 0;
}

int TextFile::readEof() {  
  char buf[100];
  int token=getToken(buf,sizeof(buf));
  if (token!=TOKEN_EOF) err("EOF",token2str(token,buf));
  return 0;
}

int TextFile::readSpace() {  
  char buf[100];
  int token=getToken(buf,sizeof(buf));
  if (token!=TOKEN_SPACE) err("SPACE",token2str(token,buf));
  return 0;
}

int TextFile::readEolnOrEof() {
  char buf[100];
  int token=getToken(buf,sizeof(buf));
  if (token!=TOKEN_EOLN && token!=TOKEN_EOF) 
    err("EOLN_OR_EOF",token2str(token,buf));
  if (token==TOKEN_EOLN) {
    line++;tno=0;
  }
  return token;
}

int TextFile::eof() {
  return feof(f);
}

char *TextFile::token2str(int token, char *t_str) {
  static char buf[1024];
  bzero(&buf,sizeof(buf));
  switch(token) {
  case TOKEN_STD:   strncpy(buf,t_str,sizeof(buf)-1); break;
  case TOKEN_EOF:   sprintf(buf,"EOF");   break;
  case TOKEN_EOLN:  sprintf(buf,"EOLN");  break;
  case TOKEN_SPACE: sprintf(buf,"SPACE"); break;
  case TOKEN_TAB:   sprintf(buf,"TAB");   break;
  case TOKEN_DOS_EOLN: sprintf(buf,"DOS_EOLN");  break;
  default:
    sprintf(buf,"UNKNOWN");
  }
  return (char *)&buf;
}

int TextFile::err(char *expectedtoken, char *readtoken) {  
  fprintf(stdout,"WRONG\nNiepoprawny format wejscia od uzytkownika\n");
  exit(1);
}

int TextFile::error(char *message) 
{
   
     fprintf(stdout,"WRONG\n%s\n",message);
     exit(1);
}

/********************* sprawdzanie **********************************/

const int N=5000; //max. liczba wierzch.
const int M=1000000; //max. liczba kraw.
const int INF=1000000000; //liczba wieksza niz max koszt N krawedzi
const int MAX_C=2000000000;

struct edge{
  int to; //wierzch. docelowy
  int wei; //waga krawedzi
  int next; //kolejny wierzcholek na liscie sasiedztwa
};

FILE *f_data, *f_answer;
int n,m; //liczba wierzcholkow i krawedzi
edge edges[2*M]; //lista sasiedztwa
int v[N+1]; //lista sasiedztwa
edge edges2[2*M]; //lista sasiedztwa dla poddrzewa zawodnika
int v2[N+1]; //lista sasiedztwa dla poddrzewa zawodnika
int tmp2;

int stays[N+1]; //czy wierzcholek musi pozostac (1-tak/0-nie)
int st; //ile wierzcholkow ma zostac
int answer; //optymalna odpowiedz
int computed_answer;
int visited[N+1];

void input_data() {
  int a,b,u;
  int tmp=0; //kolejna wolna poz. na l.sasiedztwa
  tmp2=0; //kolejna wolna poz. na II l.sasiedztwa
  fscanf(f_data,"%d %d ", &n, &m);
  for (int i=1; i<=n; i++) {
    v[i]=-1;
    v2[i]=-1;
  }
  for (int i=0; i<m; i++) {
    fscanf(f_data,"%d %d %d ", &a, &b, &u);
    edges[tmp].to=b;
    edges[tmp].wei=u;
    edges[tmp].next=v[a];
    v[a]=tmp;
    tmp++;
    edges[tmp].to=a;
    edges[tmp].wei=u;
    edges[tmp].next=v[b];
    v[b]=tmp;
    tmp++;
  }
  fscanf(f_data,"%d ", &st); //ile wierzcholkow pozostaje
  for (int i=1; i<=n; i++) stays[i]=0;
  for (int i=0; i<st; i++) {
    fscanf(f_data,"%d ",&a);
    stays[a]=1;
  }
}

void answer_data() {
  fscanf(f_answer, "%d", &answer);
}

void user_adds(int va, int vb) {
  //czy taka krawedz jest legalna, jesli tak to dodac jej koszt
  int tmp = v[va];
  while (tmp!=-1 && edges[tmp].to!=vb) tmp=edges[tmp].next;
  if (tmp==-1) {
    printf("WRONG\nPodana krawedz nie istnieje\n");
    exit(1);
  }
  computed_answer+=edges[tmp].wei;
  //dodanie krawedzi do podgrafu zawodnika
  edges2[tmp2].to=vb;
  edges2[tmp2].next=v2[va];
  v2[va]=tmp2;
  tmp2++;
  edges2[tmp2].to=va;
  edges2[tmp2].next=v2[vb];
  v2[vb]=tmp2;
  tmp2++;
}

void dfs_visit(int nr) {
  if (visited[nr]==1) return;
  visited[nr]=1;
  int pos=v2[nr];
  while (pos>=0) {
    dfs_visit(edges2[pos].to);
    pos=edges2[pos].next;
  } 
}

void test_connectivity() {
  //czy graf jest spojny i zawiera wszystkie czarne
  int tmp=1;
  for (int i=1; i<=n; i++) visited[i]=0;
  while (stays[tmp]==0) tmp++;
  dfs_visit(tmp);
  for (int i=1; i<=n; i++) if (stays[i]==1 && visited[i]==0) {
    printf("WRONG\nGraf jest niespojny\n");
    exit(1);
  }
}

int InputChecker::check() {
  int user_answer, user_edges;
  user_answer = readInt(0,MAX_C);
  if (user_answer>2*answer) error("Koszt zbyt duzy");
  readSpace();
  user_edges = readInt(0,m);
  for (int i=0; i<user_edges; i++) {
    readEoln();
    int a,b;
    a=readInt(1,n);
    readSpace();
    b=readInt(1,n);
    user_adds(a,b);
  }
  readEolnOrEof();
//  if (!eof) error("Oczekiwano konca pliku");
  if (user_answer!=computed_answer) error("Podany koszt nie zgadza sie z suma kosztow krawedzi");
  test_connectivity();
}

int main(int argc, char *argv[]) {
  //otwieranie plikow
  if (argc!=4) return -1;
  f_data=fopen(argv[1],"r");
  if (f_data==NULL) {
    fprintf(stderr,"can't open: %s\n",argv[1]);
    return -1;
  }
  f_answer=fopen(argv[3],"r");
  if (f_answer==NULL) {
    fprintf(stderr,"can't open: %s\n",argv[1]);
    return -1;
  }

  InputChecker *ic;
  ic=new InputChecker;
  if (ic->init(argv[2])) {
    fprintf(stderr,"can't open: %s\n",argv[1]);
    return 1;
  }


  input_data();
  answer_data();
  computed_answer=0;
  ic->check();
  printf("OK\n");

  if (f_data!=NULL) fclose(f_data);
  if (f_answer!=NULL) fclose(f_answer);
  return 0;
}
