/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Sznurki                                        *
 *   Plik:                szn.cpp                                        *
 *   Autor:               Marcin Mucha                                   *
 *************************************************************************/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int BIG_NUMBER = 20000;


typedef pair<int,int> RESULT;

class Joiner{
private:
  vector<int> &v;
  vector<RESULT> results;
public:
  Joiner(vector<int> &_v) : v(_v){}

  int maxSumOpp(int begin, int end);
  
  // Dla tablicy v oblicza tablice par 
  // (maks. dlug. w parach, min. dlugosc usunietego)
  vector<RESULT> &getResults(int bound=BIG_NUMBER);
};

class Vertex{
  int nr;
  vector<Vertex *> ngbs;
public:
  Vertex(int _nr): nr(_nr){}
  void addNgb(Vertex *v){ ngbs.push_back(v);}
  int getDegree(){ return ngbs.size();}

  int getNr(){ return nr;}
  // Zwraca tablice indeksowana ograniczeniem na
  // dlugosci sznurka calkowicie zawartego w poddrzewie.
  // Wartosci w tablicy to minimalna dlugosc sznurka 
  // wychodzacego z poddrzewa.
  vector<int> getMinOutPaths(const Vertex *parent) const;
};

class Tree{
  vector<Vertex> V;
  int n;
public:
  Tree(istream &i);

  // Zwraca liczbe wierzcholkow nieparzystego stopnia
  int getOddDegreeVertices();

  // Zwraca minimalna dlugosc sznurka w pokryciu calego drzewa
  int getMinPathLength();
};

// **********************************************

int Joiner::maxSumOpp(int begin, int end){
  int maxSum = 0;
  for(int i=0; i < (end-begin)/2; i++)
    maxSum = max( maxSum, v[begin+i]+v[end-i-1]);
  return maxSum;
}

vector<RESULT> &Joiner::getResults(int bound){
  results.clear();

  if (v.back() > bound){
    results.push_back(RESULT(bound,BIG_NUMBER));
    return results;
  }
  
  if (v.size()%2){
    int maxSum = maxSumOpp( 0, v.size()-1);
    if( maxSum <= bound ){
      results.push_back(RESULT(maxSum,v.back()));
      // Probujemy usuwac element o coraz nizszym indeksie pilnujac
      // zeby przeciwlegle sumy nie przekroczyly bound
      for(int removed = v.size()-2; removed >= 0; removed--){
	if( removed >= v.size()/2)
	  maxSum = max( maxSum, v[removed+1]+v[v.size()-removed-2]);
	else
	  maxSum = max( maxSum, v[removed+1]+v[v.size()-removed-1]);
	if( maxSum > bound) break;
	results.push_back(RESULT(maxSum,v[removed]));
      }
    }
  } else{ // v.size() parzyste
    // Tu jest trickowy fragment
    // Obliczamy tablice dla v bez ostatniego elementu
    int last = v.back(); v.pop_back();
    getResults(bound);
    // Zmieniamy pierwsze wartosci
    for(int i=0; i < results.size(); i++){
      results[i].first = max( results[i].first, last);
      if( results[i].first >= BIG_NUMBER)
	results[i].second = BIG_NUMBER;
    }
    // I na koncu obliczamy przypadek z parzysta tablica
    v.push_back(last);
    int maxSum = maxSumOpp( 0, v.size());
    if (maxSum <= bound)
      results.push_back(RESULT(maxSum,0));
  }

  if(results.empty())
    results.push_back(RESULT(bound,BIG_NUMBER));
  return results;
}

vector<int> Vertex::getMinOutPaths(const Vertex *parent) const{
  vector<vector<int> > subtreeData;
  int maxDataSize = 0;

  // Zbieramy dane od synow

  for(int i = 0; i < ngbs.size(); i++)
    if (ngbs[i] != parent){
      subtreeData.push_back(ngbs[i]->getMinOutPaths(this));
      maxDataSize = max( (int)subtreeData.back().size(), maxDataSize);
    }

  // Lisc
  if( subtreeData.empty())
    return vector<int>(1,0);
  
  // Co najmniej maxDataSize liczb bedzie na pewno
  vector<int> data(maxDataSize,BIG_NUMBER);

  // inPathLen - maksymalna dlugosc sciezki wewnetrznej w dowolnym
  // z poddrzew
  for(int inPathLen = 0; inPathLen < maxDataSize; inPathLen++){
    // Koncowki do laczenia (trzeba pamietac o wydluzeniu!)
    vector<int> looseEnds;
    for(int i=0; i<subtreeData.size(); i++)
      if(subtreeData[i].size() > inPathLen)
	looseEnds.push_back(subtreeData[i][inPathLen]+1);
      else
	looseEnds.push_back(subtreeData[i].back()+1);
    
    sort( looseEnds.begin(), looseEnds.end());
    Joiner joiner(looseEnds);

    if( inPathLen < maxDataSize-1)
      // Wybieramy najlepszy wynik
	data[inPathLen] = joiner.getResults(inPathLen).back().second;
    else{
      vector<RESULT> &results = joiner.getResults(BIG_NUMBER);
      data.reserve(results.back().first+1);
      // Wstawiamy wszystkie wyniki pamietajac o dziurach
      for(int i=0; i<results.size(); i++){
	results[i].first = max( results[i].first, inPathLen);
	data.resize( results[i].first+1, data.back());
	data[results[i].first] = results[i].second;
      }
    }
  }
  
  return data;
}
 
Tree::Tree(istream &i){
  i >> n;
  for(int i=0; i < n+1; i++)
    V.push_back(Vertex(i));
  for(int i=1; i < n; i++){
    int u,v;
    cin >> u >> v;
    V[u].addNgb(&V[v]);
    V[v].addNgb(&V[u]);
  }
}

int Tree::getOddDegreeVertices(){
  int oddDegreeVertices=0;
  for(int i=1;i<=n;i++)
    oddDegreeVertices += V[i].getDegree()%2;
  return oddDegreeVertices;
}

int Tree::getMinPathLength(){
  // Chcemy startowac z nieparzystego wierzcholka.
  // Ostatni wierzcholek parzysty moze dac zly wynik
  // bo bedzie myslal ze jest nieparzysty
  int start = 1;
  while( V[start].getDegree()%2 == 0) start++;
  // V[0] to falszywy wierzcholek
  // W ten sposob V[start] jest korzeniem
  vector<int> p = V[start].getMinOutPaths(&V[0]);
  
  int minPathLength = n;
  for(int i=0; i < p.size(); i++)
    minPathLength = min( minPathLength, max(i,p[i]));
  return minPathLength;
}

// **********************************************

int main(){
  Tree T(cin);
  cout << T.getOddDegreeVertices()/2 << " " << T.getMinPathLength() << endl;
  return 0;
}
