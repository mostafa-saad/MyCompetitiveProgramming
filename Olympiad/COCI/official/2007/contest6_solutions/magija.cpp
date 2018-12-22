
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task MAGIJA
  Programming language C++
*/

#include <cstdio>
using namespace std;

int main(){
   char karta[201][201];
   int r, s, a, b;

   scanf("%d%d", &r, &s);

   for (int i=0; i<r; i++){
      for (int j=0; j<s; j++){
         scanf(" %c", &karta[i][j]);
         karta[2*r-i-1][j] = karta[i][2*s-j-1] = karta[2*r-i-1][2*s-j-1] = karta[i][j];
      }
   }

   scanf("%d%d", &a, &b);
   karta[a-1][b-1] = karta[a-1][b-1] == '#' ? '.' : '#';

   for (int i=0; i<2*r; i++) {
      karta[i][2*s] = '\0';
      printf("%s\n", karta[i]);
   }

   return 0;
}
