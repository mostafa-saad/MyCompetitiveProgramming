#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 3010;
const int MAXC = 3010;
int dp[MAXN][MAXN];
int cntR[MAXC];
int cntL[MAXC];

int str[MAXN];
int rev[MAXN];

int N, C;

void precalc(int* S) {
  for(int d = N-1; d>=0; d--){
    for(int i = 0; i+d < N; i++){
      int l = i;
      int r = i+d;
      if(0 <= l-1 && r+1 < N) { dp[l][r] = dp[l-1][r+1]; }
      else { dp[l][r] = 0; }
      if(S[l] == S[r]){ dp[l][r]++; }
      else { dp[l][r] = 0; }
    }
  }
}

int solve(int* S, int Lr, int center, int Rl) {
  int ans = 0;
  memset(cntR, 0, sizeof(int)*MAXC);
  memset(cntL, 0, sizeof(int)*MAXC);
  int Ll = Lr;
  int Rr = Rl;
  vector<pair<int, int> > vec;
  while(Ll >= 0){
    cntL[S[Ll]]++;
    vec.push_back(make_pair(S[Ll], cntL[S[Ll]]));
    if(!(Ll-1 >= 0 && S[Ll-1] >= S[Ll])){
      break;
    }
    Ll--;
  }
  
  int CElen = 0;
  int OKlen = 0;
  int NGlen = vec.size();
  while(Rr < N){
    int x = S[Rr];
    cntR[x]++;
    if(x < center) { break; }
    else if(x == center) { CElen++; }
    else if(cntL[x] >= cntR[x]) {
      while(OKlen+1 <= vec.size()){
        int y = vec[OKlen].first;
        int cnt = vec[OKlen].second;
        if(cntR[y] >= cnt) { OKlen++; }
        else { break; }
      }
    }
    else {
      while(NGlen-1 >= 0){
        int y = vec[NGlen-1].first;
        int cnt = vec[NGlen-1].second;
        if(x < y) { NGlen--; }
        else { break; }
      }
    }
    int LRlen = min(OKlen, NGlen);
    ans = max(ans, LRlen + CElen + LRlen);
    if(Rr - Rl + 1 == CElen + LRlen) {
      int LLr = Lr-LRlen;
      int RRl = Rr+1;
      if(LLr >= 0 && RRl < N) {
        int d = dp[LLr][RRl];
        ans = max(ans, d + LRlen + CElen + LRlen + d);
      }
    }
    Rr++;
  }
  return ans;
}

int solve2(int* S) {
  int ans=0;
  precalc(S);
  for(int i = 0; i < N; i++){
    int Lr = i, Rl = i;
    int d = dp[Lr][Rl];
    Lr -= d; Rl += d;
    ans = max(ans, (d*2-1)+solve(S, Lr, -1, Rl));
  }
  for(int i = 0; i+1 < N; i++){
    int Lr = i, Rl = i+1;
    int d = dp[Lr][Rl];
    Lr -= d; Rl += d;
    ans = max(ans, (d*2)+solve(S, Lr, -1, Rl));
  }
  for(int i = 0; i+1 < N; i++){
    int Lr = i, Rl = i+1;
    int center = -1;
    for(int j = Rl; j < N; j++){
      if(S[Lr] > S[j]) { center = S[j]; break; }
    }
    ans = max(ans, solve(S, Lr, center, Rl));
  }
  return ans;
}

int sort_them_all(int* S) {
  sort(S, S+N);
  int acc = 1;
  int ans = 0;
  for(int i = 1; i < N; i++){
    if(S[i - 1] == S[i]){ acc++; }
    else {
      ans = max(ans, acc); 
      acc = 1;
    }
  }
  ans = max(ans, acc); 
  return ans;
}

int main() {
  scanf("%d %d", &N, &C);
  for(int i = 0; i < N; i++){
    scanf("%d",str+i);
    str[i]--;
    rev[N-1-i]=C-1-str[i];
  }
  
  int ans = 0;
  ans = max(ans, solve2(str));
  ans = max(ans, solve2(rev));
  ans = max(ans, sort_them_all(str));
  printf("%d\n",ans);
}