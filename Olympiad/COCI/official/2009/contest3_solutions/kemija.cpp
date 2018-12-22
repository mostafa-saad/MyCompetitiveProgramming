#include <cstdio>
#include <cstring>
using namespace std;

int main() {
   char ulaz[105];
   fgets(ulaz, sizeof ulaz, stdin);

   for ( int i=0; ulaz[i]!='\0'; ++i ) {
      printf("%c", ulaz[i]);
      if ( strchr("aeiou", ulaz[i]) != NULL )
         i += 2;
   }

   return 0;
}
