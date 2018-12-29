/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Jaskinia                                       *
 *   Plik:                jas.cpp                                        *
 *   Autor:               Arkadiusz Paterek                              *
 *************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

#define VAR(a, b) __typeof(b) a = (b)
#define FOREACH(it, c) for(VAR(it, (c).begin()); it != (c).end(); ++it)

struct Node {
  vector<int> neigh; // s±siedzi wezla w drzewie
  int f; // funkcja f z dowodu (minimalna liczba pytañ)
  vector<int> S; // zbiór S z dowodu (warto¶ci f, które "widaæ" "patrz±c" od ojca wierzcho³ka)
  
  Node() : S(25, 0) { // inicjujemy S na 25 elementow, bo K = max_f nie moze byæ wiêksze niz log(rozmiar drzewa)
    f = 0;
  }
};

struct Tree {
  vector<Node> nodes; // wierzcho³ki tworz±ce drzewo
  
  friend istream &operator>>(istream &is, Tree &tree) { // wczytanie drzewa z wej¶æia
    vector<Node> &nodes = tree.nodes;
    nodes.clear();
    
    int size;
    is >> size;
    nodes.resize(size);

    int a, b;
    for (int i = 0; i < size - 1; ++i) {
      is >> a >> b;
      --a;
      --b;
      nodes[a].neigh.push_back(b);
      nodes[b].neigh.push_back(a);
    }
    
    return is;
  }
  
  void computeF(int n, int father) { // DFS w drzewie - obliczenie warto¶ci f w wê¼le n
    Node &node = nodes[n];
    
    FOREACH(child_i, node.neigh)
      if (*child_i != father) { // dla wszystkich s±siadów w drzewie oprócz poprzednika
        Node &child = nodes[*child_i];
        computeF(*child_i, n);
        
        for (int i = 0; i < (int)child.S.size(); ++i)
          if (child.S[i] > 0)
            ++node.S[i];
      }


    int m = node.S.size();
    do
      --m;
    while (m >= 0 && node.S[m] < 2);

    node.f = m + 1;
    while (node.S[node.f] > 0)
      ++node.f;
    
    for (int i = 0; i < node.f; ++i)
      node.S[i] = 0;

    node.S[node.f] = 1;
    
/*    cerr << "computeF " << n << " " << father << endl;
    cerr << " m = " << m << endl;
    cerr << " f = " << node.f << endl;
    cerr << " S = ";
    copy(node.S.begin(), node.S.end(), ostream_iterator<int>(cerr, " "));
    cerr << endl;*/
  }
  
  int computeAnswer() {
    computeF(0, -1);
    
    int max_f = -1;
    FOREACH(node, nodes) {
      if (node->f > max_f)
        max_f = node->f;
    }
    return max_f;
  }
};

int main() {
  Tree tree;
  cin >> tree;
  cout << tree.computeAnswer() << endl;
  return 0;
}
