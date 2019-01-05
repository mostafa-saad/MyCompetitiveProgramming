#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct prepreka {
   int x1, y1, x2, y2;
   int x;
   int index;
   int link1, link2;
};
int cmp_x2( const prepreka &A, const prepreka B ) { return A.x2 < B.x2; }
int cmp_y1( const prepreka &A, const prepreka B ) { return A.y1 < B.y1; }
int cmp_y2( const prepreka &A, const prepreka B ) { return A.y2 > B.y2; }
int cmp_index( const prepreka &A, const prepreka B ) { return A.index < B.index; }

int n;
int X, Y;
vector<prepreka> A;

const int inf = 1000000000;

void input() {
   scanf( "%d%d", &X, &Y );
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      prepreka P;
      scanf( "%d%d%d%d", &P.x1, &P.y1, &P.x2, &P.y2 );
      if( P.x1 > P.x2 ) swap( P.x1, P.x2 );
      if( P.y1 > P.y2 ) swap( P.y1, P.y2 );
      A.push_back( P );
   }
}

struct event {
   int index, y, type;
   event( int I, int Y, int T ) { index = I; y = Y; type = T; }
};
int cmp_event( const event &A, const event &B ) {
   if( A.y != B.y ) return A.y < B.y;
   return A.type < B.type;
}

struct tournament_tree {
   vector<int> a;
   int offset;
   tournament_tree( int N ) {
      for( offset = 1; offset < N; offset *= 2 );
      a.resize( 2*offset );
      for( int i = 0; i < 2*offset; ++i ) a[i] = -1;
   }

   void insert( int x, int val ) {
      if( a[offset+x] != -1 ) return;
      for( int i = offset+x; i; i >>= 1 )
         a[i] >?= val;
   }
   void erase( int x ) {
      a[offset+x] = -1;
      for( int i = (offset+x)>>1; i; i >>= 1 )
         a[i] = a[2*i] >? a[2*i+1];
   }
   int rec( int x, int i, int lo, int hi ) {
      if( hi <= x ) return a[i];
      if( lo >= x ) return -1;
      int mid = (lo+hi)/2;
      return rec( x, 2*i, lo, mid ) >? rec( x, 2*i+1, mid, hi );
   }
   int query( int x ) {
      return rec( x, 1, 0, offset );
   }
};

void init() {
   int N = 0;
   {
      int I = 0;
      int lastx = -1;
      sort( A.begin(), A.end(), cmp_x2 );
      for( vector<prepreka>::iterator P = A.begin(); P != A.end(); ++P ) {
         P->index = I++;
         P->link1 = P->link2 = -1;

         if( P->x2 != lastx ) ++N;
         P->x = N;
         lastx = P->x2;
      }
   }

   {
      int x = 0, y = 0;
      sort( A.begin(), A.end(), cmp_y1 );
      for( vector<prepreka>::iterator P = A.begin(); P != A.end(); ++P ) {
         if( P->y1 > y && P->x1 <= x && x <= P->x2 ) {
            x = P->x2+1;
            y = P->y1;
            P->y2 = inf;
         }
      }
   }
   {
      int x = 0, y = 0;
      sort( A.begin(), A.end(), cmp_y2 );
      for( vector<prepreka>::iterator P = A.begin(); P != A.end(); ++P ) {
         if( P->y2 < y && P->x1 <= x && x <= P->x2 ) {
            x = P->x2+1;
            y = P->y2;
            P->y1 = -inf;
         }
      }
   }

   sort( A.begin(), A.end(), cmp_index );
   vector<event> E;
   for( vector<prepreka>::iterator P = A.begin(); P != A.end(); ++P ) {
      E.push_back( event( P->index, P->y1, 0 ) );
      E.push_back( event( P->index, P->y1-1, 1 ) );
      E.push_back( event( P->index, P->y2+1, 2 ) );
      E.push_back( event( P->index, P->y2, 3 ) );
   }

   tournament_tree T( N+1 );
   sort( E.begin(), E.end(), cmp_event );
   for( vector<event>::iterator e = E.begin(); e != E.end(); ++e ) {
      if( e->type == 0 ) T.insert( A[e->index].x, e->index );
      if( e->type == 1 ) A[e->index].link1 = T.query( A[e->index].x );
      if( e->type == 2 ) A[e->index].link2 = T.query( A[e->index].x );
      if( e->type == 3 ) T.erase( A[e->index].x );
   }
}

typedef long long llint;
vector< pair<llint,llint> > dp;
vector< pair<int,int> > solution;

void backtrack( llint &val, int &link ) {
   if( link == -1 ) {
      solution.push_back( pair<int,int> (X, 0) ); X = 0;
      solution.push_back( pair<int,int> (0, Y) ); Y = 0;
   } else {
      if( val == X-A[link].x2-1 + abs( Y - A[link].y1+1 ) + dp[link].first ) {
         int dx = X - A[link].x2-1;
         int dy = Y - A[link].y1+1;
         if( dx ) { solution.push_back( pair<int,int> (dx, 0) ); X -= dx; }
         if( dy ) { solution.push_back( pair<int,int> (0, dy) ); Y -= dy; }
         val = dp[link].first;
         link = A[link].link1;
      } else {
         int dx = X - A[link].x2-1;
         int dy = Y - A[link].y2-1;
         if( dx ) { solution.push_back( pair<int,int> (dx, 0) ); X -= dx; }
         if( dy ) { solution.push_back( pair<int,int> (0, dy) ); Y -= dy; }
         val = dp[link].second;
         link = A[link].link2;
      }
   }
}

void solve() {
   dp.resize( n );
   for( int i = 0; i < n; ++i ) {
      {
         int j = A[i].link1;
         if( j == -1 ) dp[i].first = A[i].x2+1 + abs( A[i].y1-1 );
         else dp[i].first =
                 A[i].x2-A[j].x2 + abs( A[i].y1-1 - A[j].y1+1 ) + dp[j].first <?
                 A[i].x2-A[j].x2 + abs( A[i].y1-1 - A[j].y2-1 ) + dp[j].second;
      }
      {
         int j = A[i].link2;
         if( j == -1 ) dp[i].second = A[i].x2+1 + abs( A[i].y2+1 );
         else dp[i].second =
                 A[i].x2-A[j].x2 + abs( A[i].y2+1 - A[j].y1+1 ) + dp[j].first <?
                 A[i].x2-A[j].x2 + abs( A[i].y2+1 - A[j].y2-1 ) + dp[j].second;
      }
   }
   int link = -1;
   for( int i = n-1; i >= 0; --i )
      if( A[i].x2 < X && A[i].y1 <= Y && Y <= A[i].y2 ) {
         link = A[i].index;
         break;
      }

   long long ret = X + abs(Y);
   if( link != -1 )
      ret =
         X-A[link].x2-1 + abs( Y - A[link].y1+1 ) + dp[link].first <?
         X-A[link].x2-1 + abs( Y - A[link].y2-1 ) + dp[link].second;

   printf( "%lld\n", ret );

   while( X != 0 || Y != 0 ) backtrack( ret, link );

   printf( "%d\n", solution.size() );

   for( int i = solution.size()-1; i >= 0; --i )
      printf( "%d %d\n", solution[i].first, solution[i].second );
}



int main( void ) {
   input();

   init();

   solve();

   return 0;
}
