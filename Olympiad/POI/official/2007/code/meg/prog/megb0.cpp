/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    megb0.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie niepoprawne - zakladamy, ze numeracja          *}
{*            wierzcholkow musi byc numeracja preorder                   *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>

#define MAXN 250000
#define MAXTREE 600000

//drzewo - graf wiosek
int first_son[MAXN+1];
int next_brother[MAXN+1];
int depth[MAXN+1]; //odleglosc wioski o danym numerze od wioski 1
int tree[MAXTREE]; //drzewo licznikowe

int subtree_end[MAXN+1]; //zakres numeracji poddrzewa dla wiosek
int n,m; //liczba wiosek i wypraw
int tree_size; //rozmiar drzewa licznikowego

//tworzy drzewo - graf wiosek
void make_graph() {
  int a,b;
  
  scanf("%d ",&n);
  for (int i=1; i<=n; i++) {
    first_son[i]=0;
    next_brother[i]=0;
  }
  
  for (int i=1; i<n; i++) {
    scanf("%d %d ", &a, &b);
    next_brother[b]=first_son[a];
    first_son[a]=b;
  }
}

//oblicza glebokosc wierzcholkow i zakres poddrzewa
int init(int vertex, int dep) {
  subtree_end[vertex]=vertex;
  depth[vertex] = dep;
  int son = first_son[vertex];
  while (son!=0) {
    int tmp=init(son,dep+1);
    if (tmp>subtree_end[vertex]) subtree_end[vertex]=tmp;
    son = next_brother[son];
  }
  return subtree_end[vertex];
}

//tworzenie drzewa licznikowego
void make_tree() {
 tree_size = 2;
 while (tree_size<=n) tree_size*=2;
 tree_size*=2;
 
 for (int i=0; i< tree_size; i++) tree[i]=0;
}

//uaktualnic przedzial [a,b] - liczba drog zmniejsza sie o 1
void change_interval(int a, int b, int act_num, int act_size) {
  if (a<=0 && b>=act_size-1) {
    tree[act_num]+=1;
    return;
  }
  int new_size = act_size / 2;
  if (a < new_size) change_interval(a,b,2*act_num+1,new_size);
  if (b >= new_size) change_interval(a-new_size, b-new_size,2*act_num+2,new_size);
}

void change_road(int a, int b) {
  change_interval(b, subtree_end[b],0,tree_size/2);
}

//sumuje wartosci w drzewie licznikowym 
int count_values(int number, int act_num, int tree_size, int act_value) {
  act_value-=tree[act_num];
  if (tree_size>1) {
    int new_size = tree_size/2;
    if (number<new_size) 
      act_value = count_values(number, 2*act_num+1, new_size, act_value);
    else 
      act_value=count_values(number-new_size, 2*act_num+2, new_size, act_value);
  }
  return act_value;
}

//wycieczka do miasta 'vertex'
void trip(int vertex) {
  int d = depth[vertex];
  d=count_values(vertex, 0, tree_size/2, d);
  printf("%d\n",d);
}

int main() {
  char z;
  int a,b;

  make_graph();
  init(1,0);
  make_tree();
  
  scanf("%d ",&m);
  for (int j=0; j<n+m-1; j++) {
    scanf ("%c ",&z);
    if (z=='A') {
      scanf("%d %d ", &a, &b);
      change_road(a,b);
    }
    else {
      scanf("%d ", &a);
      trip(a);
    }
  }
  return 0;
}
