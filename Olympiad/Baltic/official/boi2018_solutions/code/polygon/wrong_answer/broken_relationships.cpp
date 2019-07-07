#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX_PEOPLE = 100005;

vector<int> lovers [MAX_PEOPLE];
int love_target [MAX_PEOPLE];

int component [MAX_PEOPLE];
void explore (int vertex) {
  if (component[vertex] == -1) { /* we detected a cycle */
    component[vertex] = vertex;
  } else if (component[vertex] == 0) {
    component[vertex] = -1;
    explore(love_target[vertex]);
    component[vertex] = component[love_target[vertex]];
  }
}

int mls_exclu [MAX_PEOPLE];
int mls_inclu [MAX_PEOPLE];

void calculate_dp (int vertex, int forbidden) {
  for (int child : lovers[vertex]) {
    if (child != vertex && child != forbidden) {
      calculate_dp(child, forbidden);
    }
  }

  /* calculate the values of the dynamic programming functions */
  
  mls_inclu[vertex] = 1;
  for (int child : lovers[vertex]) {
    if (child != vertex && child != forbidden) {
      mls_inclu[vertex] += mls_exclu[child];
    }
  }

  mls_exclu[vertex] = 0;
  for (int child : lovers[vertex]) {
    if (child != vertex && child != forbidden) {
      mls_exclu[vertex] = max(mls_exclu[vertex], mls_inclu[child] - mls_exclu[child]);
    }
  }
  mls_exclu[vertex] += mls_inclu[vertex] - 1;
}

int process_component (int vertex) {
  if (love_target[vertex] == vertex) { /* a tree */
    calculate_dp(vertex, -1);
    return mls_exclu[vertex];
  } else {
    /* variant 1: vertex stays with its original target */
    int variant_1 = 1;
    for (int lover : lovers[vertex]) {
      if (lover != love_target[vertex]) {
        calculate_dp(lover, love_target[vertex]);
        variant_1 += mls_exclu[lover];
      }
    }

    /* variant 2: it doesn't :'( */
    calculate_dp(vertex, vertex);
    int variant_2 = mls_exclu[vertex];

    return max(variant_1, variant_2);
  }
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

  for (int i = 1; i <= character_count; i++) {
    /* assign each character to a connected component */
    if (component[i] == 0) {
      explore(i);
    }
  }

  int answer = 0;
  for (int i = 1; i <= character_count; i++) {
    if (component[i] == i) {
      answer += process_component(i);
    }
  }

  cout << character_count - answer << endl;
}
