#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

typedef unsigned long long llint;

typedef pair< int, int > par;
#define a first
#define b second
  
const int MAXN = 55;
const int MAXK = 10;

const int MAX = 10010;

int phi[MAX];
int pr[MAX];

llint multi( llint a, llint b, llint mod ){ // (a*b)%mod 
  if( b == 0 ) return 0;
  if( b&1 ) return ( multi( a, b-1, mod ) + a )%mod;
  return (2*multi( a, b/2, mod ))%mod;
}

llint power( llint a, llint b, llint mod ) { // (a^b)%mod
  if( b == 0 ) return 1%mod;
  if( b&1 ) return multi( power( a, b-1, mod ), a, mod );
  llint tmp = power( a, b/2, mod );
  return multi( tmp, tmp, mod );
}

void initCRT() {
  for( int i = 2; i < MAX; ++i )
    if( pr[i] == 0 )
      for( int j = i; j < MAX; j += i )
	pr[j] = i;

  phi[1] = 1;
  for (int i = 2; i < MAX; ++i) {
    int c = 1, x = i;
    while( x%pr[i] == 0 ) c *= pr[i], x /= pr[i];
    phi[i] = phi[x]*( pr[i]-1 )*( c/pr[i] );
  }
}

llint CRT( vector< par > v )  {
  int n = v.size(), lo = 0;
  for (int i = 0; i < n; ++i) {
    lo = max( lo, v[i].a );
    v[i].a %= v[i].b;
  }

  map< int, vector< par > > M;
  for( int i = 0; i < n; ++i ) { //rastav na proste faktore
    int x = v[i].b;
    for( int d = 2; d*d <= x; ++d ) 
      if( x%d == 0 ) {
        int pot = 1;
        while (x%d == 0) x /= d, pot *= d;
	M[d].push_back( make_pair( pot, v[i].a%pot ) );
      }
    if( x > 1 ) M[x].push_back( make_pair( x, v[i].a%x ) );
  }

  llint u = 1;
  for( map< int, vector< par > > :: iterator it = M.begin(); it != M.end(); ++it ) {
    vector< par > &v = it->b;
    sort( v.begin(), v.end() );
    par z = v.back();
    for( int i = 0; i < (int)v.size(); ++i ) 
      if( z.b%v[i].a != v[i].b ) return -1;
    u *= z.a;
  }

  llint x = 0;
  for( map< int, vector< par > > :: iterator it = M.begin(); it != M.end(); ++it ) {
    vector< par > &V = it->second;
    par z = V.back();
    x = ( x + multi( z.b, power( u/z.a, phi[z.a], u ), u ) )%u;
  }

  while( x < lo ) x += u;
  return x;
}

vector< par > v[MAXK], vm;
llint ans;

void rec( int x, int k ) {
  if( x == k ) {
    llint fixed = 0;
    for( int i = 0; i < k; ++i )
      if( vm[i].b == 0 ) fixed = vm[i].a;
 
    if( fixed ) {
      bool ok = true;
      for( int i = 0; i < k; ++i ) {
        if( vm[i].b == 0 ) {
          if( vm[i].a != fixed ) { ok = false; break; }
        } else
          if( fixed < vm[i].a || ( fixed%vm[i].b != vm[i].a%vm[i].b ) ) { ok = false; break; }
      }
      if( ok && ( ans == 0 || fixed < ans ) ) ans = fixed;
      return;
    }
    llint f = CRT(vm);
    if( f && ( ans == 0 || f < ans ) ) ans = f;
    return;
  }
  for( int i = 0; i < (int)v[x].size(); ++i ) {
    vm.push_back( v[x][i] );
    rec( x+1, k );
    vm.pop_back();
  }
}

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };

char a[MAXK][MAXN][MAXN];
int bio[MAXN][MAXN][4];
int sx[MAXK], sy[MAXK], sd[MAXK];
int ex, ey, n, m, k;

int main( void ) {
  initCRT();

  scanf( "%d %d %d", &n, &m, &k  );
  scanf( "%d %d", &ex, &ey ); --ex, --ey;
  for( int i = 0; i < k; ++i ) {
    char s[5];
    scanf( "%d %d %s", sx+i, sy+i, s );
    
    if( s[0] == 'D' ) sd[i] = 0;
    if( s[0] == 'L' ) sd[i] = 1;
    if( s[0] == 'U' ) sd[i] = 2;
    if( s[0] == 'R' ) sd[i] = 3;

    --sx[i], --sy[i];
    for( int j = 0; j < n; ++j ) {
      scanf( "%s", a[i][j] );
      for( int k = 0; k < m; ++k )
        a[i][j][k] = (a[i][j][k]-'0')%4;
    }
  }

  for( int i = 0; i < k; ++i ) {
    memset( bio, 0, sizeof( bio ) );
    int x = sx[i], y = sy[i], d = sd[i], c = 1;
    while( !bio[x][y][d] ) {
      bio[x][y][d] = c;
      d = (d + a[i][x][y])%4;
      if( x+dx[d] < 0 || x+dx[d] >= n || y+dy[d] < 0 || y+dy[d] >= m ) d = (d + 2)%4;
      x += dx[d], y += dy[d];
      c++;
    }
    
    int start = bio[x][y][d], len = c-bio[x][y][d]; 
    for( int d = 0; d < 4; ++d )
      if( bio[ex][ey][d] ) {
        if( bio[ex][ey][d] < start ) v[i].push_back( make_pair( bio[ex][ey][d], 0 ) ); else
          v[i].push_back( make_pair( bio[ex][ey][d], len ) );
      }
  }
  
  ans = 0;
  rec( 0, k );
  if( ans == 0 ) printf( "-1\n" ); else
    printf( "%llu\n", ans );
  return 0;
}
