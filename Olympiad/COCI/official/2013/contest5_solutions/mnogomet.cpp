#include <cstdio>
#include <cstring>

const int MAXN = 101;
const int MAXR = 15;
const int MAXT = 602;
const int MAX_STANJA = 2 * MAXN + 2;

// pGol[ ciji_golman_ima_loptu ][ tko_ce_zabit ][ koji_potez ];
// pGol[ 0 ][ 1 ][ 1 ] je vjerojatnost da ako golman tima 0 primi loptu da prvi
// potez odmah da gol timu 1.
double pGol[ 2 ][ 2 ][ MAXT ];

// pMir[ ciji_golman_ima_loptu ][ koji_potez ] vjerojatnost da se odigra
// koji_potez i da jos nije pao gol.
double pMir[ 2 ][ MAXT ];

// N je broj igraca (s golmanom) u jednoj ekipi
// T je broj poteza koji ce se odigrati
// R je do koliko se igra.
int N, T, R;

// ova klasa je odgovorna da ucita podatke o preciznostima i dodavanjima i
// generira nizove pGol i pMir.
class Preprocess {
  // stanje u preprocesingu je P(entitet, t), vjerojatnost da u
  // trenutku t entitet ima loptu. entitet moze biti bilo koji od igraca dva
  // tima, i golove. gol tima cemo kodirati kao 2*N + TIM
  // preciznost igraca
  double matrix[ MAX_STANJA ][ MAX_STANJA ];

  // broj stanja s kojima baratamo.
  int matrix_size;

  // ucita preciznosti i vjerojatnosti dodavanja.
  void load() {
    int kard[2], kome;
    double p;
    memset(matrix, 0, sizeof matrix);
    for (int tim = 0; tim < 2; ++tim) {
      for (int id = 0; id < N; ++id) {
        // vjerojatnost da ovaj igrac sad zabije gol protivniku.
        // a suprotna vjerojatnost se pridodaje vjerojatnosti da je dodao loptu
        // golmanu protivnika. (fulao gol)
        scanf("%lf%d%d", &p, kard + 0, kard + 1);
        // kome moze dodati i tko mu moze odzeti
        for (int protivnik = 0; protivnik < 2; ++protivnik) {
          for (int k = 0; k < kard[protivnik]; ++k) {
            scanf("%d", &kome);
            matrix
              [ tim * N + id ]
              [ (protivnik ^ tim) * N + kome - 1 ]
                += 1. / (1+kard[0]+kard[1]);
          }
        }
        // i dodaj posljedice udarca.
        matrix[ tim * N + id ][ 2 * N + (!tim) ] += p / (1+kard[0]+kard[1]);
        matrix[ tim * N + id ][ (!tim) * N + 0 ] += (1-p) / (1+kard[0]+kard[1]);
      }
    }
    /*
    for (int i = 0; i < matrix_size; ++i) {
      for (int j = 0; j < matrix_size; ++j) {
        printf("%6.3lf", matrix[i][j]);
      }
      printf("\n");
    }
    */
  }

  // vrti vjerojatnosti u matrici i generira pGol
  void solve() {
    for (int tim = 0; tim < 2; ++tim) {
      double p[ 2 ][ MAX_STANJA ];
      int staro = 0;
      memset( p[ staro ], 0, sizeof p[0] );
      p[ staro ][ tim * N ] = 1;
      // TODO, ovdje moze biti N^3, mnozenje matrica
      for (int t = 0; t < T + 1; ++t) {
        // updateam rezultat
        pGol[ tim ][ 0 ][ t ] = p[ staro ][ 2 * N + 1 ];
        pGol[ tim ][ 1 ][ t ] = p[ staro ][ 2 * N + 0 ];
        // nagradim nove vjerojatnosti na temelju starih
        memset( p[!staro], 0, sizeof p[0] );
        for (int k = 0; k < matrix_size; ++k)
          for (int j = 0; j < matrix_size; ++j)
            p[ !staro ][ j ] += p[ staro ][ k ] * matrix[ k ][ j ];
        // i staro je novo novo.
        staro = !staro;
      }
    }
  }

