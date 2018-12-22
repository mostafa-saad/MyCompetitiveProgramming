#include <cstdio>
#include <vector>

const int MAXN = 100100;

int n;
int temperatura[MAXN];
int zima_dolazi[MAXN];

int najveca_duzina;
std::vector< int > lista_najduzih;

void oznaci(int kraj_zime, int duzina_zime) {
  int pocetak_zime = kraj_zime - duzina_zime;

  for (int i = pocetak_zime-1; i >= 0 && i >= pocetak_zime-2*duzina_zime; --i) {
    zima_dolazi[i] = 1;
  }

  if (duzina_zime > najveca_duzina) {
    lista_najduzih.clear();
    najveca_duzina = duzina_zime;
  }
  if (duzina_zime == najveca_duzina) {
    lista_najduzih.push_back(pocetak_zime);
  }
}

int pronadji_najduzu() {
  int najveci_broj_dodatnih_dana = 0;

  for (int i = 0; i < (int)lista_najduzih.size(); ++i) {
    int broj_dodatnih_dana = 0;
    for (int j = lista_najduzih[i]-najveca_duzina*2-1;
         j >= 0 && j >= lista_najduzih[i]-3*najveca_duzina;
         --j) {
      broj_dodatnih_dana += !zima_dolazi[j];
    }
    if (broj_dodatnih_dana > najveci_broj_dodatnih_dana) {
      najveci_broj_dodatnih_dana = broj_dodatnih_dana;
    }
  }

  return najveci_broj_dodatnih_dana;
}

int main() {
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", temperatura+i);
  }

  int trenutna_duzina = 0;
  for (int i = 0; i <= n; ++i) {
    if (temperatura[i] >= 0) {
      oznaci(i, trenutna_duzina);
      trenutna_duzina = 0;
      continue;
    }

    ++trenutna_duzina;
  }

  int broj_dana = 0;
  for (int i = 0; i < n; ++i) {
    broj_dana += zima_dolazi[i];
  }

  printf("%d\n", broj_dana + pronadji_najduzu());

  return 0;
}
