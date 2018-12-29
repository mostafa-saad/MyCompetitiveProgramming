/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Pracowity Jas                                      *
 *   Autor:                Paweł Czerwiński                                   *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/



#include <stdio.h>
#include <assert.h>

#define MAX_N 1000000
#define POW2_MAX_N 1048576
#define MODULO 1000000007


typedef long long int num_t;

struct _input_t {
  num_t n;
  num_t p[MAX_N];
};

typedef struct _input_t input_t;



void read_in(input_t * input) {
  num_t i;
  scanf("%lld", &input->n);
  for(i = 0; i < input->n; ++i) {
    scanf("%lld", input->p + i);
  }
}

void print_in(input_t * input) {
  num_t i;
  printf("%lld\n", input->n);
  for(i = 0; i < input->n - 1; ++i) {
    printf("%lld ", input->p[i]);
  }
  printf("%lld", input->p[i]);
  printf("\n");
}


num_t g(num_t n) {
  assert(n >= 1);
  return (((n-1)/2) + 1) % MODULO;
}

static num_t _f[MAX_N + 1];
static num_t _pos[2 * POW2_MAX_N];
static num_t _pow2_n;


void init(num_t n){
  num_t i;
  _f[1] = 0;
  for(i = 2; i <= n; ++i){
    _f[i] = (((i % MODULO) * _f[i-1]) % MODULO  + (((i-1) % MODULO) * (g(i) % MODULO) % MODULO)) % MODULO;
    //_f[i] = i * _f[i-1] + (i-1) * g(i);
  }

  _pow2_n = 1;
  while(n > _pow2_n) {
    _pow2_n *= 2;
  }

  for(i = _pow2_n; i < 2 * _pow2_n; ++i) {
    _pos[i] = 1;
  }

  for(i = _pow2_n; i > 0; --i) {
    _pos[i-1] = _pos[2*(i-1)] + _pos[2*(i-1) + 1];
  }
}

num_t my_node(num_t x) {
  return _pow2_n + x - 1;
}

void remove_x(num_t x) {
  num_t v = my_node(x);
  while(v != 0) {
    assert(_pos[v] >= 1);
    _pos[v] -= 1;
    v /= 2;
  }
}

num_t position_x(num_t x) {
  num_t v = my_node(x);
  num_t pos = _pos[v];

  if (pos == 0)
    return 0;
  while (v != 1) {
    if (v % 2 == 1)
      pos += _pos[v - 1];
    v /= 2;
  }
  return pos;
}

num_t f(num_t n) {
  return _f[n];
}




int main() {
  input_t input;
  num_t answer = 0;
  num_t n;
  num_t i,pos;

  read_in(&input);

  init(input.n);
  n = input.n;

  for(i = 0; i < input.n; ++i){

    pos = position_x(input.p[i]);
    answer = (answer + ((pos - 1) * (f(n-1) + g(n))) % MODULO) % MODULO;
    remove_x(input.p[i]);
    n--;
  }

  printf("%lld\n", answer);
  return 0;
}


// 1)
// Pierwsza obserwacja: liczba swapów
// od permutacji
// x y z ...
// do
// 1 2 3 4 ...
//
// jest równa ilości swapów od
// 1 2 3 4 ...
// do
// x y z
// (tak wygodniej mi myśleć :p )
//
//
// 2)
// Załóżmy mamy funkcję f która dla zadanego n zwraca liczbę swapów potrzebną do przejścia przez wszystkie kolejne permutacje od
// 1 2 3 ... n
// do
// n n-1 ... 2 1
//
// (tj f(3) = 7 bo
// 1 2 3 -> 1 3 2   :  1
// 1 3 2 -> 2 1 3   :  2
// 2 1 3 -> 2 3 1   :  1
// 2 3 1 -> 3 1 2   :  2
// 3 1 2 -> 3 2 1   :  1
// )
//
//
// 3)
// pomocna również będzie funkcja g, która zwraca liczbę swapów potrzebną do przejścia z permutacji
// x b_1 .. b_(n-1)
// gdzie b_i > b_(i+1)
// do
// b_j   b_(n-1) ... x ... b_1
//
// gdzie b_(j-1) > x > b_(j+1)
//
// tj z ostatniej permutacji o prefiksie x do następnej w porządku leksykograficznym
//
// (g(3) = 2
// 1 3 2 -> 2 1 3   :  2
//
// g(4) = 2
// 1 4 3 2 -> 2 1 3 4  : 2
// )
//
//
// 4)
// naszym celem jest obliczenie liczby swapów od permutacji
// 1 2 3 ... n
// do
// x y z ...
// wpierw obliczamy
// od 1 2 3
// do
// x a_1 a_2 ...
//
// gdzie a jest posortowane tj. a_i < a_(i+1)
// (pierwszej permutacji o prefiksie x )
//
// ta wartość to
// (x - 1) * (f(n-1) + g(n))
//
// wyjaśnienie
//
// 1 2 3 4 5
// do
// 1 5 4 3 2   to f(4)
// do
// 2 1 3 4 5  to g(5)
// do
// 2 5 4 3 1 to f(4)
// do
// 3 1 2 4 5 to g(5) itd
//
// jak obliczyliśmy liczbę przejść do x a_1 a_2 ...
// to teraz liczymy liczbę przejść z a_1 a_2 ...
// do y b_1 b_2
// (mamy już ciąg bez x, tj o 1 krótszy)
// itd.
//
// pod koniec sumujemy i mamy wynik.
//
//
// 5)
//
// jedynie brakuje nam magicznych funkcji f i g
//
// g(n) = podłoga((n-1) / 2)  + 1
//
// dowód.
// mamy obliczyć liczbę swapów
//
// x b_1 .. b_(n-1)
// gdzie b_i > b_(i+1)
// do
// b_j   b_(n-1) ... x ... b_1
//
// gdzie b_(j-1) > x > b_(j+1)
//
// wpierw odwracamy
// b_1 .. b_(n-1) do b_(n-1) ... b_1   mamy podłoga((n-1)/2) swapy
// następnie zamieniamy x z b_j czyli mamy łącznie podłoga((n-1)/2) + 1 swapy
//
// dowód minimalności
// a) niech n będzie parzyste wtedy mamy co najmniej
// n-1 elementów do przestawienia   (element środkowy ciągu b nie jest ruszany)
// jeden swap ustawia maksymalnie 2 elementy
// więc potrzebujemy co najmniej
// sufit((n-1/2)) swapów
// skoro n jest parzyste to
// sufit((n-1/2)) = podłoga((n-1)/2) + 1
//
// b) niech n będzie nieparzyste
// wtedy musimy przestawić każdy element wiec potrzeba
// sufit(n/2) = n/2 + 1 = podłoga((n-1)/2) + 1 swapów
//
// więc jesteśmy szczęśliwi
// g(n) = podłoga((n-1)/2) + 1
//
//
// 6)
// f(n) = n * f(n-1) + (n-1) * g(n) = n * f(n-1) + (n-1)(podłoga((n-1)/2) + 1)
