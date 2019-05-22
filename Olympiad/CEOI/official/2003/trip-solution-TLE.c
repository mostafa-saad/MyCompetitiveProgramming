#include <stdio.h>
#include <string.h>
#define max(x,y) ((x>y)?(x):(y))

int dp[81][81];
char s1[81],s2[81];

char out[1000][81],act[81];
int nsol,l1,l2;

void backtrack(int i, int j, int pos) {
	if (s1[i] == s2[j]) {
		act[pos++] = s1[i];
		if (pos<dp[0][0])
			backtrack(i+1,j+1,pos);
		else {
			act[pos] = 0;
			for (i=0; i<nsol; i++)
				if (!strcmp(out[i],act))
					break;
			if (i == nsol)
				strcpy(out[nsol++],act);
		}
	}
	else {
		if (dp[i][j] == dp[i+1][j])
			backtrack(i+1,j,pos);
		if (dp[i][j] == dp[i][j+1])
			backtrack(i,j+1,pos);
	}
}

int main() {
	int i,j;
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
	gets(s1);
	gets(s2);
	l1 = strlen(s1);
	l2 = strlen(s2);
	for (i=0; i<=l1; i++)
		dp[i][l2] = 0;
	for (j=0; j<=l2; j++)
		dp[l1][j] = 0;
	for (i=l1-1; i>=0; --i)
		for (j=l2-1; j>=0; --j) {
			if (s1[i] == s2[j])
				dp[i][j] = dp[i+1][j+1]+1;
			else
				dp[i][j] = max(dp[i][j+1],dp[i+1][j]);
		}
	nsol = 0;
	backtrack(0,0,0);
	for (i=0; i<nsol; i++)
		printf("%s\n",out[i]);
	return 0;
}
