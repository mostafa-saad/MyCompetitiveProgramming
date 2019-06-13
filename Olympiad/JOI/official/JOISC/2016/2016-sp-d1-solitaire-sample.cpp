#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<map>
using namespace std;

typedef long long Int;
typedef pair<Int, Int> P;
#define MOD 1000000007

Int dp[2006][6006][2];
Int c[4001][4001];
Int cnt[4001];
char board[3][2000];

vector<P> block;
void init(){
	for(Int i = 0;i < 4001;i++){
		for(Int j = 0;j <= i;j++){
			if(i == 0 || j == 0)c[i][j] = 1;
			else c[i][j] = c[i-1][j] + c[i-1][j-1];
			c[i][j] %= MOD;
		}
	}
}

void go(vector<Int> &vec){
	Int n = vec.size();
	if(n == 0)return;
	for(Int i = 0;i <= n;i++){
		for(Int j = 0;j <= 3 * (i+1);j++){
			dp[i][j][0] = dp[i][j][1] = 0;
		} 
	}

	vector<Int>sum = vec;
	for(Int i = 1;i < n;i++)sum[i] += sum[i-1];
	for(Int i = 0;i < n;i++){
		if(i == 0){
			if(vec[i] == 1){
				dp[0][1][1] = 1;
			}
			if(vec[i] == 2){                  
				dp[0][1][0] = 1;
				dp[0][2][1] = 1;
			}
			if(vec[i] == 3){                  
				dp[0][1][0] = 2;              
				dp[0][2][0] = 2;
				dp[0][3][1] = 2;
			}
			continue;
		}
		for(Int j = 1;j <= 3 * (i+1);j++){
			dp[i-1][j][1] += dp[i-1][j-1][1];
			dp[i-1][j][0] += dp[i-1][j-1][0];
		}
		if(vec[i] == 1){
			for(Int j = 1;j <= sum[i];j++){
				dp[i][j][1] += dp[i-1][sum[i-1]][1];
				dp[i][j][1] += dp[i-1][sum[i-1]][0] - dp[i-1][j-1][0];
				dp[i][j][1] %= MOD;
			}
		}
		
		
		if(vec[i] == 2){
			for(Int j = 1;j <= sum[i];j++){
//				dp[i][j][0] += dp[i-1][j-1][0] * (sum[i] - j);
				dp[i][j][0] += dp[i-1][j-1][1] * (sum[i] - j);
				dp[i][j][0] %= MOD;
				
				dp[i][j][1] += (dp[i-1][sum[i-1]][0] - dp[i-1][j-2][0]) * (j-1);
				dp[i][j][1] += dp[i-1][sum[i-1]][1] * (j-1);
				dp[i][j][1] %= MOD;
			}
		}
		
		
		if(vec[i] == 3){
			for(Int j = 1;j <= sum[i];j++){
//				dp[i][j][0] += dp[i-1][j-1][0] * (sum[i] - j) % MOD * (sum[i] - j - 1);
				dp[i][j][0] += dp[i-1][j-1][1] * (sum[i] - j) % MOD * (sum[i] - j - 1);
				dp[i][j][0] %= MOD;
				
				
//				if(j >= 2)dp[i][j][0] += dp[i-1][j-2][0] * (j-1) % MOD * (sum[i] - j) * 2;
				if(j >= 2)dp[i][j][0] += dp[i-1][j-2][1] * (j-1) % MOD * (sum[i] - j) * 2;
				dp[i][j][0] %= MOD;
				
				
				dp[i][j][1] += (dp[i-1][sum[i-1]][0] - dp[i-1][j-1][0]) * (j-1) % MOD * (j-2);
				dp[i][j][1] += dp[i-1][sum[i-1]][1] * (j-1) % MOD * (j-2);
				dp[i][j][1] %= MOD;
			}
		}
	}    
	
	Int res = 0;
	for(Int i = 1;i <= sum[n-1];i++){
		res += dp[n-1][i][0];
		res += dp[n-1][i][1];
		res %= MOD;
	}
	block.push_back(P(res, sum[n-1]));
}





int main(){
	init();
	Int black = 0;
	Int n;
	cin >> n;

	for(Int i = 0;i < 3;i++){
		for(Int j = 0;j < n;j++){
			cin >> board[i][j];
			if(board[i][j] == 'x')cnt[j]++, black++;
			if(board[i][j] != 'o' && board[i][j] != 'x' ){
//				cerr << "oxoxo" << endl;
//				exit(10);
			}
		}
	}
	if(board[0][0] == 'x' || board[2][0] == 'x' || board[0][n-1] == 'x' || board[2][n-1] == 'x'){
		cout << 0 << endl;
		return 0;
	}

	for(Int i = 0;i < n;i++){
		if(i == 0)continue;
		if(board[0][i-1] == 'x' && board[0][i] == 'x'){
			cout << 0 << endl;
			return 0;
		}
		if(board[2][i-1] == 'x' && board[2][i] == 'x'){
			cout << 0 << endl;
			return 0;
		}
	}	

	vector<Int> tmp;
	for(Int i = 0;i < n;i++){
		if(board[1][i] == 'o'){
			go(tmp);
			tmp.clear();
			if(board[0][i] == 'x')block.push_back(P(1, 1));
			if(board[2][i] == 'x')block.push_back(P(1, 1));
		}
		else{
			tmp.push_back(cnt[i]);
		}
	}
	go(tmp);
	
	Int res = 1;
	
	for(Int i = 0;i < block.size();i++){
		Int a = block[i].first;
		Int b = block[i].second;
		res *= a;res %= MOD;
		res *= c[black][b];res %= MOD;
		black -= b;
	}
	
	if(black != 0)cout << "PYA" << endl;
	res %= MOD;
	if(res < 0)res += MOD;
	cout << res << endl;
	return 0;
}
