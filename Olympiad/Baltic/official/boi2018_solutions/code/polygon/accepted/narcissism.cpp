#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX_PEOPLE = 100005;

vector<int> lovers [MAX_PEOPLE];
int love_target [MAX_PEOPLE];

int mls_exclu [MAX_PEOPLE];
int mls_inclu [MAX_PEOPLE];

void dfs (int vertex) {
  for (int child : lovers[vertex]) {
    if (child != vertex) {
      dfs(child);
    }
  }

  /* calculate the values of the dynamic programming functions */
  
  mls_inclu[vertex] = 1;
  for (int child : lovers[vertex]) {
    if (child != vertex) {
      mls_inclu[vertex] += mls_exclu[child];
    }
  }

  mls_exclu[vertex] = 0;
  for (int child : lovers[vertex]) {
    if (child != vertex) {
      mls_exclu[vertex] = max(mls_exclu[vertex], mls_inclu[child] - mls_exclu[child]);
    }
  }
  mls_exclu[vertex] += mls_inclu[vertex] - 1;
}

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

  int answer = 0;
  for (int i = 1; i <= character_count; i++) {
    if (i == love_target[i]) {
      /* i loves themselves and therefore is a root. */
      dfs(i);
      answer += mls_exclu[i];
    }
  }

  cout << character_count - answer << endl;
}
