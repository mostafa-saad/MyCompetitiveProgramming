#include <algorithm>
#include <cstdio>

typedef long long llint;

enum direction { LEFT, RIGHT, DOWN, UP };

struct point {
   llint x, y;
   bool flag;
   point *next[4];
   point *CCW, *CW;

   point() { 
      flag = false;
      for( int i = 0; i < 4; ++i ) next[i] = NULL;
      CCW = CW = NULL;
   }
};

int ccw( point *A, point *B, point *C ) {
   llint t = (B->x-A->x)*(C->y-A->y) - (C->x-A->x)*(B->y-A->y);
   if( t < 0 ) return -1;
   if( t > 0 ) return 1;
   return 0;
}

bool cmp_x( point *A, point *B ) { return A->x < B->x; }
bool cmp_y( point *A, point *B ) { return A->y < B->y; }

void connect( int n, point **order, point **extreme, direction A, direction B ) {
   extreme[A] = order[0]; 
   extreme[B] = order[n-1];
   for( int i = 1; i < n; ++i ) {
      order[i]->next[A] = order[i-1];
      order[i-1]->next[B] = order[i];
   }
}

void go_inwards( char *chosen, point **order, int steps, point **extreme ) {
   for( int i = 0; i < steps; ++i ) {
      if( chosen[i] == 'L' ) order[i] = extreme[LEFT];
      if( chosen[i] == 'R' ) order[i] = extreme[RIGHT];
      if( chosen[i] == 'D' ) order[i] = extreme[DOWN];
      if( chosen[i] == 'U' ) order[i] = extreme[UP];
      
      order[i]->flag = 1;

      for( int d = 0; d < 4; ++d ) 
         while( extreme[d]->flag ) 
            extreme[d] = extreme[d]->next[d^1];
   }
}

void add( llint &area, point *P ) {
   P->CCW->CW = P;
   P->CW->CCW = P;
   area += P->x     * P->CCW->y  - P->y     * P->CCW->x;
   area += P->CW->x * P->y       - P->CW->y * P->x;
   area -= P->CW->x * P->CCW->y  - P->CW->y * P->CCW->x;
}
void sub( llint &area, point *P ) {
   P->CCW->CW = P->CW;
   P->CW->CCW = P->CCW;
   area -= P->x     * P->CCW->y  - P->y     * P->CCW->x;
   area -= P->CW->x * P->y       - P->CW->y * P->x;
   area += P->CW->x * P->CCW->y  - P->CW->y * P->CCW->x;
}

llint *go_outwards( char *chosen, point **order, int steps, point **extreme ) {
   llint *result = new llint[steps];

   llint area = 0;
   
   for( int i = steps-1; i >= 0; --i ) {
      direction d;
      if( chosen[i] == 'L' ) d = LEFT;
      if( chosen[i] == 'R' ) d = RIGHT;
      if( chosen[i] == 'D' ) d = DOWN;
      if( chosen[i] == 'U' ) d = UP;
      
      point *A = order[i];

      for( A->CCW = extreme[d]; A->CCW != extreme[d^1] && ccw( A, A->CCW, A->CCW->CCW ) <= 0; A->CCW = A->CCW->CCW ) 
         if( A->CCW != extreme[d] ) sub( area, A->CCW );
      for( A->CW  = extreme[d]; A->CW  != extreme[d^1] && ccw( A, A->CW,  A->CW->CW   ) >= 0; A->CW  = A->CW->CW   ) 
         if( A->CW != extreme[d] ) sub( area, A->CW );

      if( A->CW != extreme[d] && A->CCW != extreme[d] ) sub( area, extreme[d] );

      add( area, A );
      
      if( A->x < extreme[LEFT]->x ) extreme[LEFT] = A;
      if( A->x > extreme[RIGHT]->x ) extreme[RIGHT] = A;
      if( A->y < extreme[DOWN]->y ) extreme[DOWN] = A;
      if( A->y > extreme[UP]->y ) extreme[UP] = A;

      result[i] = area;
   }
   
   return result;
}

typedef point * ppoint;

int main( void ) {
   int n;
   scanf( "%d", &n );
   point *data = new point[n];
   for( int i = 0; i < n; ++i ) scanf( "%lld%lld ", &data[i].x, &data[i].y );

   point **order = new ppoint[n];
   for( int i = 0; i < n; ++i ) order[i] = data + i;

   point *extreme[4];
   std::sort( order, order+n, cmp_x ); connect( n, order, extreme, LEFT, RIGHT );
   std::sort( order, order+n, cmp_y ); connect( n, order, extreme, DOWN, UP );

   char *chosen = new char[n];
   gets( chosen );
   
   go_inwards( chosen, order, n-2, extreme );

   extreme[LEFT]->CCW = extreme[LEFT]->CW = extreme[RIGHT];
   extreme[RIGHT]->CCW = extreme[RIGHT]->CW = extreme[LEFT];
   
   llint *result = go_outwards( chosen, order, n-2, extreme );

   for( int i = 0; i < n-2; ++i ) printf( "%lld.%lld\n", result[i]>>1, (result[i]&1)*5 );
   
   delete[] order;
   delete[] data;
   delete[] chosen;
   delete[] result;   
   
   return 0;
}
