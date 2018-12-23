#include <bits/stdc++.h>
using namespace std;

typedef long long int LL;

const LL INF = 1e15;

struct Event {
  int cores;
  int freq;
  int value;
  int id;

  Event(int cores_, int freq_, int value_, int id_):
    cores(cores_), freq(freq_), value(value_), id(id_) {}

  bool operator<(const Event& other) const {
    if (freq != other.freq) return freq > other.freq;
    return id < other.id;
  }
};

int n, m;
vector<Event> events;
vector<LL> DP;

int main() {
  int cores_available = 0;

  cin >> n;
  for (int i = 0; i < n; i++) {
    int cores, freq, price;
    cin >> cores >> freq >> price;
    cores_available += cores;
    events.push_back(Event(cores, freq, price, -1));
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    int cores, freq, reward;
    cin >> cores >> freq >> reward;
    events.push_back(Event(cores, freq, reward, i));
  }

  sort(events.begin(), events.end());

  DP.resize(cores_available + 1, -INF);
  DP[0] = 0;

  for (const Event& evt : events) {
    if (evt.id == -1) {
      for (int i = cores_available; i >= evt.cores; i--)
        DP[i] = max(DP[i], DP[i - evt.cores] - evt.value);
    }
    else {
      for (int i = 0; i <= cores_available - evt.cores; i++)
        DP[i] = max(DP[i], DP[i + evt.cores] + evt.value);
    }
  }

  LL result = -1;
  for (int i = 0; i <= cores_available; i++)
    result = max(result, DP[i]);

  cout << result << "\n";

  return 0;
}
