#include <iostream>
#include <string>
using namespace std;

string S;
int indent = 0;

void uvuci() {
  for (int i = 0; i < indent; ++i)
    cout << "  ";
}

int main() {
  cin >> S;

  for (int i = 0; i < S.size(); ++i) {
    switch (S[i]) {
      case '}':
        if (S[i - 1] != '{') {
          indent--;
          cout << endl;
          uvuci();
          cout << "}";
        }
        break;
      case '{':
        cout << "{";
        cout << endl;
        if (S[i + 1] == '}') {
          uvuci();
          cout << "}";
          ++i;
        } else {
          indent++;
          uvuci();
        }
        break;
      case ',':
        cout << "," << endl;
        uvuci();
        break;
      default:
        cout << S[i];
    }
  }

  return 0;
}
