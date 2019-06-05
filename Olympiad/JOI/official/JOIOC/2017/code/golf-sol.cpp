#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>
#include <set>
#include <queue>

using namespace std;

const int INF = 1000000010;
const int MAX_N = 100010;
const int SEGSIZE = (1<<18);

const int DEL = 0;
const int ASK = 1;
const int ADD = 2;

const int TATE = 0;
const int YOKO = 1;

typedef tuple<int,int,int> T;
typedef pair<int,int> P;

struct node{
  int val;
  node *chl, *chr;
  node(){}
  node( int val ): val(val), chl(NULL), chr(NULL) {}
  node( int val, node *chl, node *chr ) : val(val), chl(chl), chr(chr) {}
};

node nodes[50000010];
int np;

int val( node *t ){ return !t ? 0 : t->val; }
node* chl( node *t ){ return !t ? NULL : t->chl; }
node* chr( node *t ){ return !t ? NULL : t->chr; }

node* newnode( int val = 0, node *chl = NULL, node *chr = NULL ){
  nodes[np] = node( val , chl , chr );
  return &nodes[np++];
}

int add( int x , int id , int l , int r , node *cur ){
  if( r - l == 1 ){
    if( cur->val == 0 ){
      cur->val = id + 1;
      return 1;
    } else {
      return 0;
    }
  }
  int md = ( l + r ) / 2;
  int res = 0;
  if( x < md ){
    if( !chl(cur) ){
      cur->chl = newnode();
    }
    res = add( x , id , l , md , chl(cur) );
  } else {
    if( !chr(cur) ){
      cur->chr = newnode();
    }
    res = add( x , id , md , r , chr(cur) );
  }
  cur->val += res;
  return res;
}

int search( int a , int b , queue<P> &que, int dir, int dist[], int ndist, int l , int r , node *cur ){
  if( r - l == 1 ){
    if( cur->val == 0 ){
      return 0;
    }
    if( dist[val(cur)-1] == INF ){
      dist[val(cur)-1] = ndist;
      que.emplace( dir, val(cur)-1 );
    }
    cur->val = 0;
    return 1;
  }
  if( val(cur) == 0 ){
    return 0;
  }
  if( b <= l || r <= a ){
    return 0;
  } else {
    int md = ( l + r ) / 2;
    int chlr = 0;
    int chrr = 0;
    if( chl(cur) ){
      chlr = search( a , b , que , dir , dist , ndist , l , md , chl(cur) );
    }
    if( chr(cur) ){
      chrr = search( a , b , que , dir , dist , ndist , md , r , chr(cur) );
    }
    cur->val -= chlr + chrr;
    return chlr + chrr;
  }
}

void make_nex( vector<node*> &segs, queue<P> &que, int dist[], int ndist, int dir, int a , int b , int x , int l = 0, int r = SEGSIZE, int k = 0 ){
  search( a , b , que , dir , dist , ndist , 0 , SEGSIZE , segs[k] );
  if( r - l == 1 ){
    return;
  }
  if( x < (r+l)/2 ){
    make_nex( segs, que, dist, ndist, dir, a, b, x, l, (l+r)/2, k*2+1 );
  } else {
    make_nex( segs, que, dist, ndist, dir, a, b, x, (l+r)/2, r, k*2+2 );
  }
}

void devide_and_add( vector<node*> &segs, int id, int x, int top, int bottom, int l = 0, int r = SEGSIZE, int k = 0 ){
  if( top <= l and r <= bottom ){
    add( x , id , 0 , SEGSIZE, segs[k] );
  } else if( l < bottom and top < r ){
    devide_and_add( segs, id, x, top, bottom, l, (l+r)/2, k*2+1 );
    devide_and_add( segs, id, x, top, bottom, (l+r)/2, r, k*2+2 );
  }
}

