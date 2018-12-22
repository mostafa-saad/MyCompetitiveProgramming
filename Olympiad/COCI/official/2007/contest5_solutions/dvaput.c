
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task DVAPUT
  Programming language C
*/

#include <stdio.h>
#include <string.h>

#define MAXLEN  200000
#define MAXHASH 200003

typedef struct {
   int hash, key, next;
} node;

int nnodes = 0;
node nodes[MAXLEN];
int tablica[MAXHASH];

int trazi2( const char *str, int len )
{
   unsigned hash, sub;
   int i;

   if ( len == 0 ) return 1;

   while ( nnodes > 0 ) {
      tablica[ nodes[--nnodes].hash ] = -1;
   }

   hash = 0; sub = 1;
   for ( i=0; i<len; ++i ) {
      sub = (26*sub) % MAXHASH;
      hash = (26*hash + str[i]) % MAXHASH;
   }

   sub = MAXHASH - sub;
   for ( i=len-1; str[i]!='\0'; ++i ) {
      int p;
      for ( p=tablica[hash]; p!=-1; p=nodes[p].next ) {
         int isti = 1, j;
         for ( j=0; j<len; ++j )
            if ( str[ nodes[p].key+j ] != str[ i-len+1+j ] ) {
               isti = 0;
               break;
            }
         if ( isti )
            return 1;
      }

      nodes[nnodes].hash = hash;
      nodes[nnodes].key  = i-len+1;
      nodes[nnodes].next = tablica[hash];
      tablica[hash] = nnodes++;

      hash = (26*hash + sub*str[i-len+1] + str[i+1]) % MAXHASH;
   }

   return 0;
}

int main()
{
   int L, i, lo, hi;
   static char str[MAXLEN+1];
   scanf( "%d%s", &L, str );

   for ( i=0; i<MAXHASH; ++i )
      tablica[i] = -1;

   lo = 0; hi = L-1;
   while ( lo<hi ) {
      int mid = (lo+hi+1) / 2;

      if ( trazi2(str, mid) ) lo = mid;
      else hi = mid-1;
   }

   printf( "%d\n", lo );
   return 0;
}
