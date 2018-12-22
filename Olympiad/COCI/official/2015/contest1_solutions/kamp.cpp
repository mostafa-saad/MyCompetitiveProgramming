#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 1000000
#define time first
#define nextHouse second

typedef long long llint;
typedef pair<int, int> edge;

vector<edge> graph[MAXN];
int K[MAXN], nearestInK[MAXN];
int branch1[MAXN], branch2[MAXN];

llint furthest[MAXN];
llint maxTime1[MAXN], maxTime2[MAXN];
llint distToK[MAXN];

llint totalTimeInK;

int findK(int x, int previousHouse){
  int connected = 0;
  int d = graph[x].size();
  for (int i=0; i<d; i++){
    int nextHouse = graph[x][i].nextHouse;
    if (nextHouse == previousHouse) continue;

    //int connectedBranch = findK(nextHouse, x);
    if (findK(nextHouse, x) == 1){
      K[x] = connected = 1;
      totalTimeInK += graph[x][i].time;
    }
  }

  if (K[x] == 1) connected = 1;
  return connected;
}

llint calcMaxBranches(int x, int previousHouse, llint currentPath){
  int d = graph[x].size();
  for (int i=0; i<d; i++){
    int nextHouse = graph[x][i].nextHouse;
    if (previousHouse == nextHouse || K[nextHouse] != 1) continue;
    int time = graph[x][i].time;

    llint currentTime = time + calcMaxBranches(nextHouse, x, currentPath + time);
    if (currentTime > maxTime1[x]){
      maxTime2[x] = maxTime1[x]; branch2[x] = branch1[x];
      maxTime1[x] = currentTime; branch1[x] = i;
    } else if (currentTime > maxTime2[x]){
      maxTime2[x] = currentTime; branch2[x] = i;
    }
  }

  return maxTime1[x];
}

void calcFurthest(int x, int previousHouse, llint currentPath){
  furthest[x] = max(currentPath, maxTime1[x]);

  int d = graph[x].size();
  for (int i=0; i<d; i++){
    int nextHouse = graph[x][i].nextHouse;
    if (previousHouse == nextHouse || K[nextHouse] != 1) continue;
    int time = graph[x][i].time;

    if (i != branch1[x]) calcFurthest(nextHouse, x, time + max(currentPath, maxTime1[x]));
    else                 calcFurthest(nextHouse, x, time + max(currentPath, maxTime2[x]));
  }
}

void calcDistToK(int x, int previousHouse, int currentPath, int near){
  distToK[x] = currentPath;
  nearestInK[x] = near;

  int d = graph[x].size();
  for (int i=0; i<d; i++){
    int nextHouse = graph[x][i].nextHouse; if (previousHouse == nextHouse) continue;
    int time = graph[x][i].time;

    if (K[nextHouse] == 1) calcDistToK(nextHouse, x, 0, nextHouse);
    else calcDistToK(nextHouse, x, time + currentPath, near);
  }
}

int main(void){

  int n, k; scanf ("%d%d", &n, &k);
  for (int i=0; i<n-1; i++){
    int a, b, c; scanf ("%d%d%d", &a, &b, &c); a--; b--;
    graph[a].push_back(edge(c, b));
    graph[b].push_back(edge(c, a));
  }

  int a;
  for (int i=0; i<k; i++){
    scanf ("%d", &a); a--;
    K[a] = 1;
  }

  findK(a, -1);

  int beginning;
  for (int i=0; i<n; i++)
    if (K[i] == 1){
        beginning = i;
        break;
    }

  calcMaxBranches(beginning, -1, 0);
  calcFurthest   (beginning, -1, 0);
  calcDistToK    (beginning, -1, 0, beginning);

  for (int i=0; i<n; i++)
    printf ("%lld\n", distToK[i] + 2*totalTimeInK - furthest[nearestInK[i]]);

  return 0;
}
