/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Pracowity Jas                                      *
 *   Autor:                Paweł Czerwiński                                   *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <iostream>
#include <cassert>

const int MAX_N = 1000000;
const int POW2_MAX_N = 1048576;
const int MODULO = 1000000007;


typedef long long int num_t;

struct _input_t {
  num_t n;
  num_t p[MAX_N];
};

typedef struct _input_t input_t;



void read_in(input_t * input) {
  num_t i;
  std::cin >> input->n;

  for(i = 0; i < input->n; ++i) {
    std::cin >> input->p[i];
  }
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

  std::cout << answer << std::endl;
  return 0;
}
