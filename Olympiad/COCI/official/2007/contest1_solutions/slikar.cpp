
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task SLIKAR
  Programming language C++
*/

#include <cstdio>
#include <queue>
#include <cstring>
#include <utility>
using namespace std;

#define MAXN 50

int  r, s;
char karta[MAXN+1][MAXN+1];
int  poplava[MAXN+1][MAXN+1];
int  slikar[MAXN+1][MAXN+1];

int  potez[8][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

queue<pair<int, int> > Q;

int main() {
   memset( poplava, -1, sizeof poplava );
   memset( slikar, -1, sizeof slikar );

   scanf( "%d%d", &r, &s);
   for ( int i=0; i<r; ++i )
      scanf( "%s", karta[i] );

   int sx=-1, sy=-1, dx=-1, dy=-1;

   // prolazak kroz kartu i nalazenje poplavljenih polja
   for ( int i=0; i<r; ++i )
      for ( int j=0; j<s; ++j ) {
         if ( karta[i][j] == 'S' ) {
            sx = i; sy = j;
            karta[i][j] = '.';
         }

         if ( karta[i][j] == 'D' ) {
            dx = i; dy = j;
         }

         if ( karta[i][j] == '*' ) poplava[i][j] = 0;
         if ( karta[i][j] == '.' ) {
            bool poplavljeno = false;
            for (int k = 0; k < 4; k++) {
               int ni = i + potez[k][0];
               int nj = j + potez[k][1];
               if ( ni < 0 || ni >= r ) continue;
               if ( nj < 0 || nj >= s ) continue;
               if ( karta[ni][nj] == '*' ) poplavljeno = true;
            }
            if ( poplavljeno ) {
               Q.push( make_pair(i, j) );
               poplava[i][j] = 1;
            }
         }

      }

   // poplava
   while ( !Q.empty() ) {
      int x = Q.front().first;
      int y = Q.front().second;
      Q.pop();

      for ( int k=0; k<4; ++k ) {
         int nx = x + potez[k][0];
         int ny = y + potez[k][1];
         if ( nx < 0 || nx >= r ) continue;
         if ( ny < 0 || ny >= s ) continue;
         if ( poplava[nx][ny] == -1 && karta[nx][ny] != 'X' && karta[nx][ny] != 'D' ) {
            poplava[nx][ny] = poplava[x][y] + 1;
            Q.push( make_pair( nx, ny ) );
         }
      }
   }

   // slikar
   slikar[sx][sy] = 0;
   Q.push( make_pair( sx, sy ) );

   while ( !Q.empty() ) {
      int x = Q.front().first;
      int y = Q.front().second;
      Q.pop();

      for ( int k = 0; k < 4; ++k ) {
         int nx = x + potez[k][0];
         int ny = y + potez[k][1];
         if ( nx < 0 || nx >= r ) continue;
         if ( ny < 0 || ny >= s ) continue;
         if ( slikar[nx][ny] == -1 && karta[nx][ny] != 'X' )
            if ( poplava[nx][ny] > slikar[x][y] + 1 || poplava[nx][ny] == -1 ) {
               slikar[nx][ny] = slikar[x][y] + 1;
               Q.push(make_pair(nx, ny));
            }
      }
   }

   if ( slikar[dx][dy] != -1 )
      printf( "%d\n", slikar[dx][dy] );
   else
      printf( "KAKTUS\n" );

   return 0;
}
