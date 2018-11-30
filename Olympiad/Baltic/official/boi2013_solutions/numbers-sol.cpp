#define ll long long
ll dp[10][10][20][2];
string str;

// all : all digits are allowed
ll Calc(int first, int second, int len, bool all){
	if(len>=str.length()){
		return 1;
	}else{
		if(dp[first][second][len][all]==-1){
			ll help= 0;
			
			if(all){
				for(int n=0;n<=9;n++){
					if(n!=first && n!=second){
						help+=Calc(second,n, len+1, true);
					}
				}
			}else{
				int limit = str[len]-'0';
				for(int n=0;n<limit;n++){
					if(n!=first && n!=second){
						help+=Calc(second, n, len+1,true);
					}
				}
				if(limit!=first && limit!=second){
					help+=Calc(second, limit, len+1,false);
				}
			}
			dp[first][second][len][all]=help;
		}
		return dp[first][second][len][all];
	}
}

ll Get(ll num){
		if(num<0) return 0;
		
		stringstream ss; ss << num; str = ss.str();
		
		memset(dp,-1,sizeof(dp));
		
		int first = str[0]-'0';
		ll res =1;
			
		for(int n=1;n<=first;n++){
			res+=Calc(n,n,1,n!=first);
		}
		
		for(int k=2;k<=str.length();k++){
			for(int n=1;n<10;n++){
				res+=Calc(n,n,k,true);
			}
		}
		
		return res;
}
int main(){
	ll a,b;
	scanf("%lld %lld",&a,&b);
	ll counter = Get(b)-Get(a-1);
	printf("%lld\n",counter);
}
