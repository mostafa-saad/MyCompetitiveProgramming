#include<cstdio>
using namespace std;

char a[505][505];
int sol[5];

int main()
{
	int m, n; scanf("%d%d", &m, &n);
	for(int i=0; i<5*m+1; i++) scanf("%s", a[i]);
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
		{
			int x = 1 + 5*i;
			int y = 1 + 5*j;
			int k = 0;
			for(int l=0; l<4; l++)
				k += (a[x+l][y] == '*');
			sol[k]++;
		}
	for(int i=0; i<5; i++)
        printf("%d%c", sol[i], i==4?'\n':' ');
}
