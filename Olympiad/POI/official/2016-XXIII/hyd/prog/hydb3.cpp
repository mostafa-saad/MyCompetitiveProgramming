/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Hydrorozgrywka                                     *
 *   Autor programu:       Wojtek Nadara                                      *
 *   Zlozonosc czasowa:    O(m)                                               *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         Traktuje ono kaktusy typu A jako kaktusy typu 1,   *
 *                         a kaktusy typu B jako 0                            *
 *                         i przez to zle wylicza typy wielu kaktusow         *
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
  t0 = 1, // Pek nie zmieniajacy parzystosci
  t1, // Pek zmieniajacy parzystosc
};
const int kTypesNum = 2;
Type all_types[] = {t0, t1};

// To indeksowane nrami cykli
Type cact_down_type[N];
int cnt_cact_down_from_v[N][kTypesNum + 1];
bool win_down[N];

void dfs_to_down(int cyc_v) {
  for (int cyc_nei : cyc_from_cyc[cyc_v]) {
    dfs_to_down(cyc_nei);
  }
  int win_even = 0, win_odd = 0;
  for (size_t ind = 1; ind < cyc[cyc_v].size(); ind++) {
    int act_v = cyc[cyc_v][ind];
    if (cnt_cact_down_from_v[act_v][t1] % 2) {
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
    cact_down_type[cyc_v] = t1;
  } else if (win_odd) {
    cact_down_type[cyc_v] = t0;
  } else if (cyc[cyc_v].size() % 2 == 0) {
    cact_down_type[cyc_v] = t0;
  } else {
    cact_down_type[cyc_v] = t1;
  }
  cnt_cact_down_from_v[cyc[cyc_v][0]][cact_down_type[cyc_v]]++;
}

// A to indeksowane wierzcholkami
// (niespojnosc z tym, ze cact_down_type bylo indeksowane cyklami, ale jaksos przezyjemy)
Type cact_up_type[N];
int cnt_cact_all_from_v[N][kTypesNum + 1];
// Odleglosc do najblizszego wygrywajacego peku na wlasciwym cyklu v z ustalonej strony
// [v][0] - z lewej, [v][1] - z prawej
int dis_to_win[N][2]; 

void dfs_to_up(int cyc_v, bool is_overcact_win) {

  int my_root = cyc[cyc_v][0];
  
  vector<int> doubled_cyc;
  for (int j = 0; j < 2; j++) {
    for (size_t i = 0; i < cyc[cyc_v].size(); i++) {
      doubled_cyc.push_back(cyc[cyc_v][i]);
    }
  }
  for (int dir = -1; dir <= 1; dir += 2) {
    int start_ind;
    int dis_to_last_win = -3 * N;
    if (dir == -1) {
      start_ind = doubled_cyc.size() - 1;
    } else {
      start_ind = 1;
    }
    if (is_overcact_win) {
      dis_to_last_win = 0;
    }
    for (size_t ind = start_ind; ind >= 1 && ind < doubled_cyc.size(); ind += dir) {
      int act_v = doubled_cyc[ind];
      dis_to_last_win++;
      dis_to_win[act_v][(1 - dir) / 2] = dis_to_last_win;
      if ((act_v == my_root && is_overcact_win) ||
          (act_v != my_root && win_down[act_v])) {
        dis_to_last_win = 0;
      }
    }
  }
  
  for (size_t i = 1; i < cyc[cyc_v].size(); i++) {
    int act_v = cyc[cyc_v][i];
    // Na cyklu nie ma wygrywajacych pekow lub jest tylko jeden wygrywajacy pek
    // i jest to kaktus zaczepiony w act_v, ktorego nie chcemy uwzgledniac w liczeniu
    // typu overcact[act_v]
    if (dis_to_win[act_v][0] < 0 || dis_to_win[act_v][0] == int(cyc[cyc_v].size())) {
      if (cyc[cyc_v].size() % 2 == 0) {
        cact_up_type[act_v] = t0;
      } else {
        cact_up_type[act_v] = t1;
      }
    } else if (dis_to_win[act_v][0] % 2 == 0 || dis_to_win[act_v][1] % 2 == 0) {
      cact_up_type[act_v] = t1;
    } else {
      cact_up_type[act_v] = t0;
    }
    
    for (Type t : all_types) {
      cnt_cact_all_from_v[act_v][t] = cnt_cact_down_from_v[act_v][t] + (cact_up_type[act_v] == t);
    }

    for (int cyc_nei : cyc_from_v[act_v]) {
      Type child_type = cact_down_type[cyc_nei];
      cnt_cact_all_from_v[act_v][child_type]--;
      dfs_to_up(cyc_nei, cnt_cact_all_from_v[act_v][t1] % 2);
      cnt_cact_all_from_v[act_v][child_type]++;
    } 
  }
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
  
  int root = 0;
  for (int i = 1; i <= n; i++) {
    if (slo[i].size() == 2) {
      root = i;
      break;
    }
  }
  
  dfs1(root, -1);
  
  for (int i = 1; i <= cyc_num; i++) {
    if (cyc[i][0] == root) { 
      continue;
    }
    cyc_from_v[cyc[i][0]].push_back(i);
    cyc_from_cyc[belong[cyc[i][0]]].push_back(i);
  }
  
  assert(cyc_num == m - n + 1);
  
  // Nr cyklu, do ktorego nalezy korzen
  int cyc_root = belong[slo[root][0]]; // Ale smiszne, chyba inaczej nie umiem :D
  dfs_to_down(cyc_root);
  
  dfs_to_up(cyc_root, false);
  
  cnt_cact_all_from_v[root][cact_down_type[cyc_root]]++;
  
  for (int i = 1; i <= n; i++) {
    size_t cnt_all_types = 0;
    for (Type type : all_types) {
      cnt_all_types += cnt_cact_all_from_v[i][type];
    }
    assert(i == root || 2 * cnt_all_types == slo[i].size());
    if (cnt_cact_all_from_v[i][t1] % 2) {
      cout << "1\n";
    } else {
      cout << "2\n";
    }
  }
  return 0;
}