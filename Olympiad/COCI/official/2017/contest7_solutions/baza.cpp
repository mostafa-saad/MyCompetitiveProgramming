#include <iostream>

using namespace std;
const int MAXN=1000;

int n, m, q;
int z;
int x[MAXN+10];
int a[MAXN+10][MAXN+10];
bool e;

int main (void){
  cin >> n >> m;

  for (int i=0;i<n;i++){
    for (int j=0;j<m;j++){
      cin >> a[i][j];
    }
  }

  cin >> q;

  for (int i=0;i<q;i++){
    for (int j=0;j<m;j++){
      cin >> x[j];
    }

    z = 0;
    for (int j=0;j<n;j++){
      e = 1;
      for (int k=0;k<m;k++){
        if (x[k] != -1 && x[k] != a[j][k]){
          e = 0;
          break;
        }
      }

      if (e){
        z++;
      }
    }

    cout << z << endl;
  }

  return 0;
}
