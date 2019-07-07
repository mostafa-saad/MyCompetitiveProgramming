#include <bits/stdc++.h>
using namespace std;
#define Foreach(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c) for(auto &(i) : (c))
#define x first
#define y second
#define pb push_back
#define PB pop_back()
#define iOS ios_base::sync_with_stdio(false)
#define sqr(a) (((a) * (a)))
#define all(a) a.begin() , a.end()
#define error(x) cerr << #x << " = " << (x) <<endl
#define Error(a,b) cerr<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) ((x)<<1)
#define R(x) (((x)<<1)+1)
#define umap unordered_map
#define double long double
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex<double> point;
template <class T>  inline void smax(T &x,T y){ x = max((x), (y));}
template <class T>  inline void smin(T &x,T y){ x = min((x), (y));}
const int maxn = 21;
bool mat[maxn][maxn][maxn * maxn], row[maxn * maxn][maxn * maxn], col[maxn * maxn][maxn * maxn];
int a[maxn][maxn][maxn][maxn], n;
int cnt = 0, cnt0;
inline void put(int x, int y, int i, int j, int val){
	if(~a[x][y][i][j] or mat[x][y][val] or row[x * n + i][val] or col[y * n + j][val]){
		return ;
	}
	mat[x][y][val] = row[x * n + i][val] = col[y * n + j][val] = true;
	a[x][y][i][j] = val;
	++ cnt;
}

typedef pair<pii, pii> cell;
vector<cell> cs;
int main(){
	memset(a, -1, sizeof a);
	iOS;
	cin >> n;
	For(x,0,n)
		For(i,0,n)
			For(y,0,n)
				For(j,0,n){
					int q;
					cin >> q;
					-- q;
					if(~q)
						put(x, y, i, j, q);
					else
						cs.pb({{x, y}, {i, j}});
				}
	random_shuffle(all(cs));
	cnt0 = cnt;
	rep(cl, cs){
		int x = cl.x.x, y = cl.x.y, X = cl.y.x, Y = cl.y.y;
		vi is = vi();
		For(i,0,n*n)
			is.pb(i);
		random_shuffle(all(is));
		rep(i,is)
			put(x, y, X, Y, i);
	}

	For(x,0,n)
		For(i,0,n)
			For(y,0,n)
				For(j,0,n)
					cout << ++ a[x][y][i][j] << " \n"[y + 1 == n && j + 1 == n];
}
