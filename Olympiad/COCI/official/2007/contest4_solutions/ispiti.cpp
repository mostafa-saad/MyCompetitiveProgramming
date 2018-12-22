
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task ISPITI
  Programming language C++
*/

#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int n, m;
struct ucenik {
   int a, b;
   int sorted_index; // indeks ucenika u sortiranom nizu ucenika
   int index;  // indeks ucenika u inputu
} U[200000];

bool pair_cmp( const ucenik &X, const ucenik &Y ) { // sortiranje po drugom, pa prvom broju
   if( X.b != Y.b ) return X.b < Y.b;
   return X.a < Y.a;
}

bool index_cmp( const ucenik &X, const ucenik &Y ) { // sortiranje po indeksu ucenika
   return X.index < Y.index;
}

struct event { // jedan dogadjaj iz inputa: type = 1 za dolazak ucenika, a 2 za upit
   int who, type;
} E[200000];

int tree[1<<19];

inline int bolji( int uc1, int uc2 ) { // usporedjuje po prvom broju ucenike, i pazi na prazna mjesta u stablu
   if( uc1 == -1 ) return uc2;
   if( uc2 == -1 ) return uc1;
   if( U[uc1].a < U[uc2].a ) return uc2;
   return uc1;
}

void update( int i, int lo, int hi, int uc ) { // dodaj ucenika uc u tournament tree
   if( lo > U[uc].sorted_index || hi < U[uc].sorted_index ) return;

   if( lo == hi ) { // ako smo na listu stabla, zapisi uc
      tree[i] = uc;
   } else {
      int mid = (lo+hi)/2;
      update( 2*i, lo, mid, uc ); // odi lijevo
      update( 2*i+1, mid+1, hi, uc ); // odi desno

      tree[i] = bolji( tree[2*i], tree[2*i+1] ); // u trenutni zapisi "bolji" od dva podstabla
   }
}

// i u query i u update proceduri, varijabla i pamti trenutnu poziciju u stablu, a lo i hi pamte u kojem podintervalu trazimo

int query( int i, int lo, int hi, int uc ) { // vrati prvi desno koji ima prvi broj veci od ucenika uc
   if( hi <= U[uc].sorted_index ) return -1; // ako se uc nalazi ljevo od podintervala [lo, hi) vrati -1
   if( tree[i] == -1 || U[tree[i]].a < U[uc].a ) return -1; // ako u podintervalu nema ucenika ili je najveci prvi broj manji od onoga u uc, vrati -1

   if( lo == hi ) return tree[i];

   int mid = (lo+hi)/2; // novi podintervali su [lo, mid) i [mid, hi)

   int t = query( 2*i, lo, mid, uc );
   if( t != -1 ) return t; // ako u lijevom podintervalu ima netko veci od njega, vrati rezultat, nema potrebe da idemo u desni
   return query( 2*i+1, mid+1, hi, uc ); // vrati prvi veci u desnom podintervalu

}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) { // prvo sve ucitamo, onda rjesavamo problem
      char c;
      scanf( " %c", &c );
      if( c == 'D' ) {
         scanf( "%d%d", &U[m].a, &U[m].b );
         U[m].index = m;
         E[i].who = m++;
         E[i].type = 1;
      } else {
         scanf( "%d", &E[i].who ); --E[i].who;
         E[i].type = 2;
      }
   }

   sort( U, U+m, pair_cmp ); // sortiramo ucenike po drugom broju, a po prvom u slucaju izjednacenja
   for( int i = 0; i < m; ++i ) U[i].sorted_index = i; // sazimanje
   sort( U, U+m, index_cmp ); // vracamo ih kako su bili, da mozemo lako doci do i-tog ucenika

   memset( tree, -1, sizeof tree );
   for( int i = 0; i < n; ++i ) {
      if( E[i].type == 1 ) {
         update( 1, 0, m-1, E[i].who ); // doselio se ucenik E[i].who
      } else {
         int x = query( 1, 0, m-1, E[i].who ); // nadji prvi desno u tree-u od ucenika E[i].who, koji ima veci prvi broj
         if( x == -1 ) printf( "NE\n" );
         else printf( "%d\n", x+1 );
      }
   }

   return 0;
}
