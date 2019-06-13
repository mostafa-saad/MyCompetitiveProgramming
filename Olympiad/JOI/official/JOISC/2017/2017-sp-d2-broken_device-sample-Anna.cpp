#include "Annalib.h"
#include <cstdio>

static bool used[150];
static int cnt[150];

static int dat[150];
static int it;

static int ans[150];

void set_block( int i, int a, int b, int c ){
  ans[i*3+0] = a;
  ans[i*3+1] = b;
  ans[i*3+2] = c;
}

void Anna( int N, long long X, int K, int P[] ){

  it = 0;
  for( int i = 0; i < N; i++ ){
    used[i] = false;
    cnt[i] = dat[i] = ans[i] = 0;
  }

  for( int i = 0; i < 60; i++ ){
    dat[i] = X % 2;
    X /= 2;
  }
  
  for( int i = 0; i < K; i++ ){
    used[ P[i] ] = true;
    cnt[ P[i] / 3 ]++;
  }

  for( int i = 0; i < N/3; i++ ){
    if( cnt[i] == 0 ){
      int c = dat[it] * 2 + dat[it+1];
      if( c == 0 ){
        set_block( i, 1, 0, 0 );
      } else if( c == 1 ){
        set_block( i, 1, 0, 1 );
      } else if( c == 2 ){
        set_block( i, 0, 1, 1 );
      } else if( c == 3 ){
        set_block( i, 1, 1, 1 );
      }
      it += 2;
    } else if( cnt[i] == 1 ){
      if( used[i*3+0] ){
        if( dat[it] == 0 ){
          set_block( i, 0, 1, 0 );
        } else if( dat[it] == 1 ){
          set_block( i, 0, 0, 1 );
        }
        it++;
      } else if( used[i*3+1] ){
        if( dat[it] == 1 ){
          set_block( i, 0, 0, 1 );
          it++;
        } else if( dat[it+1] == 0 ){
          set_block( i, 1, 0, 0 );
          it += 2;
        } else if( dat[it+1] == 1 ){
          set_block( i, 1, 0, 1 );
          it += 2;
        }
      } else if( used[i*3+2] ){
        if( dat[it] == 0 ){
          set_block( i, 0, 1, 0 );
        } else if( dat[it] == 1 ){
          set_block( i, 1, 1, 0 );
        }
        it++;
      }
    }
  }

  for( int i = 0; i < N; i++ ){
    Set( i, ans[i] );
  }
}
