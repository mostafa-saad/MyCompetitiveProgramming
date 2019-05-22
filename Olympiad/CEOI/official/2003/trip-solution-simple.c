#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b))?(a):(b)

char s1[85], s2[85];
int a[81][81];

char sol[2][81][1000][81];
int nsol[2][81];

int main () {
	int i,j,l1,l2,k;
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
	gets(s1);
	gets(s2);
	l1 = strlen(s1);
	l2 = strlen(s2);
	for (i=0; i<=l1; i++)
		for (j=0; j<=l2; j++)
			if (i == 0 || j == 0) {
				a[i][j] = 0;
				nsol[i&1][j] = 1;
				sol[i&1][j][0][0] = 0;
			}
		else {
			nsol[i&1][j] = 0;
			if (s1[i-1] == s2[j-1]) {
				a[i][j] = a[i-1][j-1]+1;
				for (k=0; k<nsol[!(i&1)][j-1]; k++) {
					strcpy(sol[i&1][j][k],sol[!(i&1)][j-1][k]);
					sol[i&1][j][k][a[i][j]-1] = s1[i-1];
					sol[i&1][j][k][a[i][j]] = 0;
				}
				nsol[i&1][j] = k;
			}
			else {
				a[i][j] = max(a[i-1][j],a[i][j-1]);
				if (a[i][j] == a[i-1][j]) {
					for (k=0; k<nsol[!(i&1)][j]; k++)
						strcpy(sol[i&1][j][k],sol[!(i&1)][j][k]);
					nsol[i&1][j] = k;
				}
				if (a[i][j] == a[i][j-1]) {
					int l,nl = nsol[i&1][j];
					for (k=0; k<nsol[i&1][j-1]; k++) {
						for (l=0; l<nsol[i&1][j]; l++)
							if (!strcmp(sol[i&1][j][l],sol[i&1][j-1][k]))
								break;
						if (l == nsol[i&1][j])
							strcpy(sol[i&1][j][nl++],sol[i&1][j-1][k]);
					}
					nsol[i&1][j] = nl;
				}
			}
		}
	i = l1 % 2;
	for (j = 0; j<nsol[i][l2]; j++)
		printf("%s\n",sol[i][l2][j]);
	return 0;
}

