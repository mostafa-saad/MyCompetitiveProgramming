#include <bits/stdc++.h>
using namespace std;

struct Tree {
  vector<int> nodes;  // original mapping
  vector<vector<int>> adj;

  void init(int num_nodes) {
    nodes.resize(num_nodes);
    adj.resize(num_nodes);
  }

  void clear() {
    nodes.clear();
    adj.clear();
  }
};

class Decompositor {
 public:
  Decompositor(const Tree &tree) : tree_(tree), next_label_(0) {
    size_.resize(tree.nodes.size());
    done_.resize(tree.nodes.size());
    queue_.push(0);
  }

  // vraca sljedece dekomponirano stablo
  bool NextTree(Tree &decomposed_tree) {
    decomposed_tree.clear();
    int node = GetQueuedNode();
    if (node == -1) return false;
    
    CalculateSize(node);
    int centroid = FindCentroid(node, size_[node]);
    assert(centroid != -1);
    
    // build tree
    decomposed_tree.init(size_[node]);
    next_label_ = 0;
    BuildTree(decomposed_tree, centroid);
    
    // mark labels
    done_[centroid] = true;
    for (int y : tree_.adj[centroid])
      queue_.push(y);
    return true;
  }

 private:
  const Tree &tree_;
  queue<int> queue_;
  vector<int> size_;
  vector<bool> done_;
  int next_label_;

  int GetQueuedNode() {
    for (; !queue_.empty(); queue_.pop()) {
      int x = queue_.front();
      if (!done_[x]) return x;
    }
    return -1;
  }

  void CalculateSize(int x, int prev = -1) {
    size_[x] = 1;
    for (int y : tree_.adj[x]) {
      if (y == prev || done_[y]) continue;
      CalculateSize(y, x);
      size_[x] += size_[y];
    }
  }

  int FindCentroid(int x, int tot_size, int prev = -1) {
    if (IsCentroid(x, tot_size)) return x;
    for (int y : tree_.adj[x]) {
      if (y == prev || done_[y]) continue;
      int q = FindCentroid(y, tot_size, x);
      if (q != -1) return q;
    }
    return -1;
  }

  bool IsCentroid(int x, int tot_size) {
    bool flag = false;
    if (2 * (tot_size - size_[x]) > tot_size) return false;
    for (int y : tree_.adj[x]) {
      if (done_[x] || size_[y] > size_[x]) continue;
      if (2 * size_[y] > tot_size) return false;
    }
    return true;
  }

  void BuildTree(Tree &target, int x, int prev = -1, int prev_label = -1) {
    int label = next_label_++;
    target.nodes[label] = x;
    if (prev_label != -1)
      target.adj[prev_label].push_back(label);
    for (int y : tree_.adj[x]) {
      if (y == prev || done_[y]) continue;
      BuildTree(target, y, x, label);
    }
  }
};

const int MAXN = 100100;
char input[MAXN];

class TreeSolver {
 public:
  TreeSolver(const Tree &tree): tree_(tree) {
    hash_down_.resize(tree.nodes.size());
    hash_up_.resize(tree.nodes.size());
    hash_set_.resize(tree.nodes.size());
    stack_.reserve(tree.nodes.size());
  }

  void Build(int x = 0, int dep = 0, long long hdown = 0, long long hup = 0) {
    const char c = input[tree_.nodes[x]];
    hash_down_[x] = hdown * BASE + c;
    hash_up_[x] = hup + power_[dep] * c;
    for (int y : tree_.adj[x]) {
      Build(y, dep + 1, hash_down_[x], hash_up_[x]);
    }
  }

  int Solve() {
    return max(2 * Run(0) + 1, 2 * Run(1));
  }

  int Run(int k) {
    int lo = 0, hi = (int)tree_.nodes.size();
    while (lo < hi) {
      int mid = (lo + hi + 1) / 2;
      if (Check(mid, k)) lo = mid;
      else hi = mid - 1;
    }
    return lo;
  }
  
  static void InitPowers() {
    power_[0] = 1;
    for (int i = 1; i < MAXN; ++i)
      power_[i] = power_[i - 1] * BASE;
  }

 private:
  static const int BASE = 31337;
  static long long power_[MAXN];
  Tree tree_;
  vector<long long> hash_down_;
  vector<long long> hash_up_;
  vector<unordered_set<long long>> hash_set_;
  vector<int> stack_;

  void SetHashes(int x, int dep) {
    hash_set_[dep].insert(hash_down_[x]);
    for (int y : tree_.adj[x])
      SetHashes(y, dep + 1);
  }

  void ResetHashes() {
    for (auto &it : hash_set_)
      it.clear();
  }

  // k 0 za neparno, 1 za parno
  bool Check(int len, int k) {
    // pazi na prazni string
    if (len == 0 && k == 1) return true;
    stack_.clear();
    stack_.push_back(0);
    const int n = (int)tree_.adj[0].size();
    for (int step = 0; step < 2; ++step) {
      ResetHashes();
      for (int i = 0; i < n; ++i) {
        const int node = tree_.adj[0][i];
        if (i > 0 && CheckSubtree(len, node, k)) return true;
        if (i + 1 != n) SetHashes(node, 1);
      }
      reverse(tree_.adj[0].begin(), tree_.adj[0].end());
    }
    return false;
  }

  bool CheckSubtree(int len, int x, int k) {
    const int dep = (int)stack_.size();
    stack_.push_back(x);
    bool ret = false;
    if (dep >= len) {
      if (CheckChain(len, dep, k)) {
        stack_.pop_back();
        return true;
      }
    }
    for (int y : tree_.adj[x]) {
      if (CheckSubtree(len, y, k)) {
        stack_.pop_back();
        return true;
      }
    }
    stack_.pop_back();
    return false;
  }

  bool CheckChain(int len, int dep, int k) {
    int tot_len = 2 * len - k;
    if (dep >= tot_len) {
      long long hdown = hash_down_[stack_.back()];
      long long hup = hash_up_[stack_.back()];
      int i = dep - tot_len;
      if (i > 0) {
        hdown -= power_[tot_len + 1] * hash_down_[stack_[i - 1]];
        hup -= hash_up_[stack_[i - 1]];
      }
      return hdown * power_[i] == hup;
    }
    int tail = tot_len - dep;
    int head = dep - tail;
    if (hash_down_[stack_[head]] != hash_up_[stack_[head]])
      return false;
    long long hdown = hash_down_[stack_.back()];
    if (head > 0) hdown -= power_[tail + 1] * hash_down_[stack_[head - 1]];
    return hash_set_[tail].find(hdown) != hash_set_[tail].end();
  }
};

long long TreeSolver::power_[MAXN];

void LoadTree(Tree &tree) {
  int n;
  scanf("%d", &n);
  scanf("%s", input);
  tree.init(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    tree.adj[u].push_back(v);
    tree.adj[v].push_back(u);
  }
}

int main(void) {
  TreeSolver::InitPowers();
  
  Tree tree;
  LoadTree(tree);
  Decompositor decomp(tree);

  // border case :/
  if (tree.nodes.size() == 2 && input[0] == input[1]) {
    printf("2\n");
    return 0;
  }

  int ans = 0;
  for (Tree decomp_tree; decomp.NextTree(decomp_tree);) {
    TreeSolver solver(decomp_tree);
    solver.Build();
    ans = max(ans, solver.Solve());
  }

  printf("%d\n", ans);
  
  return 0;
}

