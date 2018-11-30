/*
TASK: CAMP
LANG: C++
*/

#include <fstream>
#include <iostream>
using namespace std;

#define inputFilename	"CAMP.IN"
#define outputFilename	"CAMP.OUT"

struct CHARACTERISTIC {
	// input data
	int r, c, l, w, arrange;
	int altitude;
	// for optimization
	int p0, p1, p2, p3;
	int o0, o1, o2, o3;
};

int rows, cols;
int *map;
int length, width, chars;

// precalculates optimized characteristic
void precalculateCharacteristic(CHARACTERISTIC &ch, int colsInSumMap)
{
	ch.p0 = (ch.r - 1) * colsInSumMap + (ch.c - 1);
	ch.p1 = ch.p0 + ch.w;
	ch.p2 = ch.p0 + ch.l * colsInSumMap;
	ch.p3 = ch.p2 + ch.w;
	if (1 == ch.arrange) {
		// vertical arrangement
		ch.o0 = ch.p2;
		ch.o1 = ch.p3;
		ch.o2 = ch.o0 + ch.l * colsInSumMap;
		ch.o3 = ch.o2 + ch.w;
	} else {
		// horizontal arrangement
		ch.o0 = ch.p1;
		ch.o1 = ch.o0 + ch.w;
		ch.o2 = ch.p3;
		ch.o3 = ch.o2 + ch.w;
	}
}

// creates map of sums
void CreateSumMap(int rows, int cols, int *map, int *sumMap)
{
	memset(sumMap, 0, sizeof(int) * (rows + 1) * (cols + 1));

	for (int i = 1; i < rows + 1; ++i) {
		int rowSum = 0;
		for (int ii = 1; ii < cols + 1; ++ii) {
			rowSum += map[(i - 1) * cols + (ii - 1)];
			sumMap[i * (cols + 1) + ii] = rowSum + sumMap[(i - 1) * (cols + 1) + ii];
		}
	}
}

// solves by checking almost all characteristics on every location
void solve(int *map, CHARACTERISTIC *ch, int &maxOK, int &bestRow, int &bestCol)
{
	// convert map to map of sums
	int *sumMap = new int[(rows + 1) * (cols + 1)];
	CreateSumMap(rows, cols, map, sumMap);

	// check every location
	for (int i = 0; i <= rows - length; ++i) {
		for (int ii = 0; ii <= cols - width; ++ii) {
			int countOK = 0;
			int *offset = sumMap + i * (cols + 1) + ii;

			// for every characteristics
			for (int j = chars - 1; j >= 0; --j) {
				int sum1 = offset[ch[j].p0] - offset[ch[j].p1] - offset[ch[j].p2] + offset[ch[j].p3];
				int sum2 = offset[ch[j].o0] - offset[ch[j].o1] - offset[ch[j].o2] + offset[ch[j].o3];

				if (0 == ch[j].altitude) {
					if (sum1 < sum2)
						++countOK;
				} else {
					if (sum1 >= sum2)
						++countOK;
				}

				//cout << sum1 - sum2 << "\t";
				if (countOK + j <= maxOK)
					break;
			}

			if (countOK > maxOK) {
				maxOK = countOK;
				bestRow = i + 1;
				bestCol = ii + 1;
			}

			//cout << "(" << countOK << ")\t\t";
			//cout << countOK << "\t";
		}

		//cout << endl;
	}
	delete[] sumMap;
}

int main()
{
	// read input
	ifstream inF(inputFilename);
	// read the map
	inF >> rows >> cols;
	map = new int[rows * cols];
	for (int i = 0; i < rows; ++i)
		for (int ii = 0; ii < cols; ++ii)
			inF >> map[i * cols + ii];
	// read the camp
	inF >> length >> width;
	inF >> chars;
	CHARACTERISTIC *ch = new CHARACTERISTIC[chars];
	for (int i = 0; i < chars; ++i)
	{
		// read every characteristic
		inF >> ch[i].r >> ch[i].c >> ch[i].l >> ch[i].w
			>> ch[i].arrange >> ch[i].altitude;
		precalculateCharacteristic(ch[i], cols + 1);
	}
	inF.close();

	// solve
	int maxOK = 0;
	int bestRow = 1, bestCol = 1;
	solve (map, ch, maxOK, bestRow, bestCol);

	delete[] ch;
	delete[] map;

	//cout << "  chars=" << maxOK << ", (row, col)=(" << bestRow << ", " << bestCol << ")\n";

	// write output
	ofstream outF(outputFilename);
	outF << bestRow << " " << bestCol/* << " " << maxOK*/ << endl;
	outF.close();

	return 0;
}
