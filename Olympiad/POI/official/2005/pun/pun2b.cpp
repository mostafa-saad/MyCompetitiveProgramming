/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PUN (Punkty)                                   *
 *   Plik:                pun2b.cpp                                      *
 *   Autor:               Arkadiusz Paterek                              *
 *   Opis:                Rozwi±zanie niepoprawne 2                      *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const bool debug = false;
const bool debug2 = false;

#define x first
#define y second

typedef float ld;
typedef pair < ld, ld > Point;

ld pi;                          // = 4*arctg(1)
const ld epsilon = 1e-6f;

const int MIN_XY = -20000;      // maksymalna warto¶æ wspó³rzêdnej
const int MAX_XY = 20000;       // maksymalna warto¶æ wspó³rzêdnej
const int MAX_K = 25000;        // maksymalna liczba punktów w zbiorze

// Wczytuje opis zbioru punktów.
void readSet(vector < Point > &result)
{
  int size;
  cin >> size;
  for (int i = 0; i < size; ++i) {
    ld x, y;
    cin >> x >> y;
    result.push_back(make_pair(x, y));
  }
}

// Wczytuje wej¶cie: wzór i zbiory punktów do porównania z wzorem
void readInput(vector < Point > &pattern, vector < vector < Point > >&sets)
{
  readSet(pattern);
  int n;
  cin >> n;
  sets.resize(n);
  for (int i = 0; i < n; ++i)
    readSet(sets[i]);
}

void print(vector < Point > &set)
{
  if (!debug)
    return;
  for (int i = 0; i < (int) set.size(); ++i)
    cout << "(" << set[i].x << ", " << set[i].y << ") ";
  cout << endl;
}

inline ld length(Point & p)
{
  return sqrt(p.x * p.x + p.y * p.y);
}

// Oblicza rozmiar zbioru wektorów (d³ugo¶æ najd³u¿szego wektora).
ld getSize(vector < Point > &set)
{
  int k = set.size();
  ld best = 0;
  for (int i = 0; i < k; ++i) {
    ld size = length(set[i]);
    if (size > best)
      best = size;
  }
  return best;
}

// Porównanie warto¶ci double.
// W diffDigit zwraca indeks pierwszej cyfry (dziesiêtnej) po przecinku,
// na której v1 i v2 ró¿ni± siê.
ld equals(ld v1, ld v2, int &diffDigit)
{
  ld result;
  if (v1 >= v2)
    result = v1 - v2;
  else
    result = v2 - v1;

  ld diff = 1.0L;
  diffDigit = 0;
  while (diffDigit < 16 && diff > result) {
    diff /= 10;
    ++diffDigit;
  }

  return result < epsilon;
}

ld equals(ld v1, ld v2)
{
  int tmp = 0;
  return equals(v1, v2, tmp);
}

// Przeskalowanie i przesuniêcie zbioru punktów,
// tak aby ¶rodek ciê¿ko¶ci znalaz³ siê w punkcie (0,0)
// oraz najd³u¿szy wektor (punkt) mia³ d³ugo¶æ MAX_XY.
void transform(vector < Point > &set)
{
  int k = set.size();

  ld sum_x = 0;
  ld sum_y = 0;
  for (int i = 0; i < k; ++i) {
    sum_x += set[i].x;
    sum_y += set[i].y;
  }

  for (int i = 0; i < k; ++i) {
    set[i].x *= k;
    set[i].y *= k;
  }

  for (int i = 0; i < k; ++i) {
    set[i].x -= sum_x;
    set[i].y -= sum_y;
  }

  ld size = getSize(set);
  if (equals(size, 0))
    return;

  ld scale = MAX_XY / size;
  for (int i = 0; i < k; ++i) {
    set[i].x *= scale;
    set[i].y *= scale;
  }
}

