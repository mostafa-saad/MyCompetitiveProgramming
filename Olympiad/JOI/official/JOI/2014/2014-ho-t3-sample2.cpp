// O(N log^2 N) solution
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1000010;
typedef long long i64;

int N;
i64 A[MAXN];
i64 S[MAXN*4];

int find_next(int pos, i64 C)
{
	return upper_bound(S, S+(N*3), S[pos]+C-1) - S;
}

bool check(i64 C)
{
	for(int i=0;i<N;i++){
		int pos = i;
		pos = find_next(pos, C); if(pos > i+N) continue;
		pos = find_next(pos, C); if(pos > i+N) continue;
		pos = find_next(pos, C); if(pos > i+N) continue;
		return true;
	}

	return false;
}

int main()
{
	scanf("%d", &N);
	for(int i=1;i<=N;i++) scanf("%lld", A+i);
	S[0] = 0;
	for(int i=1;i<=N;i++) S[i] = S[i+N] = S[i+2*N] = A[i];
	for(int i=1;i<=3*N;i++) S[i] += S[i-1];

	i64 left=1, right=S[N]/3;
	while(left < right){
		i64 mid = (left+right+1)/2;

		if(check(mid)){
			left = mid;
		}else{
			right = mid-1;
		}
	}

	printf("%lld\n", left);

	return 0;
}
