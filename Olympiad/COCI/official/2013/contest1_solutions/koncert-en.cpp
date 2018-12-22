#include <cstdio>
#include <vector>

using namespace std;

const char* GUY = "GUY";
const char* GIRL = "GIRL";

const char* ENTER = "ENTER";
const char* EXIT = "EXIT";
const char* GIVE = "GIVE";

void readTickets(int& m, int& a, vector<bool>& v) {
  scanf("%d %d", &m, &a);
  v.resize(m, false);
  for (int i = 0; i < a; ++i) {
    int id;
    scanf("%d", &id);
    v[id - 1] = true;
  }
}

void enterConcert(int id) {
  printf("%s %s %d\n", ENTER, GUY, id + 1);
}
void exitConcert(int id) {
  printf("%s %s %d\n", EXIT, GUY, id + 1);
}
void giveTicket(bool guy1, int id1, int id2) {
  printf("%s %s %d %s %d\n", 
    GIVE, guy1 ? GUY : GIRL, id1 + 1, GUY, id2 + 1);
}

int main(void) {
  int m, a;
  vector<bool> guys;
  readTickets(m, a, guys);
  
  int n, b;
  vector<bool> girls;
  readTickets(n, b, girls);
  
  int id = 0;
  for (int i = 0; i < n; ++i) {
    if (girls[i]) {
      while (id < m && guys[id])
        ++id;
      if (id < m) {
        giveTicket(false, i, id);
        girls[i] = false;
        guys[id] = true;
      }
    }
  }
  
  if (m == 1) {
    enterConcert(0);
  } else {
    if (!guys[1]) {
      for (int i = 2; i < m; ++i)
        if (guys[i]) {
          giveTicket(true, i, 1);
          guys[i] = false;
          guys[1] = true;
        }
    }
    for (int i = 1; i < m; ++i) {
      enterConcert(0);
      enterConcert(i);
      if (i + 1 < m) {
        giveTicket(true, i, 0);
        exitConcert(0);
        giveTicket(true, 0, i + 1);
      }
    }
  }
  
  return 0;
}
