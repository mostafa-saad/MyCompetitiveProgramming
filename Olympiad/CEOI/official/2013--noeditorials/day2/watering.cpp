// CEOI 2013 - Task: Watering - Solution
// Author: Adrian Satja Kurdija

// Warning! The solution may not solve all possible inputs (this is an output-only task).
// Read the algorithm description at http://ceoi2013.hsin.hr

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char a[605][605];
char b[10][10];
int R, S;

inline char c(int i, int j) {
    return 'b' + i * 5 + j;
}

char ccc = 'z';
inline char cc(int i, int j) {
    ccc = (ccc == 'z'? 'y' : 'z');
    return ccc;
}

bool solve() {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (b[i][j] == '.') {
                b[i][j] = c(i,j);
                if (j+2 < 5 && b[i][j+1] == '.' && b[i][j+2] == '.') {
                    b[i][j+1] = b[i][j+2] = c(i,j);
                    if (solve()) return true;
                    b[i][j+1] = b[i][j+2] = '.';
                }
                if (i+2 < 5 && b[i+1][j] == '.' && b[i+2][j] == '.') {
                    b[i+1][j] = b[i+2][j] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i+2][j] = '.';
                }
                if (i+1 < 5 && j+1 < 5 && b[i+1][j] == '.' && b[i][j+1] == '.') {
                    b[i+1][j] = b[i][j+1] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i][j+1] = '.';
                }
                if (i+1 < 5 && j+1 < 5 && b[i][j+1] == '.' && b[i+1][j+1] == '.') {
                    b[i][j+1] = b[i+1][j+1] = c(i,j);
                    if (solve()) return true;
                    b[i][j+1] = b[i+1][j+1] = '.';
                }
                if (i+1 < 5 && j+1 < 5 && b[i+1][j] == '.' && b[i+1][j+1] == '.') {
                    b[i+1][j] = b[i+1][j+1] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i+1][j+1] = '.';
                }
                if (i+1 < 5 && j-1 >= 0 && b[i+1][j] == '.' && b[i+1][j-1] == '.') {
                    b[i+1][j] = b[i+1][j-1] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i+1][j-1] = '.';
                }
                b[i][j] = '.';
                return false;
            }
    return true;
}

char ograda = '#';
inline char& p(int r, int s, int x, int y) {
  if (x < 0 || x >= 5 || y < 0 || y >= 5)
    return ograda;
  return a[r * 5 + x][s * 5 + y];
}

inline char h(int x, int y) {
  if (a[x][y] != a[x+1][y] || a[x][y] == '.')
    return '-';
  return '_';
}
inline char v(int x, int y) {
  if (a[x][y] != a[x][y+1] || a[x][y] == '.')
    return '|';
  return '_';
}

inline void ispis() {
  for (int x = 0; x < R * 5; ++x) {
    for (int y = 0; y < S * 5; ++y) {
      printf("%c", a[x][y]);
      if (y % 5 == 4 && y + 1 != S * 5)
        printf("%c", v(x, y));
    }
    printf("\n");
    if (x % 5 != 4 || x == R * 5 - 1)
      continue;
    for (int y = 0; y < S * 5; ++y) {
      printf("%c", h(x, y));
      if (y % 5 == 4 && y + 1 != S * 5)
        printf("+");
    }
    printf("\n");
  }
}

int main () {
  scanf("%d%d", &R, &S);
  for (int x = 0; x < R * 5; ++x)
    for (int y = 0; y < S * 5; ++y)
      a[x][y] = '.';

  char buff[S * 6];
  int x = 0;
  while (x < 5 * R) {
    scanf("%s", buff);
    if (buff[0] == '-') continue;
    int s = strlen(buff);
    int y = 0;
    for (int j = 0; j < s; ++j) {
      if (buff[j] == '|') continue;
      if (buff[j] == '#')
        a[x][y] = '#';
      y++;
    }
    x++;
  }

  vector<pair<int,int> > polja;
  for (int r = 0; r < R; ++r)
    if (r % 2 == 0)
      for (int s = 0; s < S; ++s)
        polja.push_back(make_pair(r, s));
    else
      for (int s = S - 1; s >= 0; --s)
        polja.push_back(make_pair(r, s));

  for (int i = 0; i < (int)polja.size() - 1; ++i) {
    // Treba li staviti triominu izmedju polja?
    int praznih = 0;
    for (int x = 0; x < 5; ++x)
      for (int y = 0; y < 5; ++y)
        praznih += (p(polja[i].first, polja[i].second, x, y) == '.');
//    printf("(%d %d) %d\n", polja[i].first, polja[i].second, praznih);
    if (praznih % 3 == 0) continue;

    // Stavi triominu tako da (praznih - viri) % 3 == 0.
    // Nadji dva susjedna polja:
    for (int x = 0; x < 5; ++x)
      for (int y = 0; y < 5; ++y)
        for (int xx = 0; xx < 5; ++xx)
          for (int yy = 0; yy < 5; ++yy)
            if (abs(polja[i].first * 5 + x - polja[i + 1].first * 5 - xx)
                + abs(polja[i].second * 5 + y - polja[i + 1].second * 5 - yy)
                == 1 &&
                p(polja[i].first, polja[i].second, x, y) == '.' &&
                p(polja[i + 1].first, polja[i + 1].second, xx, yy) == '.') {
              int praznih_save = praznih;
              int j = i;
              int X = x, Y = y;
              praznih -= 2;
              if (praznih % 3 != 0) {
                j = i + 1;
                X = xx; Y = yy;
                ++praznih;
              }
              for (int nx = 0; nx < 5; ++nx)
                for (int ny = 0; ny < 5; ++ny)
                  if (abs(polja[j].first * 5 + X - polja[j].first * 5 - nx)
                      + abs(polja[j].second * 5 + Y - polja[j].second * 5 - ny)
                      == 1 &&
                      p(polja[j].first, polja[j].second, nx, ny) == '.') {
                    p(polja[i].first, polja[i].second, x, y) =
                    p(polja[i + 1].first, polja[i + 1].second, xx, yy) =
                    p(polja[j].first, polja[j].second, nx, ny) = cc(x, y);
              
              bool ok = true;
              for (int r = 0; r < 5 && ok; ++r)
                for (int s = 0; s < 5; ++s)
                  if (p(polja[i].first, polja[i].second, r, s) == '.' &&
                      p(polja[i].first, polja[i].second, r-1, s) != '.' &&
                      p(polja[i].first, polja[i].second, r+1, s) != '.' &&
                      p(polja[i].first, polja[i].second, r, s-1) != '.' &&
                      p(polja[i].first, polja[i].second, r, s+1) != '.' ||
                      p(polja[i + 1].first, polja[i + 1].second, r, s) == '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r-1, s) != '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r+1, s) != '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r, s-1) != '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r, s+1) != '.') {
                    ok = false;
                    break;
                  }
              if (ok) goto line;
              p(polja[i].first, polja[i].second, x, y) =
              p(polja[i + 1].first, polja[i + 1].second, xx, yy) =
              p(polja[j].first, polja[j].second, nx, ny) = '.';
              praznih = praznih_save;
              cc(x, y);
                  }
            }
    line: ;
  }

  for (int r = 0; r < R; ++r)
    for (int s = 0; s < S; ++s) {
      for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
          b[x][y] = p(r, s, x, y);
      if (!solve())
        printf("Shouldn't happen! %d %d\n\n", r, s);
      for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
          p(r, s, x, y) = b[x][y];
    }
  ispis();

  return 0;
}
