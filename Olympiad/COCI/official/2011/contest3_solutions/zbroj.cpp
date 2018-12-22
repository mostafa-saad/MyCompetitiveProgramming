#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(void) {

  string a, b;
  cin >> a >> b;

  string a1 = a, a2 = a;
  for (int i = 0; i < a1.size(); ++i)
    if (a1[i] == '6') --a1[i];
  for (int i = 0; i < a2.size(); ++i)
    if (a2[i] == '5') ++a2[i];

  string b1 = b, b2 = b;
  for (int i = 0; i < b1.size(); ++i)
    if (b1[i] == '6') --b1[i];
  for (int i = 0; i < b2.size(); ++i)
    if (b2[i] == '5') ++b2[i];

  printf("%d %d\n", atoi(a1.c_str()) + atoi(b1.c_str()), atoi(a2.c_str()) + atoi(b2.c_str()));
  return 0;
}
