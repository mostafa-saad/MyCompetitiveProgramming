#include<cstdio>
#include<iostream>
#include<algorithm>
#include "oi.h"

oi::Random RG;
using namespace std;

bool prime(int p) {
  if (p <= 1) {
    return false;
  }
  for (int d = 2; d * d <= p; ++d) {
    if (p % d == 0) {
      return false;
    }
  }
  return true;
}

bool check_generator(int a,int n){
  if(a == 0 || a == 1) return 0;
  if(__gcd(a,n) != 1) return 0;
  long long tp = a;
  int cnt = 1;
  while(tp != 1){
    cnt++;
    tp = (tp*a)%n;
  }
  return cnt == n-1;
}

int find_generator(int n){
  int g = 2;
  if(n == 1) return 1;
  while(!check_generator(g,n)) g++;
  return g;
}

int find_medium_generator(int n){
  int g = n/3;
  while(!check_generator(g,n)) g++;
  return g;
}

int find_large_generator(int n){
  int g = n-2;
  while(!check_generator(g,n)) g--;
  return g;
}

template<typename F>
void zwykly(const char* filename,int m1, int m3, int k, F generator) {
  assert(prime(m1));
  assert(prime(m3));
  FILE *out = fopen(filename, "w");
  if((m1-2)%k == 0) k++;
  //cerr<<(m1-2)%k<<"\n";
  int g1 = generator(m1);
  int g3 = RG.rand()%(m3/2)+m3/3;
  fprintf(out,"# %d %d %d %d %d\n",g1,g3,m1,m3,k);
  fprintf(stderr, "%s\t n: %8d\tile: %8d\tA: %8d\tB: %8d\tratio: %.02lf\n", filename, m1, m1 / k, k, (m1-2)%k, 
      (0.0 + (m1-2) % k) / k);
  fclose(out);
}

int main(){
  //zwykly("kol0.in",37,41,5);
  
  // pierwsza liczba do liczba kart, druga liczba to zakres z jakiego karty wystepuja,
  // trzecia liczba to k, licznosc kazdego rodzaju kart.
  // pierwsze dwie liczby musza byc liczbami pierwszymi
  
  //zwykly() szuka generatora od 2 w gore
  //zwykly() szuka generatora od n-2 w dol
  //zwykly() szuka generatora od n/2 w gore
  
  
  zwykly("kol1a.in",10039,10169,15,find_generator);
  zwykly("kol1b.in",1009,5,10001,find_generator);
  zwykly("kol1c.in",10039,10169,530,find_medium_generator);
  
  zwykly("kol2a.in",100129,1979293087,15,find_generator);
  zwykly("kol2b.in",199999,1979293087,3,find_medium_generator);
  zwykly("kol2c.in",100213,1979293087,4356,find_medium_generator);
  
  zwykly("kol3a.in",103217,533509,17,find_generator);
  zwykly("kol3b.in", 2100011, 1999999973, 11, find_large_generator);
  //zwykly("kol3b.in",333679,533509,153,find_generator);
  zwykly("kol3c.in",1000003,1999999973,779,find_generator);
  zwykly("kol3d.in",103217,533509,543,find_medium_generator);
  
  zwykly("kol4a.in",1000003,1979293087,18,find_generator);
  zwykly("kol4b.in", 2500027, 789789773, 7, find_medium_generator);
  //zwykly("kol4b.in",999953, 1999999973, 4,find_generator);
  zwykly("kol4c.in",333491,573479,161,find_generator);
  zwykly("kol4d.in",1000117,1979293087,654,find_medium_generator);
  
  zwykly("kol5a.in",2000003, 1999999973, 123,find_generator);
  zwykly("kol5b.in",5000011, 1475200409, 4 ,find_generator);
  zwykly("kol5c.in",2000107, 1999999973, 345,find_medium_generator);
  
  zwykly("kol6a.in",3500017, 1475200409, 518,find_generator);
  zwykly("kol6b.in",8010011, 1475200409, 4,find_generator);
  zwykly("kol6c.in",3500111, 1475200409, 743,find_medium_generator);
  
  zwykly("kol7a.in",5000011, 1955293507, 1025,find_generator);
  zwykly("kol7b.in",15088019, 1955293507, 9,find_large_generator);
  zwykly("kol7c.in",5000101, 1955293507, 422,find_medium_generator);
  
  zwykly("kol8a.in",6500003, 1475200247, 1079,find_generator);
  zwykly("kol8b.in", 30111121, 1999999973, 3,find_generator);
  zwykly("kol8c.in",1000609, 1475200247,22334,find_large_generator);
  zwykly("kol8d.in",6500101, 1475200247, 654,find_medium_generator);
  
  zwykly("kol9a.in",8000009, 1999999973, 261,find_generator);
  zwykly("kol9b.in",40000003, 1475200247, 2,find_medium_generator);
  zwykly("kol9c.in",1000609, 1475200247,17868,find_generator);
  zwykly("kol9d.in",8000101, 1999999973, 567,find_medium_generator);
  
  zwykly("kol10a.in",10000511, 1979293087, 7,find_generator);
  zwykly("kol10b.in", 50000017, 100000007, 3, find_large_generator);
  zwykly("kol10c.in",1000609, 1475200247,22324,find_generator);
  zwykly("kol10d.in",10000511, 1979293087, 638,find_medium_generator);
  
}
