#include <iostream>
#include <vector>
#include <map>

using namespace std;

int set_size (int bitmask) {
  int ans = 0;
  for (; bitmask != 0; bitmask /= 2) {
    ans += bitmask & 1;
  }
  return ans;
}

const int MAX_PEOPLE = 25;

vector<int> lovers [MAX_PEOPLE];
int love_target [MAX_PEOPLE];

int component [MAX_PEOPLE];
int color_count [MAX_PEOPLE];

void flood_fill (int vertex, int color, int to_be_shot) {
  component[vertex] = color;

  if (!(to_be_shot & 1 << (vertex - 1))) {
    /* vertex is in T and has the arc originating from it intact */
    if (component[love_target[vertex]] == 0) {
      flood_fill(love_target[vertex], color, to_be_shot);
    }
  }

  /* the flood flows in both directions! */
  for (auto child : lovers[vertex]) {
    if (!(to_be_shot & 1 << (child - 1))) {
      /* child is in T and has the arc originating from it intact */
      if (component[child] == 0) {
        flood_fill(child, color, to_be_shot);
      }
    }
  }
}

bool can_be_shot (int to_be_shot, int character_count) {
  /* checks if the set to_be_shot is a fitting candidate
   * to be the set of people to be shot with the love arrow in the final solution */
  for (int i = 1; i <= character_count; i++) {
    if (love_target[i] == i) {
      if (!(to_be_shot & 1 << (i - 1))) {
        /* people who love themselves must be shot with the love arrow */
        return false;
      }
    }
  }

  for (int i = 1; i <= character_count; i++) {
    /* prepare to flood fill the graph */
    component[i] = 0;
    color_count[i] = 0;
  }

  for (int i = 1; i <= character_count; i++) {
    if (component[i] == 0) {
      flood_fill(i, i, to_be_shot);
    }
    color_count[component[i]]++;
  }

  for (int i = 1; i <= character_count; i++) {
    if (color_count[i] > 2) {
      return false;
    }
  }

  return true;
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

  int ans = MAX_PEOPLE;
  for (int i = 0; i < 1 << character_count; i++) {
    if (can_be_shot(i, character_count)) {
      ans = min(ans, set_size(i));
    }
  }
  cout << ans << endl;
}
