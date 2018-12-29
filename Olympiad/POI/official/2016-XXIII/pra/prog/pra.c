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
  return ((n-1)/2) + 1;
}

static num_t _pos[2 * POW2_MAX_N];
static num_t _pow2_n;


void init(num_t n){
  num_t i;

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



void get_index(input_t const * const input, num_t _I[]) {
  num_t i;
  init(input->n);

  for (i = 0; i < input->n + 1; ++i){
    _I[i] = 0;
  }

  for (i = 0; i < input->n; ++i){
    _I[input->n - 1 - i] += position_x(input->p[i]) - 1;
    remove_x(input->p[i]);
  }

  for (i = 0; i < input->n; ++i) { // maksymalna permutacja to n! - 1
    if(_I[i] >= i + 1) {
      _I[i + 1] += (_I[i] - (_I[i] % (i + 1))) / (i + 1);
      _I[i] %= i + 1;
    }
    assert(_I[i] >= 0);
  }

}


num_t answer(num_t I[], num_t n) {
  num_t answer = 0;
  num_t k;
  num_t l, r;
  num_t count;
  num_t multipler;

  l = I[n-1];
  r = 0;
  for(k = n; k > 1; --k) {
    multipler = ((k + 1) / 2) % MODULO;

    assert(l >= r);
    count = (l - r) % MODULO;
    answer = (answer + ((count * multipler) % MODULO)) % MODULO;

    r = l % MODULO;
    l = (I[k - 2] + ((k - 1) * r) % MODULO) % MODULO;
    if (r > l)
      l += MODULO;
  }
  return answer;
}

int main() {
  input_t input;

  static num_t I[MAX_N + 1];

  read_in(&input);

  init(input.n);
  get_index(&input, I);

  printf("%lld\n", answer(I, input.n));

  return 0;
}