  // mora izgenerirati pMir
  void post() {
    for (int tim = 0; tim < 2; ++tim) {
      double mir = 1;
      for (int t = 0; t < T + 1; ++t) {
        mir -= pGol[ tim ][ 0 ][ t ];
        mir -= pGol[ tim ][ 1 ][ t ];
        pMir[ tim ][ t ] = mir;
      }
    }
  }

 public:
  Preprocess() {
    matrix_size = 2 * N + 2;
    load();
    solve();
    post();
  }
};

void load() {
  scanf("%d%d%d", &N, &R, &T);
  new Preprocess();
}

double dp[ MAXR ][ MAXR ][ 2 ][ MAXT ];

// pre:
// R^2 * 2 * T * 2 * T
// == 4 (RT)^2 == 4 * 36 * 10^6 == 10^8

// vjerojatnost da je u t-tom potezu ekipa tko zabila gol za r1:r2
// u trenutku 0 je ekipa 1 zabila gol za 0:0 zato je ekipa 0 dobila loptu.
double solve(int r1, int r2, int tko, int t) {
  if (r1 < 0 || r2 < 0 || t < 0) return 0;
  if (!r1 && !r2 && tko && !t) return 1;
  double &sol = dp[ r1 ][ r2 ][ tko ][ t ];
  if (sol != -1) return sol;

  // stavljam parametre r1 i r2 u niz, tako mi je lakse.
  int rezultat[2] = {r1, r2};
  // prosli rezultat je jedinstven (ekipa koja je sad zabila gol je prije imala
  // gol manje). ovdje ce ovo mozda biti negativno ali onda je vjerojatnost 0
  // zbog prve linije u funkciji.
  rezultat[tko] -= 1;
  sol = 0;

  // prosli rezultat je jedinstven (neka je to R) i imamo ga u nizu rezultat.
  // vjerojatnost da je u t-tom potezu ekipa tko zabila gol za r1:r2
  // rastavljamo na slucajeve tko je zabio prosli gol (za R).
  for (int tko_zabio_prosli = 0; tko_zabio_prosli < 2; ++tko_zabio_prosli) {
    // rastavljam ovu vjerojatnost na slucajeve u kojem trenutku je pao taj gol
    // za prosli rezultat.
    for (int prosli_t = 0; prosli_t < t; ++prosli_t) {
      sol +=
        solve(rezultat[0], rezultat[1], tko_zabio_prosli, prosli_t) *
        pGol[ !tko_zabio_prosli ][ tko ][ t - prosli_t ];
    }
  }

  return sol;
}

// vjerojatnost da se igra zavrsila sa r1:r2. nesmije biti r1==r2==K
double read(int r1, int r2) {
  double sol = 0;
  int rezultat[2] = {r1, r2};
  // ako nije bilo golova onda je to poseban slucaj.
  if (!r1 && !r2) {
    return pMir[ 0 ][ T ];
  }
  // ako je igra stala zbog zabijanja R golova jednog tima?
  if (r1 == R || r2 == R) {
    // odaberem pobjednika (samo jednog).
    for (int pobjednik = 0; pobjednik < 2; ++pobjednik) {
      if (rezultat[pobjednik] != R) continue;
      for (int t = 0; t <= T; ++t)
        sol += solve(r1, r2, pobjednik, t);
    }
  } else {
    // rastavljam na tko je dao zadnji gol.
    for (int zadnji_gol = 0; zadnji_gol < 2; ++zadnji_gol) {
      // rastavljam na kad je pao taj zadnji gol.
      for (int t = 0; t <= T; ++t) {
        sol += solve(rezultat[0], rezultat[1], zadnji_gol, t)
          * pMir[ !zadnji_gol ][ T - t ];
      }
    }
  }
  return sol;
}

int main() {
  for (int i = 0; i < MAXR; ++i)
    for (int j = 0; j < MAXR; ++j)
      for (int k = 0; k < 2; ++k)
        for (int t = 0 ; t < MAXT; ++t)
          dp[i][j][k][t] = -1;
  load();
  double sum = 0;
  for (int a = 0; a <= R; ++a) {
    for (int b = 0; b <= R; ++b) {
      if (a == R && b == R) continue;
      printf("%.10lf\n", read(a, b));
      sum += read(a, b);
    }
  }
  return 0;
}
