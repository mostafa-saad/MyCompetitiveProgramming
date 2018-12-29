/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PUN (Punkty)                                   *
 *   Plik:                pun.cpp                                        *
 *   Autor:               Arkadiusz Paterek                              *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

const bool debug = false;

#define x first
#define y second

typedef long long ll;
typedef unsigned long long ull;
typedef pair < ll, ll > Point;  // punkt lub wektor

typedef pair < ull, ull > Num;  // liczba 128-bitowa bez znaku: first to starsze bity, second to m³odsze
const ull mask32 = ((1ULL << 32) - 1);  // maska: jedynki na m³odszych 32 bitach

const ll MIN_XY = -20000;       // maksymalna warto¶æ wspó³rzêdnej
const ll MAX_XY = 20000;        // maksymalna warto¶æ wspó³rzêdnej
const ll MAX_K = 25000;         // maksymalna liczba punktów w zbiorze

// mno¿enie liczb 64-bitowych bez znaku, wynik 128-bitowy
inline Num mul(const ull n1, const ull n2)
{
  ull a = n1 >> 32;
  ull b = n1 & mask32;
  ull c = n2 >> 32;
  ull d = n2 & mask32;

  //        a b  2*32bit
  // *      c d  2*32bit
  // ----------
  //        d*b    64bit
  //      d*a      64bit
  //      c*b      64bit
  // +  c*a        64bit
  // ----------
  // = l3l2l1l0   128bit

  ull db = d * b;
  ull da = d * a;
  ull cb = c * b;
  ull ca = c * a;

  ull l0 = db & mask32;
  ull l1 = (db >> 32) + (da & mask32) + (cb & mask32);
  ull l2 = l1 >> 32;
  l1 &= mask32;
  l2 += (da >> 32) + (cb >> 32) + (ca & mask32);
  ull l3 = l2 >> 32;
  l2 &= mask32;
  l3 += ca >> 32;

  return make_pair((l3 << 32) | l2, (l1 << 32) | l0);
}

