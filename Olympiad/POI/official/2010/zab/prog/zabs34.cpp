/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs34.cpp                                                *
 *   Autor:    Lukasz Bieniasz-Krzywiec                                  *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             k-te kamienie wyznaczamy w czasie O(n * log Z * log m).   *
 *             Skakanie zabki symulujemy w czasie O(n).                  *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <assert.h>

using namespace std;

const int MAX_N = 1000000;
const long long MIN_P = 0;
const long long MAX_P = (long long)1000000 * 1000000 * 1000000;

struct para {
  int x, y;
};

int n, k;
long long m;
long long p[MAX_N];
int kty[MAX_N];

/* Zwraca najmniejsze j (0 <= j < n), takie �e p[i] - p[j] <= d. */
int na_lewo(int i, long long d) {
  int l = 0, r = i;
  while (l < r) {
    int s = (l + r) / 2;
    if (p[i] - p[s] > d) l = s + 1; else r = s;
  }
  return l;
}

/* Zwraca najwi�ksze j (0 <= j < n), takie �e p[j] - p[i] <= d. */
int na_prawo(int i, long long d) {
  int l = i, r = n - 1;
  while (l < r) {
    int s = (l + r + 1) / 2;
    if (p[s] - p[i] > d) r = s - 1; else l = s;
  }
  return l;
}

void oblicz_kte() {
  for (int i = 0; i < n; ++i) {
    int a, b;
    long long l = MIN_P, r = p[n - 1];
    while (l < r) {
      long long s = (l + r) / 2;
      a = na_lewo(i, s);
      b = na_prawo(i, s);
      if (b - a + 1 <= k) l = s + 1; else r = s;
    }
    a = na_lewo(i, l);
    b = na_prawo(i, l);
    if (p[i] - p[a] >= p[b] - p[i]) {
      kty[i] = a;
    } else {
      kty[i] = b;
    }
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

