#include <cstring>
#include <string>
#include <iostream>
#define WINNING_SCORE 21
using namespace std;

int main() {
  int scores[2] = { 0, 0 };
  string input;

  cin >> input;

  for (int i = 0; i < input.length(); i++) {
    int current_player = (input[i] == 'B');
    scores[current_player]++;

    if (scores[0] == WINNING_SCORE || scores[1] == WINNING_SCORE) {
      cout << scores[0] << "-" << scores[1] << "\n";
      scores[0] = scores[1] = 0;
    }
  }

  cout << input[input.length() - 1] << "\n";
}
