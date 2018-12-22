#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int mxn = 1<<17;

struct node{
	int mx;
	int left, right;
	char start, end;
	int len;
	
} data[2*mxn];

node operator +( const node &a, const node &b ){
	node ret;
	ret.start = a.start;
	ret.end = b.end;
	ret.len = a.len + b.len;
	ret.left = a.left;
	if( a.len == a.left && a.end != b.start ) ret.left += b.left;

	ret.right = b.right;
	if( b.len == b.right && a.end != b.start ) ret.right += a.right;

	ret.mx = max( max( a.mx, b.mx ), max( ret.left, ret.right ) );
	if( a.end != b.start ) ret.mx = max( ret.mx, a.right+b.left );
	
	return ret;
}

int n;

void construct( int i, int lo, int hi ){
  if( hi-lo == 1 ){
    if( lo >= n ) data[i].mx = data[i].left = data[i].right = 0;
    else data[i].mx = data[i].left = data[i].right = 1;
    data[i].start = data[i].end = 'L';
    data[i].len = 1;
    return;
  }
  
  construct( 2*i, lo, (lo+hi)/2 );
  construct( 2*i+1, (lo+hi)/2, hi );
  data[i] = data[2*i] + data[2*i+1];
}

void change( int i ){
  i += mxn;
  if( data[i].start == 'L' ) data[i].start = 'R';
  else data[i].start = 'L';
  data[i].end = data[i].start;
  
  for( i /= 2; i > 0; i /= 2 )
    data[i] = data[2*i] + data[2*i+1];
}

int main(){
  int q;
  
  scanf( "%d %d", &n, &q );
  construct( 1, 0, mxn );

  for( ; q > 0; q-- ){
    int i;
    scanf( "%d", &i ); i--;
    
    change(i);
    printf( "%d\n", data[1].mx );
  }
  
  return 0;
}