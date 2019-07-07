
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long ulong;

int n, d;
vector<ulong> edges, move_edges;

void read_input()
{
  cin >> n >> d;
  edges.resize(n);
  edges[0] = 1;
  for (int i = 1; i < n; ++i){
    edges[i] |= 1ull << i;
    
    int j;
    cin >> j;
    edges[j] |= 1ull << i;
    edges[i] |= 1ull << j;
  }
}


void init_move_edges()
{
  move_edges.resize(n);
  for (int i = 0; i < n; ++i)
    move_edges[i] = 1ull << i;

  for (int dnow = 1; dnow < d; ++dnow){
    vector<ulong> new_move_edges(move_edges);
    
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
	if (move_edges[i] & (1ull << j))
	  new_move_edges[i] |= edges[j];
    new_move_edges.swap(move_edges);
  }
  /*
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j)
      cerr << ((move_edges[i] & (1ull << j)) ? 'X' : '.');
    cerr << endl;
  }
  */
}


int find_max(int now, ulong marked)
{
  marked |= move_edges[now];
  int mx = 0;
  for (int i = now + 1; i < n; ++i)
    if (! (marked & (1ull << i)))
      mx = max(mx, find_max(i, marked));

  return mx + 1;
}


int main()
{
  read_input();
  init_move_edges();
  assert(n < 64);
  int mx = 0;
  for (int i = 0; i < n; ++i)
    mx = max(mx, find_max(i, 0));
  cout << mx << endl;
  
  return 0;
}
