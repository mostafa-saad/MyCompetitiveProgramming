/*
  Croatian Olympiad in Informatics 2007
  Task SABOR
*/

#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;

#define MAX 1000

void edge(int x, int y, int d, int K, long long res[2])
{
   res[(x+y)%2]   += (K-d)/2;
   res[(x+y+1)%2] += (K-d+1)/2;
}

void corner(int x, int y, int d, int K, long long res[2])
{
   long long n;
   n = (K-d)/2;   res[(x+y)%2]   += n*n;
   n = (K-d-1)/2; res[(x+y+1)%2] += n*(n+1);
}

int main()
{
   int P, K;
   scanf( "%d%d", &P, &K );
   ++K;

   static int d[2*MAX+3][2*MAX+3];
   int x0=MAX+1, y0=MAX+1;
   int
      minx = x0, maxx = x0,
      miny = y0, maxy = y0;
   
   for ( int i=0; i<P; ++i ) {
      int x, y;
      scanf( "%d%d", &x, &y );
      x += x0; y += y0;
      minx = min( minx, x ); maxx = max( maxx, x );
      miny = min( miny, y ); maxy = max( maxy, y );
      d[x][y] = -1;
   }
   --minx; --miny;
   ++maxx; ++maxy;

   long long res[2] = { 0, 0 };

   queue<int> qx, qy;
   d[x0][y0] = 1;
   qx.push(x0); qy.push(y0); 
   while ( !qx.empty() ) {
      int x = qx.front(); qx.pop();
      int y = qy.front(); qy.pop();

      ++res[(x+y)%2];
      if ( d[x][y] == K ) {
         continue;
      }
      if ( x == minx || x == maxx ) edge(x, y, d[x][y], K, res);
      if ( y == miny || y == maxy ) edge(x, y, d[x][y], K, res);
      
      static const int dx[] = { -1, 0, 1, 0 };
      static const int dy[] = { 0, 1, 0, -1 };
      for ( int dir=0; dir<4; ++dir ) {
         int nx = x + dx[dir], ny = y + dy[dir];
         if ( nx < minx || nx > maxx || ny < miny || ny > maxy || d[nx][ny] != 0 ) continue;

         d[nx][ny] = d[x][y] + 1;
         qx.push( nx ); qy.push( ny );
      }
   }

   if ( d[minx][miny] > 0 ) corner( minx, miny, d[minx][miny], K, res );
   if ( d[minx][maxy] > 0 ) corner( minx, maxy, d[minx][maxy], K, res );
   if ( d[maxx][miny] > 0 ) corner( maxx, miny, d[maxx][miny], K, res );
   if ( d[maxx][maxy] > 0 ) corner( maxx, maxy, d[maxx][maxy], K, res );

   cout << res[0] << ' ' << res[1] << endl;

   return 0;
}
