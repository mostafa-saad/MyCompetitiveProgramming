#include <bits/stdc++.h>

#define FOR(i, a, b) for (int (i) = (a); (i) < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cerr << #x << " " << x << endl
#define eb emplace_back
using namespace std;

const int MaxN = 1000100;

//everything is 1-indexed

int N;
int perm[MaxN];
vector <int> radii[2 * MaxN]; // center and radius are doubled
int prefFixedPoints[MaxN];


void findSegmentBounds(const int center, const int radius, int& left, int& right){
	left = (center - radius) / 2; 
	right = (center + radius) / 2;
}

int fixedPointsInSegment(int a, int b){ // [a, b]
	return prefFixedPoints[b] - prefFixedPoints[a - 1];
}

void precomputePrefFixedPoints(){
	for (int i = 1; i <= N; i++)
		prefFixedPoints[i] = prefFixedPoints[i - 1] + ( perm[i] == i );
}

void findCenters(){
	for (int i = 1; i <= N; i++)
			radii[perm[i] + i].emplace_back(abs(perm[i] - i));

	for (int center = 2; center <= N + N; center++){ // all possible centers
		sort(radii[center].begin(), radii[center].end()); // the log in the complexity may be evaded by smart insertion
	}
}

void findBestFlip(){
	int targetMax = -MaxN, targetLeft = -1, targetRight = -1; 
	for (int center = 2; center <= N + N; center++){
		int numOfCreatedFixedPoints = 0;
		for (auto radius: radii[center]){
			numOfCreatedFixedPoints++;
			
			int left, right;
			findSegmentBounds(center, radius, left, right);
			
			int numOfLostFixedPoints = fixedPointsInSegment(left, right);	// the center as the fixed point is counted both as a lost and created
			int res = numOfCreatedFixedPoints - numOfLostFixedPoints; // so the net gain from it is zero 

			if (targetMax < res){
				targetMax = res;
				targetLeft = left;
				targetRight = right;
			}
		}
	}

	printf("%d %d\n", perm[targetLeft], perm[targetRight]);
}

void load(){
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", perm + i);
}

int main(){
	load();
	precomputePrefFixedPoints();
	findCenters();
	findBestFlip();	
	return 0;
}
