/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LIS (Listonosz)                                *
 *   Plik:                lischk.cpp                                     *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Modul sprawdzajacy wyjscie zawodnika.          *
 *                                                                       *
 *  Program oceniajacy uruchamia sie z czterema parametrami:             *
 *    1 - NazwaIN - plik wejsciowy                                       *
 *    2 - NazwaOUT - odpowiedz zawodnika,                                *
 *    3 - NazwaOK - nazwa pliku z podpowiedzia                           *
 *        (moze byc z rozwiazaniem wzorcowym)                            *
 *    4 - NrTestu - program nie powinien korzystac z tej wartosci.       *
 * Program oceniajacy wypisuje na standardowym wyjsciu                   *
 * w pierwszym wierszu jedno slowo wielkimi literami:                    *
 *    OK - wyjscie prawidlowe,                                           *
 *    SYNTAX - wyjscie prawidlowe, ale sa bledy skladni,                 *
 *    WRONG - wyjscie bledne.                                            *
 * Druga linijka jest opisem niepoprawnosci.                             *
 * Wyjscie bledow jest takie samo jest standardowe wyjscie,              *
 * program oceniajacy nie powinien wypisywac na nim zadnych informacji.  *
 * Jesli pierwsza linia nie bedzie zgodna ze specyfikacja                *
 * przyjumje sie, ze wyjscie zostalo ocenione jako bledne.               *
 *                                                                       *
 *************************************************************************/

using namespace std;

#include <cctype>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

/* Definicja tego symbolu powoduje, ze jesli zawodnik odpowie TAK,
 * a odpowiedzia poprawna jest NIE, to mimo wszystko jest sprawdzana
 * poprawnosc. Mozna w ten sposob sprawdzic, w ktorym miejscu jest
 * blad w rozwiazaniu. Z drugiej strony, a nuz jakiemus zawodnikowi
 * uda sie znalezc rozwiazanie, ktorego nie przewiduje program wzorcowy.
 */
//#define CHECK_YES_ANSWER

const string OK("OK\n");
const string WRONG("WRONG\n");
const string EXPECTED_YES("oczekiwalem slowa TAK, a dostalem NIE\n");
#ifndef CHECK_YES_ANSWER
const string EXPECTED_NO("oczekiwalem slowa NIE, a dostalem TAK\n");
#endif
const string EXPECTED_NUMBER("oczekiwalem liczby od 1 do ");
const string EXPECTED_ONE("oczekiwalem liczby 1");
const string BUT_GOT(", a dostalem ");
const string END_OF_FILE("koniec pliku\n");
const string GOT_EDGE("na sciezce dostalem krawedz ");
const string NOT_IN_GRAPH(", ktorej nie ma grafie\n");
const string EDGE("krawedz ");
const string USED_TWICE(" zostala uzyta na sciezce dwukrotnie\n");
const string IN_SEQUENCE(" z sekwencji nr ");
const string NOT_IN_PATH(" nie jest na sciezce\n");
const string NOT_CONTINUE_IN_PATH(" nie ma kontynuacji w sciezce\n");

struct edge
{
  int a, b;
  edge() { }
  edge(int a, int b) : a(a), b(b) { }
  bool operator<(const edge& e) const
  {
    return a == e.a ? b < e.b : a < e.a;
  }
  bool operator==(const edge& e) const
  {
    return a == e.a && b == e.b;
  }
  bool operator!=(const edge& e) const
  {
    return !operator==(e);
  }
};

ostream& operator<<(ostream& os, const edge& e)
{
  return os << '(' << e.a << ',' << e.b << ')';
}

bool readAnswer(ifstream& is)
{
  string s;
  is >> s;
  return s == "TAK";
}

void readEdges(ifstream& is, int m, set<edge>& edges)
{
  for (int i = 0; i < m; i++) {
    int a, b;
    is >> a >> b;
    edges.insert(edge(a, b));
  }
}

