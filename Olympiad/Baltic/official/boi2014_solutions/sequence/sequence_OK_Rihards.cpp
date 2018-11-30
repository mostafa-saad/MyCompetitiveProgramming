#include <iostream>
#include <cstdio>

using namespace std;

#define N 100000

int mas[N][10][9];

long long best = 102345678900000LL;

int atb[17];

int K;
int B[N];

void check(int gar)
{
	long long rez = 0;

	for (int i = gar; i >= 0; i--)
	{
		rez = rez * 10 + atb[i];
	}

	if (rez < best)
	{
		best = rez;
	}
}


void rek(int depth, int length, bool needFrontZero)
{
	int digit,newLength,newNeedZero;

	if (length == 1)
	{
		int dd = depth;
		
		for (int i = 9; i >= 1; i--)
		{
			if (mas[0][i][depth])
			{
				atb[dd] = i;
				dd++;
			}
		}

		if (mas[0][0][depth])
		{
			if (dd > depth)
			{
				atb[dd] = atb[dd-1];
				atb[dd-1] = 0;
				dd++;
			}
			else
			{
				atb[dd] = 0;
				atb[dd+1] = 1;
				dd += 2;
			}
		}

		if (dd == 0 || (depth == dd && needFrontZero))
		{
			atb[dd] = 1;
			dd++;
		}

		check(dd-1);
	}
	else if (length == 2)
	{
		for (int j = 0; j < 9; j++)
		{
			atb[depth] = j;

			digit = j;
			newLength = 0;
			newNeedZero = false;

			if (j == 0 && mas[0][0][depth] == 1)
			{
				newNeedZero = true;
			}

			for (int k = 0; k < 10; k++)
			{
				mas[newLength][k][depth+1] = 0;
			}

			for (int i = 0; i < length; i++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (mas[i][k][depth] && (k != digit))
					{
						mas[newLength][k][depth+1] = 1;
					}
				}

				digit = (digit + 1) % 10;
			}

			rek(depth+1, 1, newNeedZero);
		}
		
		// 9 - > 0

		atb[depth] = 9;


		for (int j = 0; j < 9; j++)
		{
			atb[depth+1] = j;

			digit = j;
			newLength = 0;
			newNeedZero = false;

			if (j == 0 && mas[0][0][depth] == 1)
			{
				newNeedZero = true;
			}

			for (int k = 0; k < 10; k++)
			{
				mas[newLength][k][depth+2] = 0;
			}

			for (int i = 0; i < length; i++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (mas[i][k][depth] && (k != digit) && (k != (9 + i) % 10))
					{
						mas[newLength][k][depth+2] = 1;
					}
				}

				digit = (digit + 1) % 10;
			}

			rek(depth+2, 1, newNeedZero);
		}
	}
	else
	{
		for (int j = 0; j < 10; j++)
		{
			atb[depth] = j;
		
			digit = j;
			newLength = 0;
			newNeedZero = false;

			if (j == 0 && mas[0][0][depth] == 1)
			{
				newNeedZero = true;
			}

			for (int k = 0; k < 10; k++)
			{
				mas[newLength][k][depth+1] = 0;
			}

			for (int i = 0; i < length; i++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (mas[i][k][depth] && (k != digit))
					{
						mas[newLength][k][depth+1] = 1;
					}
				}

				digit = (digit + 1) % 10;

				if (digit == 0 && i < length -1)
				{
					newLength++;

					for (int k = 0; k < 10; k++)
					{
						mas[newLength][k][depth+1] = 0;
					}
				}
			}

			rek(depth+1,newLength+1, newNeedZero);
		}
	}
}

long long recreate_sequence()
{
	best = 102345678900000LL;

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mas[i][j][0] = 0;
		}

		mas[i][B[i]][0] = 1;
	}

	rek(0,K,true);

	return best;
}

const int LENGTH = 6;
int ARRAY[LENGTH] = {7, 8, 9, 5, 1, 2};


int main()
{
	cin >> K;
	for (int i = 0; i < K; ++i)
		cin >> B[i];
	cout << recreate_sequence() << endl;

	return 0;
}
