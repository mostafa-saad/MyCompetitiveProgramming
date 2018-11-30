#include "coprobber.h"
#include <algorithm>

using namespace std;

int width = 1, cop = 0;

int start(int N, bool A[MAX_N][MAX_N]) {
	// Find the top right corner of the grid
	while (count(A[width], A[width] + N, true) != 2)
		width++;
	width++;
	return 0;
}

int nextMove(int robber) {
	int copX = cop % width,
		copY = cop / width,
		robberX = robber % width,
		robberY = robber / width,
		absX = abs(robberX - copX),
		absY = abs(robberY - copY);
	if (absX > absY)
		return robberX < copX ? (--cop) : (++cop);
	else if (absX < absY)
		return robberY < copY ? (cop -= width) : (cop += width);
	else
		return cop;
}
