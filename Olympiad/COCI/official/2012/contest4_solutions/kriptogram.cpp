/*
  Official solution for the Kriptogram problem.
  Complexity: O(dataLoad + lenA + lenB), where dataLoad ~ O(n log n) 
  Author: Goran Zuzic
 */

#include <algorithm>
#include <functional>

#include <cstdio>
#include <cstdlib>
#include <cstdlib>

#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/* Emulates an int that automatically initializes to -1 */

class Int {
public:
  Int() { x = -1; }
  Int(int x) : x(x) {}
  operator int& () { return x; }
private:
  int x;
};

/* Read a line terminated by '$'
 * Store offsets to last equal word that appeared 
 * before the current one or -1 for first appearence.
 */

void load(vector<int>& V) {
  static const int kMaxLen = 1000100;
  static char buffer[kMaxLen];
  static map<string, Int> dict;

  dict.clear();
  for (int pos = 0; scanf("%s", buffer) == 1 && buffer[0] != '$'; ++pos) {
    int& last = dict[buffer];
    if (last == -1) {
      V.push_back(-1);
    } else {
      V.push_back(pos - last);
    }
    last = pos;
  }
}

/* Output a vector<T> to ostream (like cout) */
template<typename T> ostream& operator << (ostream& os, const vector<T>& V) {
  bool first = true;
  for (typename vector<T>::const_iterator it = V.begin(); it != V.end(); ++it) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << *it;
  }
  return os;
}

#define TRACE(x) cout << #x " = " << x << endl

/* Slightly modified Knuth-Morris-Pratt matcher */

class Kmp {
public:
  Kmp(const vector<int>& P) : P(P) {
    computePi();
  }

  int match(const vector<int>& T) {
    int tI = 0;
    int pI = 0;

    const int pLen = P.size();
    const int tLen = T.size();

    while (tI < tLen) {
      int tVal = T[tI];
      if (tVal > pI) tVal = -1;

      if (tVal == P[pI]) {
        ++tI;
        ++pI;

        if (pI == pLen) {
          return tI - pLen;
        }
      } else if (pI > 0) {
        pI = pi[pI-1];
      } else {
        ++tI;
      }
    }

    return -7;
  }

  void printPi() {
    TRACE(pi);
  }

private:
  vector<int> pi; // KMP prefix function
  const vector<int>& P;

  void computePi() {
    int pLen = P.size();
    int i = 1, j = 0;

    pi.reserve(pLen);
    pi.push_back(0);

    while (i < pLen) {
      int iVal = P[i];
      if (iVal > j) iVal = -1;

      if (iVal == P[j]) {
        pi.push_back(++j);
        ++i;
        continue;
      } else if (j > 0) {
        j = pi[j-1];
        continue;
      } else {
        pi.push_back(0);
        ++i;
        continue;
      }
    }
  }
};

int main(void)
{
  vector<int> A, B;

  load(A);
  load(B);

  //  TRACE(A);
  //  TRACE(B);

  Kmp kmp(B);
  //  kmp.printPi();
  printf("%d\n", kmp.match(A) + 1);

  return (0-0);
}