int tryReadNode(ifstream& is, int n)
{
  string str;
  is >> str;
  if (str == "" && is.eof()) {
    cout << WRONG;
    cout << EXPECTED_NUMBER << n << BUT_GOT << END_OF_FILE;
    exit(-1);
  }
  if (str.size() <= 9) {
    bool success = true;
    for (uint i = 0; i < str.size(); i++)
      if (!isdigit(str[i])) {
        success = false;
        break;
      }
    if (success) {
      int ret = atoi(str.c_str());
      if (1 <= ret && ret <= n)
        return ret;
    }
  }
  cout << WRONG;
  cout << EXPECTED_NUMBER << n << BUT_GOT;
  cout << '\'' << str << '\'' << endl;
  exit(-1);
}

void tryReadPath(ifstream& is, int n, set<edge>& edges, vector<edge>& path)
{
  set<edge> used;
  edge e;
  e.a = tryReadNode(is, n);
  if (e.a != 1) {
    cout << WRONG << EXPECTED_ONE << BUT_GOT << e.a << endl;
    exit(-1);
  }
  while (used.size() < edges.size()) {
    e.b = tryReadNode(is, n);
    if (edges.find(e) == edges.end()) {
      cout << WRONG << GOT_EDGE << e << NOT_IN_GRAPH;
      exit(-1);
    }
    if (!used.insert(e).second) {
      cout << WRONG << EDGE << e << USED_TWICE;
      exit(-1);
    }
    path.push_back(e);
    e.a = e.b;
  }
  if (e.b != 1) {
    cout << WRONG << EXPECTED_ONE << BUT_GOT << e.b << endl;
    exit(-1);
  }
}

void checkSingleSequence(ifstream& is, int seqNr,
       map<edge,vector<edge>::const_iterator>& edgePathIdx,
       vector<edge>& path)
{
  int k;
  is >> k;
  edge e;
  is >> e.a >> e.b;
  map<edge,vector<edge>::const_iterator>::const_iterator it =
    edgePathIdx.find(e);
  if (it == edgePathIdx.end()) {
    cout << WRONG << EDGE << e << IN_SEQUENCE << seqNr
         << NOT_IN_PATH;
    exit(-1);
  }
  vector<edge>::const_iterator i = it->second;
  for (k -= 2, i++; k; k--, i++) {
    e.a = e.b;
    is >> e.b;
    if (i == path.end()) {
      cout << WRONG << EDGE << e << IN_SEQUENCE << seqNr
           << NOT_CONTINUE_IN_PATH;
      exit(-1);
    }
    if (e != *i) {
      cout << WRONG << EDGE << e << IN_SEQUENCE << seqNr
           << NOT_CONTINUE_IN_PATH;
      exit(-1);
    }
  }
}

void checkSequences(ifstream& is, vector<edge>& path)
{
  map<edge,vector<edge>::const_iterator> edgePathIdx;
  for (vector<edge>::const_iterator i = path.begin();
       i != path.end(); i++)
    edgePathIdx[*i] = i;
  int t;
  is >> t;
  for (int i = 0; i < t; i++)
    checkSingleSequence(is, i + 1, edgePathIdx, path);
}

int main(int argc, char *argv[])
{
  ifstream in(argv[1]);
  ifstream out(argv[2]);
  ifstream hint(argv[3]);
  bool correctAnswer = readAnswer(hint);
  bool outputAnswer = readAnswer(out);
  if (!outputAnswer) {
    if (outputAnswer == correctAnswer) {
      cout << OK;
      return 0;
    } else {
      cout << WRONG << EXPECTED_YES;
      return -1;
    }
  }
#ifndef CHECK_YES_ANSWER
  else
    if (outputAnswer != correctAnswer) {
      cout << WRONG << EXPECTED_NO;
      return -1;
    }
#endif

  set<edge> edges;
  vector<edge> path;

  int n, m;
  in >> n >> m;
  readEdges(in, m, edges);
  tryReadPath(out, n, edges, path);
  checkSequences(in, path);
  cout << OK;
  return 0;
}
