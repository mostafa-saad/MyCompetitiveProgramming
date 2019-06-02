/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Hydrorozgrywka                                     *
 *   Autor programu:       Wojtek Nadara                                      *
 *   Zlozonosc czasowa:    O(n * m)                                           *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int N = 5e5 + 5;
vector<int> slo[N]; // Lista sasiedztwa

vector<int> cyc[N]; // Cykle

int vis1[N];
vector<int> act_stack; // Stos DFSa
int cyc_num;
bool on_stack[N]; // Czy jest na stosie DFSa
int belong[N];
vector<int> cyc_from_cyc[N]; // Drzewo cykli
vector<int> cyc_from_v[N]; // Ktore cykle-dzieci wyrastaja z wierzcholka v
void dfs1(int v, int par) {
  vis1[v] = true;
  act_stack.push_back(v);
  on_stack[v] = true;
  
  for (int nei : slo[v]) {
    if (nei == par) {
      continue;
    }
    
    if (on_stack[nei]) {
      // Znalezlismy nowy cykl
      cyc_num++;
      
      // Tego jednego push_backa wyciagamy przed petle,
      // aby pierwszy wierzcholek na cyklu byl najwyzszym w drzewie DFS
      // oraz aby uniknac uaktualnienia belong
      cyc[cyc_num].push_back(nei); 
      for (size_t i = act_stack.size() - 1; ; i--) {
        if (act_stack[i] == nei) {
          break;
        }
        cyc[cyc_num].push_back(act_stack[i]);
        belong[act_stack[i]] = cyc_num;
      }
    }
    if (!vis1[nei]) {
      dfs1(nei, v);
    }
  }
  
  act_stack.pop_back();
  on_stack[v] = false;
}

// Typ kaktusa wyrastajacego z wierzcholka
enum Type {
  t0 = 1, // Nikt nie decyduje, kto bierze ostatnia krawedz, parzystosc sie nie zmienia
  t1, // Nikt nie decyduje, kto bierze ostatnia krawedz, parzystosc sie zmienia
  tA, // Pierwszy gracz decyduje, kto bierze ostatnia krawedz
  tB, // Drugi gracz decyduje
};
const int kTypesNum = 4;

Type cact_down_type[N];
Type cact_up_type[N];
int cnt_cact_down_from_v[N][kTypesNum + 1];
bool win_down[N];

void dfs_to_down(int cyc_v) {
  for (int cyc_nei : cyc_from_cyc[cyc_v]) {
    dfs_to_down(cyc_nei);
  }
  int win_even = 0, win_odd = 0;
  for (size_t ind = 1; ind < cyc[cyc_v].size(); ind++) {
    int act_v = cyc[cyc_v][ind];
    if (cnt_cact_down_from_v[act_v][tA] || cnt_cact_down_from_v[act_v][t1] % 2 == 1) {
      win_down[act_v] = true;
    }
  }
  for (int dir = -1; dir <= 1; dir += 2) {
    size_t start_ind;
    if (dir == -1) {
      start_ind = cyc[cyc_v].size() - 1;
    } else {
      start_ind = 1;
    }
    int dis = 0;
    for (size_t ind = start_ind; ind >= 1 && ind < cyc[cyc_v].size(); ind += dir) {
      dis++;
      int act_v = cyc[cyc_v][ind];
      if (win_down[act_v]) {
        if (dis % 2 == 0) {
          win_even++;
        } else {
          win_odd++;
        }
        break;
      }
    }
  }
  if (win_even) {
    cact_down_type[cyc_v] = tA;
  } else if (win_odd) {
    cact_down_type[cyc_v] = tB;
  } else if (cyc[cyc_v].size() % 2 == 0) {
    cact_down_type[cyc_v] = t0;
  } else {
    cact_down_type[cyc_v] = t1;
  }
  cnt_cact_down_from_v[cyc[cyc_v][0]][cact_down_type[cyc_v]]++;
}

void AddEdge(int a, int b) {
  slo[a].push_back(b);
  slo[b].push_back(a);
}

void Delete2Edges(int a) {
  slo[a].pop_back();
  slo[a].pop_back();
}
  

int main() {
  ios_base::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    slo[a].push_back(b);
    slo[b].push_back(a);
  }
  
  for (int v = 1; v <= n; v++) {
    act_stack.clear();
    cyc_num = 0;
    for (int j = 1; j <= n + 4; j++) {
      cyc[j].clear();
      vis1[j] = 0;
      on_stack[j] = 0;
      belong[j] = 0;
      cyc_from_cyc[j].clear();
      cyc_from_v[j].clear();
      cact_down_type[j] = Type(0);
      cact_up_type[j] = Type(0);
      for (int k = 0; k <= kTypesNum; k++) {
        cnt_cact_down_from_v[j][k] = 0;
      }
      win_down[j] = 0;
    }
    
    AddEdge(v, n + 1);
    AddEdge(v, n + 3);
    AddEdge(n + 1, n + 2);
    AddEdge(n + 2, n + 3);
    
    dfs1(n + 2, -1);
    
    for (int i = 1; i <= cyc_num; i++) {
      if (cyc[i][0] == n + 2) { 
        continue;
      }
      cyc_from_v[cyc[i][0]].push_back(i);
      cyc_from_cyc[belong[cyc[i][0]]].push_back(i);
    }

    assert(cyc_num == m - n + 2);
    
    int cyc_root = belong[slo[n + 2][0]]; // Ale smiszne, chyba inaczej nie umiem :D
    dfs_to_down(cyc_root);
    
    if (cact_down_type[cyc_root] == tA || cact_down_type[cyc_root] == t1) {
      cout << "1\n";
    } else {
      cout << "2\n";
    }
    
    Delete2Edges(v);
    Delete2Edges(n + 1);
    Delete2Edges(n + 2);
    Delete2Edges(n + 3);
  }
  
  return 0;
}