/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Turniej                                        *
 *   Plik:                turv1.cpp                                      *
 *   Autor:               Marcin Mucha                                   *
 *************************************************************************/

#include <vector>
#include <deque>
#include <list>

#include <stdio.h>

using namespace std;

void readData(vector< vector<int> > &players){
  int n; scanf("%d",&n);
  players.resize( n+1);
  for(int i = 1; i <= n; i++){
    int size;
    scanf("%d",&size);
    players[i].resize( size);
    for(int j=0; j < size; j++)
      scanf("%d",&players[i][j]);
  }
}

/* Znajdujemy jaki¶ zbiór zwyciêzców, byæ mo¿e niepe³ny, ale za to szybko */
void findSomeWinners(vector< vector<int> > &players, vector<bool> &isWinner){
  isWinner.resize( players.size(), true);
  for(unsigned int player=1; player < players.size(); player++)
    if( isWinner[player])
      for( vector<int>::iterator defeated=players[player].begin(); defeated != players[player].end(); defeated++)
	isWinner[*defeated] = false;
}

/* Znajdujemy pozosta³ych zwyciêzców zaczynaj±c od dowolnego niepustego ich podzbioru */
int findAllWinners( vector< vector<int> > &players, vector<bool> &isWinner){
  deque<int> winnersQueue;
  list<int> loosers;
  for(unsigned int player=1; player < players.size(); player++)
    if( isWinner[player])
      winnersQueue.push_back(player);
    else
      loosers.push_back(player);

  int counter = winnersQueue.size();

  while(!winnersQueue.empty()){
    int winner = winnersQueue.front(); winnersQueue.pop_front();

    vector<int>::iterator defeated = players[winner].begin();
    vector<int>::iterator dEnd = players[winner].end();
    for(list<int>::iterator looser = loosers.begin(); looser != loosers.end();){
      while( (defeated != dEnd) && (*defeated < *looser)) 
	defeated++;
      if ( ( defeated == dEnd) || (*defeated > *looser)){
	winnersQueue.push_back(*looser);
	isWinner[*looser] = true;
	counter++;
	looser = loosers.erase(looser);
      } else{
	defeated++; 
	looser++;
      }
    }
  }
  return counter;
}

void dumpWinners(int winnersNo, vector<bool> &isWinner){
  printf("%d",winnersNo);
  for(unsigned int i=1; i< isWinner.size(); i++)
    if(isWinner[i])
      printf(" %d", i);
  printf("\n");
}

int main(){
  vector< vector<int> > players;
  readData( players);

  vector<bool> isWinner;
  findSomeWinners( players, isWinner);

  int winnersNo = findAllWinners( players, isWinner);

  dumpWinners(winnersNo,isWinner);

  return 0;
}
