#include <iostream>

using namespace std;
int n;
int points;
string s;
string rate = "JQKA";

int find(char c){
  
  for (int i=0;i<4;i++){
    if (rate[i]==c){
      return i+1;
    }
  }

  return 0;
}

int main (void){
  
  cin >> n;

  for (int i=0;i<n;i++){
  
    cin >> s;

    for (int j=0;j<13;j++){
      points+=find(s[j]);
    }

  }

  cout << points << endl;

  return 0;

}
