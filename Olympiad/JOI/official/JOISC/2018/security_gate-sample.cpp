#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=int(a);i<int(b);i++)
#define REP(i,b) FOR(i,0,b)
#define ZERO(x) memset(x,0,sizeof(x))
using ll=long long;

const int mod=1000000007;
void add(int&a,int b){
	a+=b;
	if(a>=mod)a-=mod;
}
void sub(int&a,int b){
	a-=b;
	if(a<0)a+=mod;
}
void mult(int&a,int b){
	a=ll(a)*b%mod;
}

const int Nmax=310;
int n,org[Nmax];

namespace ValidWithoutFlip{
	int dp[Nmax][Nmax];
	int Calc(){
		ZERO(dp);
		dp[0][0]=1;
		REP(i,n){
			if(org[i]>=0)
				REP(j,n)add(dp[i+1][j+1],dp[i][j]);
			if(org[i]<=0)
				FOR(j,1,n+1)add(dp[i+1][j-1],dp[i][j]);
		}
		int ans=dp[n][0];
		return ans;
	}
}

namespace InvalidOneSide{
	int gx[Nmax/2][Nmax][2][Nmax];
	int gz[Nmax][Nmax][2][Nmax];
	int wf[Nmax][Nmax];
	int CalcGivenAX1(int a,int x){
		int res=0;
		for(int len=0;len+1<=n;len+=2)if(org[len]<=0){
			int p=gx[x][len][1][0];
			int q=wf[len+1][2*a-1];
			mult(p,q);
			add(res,p);
		}
		return res;
	}
	int CalcGivenAX2(int a,int x){
		int res=0;
		for(int len=0;len+1<=n;len+=2)if(org[len]<=0){
			int p=gx[x][len][1][0];
			int q=gz[a+x][len+1][1][2*a-1];
			mult(p,q);
			add(res,p);
		}
		return res;
	}
	int CalcGivenAX(int a,int x){
		if(a<=x){
			return CalcGivenAX1(a,x);
		}else{
			return CalcGivenAX2(a,x);
		}
	}
	void PreCalc(){
		ZERO(gx);
		REP(x,n/2){
			gx[x][0][x==0][0]=1;
			REP(i,n){
				if(org[i]>=0){
					REP(j,x)
						add(gx[x][i+1][j+1==x][j+1],gx[x][i][0][j]);
					REP(j,x)
						add(gx[x][i+1][1][j+1],gx[x][i][1][j]);
				}
				if(org[i]<=0){
					FOR(j,1,x+1)
						add(gx[x][i+1][0][j-1],gx[x][i][0][j]);
					FOR(j,1,x+1)
						add(gx[x][i+1][1][j-1],gx[x][i][1][j]);
				}
			}
		}
		ZERO(gz);
		REP(z,n){
			gz[z][n][z==0][0]=1;
			for(int i=n-1;i>=0;i--){
				if(org[i]<=0){
					REP(j,n)
						add(gz[z][i][0][j+1],gz[z][i+1][0][j]);
					if(z>0)
						add(gz[z][i][1][z],gz[z][i+1][0][z-1]);
					FOR(j,z,min(z*2,n))
						add(gz[z][i][1][j+1],gz[z][i+1][1][j]);
				}
				if(org[i]>=0){
					FOR(j,1,n)
						add(gz[z][i][0][j-1],gz[z][i+1][0][j]);
					add(gz[z][i][1][z],gz[z][i+1][0][z+1]);
					FOR(j,z+2,min(z*2+1,n))
						add(gz[z][i][1][j-1],gz[z][i+1][1][j]);
				}
			}
		}
		ZERO(wf);
		wf[n][0]=1;
		for(int i=n-1;i>=0;i--){
			if(org[i]<=0){
				REP(j,n)
					add(wf[i][j+1],wf[i+1][j]);
			}
			if(org[i]>=0){
				FOR(j,1,n)
					add(wf[i][j-1],wf[i+1][j]);
			}
		}
	}
	int Calc(){
		PreCalc();
		int res=0;
		FOR(a,1,n/2+1)REP(x,n/2-a+1)add(res,CalcGivenAX(a,x));
		return res;
	}
}

namespace InvalidBothSide{
	int gx[Nmax/2][Nmax][2][Nmax];
	int gz[Nmax/2][Nmax][3][Nmax*2];
	int CalcGivenAX(int a,int x){
		int res=0;
		for(int len=0;len+1<=n;len+=2)if(org[len]<=0){
			int p=gx[x][len][1][0];
			int q=gz[a+x][len+1][2][a*2-1+n];
			mult(p,q);
			add(res,p);
		}
		return res;
	}
	void PreCalc(bool inc){
		ZERO(gx);
		REP(x,n/2){
			gx[x][0][x==0][0]=1;
			REP(i,n){
				if(org[i]>=0){
					REP(j,x)
						add(gx[x][i+1][j+1==x][j+1],gx[x][i][0][j]);
					REP(j,x)
						add(gx[x][i+1][1][j+1],gx[x][i][1][j]);
				}
				if(org[i]<=0){
					FOR(j,1,x)
						add(gx[x][i+1][0][j-1],gx[x][i][0][j]);
					FOR(j,1,x+1)
						add(gx[x][i+1][1][j-1],gx[x][i][1][j]);
				}
			}
		}
		ZERO(gz);
		REP(z,n/2){
			gz[z][n][(z+inc)==0][0+n]=1;
			for(int i=n-1;i>=0;i--){
				if(org[i]<=0){
					REP(j,n)
						add(gz[z][i][j+1==z+inc][j+1+n],gz[z][i+1][0][j+n]);
					REP(j,n)
						add(gz[z][i][1][j+1+n],gz[z][i+1][1][j+n]);
					FOR(j,-n,min(z*2,n))
						add(gz[z][i][2][j+1+n],gz[z][i+1][2][j+n]);
				}
				if(org[i]>=0){
					FOR(j,1,n)
						add(gz[z][i][0][j-1+n],gz[z][i+1][0][j+n]);
					REP(j,n)
						add(gz[z][i][(j-1)==-1?2:1][j-1+n],gz[z][i+1][1][j+n]);
					FOR(j,-n+1,min(z*2+1,n))
						add(gz[z][i][2][j-1+n],gz[z][i+1][2][j+n]);
				}
			}
		}
	}
	int Calc(){
		int res=0;
		REP(_,2){
			PreCalc(_);
			FOR(a,-n/2+1,n/2)FOR(x,max(0,-a),n/2-abs(a)+1)add(res,CalcGivenAX(a,x));
			reverse(org,org+n);
			REP(i,n)org[i]*=-1;
		}
		return res;
	}
}

int Solve(){
	int ans=0;
	add(ans,ValidWithoutFlip::Calc());
	REP(_,2){
		add(ans,InvalidOneSide::Calc());
		reverse(org,org+n);
		REP(i,n)org[i]*=-1;
	}
	add(ans,InvalidBothSide::Calc());
	return ans;
}

int main(){
	cin>>n;
	string str;
	cin>>str;
	if(n%2==1){
		cout<<0<<endl;
		return 0;
	}
	REP(i,n){
		if(str[i]=='(')org[i]=1;
		if(str[i]==')')org[i]=-1;
	}
	cout<<Solve()<<endl;
}
