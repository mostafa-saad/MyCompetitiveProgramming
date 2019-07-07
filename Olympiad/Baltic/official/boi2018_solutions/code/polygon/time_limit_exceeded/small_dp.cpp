#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX_PEOPLE = 22;

vector<int> lovers [MAX_PEOPLE];
int love_target [MAX_PEOPLE];
int cost [MAX_PEOPLE][MAX_PEOPLE];
int dp [1 << MAX_PEOPLE];

int main () {
  ios::sync_with_stdio(false);
  
  int character_count;
  cin >> character_count;

  if (character_count % 2 == 1) {
    /* N odd; no solution */
    cout << -1 << endl;
    return 0;
  }

  map<string, int> character_index;
  /* assign an integer to each character */
  int cur_index = 1;
  for (int i = 1; i <= character_count; i++) {
    string lover, lovee;
    cin >> lover >> lovee;

    /* is this the first time we encounter these people? */
    if (character_index.count(lover) == 0) {
      character_index[lover] = cur_index;
      cur_index++;
    }

    if (character_index.count(lovee) == 0) {
      character_index[lovee] = cur_index;
      cur_index++;
    }

    int lover_idx = character_index[lover];
    int lovee_idx = character_index[lovee];
    
    lovers[lovee_idx].push_back(lover_idx);
    love_target[lover_idx] = lovee_idx;
  }

  /* pre-calculate the value of cost(p, q) for all p, q */
  for (int i = 1; i <= character_count; i++) {
    for (int j = 1; j <= character_count; j++) {
      if (i == love_target[j] && j == love_target[i]) {
        cost[i][j] = 0;
      } else if (i == love_target[j] || j == love_target[i]) {
        cost[i][j] = 1;
      } else {
        cost[i][j] = 2;
      }
    }
  }

  /* iterate over all subsets of G, in this implementation
   * also the ones with an odd number of characters. for these
   * values, the dp array will contain irrelevant information */
  dp[0] = 0;
  for (int S = 1; S < 1 << character_count; S++) {
    dp[S] = MAX_PEOPLE; /* "infinity" */

    int last = -1;
    for (int i = 1; i <= character_count; i++) {
      if (S & 1 << (i - 1)) {
        last = i;
      }
    }

    /* last denotes the last character present in that particular subset */
    for (int i = 1; i < last; i++) {
      if (S & 1 << (i - 1)) { /* i is in S */
        dp[S] = min(dp[S], dp[S & ~((1 << (i - 1)) | (1 << (last - 1)))] + cost[i][last]);
      }
    }
  }

  cout << dp[(1 << character_count) - 1] << endl;
}