// Wczytuje opis zbioru punktów.
void readSet(vector < Point > &result)
{
  int size;
  cin >> size;
  for (int i = 0; i < size; ++i) {
    ll x, y;
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

void print(vector < pair < Num, Num > >&set)
{
  if (!debug)
    return;
  for (int i = 0; i < (int) set.size(); ++i)
    cout << "(" << set[i].first.first << " " << set[i].first.
        second << ", " << set[i].second.first << " " << set[i].second.
        second << ") ";
  cout << endl;
}

void print(vector < Point > &set)
{
  if (!debug)
    return;
  for (int i = 0; i < (int) set.size(); ++i)
    cout << "(" << set[i].x << ", " << set[i].y << ") ";
  cout << endl;
}

// Przeskalowanie i przesuniêcie zbioru punktów,
// tak aby ¶rodek ciê¿ko¶ci znalaz³ siê w punkcie (0,0).
void transform(vector < Point > &set)
{
  int k = set.size();

  ll sum_x = 0;
  ll sum_y = 0;
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
}

// Odejmowanie wektorów.
Point operator-(const Point & p1, const Point & p2)
{
  return make_pair(p1.x - p2.x, p1.y - p2.y);
}

// Kwadrat d³ugo¶ci wektora.
ull sqrSize(const pair < ull, ull > p)
{
  return p.x * p.x + p.y * p.y;
}

// Oblicza kwadrat rozmiaru zbioru.
// Rozmiar to maksymalna d³ugo¶æ wektora, je¶li punkty zbioru potraktujemy
// jako wektory.
ull getSqrSize(vector < Point > &set)
{
  ull size = 0;
  for (int i = 0; i < (int) set.size(); ++i) {
    ull dist = sqrSize(set[i]);
    if (dist > size)
      size = dist;
  }
  return size;
}

// Kryterium podzia³u zbioru punktów na dwie czê¶ci:
// do pierwszej nale¿± punkty z I i II æwiartki uk³adu wspó³rzêdnych,
// punkty na dodatniej czê¶ci osi X oraz punkt (0,0).
bool upperPart(const Point & p)
{
  return p.x > 0 || (p.x == 0 && p.y >= 0);
}

// Porz±dek k±towy (relacja <) na wektorach.
// Za³o¿enie: porównywany zbiór wektorów le¿y na jednej po³owie uk³adu wspó³rzêdnych.
struct ltstr {
  bool operator() (const Point & p1, const Point & p2) {
    ll vectorProduct = p1.x * p2.y - p2.x * p1.y;
    if (vectorProduct != 0)
       return vectorProduct > 0;
    else                        // Je¶li maj± ten sam kierunek, mniejszy jest ten o mniejszej d³ugo¶ci.
       return sqrSize(p1) < sqrSize(p2);  // Wystarczy porównaæ kwadraty d³ugo¶ci wektorów.
    // Zauwa¿my, ¿e w takim porz±dku wektor (0,0) jest mniejszy od ka¿dego innego
    // wektora i po posortowaniu znajdzie siê na pocz±tku.
}};

// Sortowanie wektorów (punktów) wzglêdem k±tów, jakie tworz± z wektorem (1,0)
// oraz wzglêdem d³ugo¶ci.
// Punkty (0,0) s± traktowane jako minimalne i trafiaj± na pocz±tek tablicy.
void sortByAngles(vector < Point > &set)
{
  // Podzia³ zbioru punktów wed³ug kryterium upperPart (patrz opis funkcji upperPart).
  vector < Point >::iterator middle =
      partition(set.begin(), set.end(), upperPart);

  // Sortowanie obu czê¶ci.
  sort(set.begin(), middle, ltstr());
  sort(middle, set.end(), ltstr());
}

const ull prime = 10000019LL;   // du¿a liczba pierwsza
                             // (ale MAX*(prime+1) musi siê mie¶ciæ w long long)
//const ll MAX = 1ULL<<32;
ull _pow;                       // zmienna pomocnicza równa MAX^(8k-1) % prime

// Oblicza MAX^(8k-1) % prime.
ull calcPow(int k)
{
  ull _pow = 1;
  for (int i = 1; i <= 8 * k - 1; ++i) {
    _pow <<= 32;                // pow *= MAX;
    _pow %= prime;
  }
  return _pow;
}

// sum to suma kontrolna ci±gu.
// Obliczenie nowej sumy kontrolnej dla ci±gu z elementem next do³±czonym na koniec
ull checksumAdd(ull sum, ull next)
{
  next %= prime;
  sum <<= 32;                   // sum *= MAX;
  sum += next;
  sum %= prime;
  return sum;
}

// Oblicza sumê kontroln± ci±gu seq.
ull checksum(vector < pair < Num, Num > >&seq)
{
  ull sum = 0;
  int k = seq.size();
  for (int i = 0; i < k; ++i) {
    // Kwadraty odleg³o¶ci (128b) s± dzielone na 32-bitowe czê¶ci,
    // ¿eby unikn±æ przepe³nienia podczas obliczeñ.
    sum = checksumAdd(sum, seq[i].first.first >> 32);
    sum = checksumAdd(sum, seq[i].first.first & mask32);
    sum = checksumAdd(sum, seq[i].first.second >> 32);
    sum = checksumAdd(sum, seq[i].first.second & mask32);
    sum = checksumAdd(sum, seq[i].second.first >> 32);
    sum = checksumAdd(sum, seq[i].second.first & mask32);
    sum = checksumAdd(sum, seq[i].second.second >> 32);
    sum = checksumAdd(sum, seq[i].second.second & mask32);
  }
  return sum;
}

// Suma kontrolna po przestawieniu elementu next na koniec ci±gu.
ull _checksumCycle(ull sum, ull next)
{
  next %= prime;
  sum += (prime - next) * _pow;
  sum %= prime;
  sum <<= 32;                   // sum *= MAX;
  sum += next;
  sum %= prime;
  return sum;
}

// sum to suma kontrolna ci±gu, p to pierwszy element ci±gu
// Oblicza sumê kontroln± ci±gu po przestawieniu elementu p na koniec ci±gu.
ull checksumCycle(ull sum, pair < Num, Num > &p)
{
  // Podobnie jak w funkcji crc, elementy s± dzielone na 32-bitowe czê¶ci.
  sum = _checksumCycle(sum, p.first.first >> 32);
  sum = _checksumCycle(sum, p.first.first & mask32);
  sum = _checksumCycle(sum, p.first.second >> 32);
  sum = _checksumCycle(sum, p.first.second & mask32);
  sum = _checksumCycle(sum, p.second.first >> 32);
  sum = _checksumCycle(sum, p.second.first & mask32);
  sum = _checksumCycle(sum, p.second.second >> 32);
  sum = _checksumCycle(sum, p.second.second & mask32);
  return sum;
}

// Porównanie ci±gu seq1 i ci±gu seq2 przesuniêtego cyklicznie o i.
bool compare(vector < pair < Num, Num > >&seq1, vector < pair < Num,
             Num > >&seq2, int j)
{
  int k = seq1.size();
  for (int i = 0; i < k; ++i)
    if (seq1[i] != seq2[(i + j) % k])
      return false;
  return true;
}

// Sprawdzenie, czy dwa ci±gi punktów s± podobne.
// Ci±gi s± równoliczne, posortowane, maj± ¶rodek ciê¿ko¶ci w punkcie (0,0).
bool equal(vector < Point > &set1, vector < Point > &set2)
{
  // Obliczam rozmiar zbiorów (kwadrat d³ugo¶ci najd³u¿szego wektora w zbiorze).
  ull sqrsize1 = getSqrSize(set1);
  ull sqrsize2 = getSqrSize(set2);

  // Przeskalowujê wektory, tak ¿eby zbiory mia³y ten sam rozmiar. Konwertujê ka¿dy
  // punkt na parê (kwadrat d³ugo¶ci wektora, kwadrat odleg³o¶ci od kolejnego wektora).
  // Wynik umieszczam w tablicach seq1 i seq2.
  vector < pair < Num, Num > >seq1, seq2;
  int k = set1.size();
  for (int i = 0; i < k; ++i) {
    Num length = mul(sqrsize2, sqrSize(set1[i])); // kwadrat rozmiaru wektora
    Num dist = mul(sqrsize2, sqrSize(set1[i] - set1[(i + 1) % k])); // kwadrat odleg³o¶ci od kolejnego wektora
    seq1.push_back(make_pair(length, dist));
  }
  for (int i = 0; i < k; ++i) {
    Num length = mul(sqrsize1, sqrSize(set2[i]));
    Num dist = mul(sqrsize1, sqrSize(set2[i] - set2[(i + 1) % k]));
    seq2.push_back(make_pair(length, dist));
  }

  // Sprawdzam, czy obliczone ci±gi par (kwadrat d³ugo¶ci wektora, kwadrat
  // odleg³o¶ci od kolejnego wektora) s± cyklicznie równowa¿ne (algorytm Rabina-Millera).
  ull sum1 = checksum(seq1);
  ull sum2 = checksum(seq2);

  for (int i = 0; i < k; ++i) { // Dla ka¿dego mo¿liwego przesuniêcia ci±gu seq2...
    if (sum1 == sum2)           // Je¶li sumy kontrolne s± identyczne, dla pewno¶ci porównujemy ci±gi bezpo¶rednio.
      if (compare(seq1, seq2, i)) // Porównanie w czasie O(k) ci±gu seq1
        return true;            // z ci±giem seq2 przesuniêtym cyklicznie o i.
    sum2 = checksumCycle(sum2, seq2[i]);
  }

  return false;
}

// Sprawdzenie, czy to punkt (0,0)
bool zero(const Point & p)
{
  return p.first == 0 && p.second == 0;
}

void solve(vector < Point > &pattern, vector < vector < Point > >&sets)
{
  transform(pattern);
  sortByAngles(pattern);
  bool has_zero = false;        // Czy wzór zawiera punkt (0,0)?
  if (zero(pattern[0])) {
    has_zero = true;
    pattern.erase(pattern.begin());
  }

  int k = pattern.size();
  _pow = calcPow(k);
  for (int i = 0; i < (int) sets.size(); ++i) {
    transform(sets[i]);
    sortByAngles(sets[i]);
    if (has_zero) {             // Je¶li wzór zawiera (0,0), sprawdzamy czy i-ty zbiór te¿ zawiera (0,0).
      if (zero(sets[i][0]))
        sets[i].erase(sets[i].begin());
      else {
        cout << "NIE" << endl;
        continue;
      }
    }
    if ((int) sets[i].size() != k)  // Czy i-ty zbiór jest tego samego rozmiaru, co wzór?
      cout << "NIE" << endl;
    else if (k <= 1)            // zbiory jedno- lub dwupunktowe s± zawsze podobne
      cout << "TAK" << endl;
    else {
      if (equal(pattern, sets[i]))
        cout << "TAK" << endl;
      else {
        for (int j = 0; j < k; ++j) // Zbiór jest poddawany symetrii wzglêdem prostej y=0.
          sets[i][j].x = -sets[i][j].x;
        sortByAngles(sets[i]);
        if (equal(pattern, sets[i]))
          cout << "TAK" << endl;
        else
          cout << "NIE" << endl;
      }
    }
  }
}

int main()
{
  vector < Point > pattern;
  vector < vector < Point > >sets;

  readInput(pattern, sets);
  solve(pattern, sets);
}
