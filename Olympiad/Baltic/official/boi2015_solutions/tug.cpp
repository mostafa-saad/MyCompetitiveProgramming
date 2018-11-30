/* Tug of War
   Autor: Piotr Smulewicz
 */
#include <iostream>
#include <numeric>
#include <vector>
#include <cstdlib>
using namespace std;
const int SIZE = 30001;
const int MAX_STRENGHT = 20;
const int BACK_PACK_SIZE = SIZE * MAX_STRENGHT + 1;
int persons[SIZE * 2][2];
int str[SIZE * 2];
bool assigned[SIZE * 2];
vector<int> spots[SIZE * 2];
int item[BACK_PACK_SIZE];
unsigned int opt[SIZE * 2];
bool back_pack[BACK_PACK_SIZE + 1];
int n, j, s, a, b, pe, mi, k, sum_all, sum, res;
int main() {
  ios_base::sync_with_stdio(false);
  res = BACK_PACK_SIZE;
  cin >> n >> k;
  for (size_t i = 0; i < n * 2u; i++) {
    cin >> a >> b >> s;
    str[i] = s;
    persons[i][0] = a * 2;
    persons[i][1] = b * 2 + 1;
    spots[a * 2].push_back(i);
    spots[b * 2 + 1].push_back(i);
  }
  for (size_t s_pe = 0; s_pe < 2u * n; s_pe++) {
    pe = s_pe;
    while (!assigned[pe]) {
      for (j = 0; j < 2; j++) {
        mi = persons[pe][j];
        if (opt[mi] + 1 == spots[mi].size()) {
          assigned[pe] = true;
          sum += (1 - 2 * (mi % 2)) * str[pe];
          mi = persons[pe][1 - j];
          opt[mi]++;
          break;
        }
      }
      if (spots[mi].size() == opt[mi] + 1) {
        unsigned int poz = 0;
        while (assigned[spots[mi][poz]] && poz < spots[mi].size())
          poz++;
        if (poz < spots[mi].size())
          pe = spots[mi][poz];
        else
          break;
      } else
        break;
    }
  }
  item[abs(sum)]++;
  sum_all += abs(sum);
  for (int s_pe = 0; s_pe < 2 * n; s_pe++) {
    sum = 0;
    pe = s_pe;
    int st = 0;
    int mi2 = persons[pe][1];
    if (assigned[pe])
      continue;
    while (!assigned[pe]) {
      sum += (1 - 2 * st) * str[pe];
      assigned[pe] = true;
      mi = persons[pe][st];
      size_t poz = 0;
      while (poz < spots[mi].size() && assigned[spots[mi][poz]])
        poz++;
      if (poz < spots[mi].size())
        pe = spots[mi][poz];
      st = 1 - st;
    }
    if (mi != mi2) {
      cout << "NO" << endl;
      return 0;
    }
    if (sum != 0)
      item[abs(sum)]++;
    sum_all += abs(sum);
  }
  back_pack[0] = true;
  for (size_t i = 0; i < BACK_PACK_SIZE*1u; i++) {
    if (item[i] == 0u)
      continue;
    // cout<<"it"<<item[i]<<endl;
    for (int j = BACK_PACK_SIZE; j >= 0; --j) {
      if (back_pack[j]) {
        for (int l = 1; l <= item[i] && back_pack[j + l * i] == false; l++)
          back_pack[j + l * i] = true;
      }
    }
  }
  for (int j = BACK_PACK_SIZE; j >= 0; --j) {
    if (back_pack[j])
      res = min(res, abs(sum_all - 2 * j));
  }
  // cout<<"res "<<res<<" k: "<<k<<endl;
  if (res <= k)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}