// Zwraca k±t (w radianach), jaki tworzy wektor p z wektorem (1,0).
ld getAngle(Point p)
{
  ld len = length(p);
  if (len < epsilon)
    return 0;

  ld sinus = p.y / len;
  ld cosinus = p.x / len;
  ld asinus = asin(sinus);      // przyjmuje warto¶ci z przedzia³u [-pi/2,pi/2]

  if (sinus >= 0)               // asin \in [0,pi/2]
    if (cosinus >= 0)
      return asinus;            // æwiartka I
    else
      return pi - asinus;       // æwiartka II
  else                          // asin \in [-pi/2,0)
  if (cosinus >= 0)
    return asinus + 2 * pi;     // æwiartka IV
  else
    return pi - asinus;         // æwiartka III
}

// Sortowanie wektorów (punktów) wzglêdem k±tów, jakie tworz± z wektorem (1,0).
// Wynikiem jest tablica punktów we wspó³rzêdnych biegunowych
// (pary (k±t, d³ugo¶æ wektora)), posortowana po k±tach i po d³ugo¶ciach wektorów.
// Punkty (0,0) s± traktowane jako minimalne i trafiaj± na pocz±tek tablicy.
void sortByAngles(vector < Point > &set, vector < Point > &result)
{
  int k = set.size();
  result.resize(0);

  for (int i = 0; i < k; ++i)
    result.push_back(make_pair(getAngle(set[i]), length(set[i])));

  sort(result.begin(), result.end());
}

// Odejmowanie k±tów modulo 2*pi. Wszystkie k±ty nale¿± do przedzia³u [0,2*pi)
inline ld subAngle(ld a1, ld a2)
{
  ld result = a1 - a2;
  if (result < 0)
    result += 2 * pi;
  return result;
}

// Porównanie cykliczne ci±gów w czasie O(n^2).
bool equal(vector < Point > &set1, vector < Point > &set2, int &bestDiff)
{
  int k = set1.size();
  for (int i = 0; i < k; ++i) {
    if (debug)
      cout << "* " << i << endl;
    bool match = true;
    ld angleDiff1 = subAngle(set2[i].first, set1[0].first);
    int thisDiff = 64;
    for (int j = 0; j < k; ++j) {
      Point & p1 = set1[j];
      Point & p2 = set2[(j + i) % k];
      ld angleDiff2 = subAngle(p2.first, p1.first);
      int diff1 = 64;
      int diff2 = 64;
      if (debug)
        printf("%.63f\n%.63f\n%.63f\n%.63f\n", angleDiff2, angleDiff1,
               p2.second, p1.second);
      bool eq1 = equals(angleDiff2, angleDiff1, diff1);
      bool eq2 = equals(p2.second, p1.second, diff2);
      if (debug)
        cout << diff1 << " " << diff2 << endl << endl;
      if (min(diff1, diff2) < thisDiff)
        thisDiff = min(diff1, diff2);
      if (!eq1 || !eq2) {
        match = false;
        break;
      }
    }
    if (thisDiff > bestDiff)
      bestDiff = thisDiff;
    if (match)
      return true;
  }
  return false;
}

void solve(vector < Point > &pattern, vector < vector < Point > >&sets)
{
  vector < Point > seq1, seq2;

  print(pattern);
  transform(pattern);
  sortByAngles(pattern, seq1);
  print(pattern);
  print(seq1);

  int k = pattern.size();
  for (int i = 0; i < (int) sets.size(); ++i) {
    if ((int) sets[i].size() != k)  // Czy i-ty zbiór jest tego samego rozmiaru, co wzór?
      cout << "NIE" << endl;
    else {
      print(sets[i]);
      transform(sets[i]);
      sortByAngles(sets[i], seq2);
      print(sets[i]);
      print(seq2);
      int error = -1;
      if (equal(seq1, seq2, error))
        cout << "TAK" << endl;
      else {
        for (int j = 0; j < k; ++j) // Zbiór jest poddawany symetrii wzglêdem prostej y=0.
          sets[i][j].x = -sets[i][j].x;
        sortByAngles(sets[i], seq2);
        print(seq2);
        if (equal(seq1, seq2, error))
          cout << "TAK" << endl;
        else {
          cout << "NIE" << endl;
        }
      }
      if (debug2)
        cout << "diff = " << error << endl;
    }
  }
}

int main()
{
  pi = 4 * atan(1.0L);

  vector < Point > pattern;
  vector < vector < Point > >sets;

  readInput(pattern, sets);
  solve(pattern, sets);
}
