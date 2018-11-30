#include <cstdio>
#include <iostream>
using namespace std;

#define MAXN 600

int a[MAXN+2][MAXN+2]; // given grid
int x[MAXN+2][MAXN+2]; // mine grid: 0 = no mine, 1 = mine

int r; // number of rows
int c; // number of columns

// this function rotates both grids by 90 degrees
void rotate()
{
	for (int i = 0; i <= min(r, c) + 1; i++)
	{
		for (int j = i + 1; j <= max(r, c) + 1; j++)
		{
			int tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;

			tmp = x[i][j];
			x[i][j] = x[j][i];
			x[j][i] = tmp;
		}
	}

	int tmp = r;
	r = c;
	c = tmp;
}


int b[MAXN+1];

// this function fills the entire given row, starting from position "start".
// it uses global array b
void completerow(int row, int start)
{
	// fill from start to the right end

	for (int i = start + 1; i < c; i++)
	{
		// analyse three consecutive cells x[row][i-1], x[row][i], x[row][i+1].
		// two of them are known. find the third one.
		if (x[row][i-1] == -1)
		{
			x[row][i-1] = b[i] - x[row][i] - x[row][i+1];
		}
		else if (x[row][i] == -1)
		{
			x[row][i] = b[i] - x[row][i-1] - x[row][i+1];
		}
		else
		{
			x[row][i+1] = b[i] - x[row][i-1] - x[row][i];
		}
	}

	// now fill from start to the left end (going backwards)

	for (int i = start; i >= 1; i--)
	{
		// analyse three consecutive cells x[row][i-1], x[row][i], x[row][i+1].
		// two of them are known. find the third one.
		if (x[row][i-1] == -1)
		{
			x[row][i-1] = b[i] - x[row][i] - x[row][i+1];
		}
		else if (x[row][i] == -1)
		{
			x[row][i] = b[i] - x[row][i-1] - x[row][i+1];
		}
		else
		{
			x[row][i+1] = b[i] - x[row][i-1] - x[row][i];
		}
	}
}


void fillrow(int r0, int r1, int r2, int r3)
{
	// create one line (array b) with dimensions 1 by c

	if (r0 == -1)
	{
		// in this case we know that r3 is 1 or 2 - the row we want to fill
		for (int i = 1; i <= c; i++)
		{
			b[i] = a[1][i] - x[3-r3][i-1] - x[3-r3][i] - x[3-r3][i+1];
		}
	}
	else
	{
		for (int i = 1; i <= c; i++)
		{
			b[i] = a[r2][i] + x[r0][i-1] + x[r0][i] + x[r0][i+1] - a[r1][i];
		}
	}

	// fill x[r3][3], x[r3][6], x[r3][9]...

	for (int i = 3; i <= c; i += 3)
	{
		x[r3][i] = b[i-1] + x[r3][i-3] - b[i-2];
	}

	if (c % 3 != 2)
	{
		// fill x[r3][c-2], x[r3][c-5], x[r3][c-8], ...
		
		for (int i = c - 2; i >= 1; i -= 3)
		{
			x[r3][i] = b[i+1] + x[r3][i+3] - b[i+2];
		}

		// fill entire row
		completerow(r3, 1);
	}
	else
	{
		// find two v-cells whose sum is 0 or 2
		// v cells are those with indices 1, 2, 4, 5, ..., i.e., vv.vv.vv.vv
		int i = 2;
		bool found = false;

		while (i <= c && !found)
		{
			int known = (i % 3 == 0 ? i : (i % 3 == 1 ? i - 1 : i + 1));
			int v = b[i] - x[r3][known];

			if (v != 1)
			{
				for (int j = i-1; j <= i+1; j++)
				{
					if (j != known)
					{
						x[r3][j] = v / 2;
					}
				}

				found = true;
			}
			else
			{
				i++;
			}
		}

		if (found)
		{
			completerow(r3, i-1);
		}
		else
		{
			// all pairs of v-cells have the sum 1. in this case we can use either
			// the pattern 01.01.01.01 or the pattern 10.10.10.10.
			// in this solution we use the 01.01.01.01.
			x[r3][1] = 0;
			completerow(r3, 1);
		}
	}
}


int main()
{
	freopen("mines.in", "r", stdin);
	freopen("mines.out", "w", stdout);

	memset(x, 0, sizeof(x));

	scanf("%d %d\n", &r, &c);

	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			char ch;
			scanf("%c", &ch);
			a[i][j] = ch - '0';
			x[i][j] = -1;
		}

		scanf("\n");
	}

	if (r % 3 == 2 && c % 3 == 2)
	{
		printf("cannot solve such case!\n");
		return 1;
	}

	bool rotated = false;

	if (r % 3 == 2)
	{
		rotate();
		rotated = true;
	}

	// now we can assume that r % 3 != 2

	// fill rows 3, 6, 9, ...

	int cur = 3;

	while (cur <= r)
	{
		fillrow(cur-3, cur-2, cur-1, cur);
		cur += 3;
	}

	// fill rows r-2, r-5, r-8, ...

	cur = r - 2;

	while (cur >= 1)
	{
		fillrow(cur+3, cur+2, cur+1, cur);
		cur -= 3;
	}

	if (r % 3 == 0)
	{
		cur = 2;
	}
	else
	{
		cur = 1;
	}

	// fill row "cur": a special case
	fillrow(-1, -1, -1, cur);

	cur += 3;

	// fill rows 5, 8, 11, ... or 4, 7, 10, ...

	while (cur <= r)
	{
		fillrow(cur-3, cur-2, cur-1, cur);
		cur += 3;
	}

	// rotate back

	if (rotated)
	{
		rotate();
	}

	// output answer

	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			printf("%c", x[i][j] == 0 ? '.' : 'X');
		}

		printf("\n");
	}

	return 0;
}
