#include <cstdio>
#include <cstring>
#define MAXN 100000

int sljedeci_program[MAXN];
int vec_bio[MAXN];

int main(void){
  int n, m, p; scanf ("%d%d%d", &n, &m, &p);

  memset(sljedeci_program, -1, sizeof(sljedeci_program));
  for (int i=0; i<n; i++){
    int a, b; scanf ("%d%d", &a, &b); a--; b--;

    if (sljedeci_program[b] == -1)
    sljedeci_program[b] = a;
  }

  int trenutni = p-1, ukupno_prebacivanja = 0;
  while(vec_bio[trenutni] == 0 && sljedeci_program[trenutni] != -1){
      //printf ("trenutni: %d\n", trenutni+1);
    ukupno_prebacivanja++;
    vec_bio[trenutni] = 1;
    trenutni = sljedeci_program[trenutni];
  }

  //printf ("na kraju trenutni: %d\n", trenutni+1);
  if (vec_bio[trenutni]) printf ("-1\n");
  else printf ("%d\n", ukupno_prebacivanja);

  return 0;
}
