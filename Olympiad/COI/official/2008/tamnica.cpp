#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;

typedef long long llint;
typedef pair<llint,llint> par;

const llint inf = 1000000000000000000LL;

llint kut( llint n ) {
   llint a = n/2, b = n%2;   
   return (a+1)*a + b*(a+1) + 1;
}

llint roditelj( llint x ) {
   llint lo = 0, hi = 1000000000;
   
   while( lo < hi ) {
      llint mid = (lo+hi)/2;
      if( x > kut(mid) ) lo = mid + 1; else hi = mid;
   }
   
   return kut(max(lo-4, 0LL)) - kut(lo) + x + 1;
}

vector<llint> sobe;
vector<par> uruseni;

vector<llint> dist;
vector<int> llink; 

struct cmp {
   bool operator () ( const int &A, const int &B ) {
      if( dist[A] != dist[B] ) return dist[A] < dist[B];
      return A < B;
   }
};

void update( set<int,cmp> &PQ, int x, llint d ) {
   if( dist[x] <= d ) return;

   if( dist[x] < inf ) PQ.erase( x );
   dist[x] = d;
   PQ.insert( x );
}

int main( void ) {
   llint n; int k;
   scanf( "%lld%d", &n, &k );
   
   sobe.push_back( 1 );
   sobe.push_back( n );
   sobe.push_back( 2*inf );

   for( int i = 0; i < k; ++i ) {
      llint x;
      scanf( "%lld", &x );
      
      uruseni.push_back( par( x, roditelj(x) ) );

      sobe.push_back( uruseni.back().first );
      sobe.push_back( uruseni.back().second );
   }

   sort( sobe.begin(), sobe.end() );
   sobe.erase( unique( sobe.begin(), sobe.end() ), sobe.end() );

   llink.resize( sobe.size() ); fill( llink.begin(), llink.end(), -1 );
   dist.resize( sobe.size() ); fill( dist.begin(), dist.end(), inf );

   for( vector<par>::iterator it = uruseni.begin(); it != uruseni.end(); ++it ) {
      it->first = lower_bound( sobe.begin(), sobe.end(), it->first ) - sobe.begin();
      it->second = lower_bound( sobe.begin(), sobe.end(), it->second ) - sobe.begin();

      llink[it->first] = it->second;
   }
   
   n = lower_bound( sobe.begin(), sobe.end(), n ) - sobe.begin();
   
   set<int, cmp> PQ;
   update( PQ, n, 0 );

   for( ;; ) {
      int a = *PQ.begin();
      PQ.erase( PQ.begin() );

      if( a == 0 ) break;

      update( PQ, a-1, dist[a] + sobe[a]-sobe[a-1] );
      update( PQ, a+1, dist[a] + sobe[a+1]-sobe[a] );

      if( llink[a] != -1 ) 
         update( PQ, llink[a], dist[a] + 1 );
   }

   printf( "%lld\n", dist[0] );

   return 0;
}
