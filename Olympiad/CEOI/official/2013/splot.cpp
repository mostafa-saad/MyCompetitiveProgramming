// CEOI 2013 - Task: Splot - Solution
// Author: Ante Derek

#include <cstdio>
#include <cassert>

using namespace std;

const int MAX = 1000000;
const int NEGINF = -(1<<28);

enum FunctionType {FORWARD=0, BACKWARD=1, BOTH=2, THROUGH=3, NONE=4};

static const int S_RULE[][3] = {
  {FORWARD, FORWARD, NONE},
  {FORWARD, THROUGH, FORWARD},
  {BACKWARD, NONE, BACKWARD},
  {BACKWARD, BACKWARD, THROUGH},
  {BOTH, FORWARD, BACKWARD}, 
  {BOTH, BOTH, THROUGH},
  {BOTH, THROUGH, BOTH},
  {THROUGH, THROUGH, THROUGH},
  {NONE, NONE, NONE},
  {-1, -1, -1}
};

static const int P_RULE[][5] = {
  {FORWARD, 1, 0, NONE, NONE},
  {FORWARD, 0, 0, FORWARD, FORWARD},
  {FORWARD, 0, 0, THROUGH, BOTH},
  {FORWARD, 0, 0, BOTH, THROUGH},
  {FORWARD, 0, 1, THROUGH, FORWARD},
  {FORWARD, 0, 1, FORWARD, THROUGH},
  {BACKWARD, 0, 1, NONE, NONE},
  {BACKWARD, 0, 0, BACKWARD, BACKWARD},
  {BACKWARD, 0, 0, THROUGH, BOTH},
  {BACKWARD, 0, 0, BOTH, THROUGH},
  {BACKWARD, 1, 0, THROUGH, BACKWARD},
  {BACKWARD, 1, 0, BACKWARD, THROUGH},
  {BOTH, 1, 1, NONE, NONE},
  {BOTH, 1, 0, BACKWARD, BACKWARD},
  {BOTH, 0, 1, FORWARD, FORWARD},
  {BOTH, 0, 0, BOTH, BOTH},
  {THROUGH, 0, 0, THROUGH, BOTH},
  {THROUGH, 0, 0, BOTH, THROUGH},
  {NONE, 0, 0, NONE, NONE},
  {-1, -1, -1, -1}
};

class Splot {
  enum SplotType {NODE, SERIES, PARALLEL} type;
  int source;
  int sink;
  Splot *first;
  Splot *second;
  int result[5];
  int how[5];
  Splot(SplotType _type, 
        int _source=0, 
        int _sink=0,
        Splot* a = NULL,
        Splot* b = NULL):
    type(_type),
    source(_source),
    sink(_sink),
    first(a),
    second(b) {
    for (int i=0; i<5; i++)
      how[i] = result[i] = -1;    
  }
public:
  ~Splot() {
    if (first)
      delete first;
    if (second)
      delete second;
  }
  static Splot* new_node(char c) {
    return new Splot(NODE, c=='x', c=='x');
  }
  static Splot* new_series(Splot* a, Splot *b) {
    return new Splot(SERIES, 0, 0, a, b);
  }
  static Splot* new_parallel(char s, char t, Splot* a, Splot* b) {
    return new Splot(PARALLEL, s=='x', t=='x', a, b);
  }
  int node_result(int f) {
    if (f == FORWARD || f == BACKWARD || f == BOTH)
      return result[f] = 1;
    return result[f] = source?NEGINF:0;
  }
  Splot* rec_node(int f) const {
    if (f == FORWARD || f == BACKWARD || f == BOTH)
      return new_node('x');
    else
      return new_node('o');
  }
  int series_result(int f) {
    int &what = result[f];
    what = NEGINF;
    for (int l=0; S_RULE[l][0]!=-1; l++) {
      if (S_RULE[l][0] != f)
        continue ;
      int left = first->get_result(S_RULE[l][1]);
      int right = second->get_result(S_RULE[l][2]);
      if (left != NEGINF && right != NEGINF && left+right > what) {
        how[f] = l;
        what = left+right;
      }
    }
    return what;
  }
  Splot *rec_series(int f) const {
    int l = how[f];
    return new_series(first->reconstruct(S_RULE[l][1]), 
                      second->reconstruct(S_RULE[l][2]));
  }
  int parallel_result(int f) {
    int &what = result[f];
    what = NEGINF;
    for (int l=0; P_RULE[l][0]!=-1; l++) {
      if (P_RULE[l][0] != f)
        continue ;
      int news = P_RULE[l][1];
      int newt = P_RULE[l][2];
      if ((source && !news) || (sink && !newt))
        continue ;      
      int left = first->get_result(P_RULE[l][3]);
      int right = second->get_result(P_RULE[l][4]);
      if (left != NEGINF && right != NEGINF && left+right+news+newt > what) {
        how[f] = l;
        what = left+right+news+newt;
      }
    }
    return what;
  }
  Splot *rec_parallel(int f) const {
    int l = how[f];
    return new_parallel(P_RULE[l][1]?'x':'o',
                        P_RULE[l][2]?'x':'o',
                        first->reconstruct(P_RULE[l][3]), 
                        second->reconstruct(P_RULE[l][4]));
  }
  int get_result(int f) {
    if (result[f] != -1)
      return result[f];
    if (type == NODE) 
      return node_result(f);
    else if (type == SERIES)
      return series_result(f);
    else
      return parallel_result(f);
  }
  Splot* reconstruct(int f) const {
    if (type == NODE) 
      return rec_node(f);
    else if (type == SERIES)
      return rec_series(f);
    else
      return rec_parallel(f);
  }
  void print() const {
    if (type == NODE)
      printf("%c", source?'x':'o');
    else if (type == SERIES) {
      printf("S");
      first->print();
      second->print();
      printf("#");
    } else {
      printf("P%c|", source?'x':'o');
      first->print();
      second->print();
      printf("|%c#", sink?'x':'o');
    }
  }
};

class Parser {
  const char *s;
  int p;
  Splot* do_parse() {
    if (s[p] == 'o' || s[p] == 'x')
      return Splot::new_node(s[p++]);
    if (s[p] == 'S') {
      p++;
      Splot *first = do_parse();
      Splot *second = do_parse();
      p++;
      return Splot::new_series(first, second);
    }
    assert(s[p] == 'P');
    char sc = s[p+1];
    p += 3;
    Splot *first = do_parse();
    Splot *second = do_parse();
    char tc = s[p+1]; 
    p += 3;
    return Splot::new_parallel(sc, tc, first, second);
  }
 public:
  Parser(const char *_s):
    s(_s), p(0) {
  }
  Splot* parse() {
    assert(p == 0);
    Splot *r = do_parse();
    assert(s[p] == 0 || s[p] == '\n');
    return r;
  }
};

int main() {
  static char s[MAX+1];
  scanf("%s", s);
  Splot* splot = Parser(s).parse();
  int best = splot->get_result(FORWARD);
  printf("%d\n", best);
  Splot *filled = splot->reconstruct(FORWARD);
  filled->print();
  printf("\n");
  delete splot;
  delete filled;
  return 0;
}
