#include <algorithm>
#include <cstdio>
#include <ctime>
#include <vector>

#define MAXN 50000

using namespace std;

struct loga {
   vector<int> L;
   inline int query( int index ) {
      if( index < 0 ) return 0;
      int ret = 0;
      for( int x = index+1; x; x -= x&-x ) ret += L[x-1];
      return ret;
   }

   inline void update( int index, int value ) {
      for( int x = index+1; x <= L.size(); x += x&-x )
         L[x-1] += value;
   }
};

int N, Q;
struct path {
   int root;
   loga pingu;
} putevi[MAXN];

struct cvor {
   int root;
   int size;
   int depth;   
   int pingu;
   int parent;
   int najtezi, tezina;
   int put;
   vector<int> adj;
} cvorovi[MAXN];

int queue[MAXN], *qhead, *qtail;

void dekompozicija( int b ) {
   qhead = qtail = queue;
   *qtail++ = b;         
   while( qhead != qtail ) {
      int x = *qhead++;
      cvorovi[x].put = x;
      putevi[x].root = x;
      putevi[x].pingu.L.clear();

      for( int y = x; y != -1; y = cvorovi[y].najtezi ) {
         putevi[x].pingu.L.push_back( 0 );
         cvorovi[y].put = x;
         for( vector<int>::iterator it = cvorovi[y].adj.begin(); it != cvorovi[y].adj.end(); ++it ) {
            if( *it == cvorovi[y].parent ) continue;
            if( *it == cvorovi[y].najtezi ) continue;
            *qtail++ = *it;
         }
      }   
      for( int y = x; y != -1; y = cvorovi[y].najtezi ) {
         if( y != x ) putevi[y].pingu.L.clear();
         putevi[x].pingu.update( cvorovi[y].depth - cvorovi[x].depth, cvorovi[y].pingu );
      }
   }
}

void izracunaj_sve( int b, int root ) {
   qhead = qtail = queue;
   *qtail++ = b;
   while( qhead != qtail ) {
      int x = *qhead++;
      
      cvorovi[x].root = root;
      
      for( vector<int>::iterator it = cvorovi[x].adj.begin(); it != cvorovi[x].adj.end(); ++it ) {
         if( *it == cvorovi[x].parent ) continue;
         *qtail++ = *it;
         cvorovi[*it].parent = x;
         cvorovi[*it].depth = cvorovi[x].depth + 1;
      }
   }
   do {
      int x = *--qhead;
      cvorovi[x].size = 1;
      cvorovi[x].tezina = -1;
      cvorovi[x].najtezi = -1;
      
      for( vector<int>::iterator it = cvorovi[x].adj.begin(); it != cvorovi[x].adj.end(); ++it ) {
         if( *it == cvorovi[x].parent ) continue;
         cvorovi[x].size += cvorovi[*it].size;
         if( cvorovi[*it].size > cvorovi[x].tezina ) {
            cvorovi[x].tezina = cvorovi[*it].size;
            cvorovi[x].najtezi = *it;
         }
      }
   } while( qhead != queue );
}

int limit = 50;
int sqrtN;

void balansiraj() {
   for( int i = 0; i < N; ++i ) {
      if( cvorovi[i].root != i ) continue;
      izracunaj_sve( i, i );
      dekompozicija( i );
   }
}


int main( void ) {
   scanf( "%d", &N );
   for( sqrtN = 1; sqrtN*sqrtN < N; ++sqrtN );
   
   for( int i = 0; i < N; ++i ) {
      scanf( "%d", &cvorovi[i].pingu );
      cvorovi[i].parent = -1;
      cvorovi[i].root = i;
      cvorovi[i].depth = 0;
      cvorovi[i].size = 1;
      cvorovi[i].najtezi = -1;
      cvorovi[i].tezina = -1;
      cvorovi[i].put = i;
      
      putevi[i].root = i;
      putevi[i].pingu.L.push_back( cvorovi[i].pingu );
   }

   scanf( "%d", &Q );
   for( int qq = 0; qq < Q; ++qq ) {
      static char naredba[16];
      scanf( "%s", naredba );

      if( naredba[0] == 'b' ) {
         int a, b;
         scanf( "%d%d", &a, &b ); --a; --b;

         if( cvorovi[a].root == cvorovi[b].root ) {
            printf( "no\n" );
            fflush( stdout );
         } else {
            if( cvorovi[ cvorovi[a].root ].size < cvorovi[ cvorovi[b].root ].size ) swap( a, b );
            cvorovi[a].adj.push_back( b );
            cvorovi[b].adj.push_back( a );
            
            cvorovi[ cvorovi[a].root ].size += cvorovi[ cvorovi[b].root ].size;
            cvorovi[b].parent = a;
            cvorovi[b].depth = cvorovi[a].depth + 1;

            izracunaj_sve( b, cvorovi[a].root );
            dekompozicija( b );
            printf( "yes\n" );
            fflush( stdout );
         }
      }

      if( naredba[0] == 'p' ) {
         int a, x;
         scanf( "%d%d", &a, &x ); --a;
         int p = cvorovi[a].put;
         putevi[p].pingu.update( cvorovi[a].depth - cvorovi[ putevi[p].root ].depth, x - cvorovi[a].pingu );
         cvorovi[a].pingu = x;
      }

      if( naredba[0] == 'e' ) {
         int a, b;
         scanf( "%d%d", &a, &b ); --a; --b;

         if( cvorovi[a].root != cvorovi[b].root ) {
            printf( "impossible\n" );
            fflush( stdout );
         } else {
            int pa = cvorovi[a].put, pb = cvorovi[b].put;

            int koraka = 0;
            int ret = 0;
            for( ; pa != pb; ++koraka ) {
               if( cvorovi[ putevi[pa].root ].depth < cvorovi[ putevi[pb].root ].depth ) {
                  swap( a, b );
                  swap( pa, pb );
               }
               ret += putevi[pa].pingu.query( cvorovi[a].depth - cvorovi[ putevi[pa].root ].depth );
               
               a = cvorovi[ putevi[pa].root ].parent;
               pa = cvorovi[a].put;
            }

            if( cvorovi[a].depth > cvorovi[b].depth ) swap( a, b );

            ret += putevi[pb].pingu.query( cvorovi[b].depth - cvorovi[ putevi[pb].root ].depth );
            ret -= putevi[pa].pingu.query( cvorovi[a].depth - cvorovi[ putevi[pa].root ].depth - 1 );

            printf( "%d\n", ret );
            fflush( stdout );
            
            if( koraka > limit ) {
               balansiraj();
               limit = min( 2*limit, sqrtN );
            } 
         }
      }
   }

   return 0;   
}
