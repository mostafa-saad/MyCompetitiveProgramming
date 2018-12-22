#include <cstdio>

const int inf = 1000000000;

int n, k;
int x[100], y[100];
int cm[100], sm[100];
int cv[100], sv[100];

int nabavi( int grama, int cm, int sm, int cv, int sv ) {
   int rez = inf;
   int velikih = 0;
   do {
      int malih = (grama - velikih * sv + sm-1) / sm >? 0;
      rez <?= malih * cm + velikih * cv;
   } while( velikih++ * sv <= grama );
   return rez;
}

bool moguce( int porcija ) {
   int cijena = 0;
   for( int i = 0; i < n; ++i )
      cijena += nabavi( x[i] * porcija - y[i], cm[i], sm[i], cv[i], sv[i] );
   return cijena <= k;
}

int main( void ) {
   scanf( "%d%d", &n, &k );
   for( int i = 0; i < n; ++i )
      scanf( "%d%d%d%d%d%d", &x[i], &y[i], &sm[i], &cm[i], &sv[i], &cv[i] );

   int lo = 0, hi = 1;
   while( moguce( hi ) ) hi = hi * 2;

   while( lo < hi ) {
      int mid = (lo+hi+1) / 2;
      if( moguce( mid ) ) lo = mid; else hi = mid-1;
   }

   printf( "%d\n", lo );

   return 0;
}
