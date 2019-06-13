#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class BIT{
private:
  vector<int> dat;
  int size;
public:
  void init( int n ){
    size = 1;
    while( size < n ) size *= 2;
    dat = vector<int>( size , 0 );
  }
  void add( int k , int v ){
    for( int i = k+1; i <= size; i += i & -i ) dat[i-1] += v;
  }
  int sum( int k ){ // [ 0 , k ]
    int res = 0;
    for( int i = k+1; i > 0; i -= i & -i ) res += dat[i-1];
    return res;
  }
};

vector<int> compress( vector<int> compress_array ){
  vector<int> ord = compress_array, res(0);
  sort( ord.begin() , ord.end() );
  ord.erase( unique( ord.begin() , ord.end() ) , ord.end() );
  for( int i = 0; i < compress_array.size(); i++ ) res.push_back( lower_bound( ord.begin() , ord.end() , compress_array[i] ) - ord.begin() );
  return res;
}

const int OUTPUT_QUERY = 1;
const int UPDATE_QUERY = 2;
const int MAX_N = 200000;
const int MAX_M = 200000;

int n, m;
BIT bit;
vector<int> vals, compressed;
int val[MAX_N+2], type[MAX_M], pos[MAX_M];

void add( int l , int r , int v ){ // [ l , r )
  bit.add( l , v );
  bit.add( r , -v );
}

int get( int k ){
  return bit.sum( k );
}

void update( int pos , int new_val ){
  int neighbor_min = min( val[pos-1] , val[pos+1] );
  int neighbor_max = max( val[pos-1] , val[pos+1] );
  
  if( val[pos] < new_val ){ // up
    if( val[pos] < neighbor_min ) add( val[pos] + 1 , min( neighbor_min , new_val ) + 1 , -1 );
    if( new_val  > neighbor_max ) add( max( val[pos] , neighbor_max ) + 1 , new_val + 1 , 1  );
  } else if( val[pos] > new_val ){ // down
    if( val[pos] > neighbor_max ) add( max( neighbor_max , new_val ) + 1 , val[pos] + 1 , -1 );
    if( new_val  < neighbor_min ) add( new_val + 1 , min( val[pos] , neighbor_min ) + 1 , 1  );
  }
  
  val[pos] = new_val;
}

void output( int threshold ){
  printf( "%d\n" , get( threshold ) );
}

int main(){

  scanf( "%d %d" , &n , &m );

  vals = vector<int>( n+m+1 , 0 );
  for( int i = 0; i < n; i++ ) scanf( "%d" , &vals[i] );
  for( int i = 0; i < m; i++ ){
    scanf( "%d" , &type[i] );
    if( type[i] == OUTPUT_QUERY ){
      scanf( "%d" , &vals[n+i] );
    } else if( type[i] == UPDATE_QUERY ){
      scanf( "%d %d" , &pos[i] , &vals[n+i] );
    }
  }

  compressed = compress( vals );

  bit.init( n+m+1 );
  for( int i = 0; i < n; i++ ) update( i+1 , compressed[i] );

  for( int i = 0; i < m; i++ ){
    if( type[i] == OUTPUT_QUERY ) output( compressed[n+i] );    
    else if( type[i] == UPDATE_QUERY ) update( pos[i] , compressed[n+i] );
  }
  
  return 0;
}
