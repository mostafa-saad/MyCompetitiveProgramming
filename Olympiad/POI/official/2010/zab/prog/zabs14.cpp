/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs14.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n^2 * log n).         *
 *             Skakanie zabki symulujemy w czasie O(n).                  *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <assert.h>

using namespace std;

const int MAX_N = 1000000;

struct para {
  int x, y;
};

int n, k;
long long m;
long long p[MAX_N];
int kty[MAX_N];

inline long long ABS(long long x) {
  return x < 0 ? -x : x;
}

void oblicz_kte() {
  for (int i = 0; i < n; ++i) {
    vector<pair<long long, int> > pom;
    for (int j = 0; j < n; ++j) {
      pom.push_back(make_pair(ABS(p[i] - p[j]), j));
    }
    sort(pom.begin(), pom.end());
    if (pom[k].first == pom[k - 1].first) {
      pom[k].second = pom[k - 1].second;
    }
    kty[i] = pom[k].second;
  }
}

para cykl[MAX_N];
para v2c[MAX_N];
para dzieci[MAX_N];
int stan[MAX_N];
int pom[MAX_N];
int pam[MAX_N], pam_nr = 0;
int wynik[MAX_N];

void znajdz_cykle() {
  for (int i = 0; i < n; ++i) {
    stan[i] = v2c[i].x = -1;
  }
  int cykl_nr = 0;
  for (int i = 0; i < n; ++i) {
    if (stan[i] < 0) {
      int top = 0, v = i;
      while (stan[v] < 0) {
        stan[v] = i;
        pom[top++] = v;
        v = kty[v];
      }
      if (stan[v] == i) {
        int b = top - 1;
        while (pom[b] != v) --b;
        cykl[cykl_nr].x = pam_nr; cykl[cykl_nr].y = top - b;
        for (int j = b; j < top; ++j) {
          v = pam[pam_nr++] = pom[j];
          v2c[v].x = cykl_nr; v2c[v].y = j - b;
        }
        ++cykl_nr;
      }
    }
  }
}

void zbuduj_las() {
  for (int i = 0; i < n; ++i) {
    pom[i] = 0;
  }
  for (int i = 0; i < n; ++i) {
    if (v2c[i].x < 0) {
      ++pom[kty[i]];
    }
  }
  for (int i = 0; i < n; ++i) {
    dzieci[i].x = dzieci[i].y = pam_nr;
    pam_nr += pom[i];
  }
  for (int i = 0; i < n; ++i) {
    if (v2c[i].x < 0) {
      pam[dzieci[kty[i]].y++] = i;
    }
  }
}

void rozwiaz_las() {
  zbuduj_las();
  for (int i = 0; i < n; ++i) {
    stan[i] = -1;
  }
  for (int i = 0; i < n; ++i) {
    if (v2c[i].x >= 0) {
      int c = v2c[i].x, b = cykl[c].x, p = v2c[i].y, d = cykl[c].y;
      int top = 0;
      pom[top++] = i;
      while (top > 0) {
        int v = pom[top - 1];
        if (stan[v] < 0) {
          stan[v] = dzieci[v].x;
          if (m > top - 1) {
            wynik[v] = pam[b + ((p + (m - top + 1)) % d)];
          } else {
            wynik[v] = pom[top - 1 - m];
          }
        }
        if (stan[v] < dzieci[v].y) {
          pom[top++] = pam[stan[v]++];
        } else {
          --top;
        }
      }
    }
  }
}

void skacz() {
  znajdz_cykle();
  rozwiaz_las();
  for (int i = 0; i < n; ++i) {
    printf("%d", wynik[i] + 1);
    if (i < n - 1) {
      putchar(' ');
    } else {
      puts("");
    }
  }
}

int main() {
  assert(scanf("%d%d%lld", &n, &k, &m) == 3);
  for (int i = 0; i < n; ++i) {
    assert(scanf("%lld", p + i) == 1);
  }
  oblicz_kte();
  skacz();
  return 0;
}

