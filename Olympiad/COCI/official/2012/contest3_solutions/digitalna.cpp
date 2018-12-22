#include <iostream>
#include <string>

using namespace std;

int n;
string kanal[100];

void pomakni(string sto, int kamo)
{
  int i = 0;
  while (kanal[i] != sto)
  {
    ++i;
    cout << 1;
  }
  while (i != kamo)
  {
    swap(kanal[i], kanal[i - 1]);
    --i;
    cout << 4;
  }
}

int main(void) 
{
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> kanal[i];

  pomakni("BLJTV1", 0);
  pomakni("BLJTV2", 1);

  cout << '\n';
  return 0;
}
