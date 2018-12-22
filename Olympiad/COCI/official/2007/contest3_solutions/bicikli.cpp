
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task BICIKLI
  Programming language C++
*/

#include <cstdio>
#include <vector>

using namespace std;

#define NORMALNO 0
#define OBRNUTO 1

int dostupan[2][10000];
vector<int> susjedi[2][10000];

struct MojBroj {
   bool jelvelik;
   int vrijednost;
   MojBroj( int x=0 ) { jelvelik = false; vrijednost = x; }
};

MojBroj operator + ( const MojBroj &A, const MojBroj &B ) {
   MojBroj C( A.vrijednost + B.vrijednost );
   C.jelvelik = A.jelvelik | B.jelvelik;
   if( C.vrijednost >= 1000000000 ) {
      C.jelvelik = true;
      C.vrijednost -= 1000000000;
   }
   return C;
}

void dfs( int G, int i ) {
   if( dostupan[G][i] ) return;
   dostupan[G][i] = 1;

   for( vector<int>::iterator it = susjedi[G][i].begin(); it != susjedi[G][i].end(); ++it )
      dfs( G, *it );
}

enum Boja { Bijela, Siva, Crna } boja[10000];
MojBroj memo[10000];

MojBroj rekurzija( int i ) {
   if( boja[i] == Crna ) return memo[i];
   if( boja[i] == Siva ) throw "inf";

   boja[i] = Siva;

   memo[i] = MojBroj( 0 );
   if( i == 1 ) memo[i] = MojBroj( 1 );

   for( vector<int>::iterator it = susjedi[0][i].begin(); it != susjedi[0][i].end(); ++it )
      if( dostupan[NORMALNO][*it] && dostupan[OBRNUTO][*it] )
         memo[i] = memo[i] + rekurzija( *it );

   boja[i] = Crna;

   return memo[i];
}

int main( void ) {
   int n, m;
   scanf( "%d%d", &n, &m );

   for( int i = 0; i < m; ++i ) {
      int a, b;
      scanf( "%d %d", &a, &b ); --a; --b;

      susjedi[NORMALNO][a].push_back( b );
      susjedi[OBRNUTO][b].push_back( a );
   }

   dfs( NORMALNO, 0 );
   dfs( OBRNUTO, 1 );

   try {
      MojBroj ret = rekurzija( 0 );

      if( ret.jelvelik ) printf( "%09d\n", ret.vrijednost );
      else printf( "%d\n", ret.vrijednost );

   } catch( ... ) {
      printf( "inf\n" );
   }

   return 0;
}
