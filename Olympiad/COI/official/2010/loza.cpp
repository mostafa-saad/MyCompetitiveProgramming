#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define MAX 300000

struct interval {
   int x1, x2;
   interval( int X1, int X2 ) { x1 = X1; x2 = X2; }
};

int n;
struct node {
   int kids;
   int left_len, right_len;
   node *left_child, *right_child;

   int x;
   vector<interval> *subtree;
} a[MAX];

long long ret = 0;

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      static char name[32];
      scanf( "%s", name );
      a[i].left_len = (strlen(name)+1)/2;
      a[i].right_len = (strlen(name)+2)/2;

      if( i ) {
         int dad;
         scanf( "%d", &dad ); --dad;
         if( a[dad].kids++ == 0 ) a[dad].left_child = &a[i];
         else a[dad].right_child = &a[i];
      }
   }

   for( int i = n-1; i >= 0; --i ) {
      ret += (a[i].left_len+a[i].right_len+1)*3;

      if( a[i].kids == 0 ) {
         a[i].subtree = new vector<interval>();
         a[i].x = 0;
      }
      if( a[i].kids == 1 ) {
         a[i].subtree = a[i].left_child->subtree;
         a[i].x = a[i].left_child->x;

         ret += 3;
      }
      if( a[i].kids == 2 ) {
         vector<interval> *L = a[i].left_child->subtree;
         vector<interval> *R = a[i].right_child->subtree;
         int m = min( L->size(), R->size() );

         int move = -1000000000;
         for( int j = 1; j <= m; ++j )
            move = max( move, (*L)[L->size()-j].x2 - (*R)[R->size()-j].x1 + 1 );

         int even = (a[i].left_child->x&1) == (a[i].right_child->x&1);
         if( (move&1) == even ) ++move;

         if( L->size() < R->size() ) {
            a[i].subtree = R;
            a[i].left_child->x -= move;
            for( int j = 1; j <= m; ++j ) {
               (*L)[L->size()-j].x1 -= move;
               (*L)[L->size()-j].x2 -= move;
            }
         } else {
            a[i].subtree = L;
            a[i].right_child->x += move;
            for( int j = 1; j <= m; ++j ) {
               (*R)[R->size()-j].x1 += move;
               (*R)[R->size()-j].x2 += move;
            }
         }

         for( int j = 1; j <= m; ++j ) {
            (*R)[R->size()-j].x1 = (*L)[L->size()-j].x1;
            (*L)[L->size()-j].x2 = (*R)[R->size()-j].x2;
         }
         a[i].x = (a[i].right_child->x + a[i].left_child->x)/2;

         ret += 4 + a[i].right_child->x - a[i].left_child->x;
      }

      a[i].subtree->push_back( interval(a[i].x-a[i].left_len, a[i].x+a[i].right_len) );
   }

   printf( "%lld\n", ret );

   return 0;
}
