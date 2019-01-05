#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

struct point { double x, y; };
typedef pair<double,int> par;

int n, k;
point p[5000];

double solution_r;
point solution;

const double pi = acos( -1.0 );

vector<par> sweep;
int check( double r ) {
   for( int i = 0; i < n; ++i ) {
      
      sweep.clear();
      for( int j = 0; j < n; ++j ) {
         if( i == j ) continue;

         double dx = p[j].x-p[i].x;
         double dy = p[j].y-p[i].y;
         double a = sqrt( dx*dx + dy*dy );
         if( a > 2*r ) continue;

         double alfa = atan2( dy, dx );
         double beta = acos( a/(2*r) );
         
         sweep.push_back( par( alfa-beta, +1) );
         sweep.push_back( par( alfa+beta, -1) );
         sweep.push_back( par( alfa-beta+2*pi, +1) );
         sweep.push_back( par( alfa+beta+2*pi, -1) );
      }
      sort( sweep.begin(), sweep.end() ); 

      int cnt = 1;
      for( vector<par>::iterator it = sweep.begin(); it != sweep.end(); ++it ) {
         cnt += it->second;
         if( cnt >= k ) { 
            solution_r = r;
            solution.x = p[i].x + r*cos(it->first);
            solution.y = p[i].y + r*sin(it->first);
            return 1;
         }
      }
   }
   return 0;
}

int main( void ) {
   scanf( "%d%d", &n, &k );
   for( int i = 0; i < n; ++i ) scanf( "%lf%lf", &p[i].x, &p[i].y );

   double lo = 0, hi = 20000;
   for( int iter = 0; iter < 30; ++iter ) {
      double r = (lo+hi)/2;
      if( check( r ) ) hi = r; else lo = r;
   }
    
   printf( "%.4lf\n%.4lf %.4lf\n", solution_r, solution.x, solution.y );

   return 0;
}
