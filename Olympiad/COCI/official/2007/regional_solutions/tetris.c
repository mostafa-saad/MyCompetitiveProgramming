
/*
  Croatian Regional Competition in Informatics 2007
  Task TETRIS
  Programming language C
*/

#include <stdio.h>

int main()
{
   int i, S, F, niz[100];
   int moze[8] = {0};

   scanf( "%d%d", &S, &F );
   for ( i=0; i<S; ++i ) {
      scanf( "%d", &niz[i] );

      moze[1] += 1;
      moze[1] += i>=3 && niz[i] == niz[i-1] && niz[i] == niz[i-2] && niz[i] == niz[i-3];

      moze[2] += i>=1 && niz[i] == niz[i-1];

      moze[3] += i>=2 && niz[i] == niz[i-1]+1 && niz[i] == niz[i-2]+1;
      moze[3] += i>=1 && niz[i] == niz[i-1]-1;

      moze[4] += i>=2 && niz[i] == niz[i-1]   && niz[i] == niz[i-2]-1;
      moze[4] += i>=1 && niz[i] == niz[i-1]+1;

      moze[5] += i>=1 && niz[i] == niz[i-1]+1;
      moze[5] += i>=1 && niz[i] == niz[i-1]-1;
      moze[5] += i>=2 && niz[i] == niz[i-1]   && niz[i] == niz[i-2];
      moze[5] += i>=2 && niz[i] == niz[i-1]+1 && niz[i] == niz[i-2];

      moze[6] += i>=2 && niz[i] == niz[i-1]   && niz[i] == niz[i-2];
      moze[6] += i>=2 && niz[i] == niz[i-1]   && niz[i] == niz[i-2]+1;
      moze[6] += i>=1 && niz[i] == niz[i-1];
      moze[6] += i>=1 && niz[i] == niz[i-1]-2;

      moze[7] += i>=2 && niz[i] == niz[i-1]   && niz[i] == niz[i-2];
      moze[7] += i>=2 && niz[i] == niz[i-1]-1 && niz[i] == niz[i-2]-1;
      moze[7] += i>=1 && niz[i] == niz[i-1];
      moze[7] += i>=1 && niz[i] == niz[i-1]+2;
   }

   printf( "%d\n", moze[F] );

   return 0;
}
