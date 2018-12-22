#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

const int MAX = 2010;

int n, m;
char grid[MAX][MAX];
bool vis[MAX][MAX];

int main(void) {

  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> grid[i];

  vector< point > curr, next;
  for (curr.push_back({0, 0}); !curr.empty(); curr = next) {
    point p = curr.back();
    cout << grid[p.x][p.y];

    char mn = 'z';
    for (point pt : curr) {
      int dx = 1, dy = 0;
      for (int i = 0; i < 2; ++i) {
        swap(dx, dy);
        int nx = pt.x + dx;
        int ny = pt.y + dy;
        if (nx >= n || ny >= m) continue;
        mn = min(mn, grid[nx][ny]);
      }
    }
    
    next.clear();
    for (point pt : curr) {
      int dx = 1, dy = 0;
      for (int i = 0; i < 2; ++i) {
        swap(dx, dy);
        int nx = pt.x + dx;
        int ny = pt.y + dy;
        if (nx >= n || ny >= m) continue;
        if (vis[nx][ny]) continue;
        if (grid[nx][ny] == mn) {
          next.push_back({nx, ny});
          vis[nx][ny] = 1;
        }
      }
    }
  }

  cout << endl;

  return 0;
}
