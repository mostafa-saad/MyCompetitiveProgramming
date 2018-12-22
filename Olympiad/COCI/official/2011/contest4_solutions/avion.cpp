#include <iostream>
#include <string>

using namespace std;

int main(void) {
  string text;
  bool printed = false;

  for (int i = 0; i < 5; ++i) {
    cin >> text;
    if (text.find("FBI") != string::npos) {
      cout << i+1 << " ";
      printed = true;
    }
  }

  if (printed == false) {
    cout << "HE GOT AWAY!";
  }
  cout << endl;

  return 0;
}
