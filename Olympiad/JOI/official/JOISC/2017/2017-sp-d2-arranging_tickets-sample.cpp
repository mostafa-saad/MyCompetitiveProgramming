#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX_N = 200000;
const int MAX_M = 100000;

typedef pair<int, int> P;

struct Segtree{
	int N;
	long long dat[524288];
	bool flg[524288];
	void init(int N_){
		N = 1;
		while(N < N_) N *= 2;
		for(int i = 1; i < N * 2; ++i){
			dat[i] = 0;
			flg[i] = true;
		}
	}
	void add(int i, long long x){
		i += N;
		int tmp = i;
		int j = -1;
		while(tmp > 0){
			if(flg[tmp]) j = tmp;
			tmp /= 2;
		}
		if(j != -1){
			tmp = i;
			while(tmp > j){
				flg[tmp] = true;
				flg[tmp ^ 1] = true;
				dat[tmp] = 0;
				dat[tmp ^ 1] = 0;
				tmp /= 2;
			}
		}
		while(i > 0){
			flg[i] = false;
			dat[i] += x;
			i /= 2;
		}
	}
	long long getAll(){
		return dat[1];
	}
	void setZero(long long x, int i){
		if(i >= N){
			dat[i] -= x;
		}else{
			long long ri = dat[i * 2 + 1];
			if(x <= ri){
				setZero(x, i * 2 + 1);
			}else{
				dat[i * 2 + 1] = 0;
				flg[i * 2 + 1] = true;
				setZero(x - ri, i * 2);
			}
			dat[i] = dat[i * 2] + dat[i * 2 + 1];
		}
	}
	void setZero(long long x){
		setZero(x, 1);
	}
	
	void restore(int i){
		if(i >= N){
			if(flg[i]) dat[i] = 0;
			return;
		}
		if(flg[i]){
			flg[i * 2] = true;
			flg[i * 2 + 1] = true;
		}
		restore(i * 2);
		restore(i * 2 + 1);
	}
	void restoreAll(){
		restore(1);
	}
	long long get(int i){
		return dat[i + N];
	}
};

Segtree seg;

int N, M;
int A[MAX_M], B[MAX_M], C[MAX_M];

long long sum[MAX_N];
int ml, mr;

long long tmp[MAX_N];

long long need[MAX_N]; // need to flip need[i] people which contain section i
long long added[MAX_N];

vector<P> vecs[MAX_N];

bool check(long long num, int t, long long m){
	// flip num people
	// all contain section t
	// result = m
	
	if(num > m) return false;
	
	for(int i = 0; i < N; ++i){
		vecs[i].clear();
		tmp[i] = 0;
		added[i] = 0;
	}
	seg.init(N);
	for(int i = 0; i < t; ++i){
		need[i] = (sum[i] + num - m + 1) / 2;
	}
	need[t] = num;
	
	for(int i = 0; i < M; ++i){
		if(A[i] <= t && B[i] > t){
			vecs[A[i]].push_back(P(B[i], C[i]));
			tmp[B[i]] += C[i];
		}
	}
	long long flipped = 0;
	for(int i = 0; i <= t; ++i){
		for(int j = 0; j < vecs[i].size(); ++j){
			int b = vecs[i][j].first;
			int c = vecs[i][j].second;
			seg.add(b, c);
		}
		if(flipped < need[i]){
			long long n = need[i] - flipped;
			if(seg.getAll() < n){
				return false;
			}
			seg.setZero(n);
			flipped = need[i];
		}
	}
	if(flipped != num) return false;
	
	seg.restoreAll();
	
	for(int i = t + 1; i < N; ++i){
		long long all = tmp[i];
		long long remained = seg.get(i);
		long long flipped = all - remained;
		added[t] -= flipped;
		added[i] += flipped * 2;
		added[N - 1] -= flipped;
	}
	
	for(int i = t + 1; i < N; ++i){
		added[i] += added[i - 1];
	}
	for(int i = t + 1; i < N; ++i){
		long long x = sum[i] + added[i];
		if(x > m) return false;
	}	
	return true;
}

bool checkAll(long long m){
	// result = m
	bool flg = check(sum[ml] - m, ml, m);
	if(flg) return true;
	flg = check(sum[ml] - (m - 1), ml, m);
	if(flg) return true;
	flg = check(sum[mr] - m, mr, m);
	if(flg) return true;
	flg = check(sum[mr] - (m - 1), mr, m);
	if(flg) return true;
	return false;
}

long long solve(){
	for(int i = 0; i < N; ++i){
		sum[i] = 0;
	}
	for(int i = 0; i < M; ++i){
		if(A[i] > B[i]) swap(A[i], B[i]);
		sum[A[i]] += C[i];
		sum[B[i]] -= C[i];
	}
	for(int i = 1; i < N; ++i){
		sum[i] += sum[i - 1];
	}
	long long ma = 0;
	for(int i = 0; i < N; ++i){
		if(ma < sum[i]) ma = sum[i];
	}
	ml = -1, mr = -1;
	for(int i = 0; i < N; ++i){
		if(ma == sum[i]){
			ml = i;
			break;
		}
	}
	for(int i = N - 1; i >= 0; --i){
		if(ma == sum[i]){
			mr = i;
			break;
		}
	}
	long long lb = 0, ub = ma;
	
	while(ub - lb > 1){
		long long mid = (ub + lb) / 2;
		bool flg = checkAll(mid);
		if(flg){
			ub = mid;
		}else{
			lb = mid;
		}
	}
	return ub;
}

void input(){
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; ++i){
		scanf("%d%d%d", A + i, B + i, C + i);
		A[i]--;
		B[i]--;
	}
}

int main(){
	input();
	long long ans = solve();
	printf("%lld\n", ans);
	return 0;
	
}
