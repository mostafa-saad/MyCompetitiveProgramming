#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
int dy[] = { -1, 1, -2, 2, -2, 2, -1, 1 };

const int MAXN = 31;
const int MAXT = 1000001;
const int MAXP = 170; //prosti brojevi manji od 1000
const int MAXPOT = 20; //najveca potencija nekog prostog broja u rastavu broja t

int pr[MAXT], f[MAXT], ff[MAXT], fp[MAXT];
int k[MAXN][MAXN], b[MAXN], bb[MAXN], m[MAXN];
int n, T;

int ind[1000], prosti[MAXP], cnt;
int faktor[MAXP][MAXPOT][MAXN]; // matrica F(p na q)
int fnula[MAXP][MAXP][MAXN]; // matrica G(x,y)

vector< int > v[MAXT];

inline void postavi( int &x, int y, int v ) { // postavlja y-ti bit u x na vrijednost v
  if( v == 1 ) x |= (1<<y); else
    x &= ~(1<<y);
}

inline int daj( int x, int y ) { return (x>>y)&1; } // vraca vrijednost y-tog bita u x

void sito( int MAX ) {
// izracunava sve proste brojeve manje od 1000
   for( int i = 2; i*i < MAXT; ++i )
    if( !pr[i] ) {
      for( int j = i+i; j < MAXT; j += i )
        pr[j] = 1, f[j] = i;
      ind[i] = cnt;
      prosti[cnt++] = i;
    }

// izracunava po jedan prosti faktor i njegov eksponent za svaki broj manji od MAXT kako bi mogli brojeve rastavljati na proste faktore
    for( int i = 2; i < MAXT; ++i ) {
        if( f[i] == 0 ) f[i] = i;
        int x = i;
        ff[i] = 1, fp[i] = 0;
        while( x%f[i] == 0 ) x /= f[i], ff[i] *= f[i], fp[i]++;
    }
}

void solveG() { // izracunava funkciju G(i,j)
    for( int i = 0; i < cnt; ++i ) {
        for( int j = 0; j < n; ++j )
            fnula[i][i][j] = faktor[i][0][j];

    for( int j = i+1; j < cnt; ++j )
      for( int k = 0; k < n; ++k )
        fnula[i][j][k] = (fnula[i][j-1][k] & faktor[j][0][k] );
  }
}

int main( void ) {
  scanf( "%d %d", &n, &T );

  int px, py;
  scanf( "%d %d", &px, &py ); --px, --py;

  sito( MAXT );

  for( int i = 0; i < n; ++i )
    for( int j = 0; j < n; ++j ) {
      scanf( "%d", k[i]+j );
      if( k[i][j] >= 1000 ) { // manje od 1000 slobodnih vremena, sve ih stavi rucno
        for( int l = k[i][j]; l <= T; l += k[i][j] )
          v[l].push_back( i*32 + j );
      } else { // period manji do 1000
        int x = k[i][j];
        for( int p = 0; p < cnt; ++p ) {
          int c = 0;
          while( x%prosti[p] == 0 ) x /= prosti[p], c++;
          while( c < MAXPOT ) postavi( faktor[p][c][i], j, 1 ), c++;
        }
      }
    }

  solveG();

  postavi( b[px], py, 1 );
  int ms1 = (1<<(n-1))-1, ms2 = (1<<(n-2))-1;

  for( int t = 0; t < T; ++t ) {
    // b - trenutna matrica
    // bb - sljedeca matrica
    // m - matrica blokiranosti sekunde t+1

    for( int i = 0; i < n; ++i ) {
      if( i-1 >= 0 ) bb[i-1] |= (b[i]>>2)|((b[i]&ms2)<<2);
      if( i-2 >= 0 ) bb[i-2] |= (b[i]>>1)|((b[i]&ms1)<<1);
      if( i+1 < n ) bb[i+1] |= (b[i]>>2)|((b[i]&ms2)<<2);
      if( i+2 < n ) bb[i+2] |= (b[i]>>1)|((b[i]&ms1)<<1);
    }

    for( int i = 0; i < n; ++i ) {
      b[i] = bb[i], bb[i] = 0;
      m[i] = (1<<n)-1;
    }

    int x = t+1, last = cnt-1;
    while( x > 1 && f[x] < 1000 ) {
      int now = ind[ f[x] ];

      if( last >= now+1 ) {
        for( int i = 0; i < n; ++i )
          m[i] &= fnula[now+1][last][i];
      }
      for( int i = 0; i < n; ++i )
        m[i] &= faktor[now][ fp[x] ][i];
      x /= ff[x], last = now-1;
    }
    if( last >= 0 )
      for( int i = 0; i < n; ++i )
        m[i] &= fnula[0][last][i];

    for( int i = 0; i < v[t+1].size(); ++i )
      postavi( m[ v[t+1][i]/32 ], v[t+1][i]%32, 1 );

    for( int i = 0; i < n; ++i )
      b[i] &= m[i];
  }

  int ans = 0;
  for( int i = 0; i < n; ++i )
    for( int j = 0; j < n; ++j )
      if( daj( b[i], j ) ) ans++;

  printf( "%d\n", ans );
  for( int i = 0; i < n; ++i )
    for( int j = 0; j < n; ++j )
      if( daj( b[i], j ) ) printf( "%d %d\n", i+1, j+1 );
  return 0;
}
