#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

#define MAX 10000

using namespace std;

int n, m;

vector<int> adj[MAX];

int n_prstena;
vector<int> prsten[MAX];

vector<int> prsteni[MAX];
vector<int> mostovi[MAX];

int traversal_time;
int discover[MAX];
int lowlink[MAX];
stack<int> S;

void dfs( int i, int dad ) {
   discover[i] = traversal_time++;
   lowlink[i] = discover[i];

   S.push( i );

   for( vector<int>::iterator it = adj[i].begin(); it != adj[i].end(); ++it ) {
      if( *it == dad ) continue;
      
      if( discover[*it] != -1 ) {
         lowlink[i] <?= discover[*it];
      } else {
         dfs( *it, i );
         
         if( lowlink[*it] < discover[i] ) {
            lowlink[i] <?= lowlink[*it];
         } else if( lowlink[*it] == discover[i] ) {
            prsteni[i].push_back( n_prstena );
            
            do {
               prsten[n_prstena].push_back( S.top() );
               S.pop();
            } while( prsten[n_prstena].back() != *it );
            
            ++n_prstena;
         } else {
            mostovi[i].push_back( S.top() ); 
            S.pop();
         }
      }
   }
}

int memo[MAX][2];

#define STAZA 0
#define DJIR 1

int rec( int X, int sto_racunam ) {
   int &ret = memo[X][sto_racunam];
   if( ret >= 0 ) return ret;

   ret = 0;

   int profit = 0; // koliko maksimalno mogu profitirati ako se ne moram vratiti u X

   for( int i = 0; i < mostovi[X].size(); ++i ) // za sve mostove koji izlaze iz X
      profit >?= 1 + rec( mostovi[X][i], STAZA ); 

   for( int i = 0; i < prsteni[X].size(); ++i ) { // za sve prstene koji vise iz X
      vector<int> &P = prsten[prsteni[X][i]];

      int best = 0;
      int smjer1 = 1, smjer2 = 1;
      int ciklus = P.size() + 1;

      for( int j = 0; j < P.size(); ++j ) {
         best >?= smjer1 + rec( P[j], STAZA );
         smjer1 += 1 + rec( P[j], DJIR );

         best >?= smjer2 + rec( P[P.size()-j-1], STAZA );
         smjer2 += 1 + rec( P[P.size()-j-1], DJIR );

         ciklus += rec( P[j], DJIR );
      }
      
      ret += ciklus;

      profit >?= best - ciklus;
   }

   if( sto_racunam == STAZA ) ret += profit;

   return ret;
}

int main( void ) {
   scanf( "%d%d", &n, &m );

   for( int i = 0; i < m; ++i ) {
      int a, b;
      scanf( "%d%d", &a, &b ); --a; --b;
      
      adj[a].push_back( b );
      adj[b].push_back( a );
   }

   memset( discover, -1, sizeof discover );
   dfs( 0, -1 );

   memset( memo, -1, sizeof memo );
   printf( "%d\n", rec( 0, 0 ) );

   return 0;
}
