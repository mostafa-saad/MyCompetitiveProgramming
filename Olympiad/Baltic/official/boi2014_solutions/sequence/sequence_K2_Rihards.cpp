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
		long long pow = 10;
		int addition = 1;
		long long numb, numb2;
		bool first;
		int was;

		while (pow < length)
		{
			pow *= 10;
			addition++;
		}

		for (int j = 0; j < pow; j++)
		{
			numb = j;

			for (int k = depth; k < depth + addition; k++)
			{
				atb[k] = numb % 10;
				numb /= 10;
			}

			numb = j;
			newLength = 0;
			newNeedZero = false;
			first = true;

			for (int k = 0; k < 10; k++)
			{
				mas[newLength][k][depth+addition] = 0;
			}

			//

			for (int i = 0; i < length; i++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (mas[i][k][depth])
					{
						numb2 = numb;
						was = -1;

						for (int p = 0; p < addition; p++)
						{
							if (k == numb2 % 10)
							{
								was = p;
							}

							numb2 /= 10;
						}

						if (was == addition-1 && first && k == 0)
						{
							newNeedZero = true;
						}
					
						if (was < 0)
						{
							mas[newLength][k][depth+addition] = 1;
						}
					}
				}

				numb = (numb + 1) % pow;

				if (numb == 0 && i < length -1)
				{
					first = false;
					newLength++;

					for (int k = 0; k < 10; k++)
					{
						mas[newLength][k][depth+addition] = 0;
					}
				}
			}

			rek(depth+addition,newLength+1, newNeedZero);
		}
	}
}

long long recreate_sequence(int K, int B[])
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

int main()
{
	scanf("%d", &K);

	for (int i = 0; i < K; i++)
	{
		scanf("%d", &B[i]);
	}

	cout << recreate_sequence(K, B) << endl;

	return 0;
}
