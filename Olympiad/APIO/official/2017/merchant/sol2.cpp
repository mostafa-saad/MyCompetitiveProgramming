#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N, M, K;
vector<vector<long long>> dist;
vector<vector<long long>> grid;

vector<vector<int>> buy;
vector<vector<int>> sell;

vector<vector<int>> earn;


bool test(long long salary) {
  grid = vector<vector<long long>>(N, vector<long long>(N, LLONG_MAX/2));

  for (int i=0;i<N;i++) {
    for (int j=0;j<N;j++) {
      if (dist[i][j] < LLONG_MAX/2) {
        grid[i][j] = dist[i][j] * salary - earn[i][j];
      }
    }
  }

  for (int k=0;k<N;k++) {
    for (int i=0;i<N;i++) {
      for (int j=0;j<N;j++) {
        grid[i][j] = min(grid[i][j], grid[i][k] + grid[k][j]);
      }
    }
  }

  for (int i=0;i<N;i++) {
    if (grid[i][i] <= 0) return true;
  }
  return false;
}

int bsearch(int mn, int mx) {
  if (mn == mx) return mn;

  int md = (mn+mx+1)/2;

  if (test(md)) {
    return bsearch(md,mx);
  }
  else {
    return bsearch(mn,md-1);
  }
}

int main() {
  cin >> N >> M >> K;

  dist = vector<vector<long long>>(N, vector<long long>(N, LLONG_MAX/2));
  buy = vector<vector<int>>(N, vector<int>(K, -1));
  sell = vector<vector<int>>(N, vector<int>(K, -1));
  earn = vector<vector<int>>(N, vector<int>(N, 0));

  for (int i=0;i<N;i++) {
    //dist[i][i] = 0;
    for (int j=0;j<K;j++) {
      cin >> buy[i][j] >> sell[i][j];
    }
  }

  for (int i=0;i<M;i++) {
    int V, W, T;

    cin >> V >> W >> T;
    V--;
    W--;

    dist[V][W] = min<long long>(dist[V][W], T);
  }

  for (int k=0;k<N;k++) {
    for (int i=0;i<N;i++) {
      for (int j=0;j<N;j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  
  for (int i=0;i<N;i++) {
    for (int j=0;j<N;j++) {
      for (int k=0;k<K;k++) {
        if (sell[j][k] != -1 && buy[i][k] != -1) {
          earn[i][j] = max(earn[i][j], sell[j][k] - buy[i][k]);
        }
      }
    }
  }

  cout << bsearch(0, 1000000000) << endl;

  
}
