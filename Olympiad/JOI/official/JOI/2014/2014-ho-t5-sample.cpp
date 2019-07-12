#include<cstdio>
#include<algorithm>
#include<set>
#include<vector>

using namespace std;
const int MAXN = 100020;

struct seg_tree
{
	static const int DEPTH = 19;
	static const int SIZE = 1<<DEPTH;

	int bit[1<<(DEPTH+1)];
	int renew[1<<(DEPTH+1)];

	seg_tree() { } 

	void init()
	{
		for(int i=0;i<2*SIZE;i++) bit[i] = renew[i] = 0;
	}

	void add(int p, int v)
	{
		p += SIZE;
		while(p){
			bit[p] += v;
			p >>= 1;
		}
	}

	int query(int l, int r)
	{
		l += SIZE;
		r += SIZE;
		int ret = 0;

		while(l < r){
			if(l&1) ret += bit[l++];
			if(r&1) ret += bit[--r];
			l >>= 1; r >>= 1;
		}

		return ret;
	}

	void set_renew(int l, int r)
	{
		l += SIZE;
		r += SIZE;

		while(l < r){
			if(l&1) renew[l++] = 1;
			if(r&1) renew[--r] = 1;
			l >>= 1; r >>= 1;
		}
	}

	bool is_renew(int p)
	{
		p += SIZE;
		while(p){
			if(renew[p]) return true;
			p >>= 1;
		}
		return false;
	}

	void unset_renew(int p)
	{
		p += SIZE;
		for(int i=DEPTH-1;i>0;i--){
			if(renew[p >> i]){
				renew[p >> i] = 0;
				renew[(p>>i)*2] = renew[(p>>i)*2+1] = 1;
			}
		}

		renew[p] = 0;
	}
};

struct action
{
	int pos, act, left, right;

	action(int p, int a, int l, int r)
	{
		pos = p; act = a; left = l; right = r;
	}
};

inline bool operator<(const action& a, const action& b)
{
	return a.pos < b.pos || (a.pos == b.pos && a.act < b.act);
}

int W, H, N;
int x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN];
vector<int> uf;
seg_tree seg;
int target[MAXN*2];

int root(int p)
{
	return (uf[p] < 0) ? p : (uf[p] = root(uf[p]));
}

bool join(int p, int q)
{
	p = root(p);
	q = root(q);

	if(p==q) return false;

	if(uf[p] < uf[q]) swap(p, q);
	uf[p] = uf[q];
	uf[q] = p;

	return true;
}

void adjust(int p)
{
	if(seg.is_renew(p)){
		uf.push_back(-1);
		seg.unset_renew(p);
		target[p] = uf.size() - 1;
	}

}

int main()
{
	scanf("%d%d%d", &W, &H, &N);
	for(int i=0;i<N;i++){
		scanf("%d%d%d%d", x1+i, y1+i, x2+i, y2+i);
		if(x1[i] > x2[i]) swap(x1[i], x2[i]);
		if(y1[i] > y2[i]) swap(y1[i], y2[i]);
	}
	for(int i=0;i<2*N;i++) target[i] = -1;

	x1[N  ] = 0; y1[N  ] = 0; x2[N  ] = W; y2[N  ] = 0;
	x1[N+1] = 0; y1[N+1] = 0; x2[N+1] = 0; y2[N+1] = H;
	x1[N+2] = W; y1[N+2] = 0; x2[N+2] = W; y2[N+2] = H;
	x1[N+3] = 0; y1[N+3] = H; x2[N+3] = W; y2[N+3] = H;
	N += 4;

	vector<int> xs;
	for(int i=0;i<N;i++){
		xs.push_back(x1[i]);
		xs.push_back(x2[i]);
	}
	xs.push_back(-1);
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());

	for(int i=0;i<N;i++){
		x1[i] = lower_bound(xs.begin(), xs.end(), x1[i]) - xs.begin();
		x2[i] = lower_bound(xs.begin(), xs.end(), x2[i]) - xs.begin();
	}

	set<int> S;
	S.insert(0);
	target[0] = 0;
	uf.push_back(-1);

	vector<action> A;

	for(int i=0;i<N;i++){
		if(x1[i] == x2[i]){
			A.push_back(action(y1[i], 0, x1[i], -1));
			A.push_back(action(y2[i], 2, x1[i], -1));
		}else{
			A.push_back(action(y1[i], 1, x1[i], x2[i]));
		}
	}

	sort(A.begin(), A.end());

	long long ret = 0;
	for(int i=0;i<A.size();i++){
		action V = A[i];

		if(V.act == 0){
			int lf = *--S.lower_bound(V.left);

			adjust(lf); adjust(V.left);
			target[V.left] = target[lf];

			S.insert(V.left);
			seg.add(V.left, 1);
		}else if(V.act == 1){
			int count = seg.query(V.left, V.right+1);
			if(count < 2) continue;
			ret += count - 1;

			seg.set_renew(V.left, *--S.upper_bound(V.right));
		}else if(V.act == 2){
			int lf = *--S.lower_bound(V.left);
			adjust(lf); adjust(V.left);
			if(join(target[lf], target[V.left])) --ret;

			S.erase(V.left);
			seg.add(V.left, -1);
		}
	}

	printf("%lld\n", ret);

	return 0;
}
