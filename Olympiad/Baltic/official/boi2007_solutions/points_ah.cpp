// Alexander Hullmann
#include <stdio.h>

#define FAST

long long M[6][6] = {
	1,1,1, 1,0,0,
	2,2,2, 0,1,0,
	1,1,1, 0,0,1,
	
	1,1,1, 0,0,0,
	2,2,2, 0,0,0,
	1,1,1, 0,0,0
};

long long vstart[6] = {
	0, 1, 0, 0, 2, 0
};

long long vend[6] = {
	1, 1, 1, 1, 0, 1
};
	
void multMatrixVector(long long pMatrix[6][6], long long pVector[6])
{
	long long result[6];
	
	for (int i = 0; i < 6; i++)
	{
		result[i] = 0;
		for (int j = 0; j < 6; j++)
			result[i] += pMatrix[i][j] * pVector[j];
		result[i] %= 1000000000LL;
	}
	
	for (int i = 0; i < 6; i++)
		pVector[i] = result[i];
}

void multMatrixMatrix(long long pMatrix[6][6], long long pMatrix2[6][6])
{
	long long result[6][6];
	
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < 6; k++)
				result[i][j] += pMatrix[i][k] * pMatrix2[k][j];
			result[i][j] %= 1000000000LL;
		}
		
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			pMatrix[i][j] = result[i][j];
}

long long multVectorVector(long long pVector1[6], long long pVector2[6])
{
	long long result = 0;
	
	for (int i = 0; i < 6; i++)
		result += pVector1[i] * pVector2[i];
	result %= 1000000000LL;
	
	return result;
}

void powerMatrix(long long pMatrix[6][6], int pExponent)
{
	long long copy[6][6];
	
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			copy[i][j] = pMatrix[i][j];
			pMatrix[i][j] = (i == j ? 1 : 0);
		}
		
	while (pExponent != 0)
	{
		if (pExponent & 1)
			multMatrixMatrix(pMatrix, copy);
		multMatrixMatrix(copy, copy);
		pExponent >>= 1;
	}
}

int main()
{
	int N;
	
	FILE* in = fopen("points.in", "r");
	fscanf(in, "%d", &N);
	fclose(in);

#ifdef FAST
	powerMatrix(M, N - 2);
	multMatrixVector(M, vstart);
#else
	for (int i = 0; i < N - 2; i++)
		multMatrixVector(M, vstart);
#endif
	
	FILE* out = fopen("points.out", "w");
	fprintf(out, "%lld\n", multVectorVector(vend, vstart));
	fclose(out);
	
	return 0;
}