void build_segtree( vector<node*> &segs, vector<T> &vec, int n, int sx, int sy, int tx, int ty, int a[], int b[], int c[], int d[] ){
  vector<T> sweep;
  sweep.emplace_back( -1, ADD, 0 );
  sweep.emplace_back( -1, ADD, SEGSIZE-1 );
  sweep.emplace_back( sx, ASK, sy );
  sweep.emplace_back( tx, ASK, ty );
  for( int i = 0; i < n; i++ ){
    sweep.emplace_back( a[i], ADD, c[i] );
    sweep.emplace_back( a[i], ADD, d[i] );
    sweep.emplace_back( b[i], DEL, c[i] );
    sweep.emplace_back( b[i], DEL, d[i] );
    sweep.emplace_back( a[i], ASK, c[i] );
    sweep.emplace_back( b[i], ASK, c[i] );
  }
  sort( sweep.begin() , sweep.end() );
  set<int> ss;
  int cnt = 0;
  for( T &q : sweep ){
    int x = get<0>(q);
    int type = get<1>(q);
    int y = get<2>(q);
    if( type == ADD ){
      ss.insert( y );
    } else if( type == DEL ){
      assert( ss.find( y ) != ss.end() );
      ss.erase( ss.find( y ) );
    } else {
      auto ite = ss.upper_bound( y );
      int bottom = (*ite);
      ite--;
      int top = (*ite);
      vec.emplace_back( x, top, bottom );
      devide_and_add( segs, int( vec.size() ) - 1, x, top, bottom+1 );
    }
  }
}

vector<int> compress( vector<int> v ){
  vector<int> ord = v;
  sort( ord.begin(), ord.end() );
  for( int &a : v ){
    a = lower_bound( ord.begin(), ord.end(), a ) - ord.begin() + 1;
  }
  return v;
}

int sx, sy, tx, ty;
int n;
int a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];

vector<int> xs, ys;

vector<T> tate, yoko;
vector<node*> seg_tate, seg_yoko;

int tate_dist[MAX_N*2];
int yoko_dist[MAX_N*2];

queue<P> que;

int main(){
  
  scanf( "%d %d %d %d" , &sx , &sy , &tx , &ty );
  xs.push_back( sx );
  ys.push_back( sy );
  xs.push_back( tx );
  ys.push_back( ty );
  scanf( "%d" , &n );
  for( int i = 0; i < n; i++ ){
    scanf( "%d %d %d %d" , &a[i] , &b[i] , &c[i] , &d[i] );
    xs.push_back( a[i] );
    xs.push_back( b[i] );
    ys.push_back( c[i] );
    ys.push_back( d[i] );
  }

  xs = compress( xs );
  ys = compress( ys );
  
  sx = xs[0];
  sy = ys[0];
  tx = xs[1];
  ty = ys[1];
  for( int i = 0; i < n; i++ ){
    a[i] = xs[i*2+2];
    b[i] = xs[i*2+3];
    c[i] = ys[i*2+2];
    d[i] = ys[i*2+3];
  }

  for( int i = 0; i < SEGSIZE*2-1; i++ ){
    seg_tate.push_back( newnode() );
    seg_yoko.push_back( newnode() );
  }

  build_segtree( seg_tate, tate, n, sx, sy, tx, ty, a, b, c, d );
  build_segtree( seg_yoko, yoko, n, sy, sx, ty, tx, c, d, a, b );

  for( int i = 0; i < tate.size(); i++ ){
    if( get<0>( tate[i] ) == sx and get<1>( tate[i] ) <= sy and sy <= get<2>( tate[i] ) ){
      que.emplace( TATE, i );
      tate_dist[i] = 1;
    } else {
      tate_dist[i] = INF;
    }
  }
  
  for( int i = 0; i < yoko.size(); i++ ){
    if( get<0>( yoko[i] ) == sy and get<1>( yoko[i] ) <= sx and sx <= get<2>( yoko[i] ) ){
      que.emplace( YOKO, i );
      yoko_dist[i] = 1;
    } else {
      yoko_dist[i] = INF;
    }
  }

  while( not que.empty() ){
    int type = que.front().first;
    int id = que.front().second;
    que.pop();
    if( type == TATE ){
      int x = get<0>( tate[id] );
      int t = get<1>( tate[id] );
      int b = get<2>( tate[id] );
      if( x == tx and t <= ty and ty <= b ){
        printf( "%d\n" , tate_dist[id] );
        return 0;
      }
      make_nex( seg_yoko, que, yoko_dist, tate_dist[id]+1, YOKO, t, b, x );
    }
    if( type == YOKO ){
      int x = get<0>( yoko[id] );
      int t = get<1>( yoko[id] );
      int b = get<2>( yoko[id] );
      if( x == ty and t <= tx and tx <= b ){
        printf( "%d\n" , yoko_dist[id] );
        return 0;
      }
      make_nex( seg_tate, que, tate_dist, yoko_dist[id]+1, TATE, t, b, x );
    }
  }

  assert( false );
  
  return 0;
}
