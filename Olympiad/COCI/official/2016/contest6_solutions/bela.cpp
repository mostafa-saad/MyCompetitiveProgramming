#include <iostream>

using namespace std;
int n;
int uk;
char ad;
string kar;

int point[2][8]={{11,4,3,2,10,0,0,0},
               {11,4,3,20,10,14,0,0}};
string card="AKQJT987";

int fnd(char k){
  for (int i=0;i<card.size();i++){
    if (card[i]==k){
      return i;
    }
  }
}

int main (void){
  cin >> n >> ad;
  for (int i=0;i<(4*n);i++){
    cin >> kar;
    uk+=point[kar[1]==ad][fnd(kar[0])];
  }
  cout << uk << endl;
  return 0;
}
